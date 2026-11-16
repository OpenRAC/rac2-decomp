#include "common.h"

typedef struct { unsigned int tag, addr, vif0, vif1; } QuadDmaTag;
union QuadCursor { QuadDmaTag *tag; int *words; unsigned char *bytes; int addr; };
extern union QuadCursor g_dma_packet_cursor __attribute__((sda));
extern int g_screen_width[] __attribute__((sda));
extern char g_dma_packet_template_a[];

/* DrawTexturedQuad, adapted from OpenRAC/rac1-decomp src/game/draw.c (GPL-3.0).
 * RAC2 reads the y extent first and adjusts y into variables of their own: sched1 ranks an
 * in-place `y0 -= 8` behind the v + vh sum, because it adds a live register. */
/* Draws a picture on the screen as a rectangle. */
void DrawTexturedQuad(int x, int y, int w, int h, int u, int v, int uw, int vh,
                   unsigned long rgba, unsigned long tex)
{
    int yt = y * 16 + g_screen_width[5];
    int yb = (y + h) * 16 + g_screen_width[5];
    int x0 = x * 16 + g_screen_width[4] - 8;
    int x1 = (x + w) * 16 + g_screen_width[4] - 8;
    int s1 = (u + uw) * 16;
    int s0 = u * 16;
    int y0 = yt - 8;
    int y1 = yb - 8;
    int vb = v + vh;
    long *p;
    int *base;

    g_dma_packet_cursor.words[0] = 0x10000007;
    g_dma_packet_cursor.words[1] = 0;
    g_dma_packet_cursor.words[2] = 0;
    g_dma_packet_cursor.words[3] = 0x50000007;
    base = g_dma_packet_cursor.words;
    g_dma_packet_cursor.words = base + 4;
    qcopy(base + 4, g_dma_packet_template_a);
    p = (long *)(base + 8);
    g_dma_packet_cursor.words = base + 8;
    p[0] = tex;
    p[1] = 0x154;
    p[2] = rgba;
    p[3] = (v << 20) + s0;
    p[4] = x0 | ((long)y0 << 16) | ((long)0xFFFFF0 << 32);
    p[5] = (v << 20) + s1;
    p[6] = x1 | ((long)y0 << 16) | ((long)0xFFFFF0 << 32);
    p[7] = (vb << 20) + s0;
    p[8] = x0 | ((long)y1 << 16) | ((long)0xFFFFF0 << 32);
    p[9] = (vb << 20) + s1;
    p[10] = x1 | ((long)y1 << 16) | ((long)0xFFFFF0 << 32);
    p[11] = 0;
    g_dma_packet_cursor.words = (int *)((char *)g_dma_packet_cursor.words + 0x60);
}
