// reference: https://github.com/chriscyh2000/NTU-Courses/tree/master/%5BCSIE2210%5DSystems%20Programming/Programming%20hw1
// discuss with b08902149 (The author of the github above), b08501098, b08502041

#include <unistd.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define ERR_EXIT(a) do { perror(a); exit(1); } while(0)

#define OBJ_NUM 3
#define STU_NUM 20  // number of students

#define FOOD_INDEX 0
#define CONCERT_INDEX 1
#define ELECS_INDEX 2
#define RECORD_PATH "./bookingRecord"

static char* obj_names[OBJ_NUM] = {"Food", "Concert", "Electronics"};

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;

typedef struct {
    char host[512];  // client's host
    int conn_fd;  // fd to talk with client
    char buf[512];  // data sent by/to client
    size_t buf_len;  // bytes used by buf
    int id;
    int wait_for_write;  // used by handle_read to know if the header is read or not.
} request;

server svr;  // server
request* requestP = NULL;  // point to a list of requests
int maxfd;  // size of open file descriptor table, size of request list

const char* accept_read_header = "ACCEPT_FROM_READ";
const char* accept_write_header = "ACCEPT_FROM_WRITE";
const unsigned char IAC_IP[3] = "\xff\xf4";

static void init_server(unsigned short port);
// initailize a server, exit for error

static void init_request(request* reqP);
// initailize a request instance

static void free_request(request* reqP);
// free resources used by a request instance

typedef struct {
    int id;          // 902001-902020
    int bookingState[OBJ_NUM]; // array of booking number of each object (0 or positive numbers)
} record;

int handle_read(request* reqP) {
    /*  Return value:
     *      1: read successfully
     *      0: read EOF (client down)
     *     -1: read failed
     */
    int r;
    char buf[512];

    // Read in request from client
    r = read(reqP->conn_fd, buf, sizeof(buf));
    if (r < 0)
        return -1;
    if (r == 0)
        return 0;
    char* p1 = strstr(buf, "\015\012");
    int newline_len = 2;
    if (p1 == NULL) {
       p1 = strstr(buf, "\012");
        if (p1 == NULL) {
            if (!strncmp(buf, IAC_IP, 2)) {
                // Client presses ctrl+C, regard as disconnection
                fprintf(stderr, "Client presses ctrl+C....\n");
                return 0;
            }
            ERR_EXIT("this really should not happen...");
        }
    }
    size_t len = p1 - buf + 1;
    memmove(reqP->buf, buf, len);
    reqP->buf[len - 1] = '\0';
    reqP->buf_len = len - 1;
    return 1;
}

int main(int argc, char** argv) {

    // Parse args.
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in cliaddr;  // used by accept()
    int clilen;

    int conn_fd;  // fd for a new connection with client
    int file_fd = open(RECORD_PATH, O_RDWR);  // fd for file that we open for reading
    char buf[512];
    int buf_len;

    // Initialize server
    init_server((unsigned short) atoi(argv[1]));

    // Loop for handling connections
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", svr.hostname, svr.port, svr.listen_fd, maxfd);

    bool to_close[maxfd];
    bool read_lock[STU_NUM] = {}, write_lock[STU_NUM] = {};

    struct pollfd fdarray[maxfd];
    fdarray[0].fd = svr.listen_fd;
    fdarray[0].events = POLLIN;

    int nfds = 1;
    int totalFds;

    while (1) {
        // TODO: Add IO multiplexing

        totalFds = poll(fdarray, nfds, -1);

        // Check new connection
        if (fdarray[0].revents & POLLIN){
            clilen = sizeof(cliaddr);
            conn_fd = accept(svr.listen_fd, (struct sockaddr*) &cliaddr, (socklen_t*) &clilen);
            if (conn_fd < 0) {
                if (errno == EINTR || errno == EAGAIN)
                    continue;  // try again
                else if (errno == ENFILE) {
                    (void) fprintf(stderr, "out of file descriptor table ... (maxconn %d)\n", maxfd);
                    continue;
                }
                ERR_EXIT("accept");
            }
            requestP[conn_fd].conn_fd = conn_fd;
            strcpy(requestP[conn_fd].host, inet_ntoa(cliaddr.sin_addr));
            fprintf(stderr, "getting a new request... fd %d from %s\n", conn_fd, requestP[conn_fd].host);

            requestP[conn_fd].wait_for_write = 0;
            fdarray[nfds].fd = conn_fd;
            fdarray[nfds].events = POLLOUT;
            to_close[nfds] = false;
            nfds++;
            sprintf(requestP[conn_fd].buf, "Please enter your id (to check your booking state):\n");
        }

        for (int i = 1; i < nfds; i++){
            if (fdarray[i].revents & POLLIN){
                fdarray[i].events = POLLOUT;
                int ret = handle_read(&requestP[fdarray[i].fd]); // parse data from client to requestP[conn_fd].buf
                fprintf(stderr, "ret = %d\n", ret);
                if (ret < 0) {
                    fprintf(stderr, "bad request from %s\n", requestP[conn_fd].host);
                    continue;
                }
// TODO: handle requests from clients
#ifdef READ_SERVER
                if (requestP[fdarray[i].fd].wait_for_write == 0){
                    int ID = atoi(requestP[fdarray[i].fd].buf) - 902001;
                    if (strlen(requestP[fdarray[i].fd].buf) == 6 && ID >= 0 && ID < STU_NUM){
                        struct flock lock;
                        lock.l_type = F_RDLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = ID * sizeof(record);
                        lock.l_len = sizeof(record);
                        if (fcntl(file_fd, F_SETLK, &lock) == -1 || write_lock[ID]){
                            sprintf(requestP[fdarray[i].fd].buf, "Locked.\n");
                            to_close[i] = true;
                        }
                        else{
                            read_lock[ID] = true;
                            requestP[fdarray[i].fd].id = ID;
                            record information;
                            lseek(file_fd, (ID * sizeof(record)), SEEK_SET);
                            read(file_fd, &information, sizeof(record));
                            sprintf(requestP[fdarray[i].fd].buf,
                                "Food: %d booked\nConcert: %d booked\nElectronics: %d booked\n\n(Type Exit to leave...)\n",
                                information.bookingState[FOOD_INDEX], information.bookingState[CONCERT_INDEX], information.bookingState[ELECS_INDEX]);
                            requestP[fdarray[i].fd].wait_for_write = 1;
                        }
                    }
                    else{
                        sprintf(requestP[fdarray[i].fd].buf, "[Error] Operation failed. Please try again.\n");
                        to_close[i] = true;
                    }
                }

                else if (requestP[fdarray[i].fd].wait_for_write == 1){
                    struct flock lock;
                    lock.l_type = F_UNLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = requestP[fdarray[i].fd].id * sizeof(record);
                    lock.l_len = sizeof(record);
                    fcntl(file_fd, F_SETLK, &lock);
                    read_lock[requestP[fdarray[i].fd].id] = false;
                    to_close[i] = true;
                    requestP[fdarray[i].fd].buf[0] = '\0';
                }

                /*fprintf(stderr, "%s", requestP[conn_fd].buf);
                sprintf(buf,"%s : %s",accept_read_header,requestP[conn_fd].buf);
                write(requestP[conn_fd].conn_fd, buf, strlen(buf));*/

#elif defined WRITE_SERVER
                if (requestP[fdarray[i].fd].wait_for_write == 0){
                    int ID = atoi(requestP[fdarray[i].fd].buf) - 902001;
                    if (strlen(requestP[fdarray[i].fd].buf) == 6 && ID >= 0 && ID < STU_NUM){
                        struct flock lock;
                        lock.l_type = F_WRLCK;
                        lock.l_whence = SEEK_SET;
                        lock.l_start = ID * sizeof(record);
                        lock.l_len = sizeof(record);
                        if (fcntl(file_fd, F_SETLK, &lock) == -1 || read_lock[ID] || write_lock[ID]){
                            sprintf(requestP[fdarray[i].fd].buf, "Locked.\n");
                            to_close[i] = true;
                        }
                        else{
                            write_lock[ID] = true;
                            requestP[fdarray[i].fd].id = ID;
                            record information;
                            lseek(file_fd, (ID * sizeof(record)), SEEK_SET);
                            read(file_fd, &information, sizeof(record));
                            sprintf(requestP[fdarray[i].fd].buf,
                                "Food: %d booked\nConcert: %d booked\nElectronics: %d booked\n\nPlease input your booking command. (Food, Concert, Electronics. Positive/negative value increases/decreases the booking amount.):\n",
                                information.bookingState[FOOD_INDEX], information.bookingState[CONCERT_INDEX], information.bookingState[ELECS_INDEX]);
                            requestP[fdarray[i].fd].wait_for_write = 1;
                        }
                    }
                    else{
                        sprintf(requestP[fdarray[i].fd].buf, "[Error] Operation failed. Please try again.\n");
                        to_close[i] = true;
                    }
                }

                else if (requestP[fdarray[i].fd].wait_for_write == 1){
                    record information;
                    lseek(file_fd, (requestP[fdarray[i].fd].id * sizeof(record)), SEEK_SET);
                    read(file_fd, &information, sizeof(record));
                    int obj_idx;
                    int num[3];
                    for (obj_idx = 0; obj_idx < OBJ_NUM; obj_idx++)
                        num[obj_idx] = information.bookingState[obj_idx];
                    obj_idx = 0;
                    int str_idx = 0;
                    int temp = 0;
                    bool minus = false;
                    bool first = true;
                    bool num_found = false;
                    bool input_valid = true;
                    int len = strlen(requestP[fdarray[i].fd].buf);
                    int num_write[3];
                    while (str_idx < len && input_valid){
                        if (requestP[fdarray[i].fd].buf[str_idx] >= '0' && requestP[fdarray[i].fd].buf[str_idx] <= '9'){
                            temp = 10 * temp + (requestP[fdarray[i].fd].buf[str_idx] - '0');
                            first = false;
                            num_found = true;
                        }

                        else if (requestP[fdarray[i].fd].buf[str_idx] == '-'){
                            if (first)
                                minus = true;
                            else
                                input_valid = false;
                            first = false;
                        }

                        else if (requestP[fdarray[i].fd].buf[str_idx] == ' '){
                            if (minus && !num_found){
                                input_valid = false;
                                continue;
                            }
                            else if (minus)
                                temp *= -1;
                            num_write[obj_idx] = temp;
                            temp = 0;
                            minus = false;
                            first = true;
                            num_found = false;
                            obj_idx++;
                        }

                        else{
                            input_valid = false;
                            first = false;
                        }
                        str_idx++;
                    }

                    if (input_valid){
                        if (minus)
                            temp *= -1;
                        num_write[obj_idx] = temp;

                        bool num_valid = true;
                        int sum = 0;
                        for (obj_idx = 0; obj_idx < OBJ_NUM; obj_idx++){
                            sum += (num[obj_idx] + num_write[obj_idx]);
                            if (num[obj_idx] + num_write[obj_idx] < 0)
                                num_valid = false;
                        }

                        if (num_valid){
                            if (sum > 15)
                                sprintf(requestP[fdarray[i].fd].buf, "[Error] Sorry, but you cannot book more than 15 items in total.\n");

                            else{
                                for (obj_idx = 0; obj_idx < OBJ_NUM; obj_idx++)
                                    information.bookingState[obj_idx] = num[obj_idx] + num_write[obj_idx];
                                lseek(file_fd, (requestP[fdarray[i].fd].id * sizeof(record)), SEEK_SET);
                                write(file_fd, &information, sizeof(record));
                                sprintf(requestP[fdarray[i].fd].buf, "Bookings for user 9020%02d are updated, the new booking state is:\nFood: %d booked\nConcert: %d booked\nElectronics: %d booked\n",
                                    (requestP[fdarray[i].fd].id + 1), information.bookingState[FOOD_INDEX], information.bookingState[CONCERT_INDEX], information.bookingState[ELECS_INDEX]);
                            }
                        }

                        else
                            sprintf(requestP[fdarray[i].fd].buf, "[Error] Sorry, but you cannot book less than 0 items.\n");
                    }

                    else
                        sprintf(requestP[fdarray[i].fd].buf, "[Error] Operation failed. Please try again.\n");

                    struct flock lock;
                    lock.l_type = F_UNLCK;
                    lock.l_whence = SEEK_SET;
                    lock.l_start = requestP[fdarray[i].fd].id * sizeof(record);
                    lock.l_len = sizeof(record);
                    fcntl(file_fd, F_SETLK, &lock);
                    write_lock[requestP[fdarray[i].fd].id] = false;
                    to_close[i] = true;
                }

                /*fprintf(stderr, "%s", requestP[conn_fd].buf);
                sprintf(buf,"%s : %s",accept_write_header,requestP[conn_fd].buf);
                write(requestP[conn_fd].conn_fd, buf, strlen(buf));*/
#endif
            }

            else if (fdarray[i].revents & POLLOUT){
                fdarray[i].events = POLLIN;
                write(fdarray[i].fd, requestP[fdarray[i].fd].buf, strlen(requestP[fdarray[i].fd].buf));
                if (to_close[i]){
                    close(fdarray[i].fd);
                    free_request(&requestP[fdarray[i].fd]);
                    fdarray[i] = fdarray[nfds - 1];
                    to_close[i] = to_close[nfds - 1];
                    nfds--;
                    i--;
                }
            }
        }
    }
    close(file_fd);
    free(requestP);
    return 0;
}

// ======================================================================================================
// You don't need to know how the following codes are working
#include <fcntl.h>

static void init_request(request* reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
    reqP->id = 0;
}

static void free_request(request* reqP) {
    /*if (reqP->filename != NULL) {
        free(reqP->filename);
        reqP->filename = NULL;
    }*/
    init_request(reqP);
}

static void init_server(unsigned short port) {
    struct sockaddr_in servaddr;
    int tmp;

    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;

    svr.listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (svr.listen_fd < 0)
        ERR_EXIT("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    tmp = 1;
    if (setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&tmp, sizeof(tmp)) < 0)
        ERR_EXIT("setsockopt");
    if (bind(svr.listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind");
    if (listen(svr.listen_fd, 1024) < 0)
        ERR_EXIT("listen");

    // Get file descripter table size and initialize request table
    maxfd = getdtablesize();
    requestP = (request*) malloc(sizeof(request) * maxfd);
    if (requestP == NULL)
        ERR_EXIT("out of memory allocating all requests");
    for (int i = 0; i < maxfd; i++)
        init_request(&requestP[i]);
    requestP[svr.listen_fd].conn_fd = svr.listen_fd;
    strcpy(requestP[svr.listen_fd].host, svr.hostname);
}
