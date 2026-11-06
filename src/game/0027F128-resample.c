#include "include_asm.h"

typedef unsigned char u8;
typedef struct {
    u8 pad[0x150];
    short display_width;
    short display_height;
    short psm;
    short fbp0;
    short storage_width;
    short storage_height;
} FsAaBuffer;
/* An array element, not a scalar: retail's read conflicts with the packet stores in the
   scheduler, which alias analysis rules out for a scalar at a fixed address. */
extern FsAaBuffer *D_001A742C[] __attribute__((sda));
extern int D_001A7BB8 __attribute__((sda));
extern char D_001A6AF0[];
extern u8 D_001A7BB1 __attribute__((sda));

/* Rebuilds the 16-strip resample packet of RAC1's framebuf.c, squeezing the height by
   115/160 unless flagged. The four-term OR is split because fold rebalances a chain of four. */
void func_00284088(int a, int b)
{
    unsigned long *q;
    int height;
    q = (unsigned long *)D_001A6AF0;
    q[0] = 0x308B400000000001UL;
    q[1] = 0xEEE;
    q[2] = 0x30000;
    q[3] = 0x47;
    q[4] = 0x100000261UL;
    q[5] = 0x14;
    q[6] = (((long)D_001A742C[0]->fbp0 << 5) | ((long)((D_001A742C[0]->display_width >> 6) & 0x3F) << 14) |
           ((long)D_001A742C[0]->psm << 20)) | 0xEA8000000UL;
    q[7] = 6;
    q[8] = 0x4400000000008010UL;
    q[9] = 0x5353;
    if (!a) b = D_001A7BB1 != 0;
    if (b) height = D_001A742C[0]->storage_height;
    else height = D_001A742C[0]->storage_height * 115 / 160;
    {
        unsigned long *p = q + 10;
        int i;
        for (i = 0; i < 16; i++) {
            if (D_001A7BB8) {
                *p++ = i * D_001A742C[0]->display_width;
                *p++ = (i * 640 + 0x6BF8) | ((long)(0x7FF8 - height * 8) << 16);
                *p++ = (i + 1) * D_001A742C[0]->display_width | 0x1A000000;
                *p++ = ((i + 1) * 640 + 0x6BF8) | ((long)(height * 8 + 0x7FF8) << 16);
            } else {
                *p++ = i * D_001A742C[0]->display_width;
                *p++ = (i * 512 + 0x6FF8) | ((long)(0x7FF8 - height * 8) << 16);
                *p++ = (i + 1) * D_001A742C[0]->display_width | 0x1A000000;
                *p++ = ((i + 1) * 512 + 0x6FF8) | ((long)(height * 8 + 0x7FF8) << 16);
            }
        }
    }
}
