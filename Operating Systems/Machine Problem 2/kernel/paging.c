#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
#include "proc.h"

/* NTU OS 2022 */
/* Page fault handler */
int handle_pgfault() {
  /* Find the address that caused the fault */
  /* uint64 va = r_stval(); */

  /* TODO */
  
  uint64 addr = r_stval();
  uint64 va = PGROUNDDOWN(addr);
  struct proc* p = myproc();
  pte_t* pte = walk(p->pagetable, va, 1);

  if (*pte & PTE_S){
    char* pa = kalloc();

    begin_op();
    uint64 blockno = PTE2BLOCKNO(*pte);
    read_page_from_disk(ROOTDEV, pa, blockno);
    *pte = PA2PTE(pa) | PTE_FLAGS(*pte);
    end_op();

    *pte &= ~PTE_S;
    *pte |= PTE_V;
  }
  else{
    char* pa = kalloc();

    if (pa == 0)
      return -3;
    
    memset(pa, 0, PGSIZE);
    if (mappages(p->pagetable, va, PGSIZE, (uint64)pa, (PTE_R | PTE_U | PTE_W | PTE_X)) != 0){
      kfree(pa);
      return -4;
    }
  }
  return 0;
}
