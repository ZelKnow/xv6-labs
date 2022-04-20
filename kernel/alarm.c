#include "types.h"
#include "param.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

uint64
sys_sigalarm()
{
    int tick;
    uint64 handle_addr;
    void (*handle)();
    argint(0, &tick);
    argaddr(1, &handle_addr);
    handle = (void (*)())handle_addr;
    struct proc *p = myproc();
    p->tick = tick;
    p->handle = handle;
    p->timepass = tick;
    return 0;
}

uint64
sys_sigreturn()
{
    memmove(myproc()->trapframe, myproc()->alarm_trapframe, sizeof(struct trapframe));
    myproc()->alarming = 0;
    return 0;
}