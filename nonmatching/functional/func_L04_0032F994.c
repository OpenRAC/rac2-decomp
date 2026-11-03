/* functional: high. Gated SAME in level 18 (the only captured call) with that level's D_L18_ names substituted in a test copy; every retail instruction ran. Retail is hand-written asm ($at as the write pointer, lq/sq and ld/sd copies); here the same reads and writes in the same order as word and doubleword copies of the same bytes. The 16-byte zero store at packet +8 of the tail is written as four words (retail's sq address is 16-aligned there). */

#include "include_asm.h"

typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;

extern u32 D_L04_001B2C48;          /* $gp+0x3C58: the DMA packet write pointer */
extern u32 D_L04_002A7D40[20];      /* 5-quadword packet header */
extern u32 D_L04_001AD8A0[4];       /* tag quadword */
extern u64 D_L04_002A7A40[46];      /* 23 constant quadwords */
extern u32 D_L04_001AD8C0[4];       /* tag quadword */
extern s16 D_L04_002A7920[46];      /* offsets into the scratchpad words at 0x70001088 */
extern u32 D_L04_001AD8E0[4];       /* tag quadword */
extern s16 D_L04_002A79E0[46];      /* offsets into the scratchpad vectors at 0x70002000 */
extern s16 D_L04_002A7980[46];      /* offsets into the scratchpad doublewords at 0x70000780 */

/* Builds the two DMA chains that draw one water ripple patch from the scratchpad
   results: the first carries the constants, 46 words and 23 pairs of xyz picked by the
   offset tables for cell `value` and an end tag with `mode` (0x14000000 | mode), the
   second 46 doublewords; each chain's first word gets its quadword count - 1, and a
   0x30000031 call tag pointing at the first chain's word block closes the packet. */
void func_L04_0032F994(int mode, int value)
{
    u32 *start = (u32 *)D_L04_001B2C48;
    u32 *at = start;
    u32 *wordblk;
    u8 *base;
    s32 i;

    for (i = 0; i < 5; i++) {
        at[0] = D_L04_002A7D40[i * 4 + 0];
        at[1] = D_L04_002A7D40[i * 4 + 1];
        at[2] = D_L04_002A7D40[i * 4 + 2];
        at[3] = D_L04_002A7D40[i * 4 + 3];
        at += 4;
    }
    at[0] = D_L04_001AD8A0[0];
    at[1] = D_L04_001AD8A0[1];
    at[2] = D_L04_001AD8A0[2];
    at[3] = D_L04_001AD8A0[3];
    at += 4;
    for (i = 0; i < 23; i++) {
        u64 lo = D_L04_002A7A40[i * 2 + 0];
        u64 hi = D_L04_002A7A40[i * 2 + 1];
        ((u64 *)at)[0] = lo;
        ((u64 *)at)[1] = hi;
        at += 4;
    }

    wordblk = at;
    at[0] = D_L04_001AD8C0[0];
    at[1] = D_L04_001AD8C0[1];
    at[2] = D_L04_001AD8C0[2];
    at[3] = D_L04_001AD8C0[3];
    at += 4;
    base = (u8 *)0x70001088 + value * 4;
    for (i = 0; i < 46; i++) {
        *at = *(u32 *)(base + D_L04_002A7920[i]);
        at++;
    }
    *(u64 *)at = 0;
    at += 2;

    at[0] = D_L04_001AD8E0[0];
    at[1] = D_L04_001AD8E0[1];
    at[2] = D_L04_001AD8E0[2];
    at[3] = D_L04_001AD8E0[3];
    at += 4;
    base = (u8 *)0x70002000 + value * 12;
    for (i = 0; i < 23; i++) {
        u32 *p = (u32 *)(base + D_L04_002A79E0[i * 2 + 0]);
        u32 *q;
        u32 x = p[0], y = p[1], z = p[2];
        q = (u32 *)(base + D_L04_002A79E0[i * 2 + 1]);
        at[0] = x;
        at[1] = y;
        at[2] = z;
        x = q[0];
        y = q[1];
        z = q[2];
        at[3] = x;
        at[4] = y;
        at[5] = z;
        at += 6;
    }
    at[0] = 0x14000000 | mode;
    at[1] = 0;
    at[2] = 0;
    at[3] = 0;
    at[4] = 0;
    at[5] = 0;
    at[5] = 0x11000000;
    at += 6;

    *start |= ((u32)((u8 *)at - (u8 *)start) >> 4) - 1;
    D_L04_001B2C48 = (u32)at;
    start = at;

    for (i = 0; i < 5; i++) {
        at[0] = D_L04_002A7D40[i * 4 + 0];
        at[1] = D_L04_002A7D40[i * 4 + 1];
        at[2] = D_L04_002A7D40[i * 4 + 2];
        at[3] = D_L04_002A7D40[i * 4 + 3];
        at += 4;
    }
    {
        u32 w5 = at[-15];
        u32 w10 = at[-10];
        at[-15] = w5 | 0x01000000;
        at[-10] = w10 | 0x01000000;
    }
    at[0] = D_L04_001AD8A0[0];
    at[1] = D_L04_001AD8A0[1];
    at[2] = D_L04_001AD8A0[2];
    at[3] = D_L04_001AD8A0[3];
    at += 4;
    base = (u8 *)0x70000780 + value * 8;
    for (i = 0; i < 46; i++) {
        *(u64 *)at = *(u64 *)(base + D_L04_002A7980[i]);
        at += 2;
    }

    *start |= ((u32)((u8 *)at - (u8 *)start) >> 4) - 1;
    D_L04_001B2C48 = (u32)at;
    start = at;

    ((u64 *)start)[1] = 0;
    start[1] = (u32)wordblk;
    start[0] = 0x30000031;
    D_L04_001B2C48 = (u32)(start + 4);
}
