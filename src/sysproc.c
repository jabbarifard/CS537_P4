#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;

  // add sleep counter in myproc();
  myproc()->wakeupIn = n;

  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_setslice(void)
{
  int pid, slice;
  if(argint(0, &pid) < 0 || argint(1, &slice) < 0) {
    return -1;
  }
  
  // Syscall
  return setslice(pid, slice);
}

int 
sys_getslice(void)
{ 
  int pid;
  if(argint(0, &pid) < 0) {
    return -1;
  }
  
  // Syscall
  return getslice(pid);
}

int 
sys_fork2(void)
{
  int ticks;
  if(argint(0, &ticks) < 0) {
    return -1;
  }

  // Check ticks not negative
  if (ticks < 0) {
    return -1;
  }

  // Syscall
  return fork2(ticks);
}

int
sys_getpinfo(void)
{
  struct pstat *ps;
  if(argptr(0, (void*)&ps, sizeof(*ps)) < 0) {
    return -1;
  }

  // Check pinfo is valid
  if (ps == 0){
    return -1;
  }

  // Syscall
  return getpinfo(ps);
}