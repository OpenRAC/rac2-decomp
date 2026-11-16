#include "names.h"
/* func_00285030 (680 bytes, 28 places): builds a textured sprite packet from the draw state
 * table D_001A6480. -G8 sibling of 00284FC0.c.
 * Own unit: -O2 -G8 -ffunction-sections -frac2-sched-defer-const (config/cflags.txt). 0xE and
 * 0x8000 share $a2 in retail because the constant 0x8000 is born a cycle after t[1]'s store
 * ends its single-use pseudo; the switch defers a constant load issued right beside such a
 * store (docs/build/compiler-notes.md). Landed under the owner's standard of 12 November 2026
 * (any generally worded opt-in rule that makes a function match); forced on for every USA
 * v1.01 unit it changes 163 functions.
 */
#include "common.h"

typedef struct { unsigned long lo : 9; unsigned long hi : 55; } TexBits;
typedef struct { u8 p0[0x160]; s16 h160; s16 h162; s16 h164; s16 h166; u8 p168[4]; u16 h16C; s16 h16E; } DrawState;
extern DrawState g_screen_adjust_offsets[];
extern s32 g_dma_packet_cursor[] MACRO_ADDR;
extern long g_quad_texture;
extern void mem_fast_helper_b();
extern int sceGsSetDefDrawEnv(void *, short, short, short, short, short);

/* Builds the drawing packet for a picture used as a screen-sized sprite. It records the picture size and where it lives in video memory. */
void gfx_build_screen_sprite_packet(s32 tw, s32 th, s32 tbp, s32 mode) {
    DrawState *draw_state = g_screen_adjust_offsets;
    s32 tbw;
    long tex;
    u8 *bytes;
    long *packet;
    long w;
    long w2;

    tbw = tw - 6;
    if (tbw <= 0) tbw = 1;
    draw_state->h166 = tbp >> 13;
    draw_state->h160 = 1 << tw;
    draw_state->h162 = 1 << th;
    tex = (tbp >> 8) | ((long)(1 << tbw) << 14);
    tex |= (long)tw << 26;
    tex |= (long)th << 30;
    tex |= 0x8000UL << 19;
    g_quad_texture = tex;
    mem_fast_helper_b(g_dma_packet_cursor[0], 0xF0);
    *(u32 *)(g_dma_packet_cursor[0] + 0) = 0x1000000E;
    *(u32 *)(g_dma_packet_cursor[0] + 4) = 0;
    *(u32 *)(g_dma_packet_cursor[0] + 8) = 0;
    *(u32 *)(g_dma_packet_cursor[0] + 0xC) = 0x5000000E;
    w = 0x4410;
    w2 = 0x106;
    {
        long *t = (long *)(g_dma_packet_cursor[0] + 0x10);
        g_dma_packet_cursor[0] = (s32)t;
        t[0] = 0x1000000000000008UL;
        t[1] = 0xE;
    }
    bytes = (u8 *)g_dma_packet_cursor[0];
    packet = (long *)(bytes + 0x10);
    g_dma_packet_cursor[0] = (s32)packet;
    sceGsSetDefDrawEnv(packet, draw_state->h164, draw_state->h160, draw_state->h162, 3, 0);
    ((TexBits *)(bytes + 0x10))->lo = draw_state->h166;
    if (mode == 0) {
        packet[2] = draw_state->h16E | ((long)(draw_state->h16C & 0xF) << 24);
    } else {
        s32 n = tw + th;
        if (n > 16) n = 16;
        packet[2] = ((tbp - (4 << n)) >> 13) | ((long)(draw_state->h16C & 0xF) << 24);
    }
    {
        long *t = (long *)(g_dma_packet_cursor[0] + 0x80);
        DrawState *s2 = g_screen_adjust_offsets;
        g_dma_packet_cursor[0] = (s32)t;
        t[0] = 0x1000000000000001UL;
        t[1] = 0xE;
        t[2] = 0x30003;
        t[3] = 0x47;
        t[4] = 0x4400000000008001UL;
        t[5] = w;
        t[6] = w2;
        t[7] = 0;
        t[8] = (0x8000 - s2->h160 * 8) | ((long)(0x8000 - s2->h162 * 8) << 16);
        t[9] = (s2->h160 * 8 + 0x8000) | ((long)(s2->h162 * 8 + 0x7FF0) << 16);
    }
    g_dma_packet_cursor[0] += 0x50;
}
