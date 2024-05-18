#include "threadtools.h"

#include <limits.h>

// reference: https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

void fibonacci(int id, int arg){
    thread_setup(id, arg);

    for (RUNNING->i = 1; ; RUNNING->i++){
        if (RUNNING->i <= 2)
            RUNNING->x = RUNNING->y = 1;
        else{
            /* We don't need to save tmp, so it's safe to declare it here. */
            int tmp = RUNNING->y;  
            RUNNING->y = RUNNING->x + RUNNING->y;
            RUNNING->x = tmp;
        }

        printf("%d %d\n", RUNNING->id, RUNNING->y);
        sleep(1);

        if (RUNNING->i == RUNNING->arg)
            thread_exit();
        else
            thread_yield();
    }
}

void collatz(int id, int arg){
    thread_setup(id, arg);

    RUNNING->x = RUNNING->arg;
    for (; RUNNING->x != 1; ){
        if (RUNNING->x % 2 == 0)
            RUNNING->x /= 2;
        else
            RUNNING->x = 3 * RUNNING->x + 1;
        
        printf("%d %d\n", RUNNING->id, RUNNING->x);
        sleep(1);

        if (RUNNING->x == 1)
            thread_exit();
        else
            thread_yield();
    }
}

void max_subarray(int id, int arg) {
    thread_setup(id, arg);

    RUNNING->x = INT_MIN; // max_so_far
    RUNNING->y = 0; // max_ending_here

    for (RUNNING->i = 1; ; RUNNING->i++) {
        async_read(5);

        int tmp;
        sscanf(RUNNING->buf, "%d", &tmp);

        RUNNING->y += tmp;
        if (RUNNING->y < 0)
            RUNNING->y = 0;
        if (RUNNING->x < RUNNING->y)
            RUNNING->x = RUNNING->y;
        
        printf("%d %d\n", RUNNING->id, RUNNING->x);
        sleep(1);

        if (RUNNING->i == RUNNING->arg)
            thread_exit();
        else
            thread_yield();
    }
}
