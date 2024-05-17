#include "kernel/types.h"
#include "user/user.h"
#include "user/list.h"
#include "user/threads.h"
#include "user/threads_sched.h"

#define NULL 0

/* default scheduling algorithm */
struct threads_sched_result schedule_default(struct threads_sched_args args)
{
    struct thread *thread_with_smallest_id = NULL;
    struct thread *th = NULL;
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (thread_with_smallest_id == NULL || th->ID < thread_with_smallest_id->ID) {
            thread_with_smallest_id = th;
        }
    }

    struct threads_sched_result r;
    if (thread_with_smallest_id != NULL) {
        r.scheduled_thread_list_member = &thread_with_smallest_id->thread_list;
        r.allocated_time = thread_with_smallest_id->remaining_time;
    } else {
        r.scheduled_thread_list_member = args.run_queue;
        r.allocated_time = 1;
    }

    return r;
}

/* Earliest-Deadline-First scheduling */
struct threads_sched_result schedule_edf(struct threads_sched_args args)
{
    struct thread *thread_missed = NULL;
    struct thread *th = NULL;

    list_for_each_entry(th, args.run_queue, thread_list) {
        if (th->current_deadline <= args.current_time && (thread_missed == NULL || th->ID < thread_missed->ID))
            thread_missed = th;
    }

    struct thread *thread_ed = NULL;
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (thread_ed == NULL || th->current_deadline < thread_ed->current_deadline || (th->current_deadline == thread_ed->current_deadline && th->ID < thread_ed->ID))
            thread_ed = th;
    }

    struct threads_sched_result r;
    struct release_queue_entry *entry = NULL;

    // There is a thread that has already missed its current deadline
    if (thread_missed != NULL){
        r.scheduled_thread_list_member = &thread_missed->thread_list;
        r.allocated_time = 0;
    }

    else if (thread_ed != NULL) {
        r.scheduled_thread_list_member = &thread_ed->thread_list;

        struct thread *thread_next_ed = NULL;
        list_for_each_entry(entry, args.release_queue, thread_list) {
            if ((entry->thrd->current_deadline < (args.current_time + thread_ed->remaining_time)) && ((entry->thrd->current_deadline + entry->thrd->period) < thread_ed->current_deadline))
                thread_next_ed = entry->thrd;
        }

        if (thread_next_ed != NULL)
            r.allocated_time = (thread_next_ed->current_deadline - args.current_time);
            
        else
            r.allocated_time = thread_ed->remaining_time;

        if (args.current_time + r.allocated_time > thread_ed->current_deadline)
            r.allocated_time = thread_ed->current_deadline - args.current_time;
    }

    // The run queue is empty
    else {
        r.scheduled_thread_list_member = args.run_queue;

        struct thread *thread_first = NULL;
        list_for_each_entry(entry, args.release_queue, thread_list) {
            if (thread_first == NULL || entry->thrd->current_deadline < thread_first->current_deadline)
                thread_first = entry->thrd;
        }
        r.allocated_time = (thread_first->current_deadline - args.current_time);
    }

    return r;
}

/* Rate-Monotonic Scheduling */
struct threads_sched_result schedule_rm(struct threads_sched_args args)
{
    struct thread *thread_missed = NULL;
    struct thread *th = NULL;

    list_for_each_entry(th, args.run_queue, thread_list) {
        if (th->current_deadline <= args.current_time && (thread_missed == NULL || th->ID < thread_missed->ID))
            thread_missed = th;
    }

    struct thread *thread_sp = NULL;
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (thread_sp == NULL || th->period < thread_sp->period || (th->period == thread_sp->period && th->ID < thread_sp->ID))
            thread_sp = th;
    }

    struct threads_sched_result r;
    struct release_queue_entry *entry = NULL;

    // There is a thread that has already missed its current deadline
    if (thread_missed != NULL){
        r.scheduled_thread_list_member = &thread_missed->thread_list;
        r.allocated_time = 0;
    }

    else if (thread_sp != NULL) {
        r.scheduled_thread_list_member = &thread_sp->thread_list;

        struct thread *thread_next_sp = NULL;
        list_for_each_entry(entry, args.release_queue, thread_list) {
            if ((entry->thrd->current_deadline < (args.current_time + thread_sp->remaining_time)) && (entry->thrd->period < thread_sp->period))
                thread_next_sp = entry->thrd;
        }

        if (thread_next_sp != NULL)
            r.allocated_time = (thread_next_sp->current_deadline - args.current_time);
            
        else
            r.allocated_time = thread_sp->remaining_time;

        if (args.current_time + r.allocated_time > thread_sp->current_deadline)
            r.allocated_time = thread_sp->current_deadline - args.current_time;
    }

    // The run queue is empty
    else {
        r.scheduled_thread_list_member = args.run_queue;

        struct thread *thread_first = NULL;
        list_for_each_entry(entry, args.release_queue, thread_list) {
            if (thread_first == NULL || entry->thrd->current_deadline < thread_first->current_deadline)
                thread_first = entry->thrd;
        }
        r.allocated_time = (thread_first->current_deadline - args.current_time);
    }

    return r;
}
