#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

// for mp3
uint64
sys_thrdstop(void)
{
  int delay;
  uint64 context_id_ptr;
  uint64 handler, handler_arg;
  if (argint(0, &delay) < 0)
    return -1;
  if (argaddr(1, &context_id_ptr) < 0)
    return -1;
  if (argaddr(2, &handler) < 0)
    return -1;
  if (argaddr(3, &handler_arg) < 0)
    return -1;

  struct proc *proc = myproc();

  //TODO: mp3
  int context_id;

  if (copyin(proc->pagetable, (char *)(&context_id), context_id_ptr, sizeof(int)) != 0)
    return -1;

  if (context_id == -1){
    for (int i = 0; i < MAX_THRD_NUM; i++){
      if (!proc->thrdstop_context_used[i]){
        context_id = i;
        proc->thrdstop_context_id = i;
        proc->thrdstop_context_used[i] = 1;
        break;
      }
    }
  }

  else
    proc->thrdstop_context_id = context_id;

  proc->thrdstop_ticks = 0;
  proc->thrdstop_delay = delay;
  proc->alarm = 1;

  proc->thrdstop_handler_ptr = handler;
  proc->thrdstop_handler_arg = handler_arg;

  if (copyout(proc->pagetable, context_id_ptr, (char *)(&context_id), sizeof(int)) != 0)
    return -1;

  return context_id;
}

// for mp3
uint64
sys_cancelthrdstop(void)
{
  int context_id, is_exit;
  if (argint(0, &context_id) < 0)
    return -1;
  if (argint(1, &is_exit) < 0)
    return -1;

  /*if (context_id < 0 || context_id >= MAX_THRD_NUM) {
    return -1;
  }*/

  struct proc *proc = myproc();

  //TODO: mp3

  if (is_exit)
    proc->thrdstop_context_used[context_id] = 0;
  
  else{
    if (context_id != -1){
      proc->thrdstop_context_id = context_id;

      struct trapframe *tf = kalloc();
      memmove(tf, proc->trapframe, PGSIZE);
      proc->thrdstop_saved_frame[proc->thrdstop_context_id] = tf;
    }
  }

  proc->alarm = 0;

  return proc->thrdstop_ticks;
}

// for mp3
uint64
sys_thrdresume(void)
{
  int context_id;
  if (argint(0, &context_id) < 0)
    return -1;

  struct proc *proc = myproc();

  //TODO: mp3

  proc->thrdstop_context_id = context_id;
  memmove(proc->trapframe, proc->thrdstop_saved_frame[context_id], PGSIZE);

  return 0;
}
