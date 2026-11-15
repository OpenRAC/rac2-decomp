#include "common.h"

/* Separate from the SDK unit; -fno-strength-reduce preserves the two
 * eight-byte cursor advances for each sprite's corner pair. */
typedef struct {
    char pad[0x150];
    short x;
    short y;
} ScreenDF838;
extern ScreenDF838 D_001A6480;
extern int *volatile D_001B22A8 MACRO_ADDR;

extern void func_002FC560(int, long);

/* Draws a screen-wide set of thin sprite strips that prepare the buffer used for shadows. */
void func_002DF838(void)
{
    int x, y, n;
    long *q;
    int *p;
    int i;
    int u;
    int v;
    int zero;
    int step;
    long *corners;

    x = gScreenAdjustOffsets.x;
    y = gScreenAdjustOffsets.y;
    n = x / 32;

    VU1_addGSregister(0x42, 0x64);

    /* The packet cursor is reloaded between these header writes in retail. */
    *(int *)gDmaPacketCursor = (n + 5) | 0x10000000;
    *(int *)((char *)gDmaPacketCursor + 4) = 0;
    *(int *)((char *)gDmaPacketCursor + 8) = 0;
    *(int *)((char *)gDmaPacketCursor + 12) = (n + 5) | 0x50000000;
    p = gDmaPacketCursor;
    gDmaPacketCursor = p + 4;
    q = (long *)(p + 4);
    zero = 0;
    q[zero] = 0x1000000000000001L;

    q[1] = 0xE;
    q[2] = 0x31001;
    q[3] = 0x47;
    q[4] = 0x2400000000008001L;
    q[5] = 0x10;
    q[6] = 0x146;
    q[7] = 0x7F808080;
    q[8] = (long)(n | 0x8000) | 0x2400000000000000L;
    q[9] = 0x44;
    i = zero;
    if (n > zero) {
        long c = (long)(0x8000 - y * 8) << 16;
        long d = (long)(y * 8 + 0x7FF0) << 16;

        u = 0x8000 + -(x * 8);
        v = 0x8200 + -(x * 8);
        corners = (long *)((char *)p + 0x60);
        do {
            step = 0x200;
            *corners++ = u | c;
            *corners++ = v | d;
            v += step;
            u += step;
            i++;
        } while (i < n);
    }
    gDmaPacketCursor = (int *)((char *)gDmaPacketCursor + (n * 16 + 0x50));
}
