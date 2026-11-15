#include "include_asm.h"
#include "names.h"

extern int mpeg_vobuf_is_empty(void *a0);

typedef int s32;

typedef unsigned char u8;

/* Returns zero when a helper reports non-zero, otherwise combines three fields of the pointed-to block (a difference plus a third term, taken modulo that third term) scaled by a constant and added to the first field. */
int mpeg_get_ring_buffer_position(volatile int *queue)
{
    int diff, size;

    if (mpeg_vobuf_is_empty((void *)queue) != 0)
        return 0;
    diff = queue[2] - queue[3];
    size = queue[4];
    diff = diff + size;
    return queue[1] + (diff % size) * 0x138c0;
}

/* Counts a timer at offset 0xc down by one, stopping at zero. */
void voBufDecCount(u8 *obj) {
 if(*(volatile s32 *)(obj+0xc)>0) *(volatile s32 *)(obj+0xc)=*(volatile s32 *)(obj+0xc)-1;
}
