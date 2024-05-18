#ifndef THREADTOOL
#define THREADTOOL

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/signal.h>

#define THREAD_MAX 16  // maximum number of threads created
#define BUF_SIZE 512
struct tcb {
    int id;  // the thread id
    jmp_buf environment;  // where the scheduler should jump to
    int arg;  // argument to the function
    int fd;  // file descriptor for the thread
    char buf[BUF_SIZE];  // buffer for the thread
    int i, x, y;  // declare the variables you wish to keep between switches
};

extern int timeslice;
extern jmp_buf sched_buf;
extern struct tcb *ready_queue[THREAD_MAX], *waiting_queue[THREAD_MAX];
/*
 * rq_size: size of the ready queue
 * rq_current: current thread in the ready queue
 * wq_size: size of the waiting queue
 */
extern int rq_size, rq_current, wq_size;
/*
* base_mask: blocks both SIGTSTP and SIGALRM
* tstp_mask: blocks only SIGTSTP
* alrm_mask: blocks only SIGALRM
*/
extern sigset_t base_mask, tstp_mask, alrm_mask;
/*
 * Use this to access the running thread.
 */
#define RUNNING (ready_queue[rq_current])

extern jmp_buf MAIN;

void sighandler(int signo);
void scheduler();

#define thread_create(func, id, arg) ({  \
    if (setjmp(MAIN) == 0)               \
        func(id, arg);                   \
})

#define thread_setup(id, arg) ({                                      \
    struct tcb *new_tcb = (struct tcb *) malloc(sizeof(struct tcb));  \
    new_tcb->id = id;                                                 \
    new_tcb->arg = arg;                                               \
    new_tcb->i = new_tcb->x = new_tcb->y = 0;                         \
    memset(new_tcb->buf, 0, sizeof(new_tcb->buf));                    \
    char fifo_name[32];                                               \
    sprintf(fifo_name, "%d_%s", id, __func__);                        \
    mkfifo(fifo_name, 0666);                                          \
    new_tcb->fd = open(fifo_name, (O_RDWR | O_NONBLOCK));             \
    ready_queue[rq_size] = new_tcb;                                   \
    rq_size++;                                                        \
    if (setjmp(new_tcb->environment) == 0)                            \
        longjmp(MAIN, 1);                                             \
})

#define thread_exit() ({                                 \
    char fifo_name[32];                                  \
    sprintf(fifo_name, "%d_%s", RUNNING->id, __func__);  \
    remove(fifo_name);                                   \
    longjmp(sched_buf, 3);                               \
})

#define thread_yield() ({                                \
    if (setjmp(RUNNING->environment) == 0){              \
        sigset_t pend_mask;                              \
        sigemptyset(&pend_mask);                         \
        sigpending(&pend_mask);                          \
        if (sigismember(&pend_mask, SIGTSTP))            \
            sigprocmask(SIG_UNBLOCK, &tstp_mask, NULL);  \
        else if (sigismember(&pend_mask, SIGALRM))       \
            sigprocmask(SIG_UNBLOCK, &alrm_mask, NULL);  \
    }                                                    \
})

#define async_read(count) ({                     \
    if (setjmp(RUNNING->environment) == 0)       \
        longjmp(sched_buf, 2);                   \
    else                                         \
        read(RUNNING->fd, RUNNING->buf, count);  \
})

#endif // THREADTOOL
