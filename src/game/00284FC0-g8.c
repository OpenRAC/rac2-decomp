#include "include_asm.h"
#include "names.h"

extern int *D_001B22A8;
extern void func_002FC560(unsigned int, unsigned long);
extern void func_002FC518(int);

/* Adapted from RAC1 framebuf.c, draw_centered_capture_background (GPL-3.0).
 * Append a centered background as 32-pixel sprite strips. */
/* Draws a background for the centered capture picture, as a row of narrow strips sized to the picture width. */
void func_00285398(int w, int h) {
    int *dmaTag;
    long *packet;
    long *stripCursor;
    int stripCount;
    int i;
    int zero;
    int step;
    int x;
    int y;
    long lo;
    long hi;

    stripCount = w / 32;
    VU1_addGSregister(0x42, 0x800000004AL);
    *(int *)((char *)gDmaPacketCursor + 0) = (stripCount + 5) | 0x10000000;
    *(int *)((char *)gDmaPacketCursor + 4) = 0;
    *(int *)((char *)gDmaPacketCursor + 8) = 0;
    *(int *)((char *)gDmaPacketCursor + 12) = (stripCount + 5) | 0x50000000;
    dmaTag = gDmaPacketCursor;
    packet = (long *)(dmaTag + 4);
    gDmaPacketCursor = dmaTag + 4;
    zero = 0;
    packet[zero] = 0x1000000000000001L;
    packet[1] = 0xE;
    packet[2] = 0x32003;
    packet[3] = 0x47;
    packet[4] = 0x2400000000000001L;
    packet[5] = 0x10;
    packet[6] = 0x146;
    packet[7] = 0x80008080L;
    packet[8] = (long)(stripCount | 0x8000) | 0x2400000000000000L;
    packet[9] = 0x44;
    i = zero;
    if (stripCount > zero) {
        lo = (long)(0x8000 - h * 8) << 16;
        x = 0x8000 + -(w * 8);
        stripCursor = (long *)((char *)dmaTag + 0x60);
        y = 0x8200 + -(w * 8);
        hi = (long)(h * 8 + 0x7FF0) << 16;
        do {
            step = 0x200;
            *stripCursor++ = x | lo;
            *stripCursor++ = y | hi;
            y += step;
            x += step;
            i++;
        } while (i < stripCount);
    }
    gDmaPacketCursor = gDmaPacketCursor + (stripCount * 4 + 20);
}


/* Adapted from RAC1 framebuf.c, draw_framebuffer_rect (GPL-3.0).
 * Append an alpha-blended rectangle in the centered 12.4 coordinate space. */
/* Draws a see-through colored rectangle on screen at the given corners. */
void func_00285548(int x0, int y0, int x1, int y1, int w, int h, unsigned int rgba) {
    long *packet;
    int ax, ay, bx, by;
    int hw, hh;

    vu1_add_vif_code(0x13000000);
    VU1_addGSregister(0x42, 0x64);
    *(int *)((char *)gDmaPacketCursor + 0) = 0x10000006;
    *(int *)((char *)gDmaPacketCursor + 4) = 0;
    *(int *)((char *)gDmaPacketCursor + 8) = 0;
    *(int *)((char *)gDmaPacketCursor + 12) = 0x50000006;
    ax = (x0 << 4) + 0x8000;
    ay = (y0 << 4) + 0x8000;
    bx = (x1 << 4) + 0x8000;
    by = (y1 << 4) + 0x8000;
    hw = w << 3;
    hh = h << 3;
    gDmaPacketCursor += 4;
    packet = (long *)gDmaPacketCursor;
    *(long *)((char *)packet + 0) = 0x1000000000000001L;
    *(long *)((char *)packet + 8) = 0xE;
    *(long *)((char *)packet + 16) = 0x33003;
    *(long *)((char *)packet + 24) = 0x47;
    *(long *)((char *)packet + 32) = 0x2400000000000001L;
    *(long *)((char *)packet + 40) = 0x10;
    *(long *)((char *)packet + 48) = 0x106;
    *(long *)((char *)packet + 56) = rgba;
    *(long *)((char *)packet + 64) = 0x2400000000008001L;
    *(long *)((char *)packet + 72) = 0x44;
    {
        long X1 = bx - hw;
        long X0 = ax - hw;
        long Y0 = ay - hh;
        long Y1 = by - hh;

        *(long *)((char *)packet + 80) = X0 | (Y0 << 16);
        *(long *)((char *)packet + 88) = X1 | (Y1 << 16);
    }
    gDmaPacketCursor += 0x18;
    VU1_addGSregister(0x42, 0x8000000044L);
    vu1_add_vif_code(0x13000000);
}

