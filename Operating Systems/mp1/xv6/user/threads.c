#include "kernel/types.h"
#include "user/setjmp.h"
#include "user/threads.h"
#include "user/user.h"

#define NULL 0

static struct thread* current_thread = NULL;
static int id = 1;
static jmp_buf env_st;
static jmp_buf env_tmp;

struct thread *thread_create(void (*f)(void *), void *arg){
    struct thread *t = (struct thread*) malloc(sizeof(struct thread));
    unsigned long new_stack_p1;
    unsigned long new_stack1;
    new_stack1 = (unsigned long) malloc(sizeof(unsigned long) * 0x100);
    new_stack_p1 = new_stack1 + 0x100 * 8 - 0x2 * 8;
    unsigned long new_stack_p2;
    unsigned long new_stack2;
    new_stack2 = (unsigned long) malloc(sizeof(unsigned long) * 0x100);
    new_stack_p2 = new_stack2 + 0x100 * 8 - 0x2 * 8;
    t->fp = f;
    t->arg = arg;
    t->ID = id;
    t->buf_set = 0;
    t->stack1 = (void*) new_stack1;
    t->stack_p1 = (void*) new_stack_p1;
    t->stack2 = (void*) new_stack2;
    t->stack_p2 = (void*) new_stack_p2;
    id++;

    // part 2
    t->sig_handler[0] = NULL_FUNC;
    t->sig_handler[1] = NULL_FUNC;
    t->signo = -1;
    t->handler_buf_set = 0;
    return t;
}

void thread_add_runqueue(struct thread *t){
    if (current_thread == NULL){
        // TODO
        current_thread = t;
        t->previous = t;
        t->next = t;
    }
    else{
        // TODO
        current_thread->previous->next = t;
        t->previous = current_thread->previous;
        current_thread->previous = t;
        t->next = current_thread;

        t->sig_handler[0] = current_thread->sig_handler[0];
        t->sig_handler[1] = current_thread->sig_handler[1];
    }
}

void thread_yield(void){
    // TODO
    if (current_thread->signo == -1 && setjmp(current_thread->env) == 0){
        current_thread->buf_set = 1;
        schedule();
        dispatch();
    }
        
    if (current_thread->signo != -1 && setjmp(current_thread->handler_env) == 0){
        current_thread->handler_buf_set = 1;
        schedule();
        dispatch();
    }
}

void dispatch(void){
    // TODO
    //printf("ID = %d, %d\n", current_thread->ID, current_thread->signo);
    if (current_thread->signo == -1){
        if (current_thread->buf_set == 0){
            if (setjmp(env_tmp) == 0){
                env_tmp->sp = (unsigned long) current_thread->stack_p1;
                longjmp(env_tmp, 1);
            }
            else{
                current_thread->fp(current_thread->arg);
                thread_exit();
            }
        }
        else
            longjmp(current_thread->env, 1);
    }
    
    else{
        if (current_thread->sig_handler[current_thread->signo] == NULL_FUNC)
            thread_exit();
        else{
            if (current_thread->handler_buf_set == 0){
                if (setjmp(env_tmp) == 0){
                    env_tmp->sp = (unsigned long) current_thread->stack_p2;
                    longjmp(env_tmp, 1);
                }
                else{
                    current_thread->sig_handler[current_thread->signo](current_thread->signo);
                    current_thread->signo = -1;
                    if (current_thread->buf_set == 0){
                        if (setjmp(env_tmp) == 0){
                            env_tmp->sp = (unsigned long) current_thread->stack_p1;
                            longjmp(env_tmp, 1);
                        }
                        else{
                            current_thread->fp(current_thread->arg);
                            thread_exit();
                        }
                    }
                    else{
                        longjmp(current_thread->env, 1);
                    }
                        
                }
            }
            else
                longjmp(current_thread->handler_env, 1);
        }
    }
}

void schedule(void){
    // TODO
    current_thread = current_thread->next;
}

void thread_exit(void){
    if(current_thread->next != current_thread){
        // TODO
        current_thread->previous->next = current_thread->next;
        current_thread->next->previous = current_thread->previous;
        struct thread *next = current_thread->next;
        free(current_thread->stack1);
        free(current_thread->stack2);
        free(current_thread);
        current_thread = next;
        dispatch();
    }
    else{
        // TODO
        // Hint: No more thread to execute
        free(current_thread->stack1);
        free(current_thread->stack2);
        free(current_thread);
        current_thread = NULL;
        longjmp(env_st, 1);
    }
}

void thread_start_threading(void){
    // TODO
    if (setjmp(env_st) == 0)
        dispatch();
}

// part 2
void thread_register_handler(int signo, void (*handler)(int)){
    // TODO
    current_thread->sig_handler[signo] = handler;
}

void thread_kill(struct thread *t, int signo){
    // TODO
    t->signo = signo;
}