#include "threadtools.h"

// discuss with b08501098, b08502041
#include <poll.h>

jmp_buf MAIN;

/*
 * Print out the signal you received.
 * If SIGALRM is received, reset the alarm here.
 * This function should not return. Instead, call longjmp(sched_buf, 1).
 */
void sighandler(int signo){
    if (signo == SIGTSTP){
        sigprocmask(SIG_SETMASK, &base_mask, NULL);
        printf("caught SIGTSTP\n");
    }
    else if (signo == SIGALRM){
        sigprocmask(SIG_SETMASK, &base_mask, NULL);
		printf("caught SIGALRM\n");
		alarm(timeslice);
    }
    longjmp(sched_buf, 1);
}

/*
 * Prior to calling this function, both SIGTSTP and SIGALRM should be blocked.
 */
void scheduler(){
    int val = setjmp(sched_buf);
    if (val == 0){
        rq_current = 0;
        longjmp(RUNNING->environment, 1);
    }

    else{
        struct pollfd fdarray1[wq_size];
        for (int i = 0; i < wq_size; i++){
            fdarray1[i].fd = waiting_queue[i]->fd;
            fdarray1[i].events = POLLIN;
        }
        poll(fdarray1, wq_size, 0);

        int index = 0;
        struct tcb* still_waiting_queue[wq_size];
        for (int i = 0; i < wq_size; i++){
            if (fdarray1[i].revents & POLLIN){
                ready_queue[rq_size] = waiting_queue[i];
                rq_size++;
                waiting_queue[i] = NULL;
            }
            else{
                still_waiting_queue[index] = waiting_queue[i];
                index++;
            }
        }
        for (int i = 0; i < index; i++)
            waiting_queue[i] = still_waiting_queue[i];
        for (int i = index; i < wq_size; i++)
            waiting_queue[i] = NULL;
        wq_size = index;

        if (val == 1){
            if (rq_current == (rq_size - 1))
                rq_current = 0;
            else
                rq_current++;
        }

        else if (val == 2){
            waiting_queue[wq_size] = ready_queue[rq_current];
            wq_size++;
            ready_queue[rq_current] = ready_queue[rq_size - 1];
            if (rq_current == (rq_size - 1))
                rq_current = 0;
            rq_size--;
        }

        else if (val == 3){
            free(ready_queue[rq_current]);
            ready_queue[rq_current] = ready_queue[rq_size - 1];
            if (rq_current == (rq_size - 1))
                rq_current = 0;
            rq_size--;
        }

        if (rq_size == 0){
            if (wq_size > 0){
                struct pollfd fdarray2[wq_size];
                for (int i = 0; i < wq_size; i++){
                    fdarray2[i].fd = waiting_queue[i]->fd;
                    fdarray2[i].events = POLLIN;
                }
                poll(fdarray2, wq_size, -1);

                int index = 0;
                for (int i = 0; i < wq_size; i++){
                    if (fdarray2[i].revents & POLLIN){
                        ready_queue[rq_size] = waiting_queue[i];
                        rq_size++;
                        waiting_queue[i] = NULL;
                    }
                    else{
                        still_waiting_queue[index] = waiting_queue[i];
                        index++;
                    }
                }
                for (int i = 0; i < index; i++)
                    waiting_queue[i] = still_waiting_queue[i];
                for (int i = index; i < wq_size; i++)
                    waiting_queue[i] = NULL;
                wq_size = index;

                rq_current = 0;
                longjmp(RUNNING->environment, 1);
            }
        }
        else
            longjmp(RUNNING->environment, 1);
    }
}
