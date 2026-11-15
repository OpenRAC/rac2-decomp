#include "include_asm.h"
#include "names.h"

extern int voBufIsFull(unsigned char *);

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

/* Returns the next free video output frame, or 0 if there is none. */
int mpeg_vobuf_get_next_frame(int *pool)
{
    int result;
    long isFull;
    isFull = voBufIsFull((unsigned char *)pool);
    if (isFull == 0)
        result = *pool + pool[2] * 0xd0000;
    else
        result = 0;
    return result;
}

/* Returns true when no video output frame is filled. */
s32 mpeg_vobuf_is_empty(u8 *pool) { return *(u32 *)(pool + 0xc) < 1; }
