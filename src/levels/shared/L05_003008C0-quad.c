#include "common.h"
extern int FloatToInt(float);
extern int g_screen_offset_x[] __attribute__((sda)), g_screen_offset_y[] __attribute__((sda));
typedef union { int *p; int address; } PacketCursor;
extern PacketCursor g_dma_packet_cursor_2[] __attribute__((sda));
extern char g_quad_copy_template[];
/* RAC1 counterpart: append_subpixel_textured_screen_quad (src/game/draw.c). */
void AppendSubpixelTexturedScreenQuad(float x, float y, float w, float h, int u, int v, int uw, int vh,
                   unsigned long rgba, unsigned long tex) {
    int x0 = FloatToInt(x * 16.0f) + g_screen_offset_x[0] - 8;
    int x1 = FloatToInt((x + w) * 16.0f) + g_screen_offset_x[0] - 8;
    int y0 = FloatToInt(y * 16.0f) + g_screen_offset_y[0] - 8;
    int y1 = FloatToInt((y + h) * 16.0f) + g_screen_offset_y[0] - 8;
    int s1 = (u + uw) * 16;
    int s0 = u * 16;
    int vb = v + vh;
    long *p;
    int *base;

    g_dma_packet_cursor_2[0].p[0] = 0x10000007;
    g_dma_packet_cursor_2[0].p[1] = 0;
    g_dma_packet_cursor_2[0].p[2] = 0;
    g_dma_packet_cursor_2[0].p[3] = 0x50000007;
    base = g_dma_packet_cursor_2[0].p;
    g_dma_packet_cursor_2[0].p = base + 4;
    qcopy(base + 4, g_quad_copy_template);
    p = (long *)(base + 8);
    g_dma_packet_cursor_2[0].p = base + 8;
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
    g_dma_packet_cursor_2[0].p = (int *)((char *)g_dma_packet_cursor_2[0].p + 0x60);
}
