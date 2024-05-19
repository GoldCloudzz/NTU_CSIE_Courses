#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

int dir_num = 0, file_num = 0;
int level = 0;

void traverse(char* path, char key, int pre_count){
    int fd, count;
    char buf[512], *p, *cur;
    struct stat st;
    struct dirent de;

    if ((fd = open(path, 0)) < 0){
        fprintf(2, "%s [error opening dir]\n", path);
        return;
    }

    if (fstat(fd, &st) < 0){
        fprintf(2, "%s [error opening dir]\n", path);
        close(fd);
        return;
    }
    
    if (level == 0){
        if (st.type == T_FILE){
            fprintf(2, "%s [error opening dir]\n", path);
            close(fd);
            return;
        }
        else{
            pre_count = 0;
            cur = path;
            while (*cur != 0){
                if (*cur == key)
                    pre_count++;
                cur++;
            }
            printf("%s %d\n", path, pre_count);
        }
    }

    if (st.type == T_FILE){
        file_num++;
    }
    else if (st.type == T_DIR){
        if (level > 0)
            dir_num++;
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)){
            if (de.inum == 0)
                continue;
            strcpy(p, de.name);
            if (strcmp(".", p) == 0 || strcmp("..", p) == 0)
                continue;
            count = pre_count;
            cur = p;
            while (*cur != '\0'){
                if (*cur == key)
                    count++;
                cur++;
            }
            printf("%s %d\n", buf, count);
            level++;
            traverse(buf, key, count);
        }
    }
    level--;
    close(fd);
}

int main(int argc, char* argv[]){
    int fdarray[2];
    pipe(fdarray);

    // child process
    if (fork() == 0){
        close(fdarray[0]);
        traverse(argv[1], argv[2][0], 0);
        write(fdarray[1], &dir_num, sizeof(int));
        write(fdarray[1], &file_num, sizeof(int));
    }

    // parent process
    else{
        close(fdarray[1]);
        read(fdarray[0], &dir_num, sizeof(int));
        read(fdarray[0], &file_num, sizeof(int));
        printf("\n%d directories, %d files\n", dir_num, file_num);
    }
    exit(0);
}