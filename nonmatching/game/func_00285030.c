/* Closer C, 1 November 2026: 680/680, 6 rows, plain -O2 -G8. No asm fence: the tex or-chain over separate
 * statements, and D_001B22A8 as an incomplete MACRO_ADDR array read [0]. A scalar is fixed_scalar_and_varying_struct_p
 * against the t[] stores, so its load moves over them; an array element does not. Left: 0x8000 is loaded before
 * the t[2] store (retail after), so 0xE and 0x8000 do not share a2. Statement order of the stores has no effect.
 */
/* Carried from rac3-decomp (src/boot_elf/text/392698.c, func_00392820): the same
   instructions. Sets up a TW x TH texture at TBP: the texture's sizes and block in the
   draw state at D_001A6480, its TEX0 word in D_001A7470, and two GS packets at the cursor
   D_001B22A8[0] (texture setup through func_00125F20, then the scissor and offset).
   Near miss (26 October 2026, xcarry), as a -g8 unit: rac3's match needs an empty asm register
   fence after the t[7] store, which rac2 does not allow; without it the TEX0 word is built in
   another order and the second packet's constants take other registers (about 25 lines off). */

#include "common.h"

typedef struct { unsigned long lo : 9; unsigned long hi : 55; } TexBits;
typedef struct { u8 p0[0x160]; s16 h160; s16 h162; s16 h164; s16 h166; u8 p168[4]; u16 h16C; s16 h16E; } DrawState;
extern DrawState D_001A6480[];
extern s32 D_001B22A8[] MACRO_ADDR;
extern long D_001A7470;
extern void func_00282A88();
extern void func_00125F20(s32, s32, s32, s32, s32, s32);

void func_00285030(s32 tw, s32 th, s32 tbp, s32 mode) {
    DrawState *s = D_001A6480;
    s32 tbw;
    long tex;
    u8 *p;
    long *q;
    long v;
    long w;

    tbw = tw - 6;
    if (tbw <= 0) tbw = 1;
    s->h166 = tbp >> 13;
    s->h160 = 1 << tw;
    s->h162 = 1 << th;
    tex = (tbp >> 8) | ((long)(1 << tbw) << 14);
    tex |= (long)tw << 26;
    tex |= (long)th << 30;
    tex |= 0x8000UL << 19;
    D_001A7470 = tex;
    func_00282A88(D_001B22A8[0], 0xF0);
    *(u32 *)(D_001B22A8[0] + 0) = 0x1000000E;
    *(u32 *)(D_001B22A8[0] + 4) = 0;
    *(u32 *)(D_001B22A8[0] + 8) = 0;
    *(u32 *)(D_001B22A8[0] + 0xC) = 0x5000000E;
    w = 0x4410;
    v = 0x106;
    {
        long *t = (long *)(D_001B22A8[0] + 0x10);
        D_001B22A8[0] = (s32)t;
        t[0] = 0x1000000000000008UL;
        t[1] = 0xE;
    }
    p = (u8 *)D_001B22A8[0];
    q = (long *)(p + 0x10);
    D_001B22A8[0] = (s32)q;
    func_00125F20((s32)q, s->h164, s->h160, s->h162, 3, 0);
    ((TexBits *)(p + 0x10))->lo = s->h166;
    if (mode == 0) {
        q[2] = s->h16E | ((long)(s->h16C & 0xF) << 24);
    } else {
        s32 n = tw + th;
        if (n > 16) n = 16;
        q[2] = ((tbp - (4 << n)) >> 13) | ((long)(s->h16C & 0xF) << 24);
    }
    {
        long *t = (long *)(D_001B22A8[0] + 0x80);
        DrawState *s2 = D_001A6480;
        D_001B22A8[0] = (s32)t;
        t[0] = 0x1000000000000001UL;
        t[1] = 0xE;
        t[2] = 0x30003;
        t[3] = 0x47;
        t[4] = 0x4400000000008001UL;
        t[5] = w;
        t[6] = v;
        t[7] = 0;
        t[8] = (0x8000 - s2->h160 * 8) | ((long)(0x8000 - s2->h162 * 8) << 16);
        t[9] = (s2->h160 * 8 + 0x8000) | ((long)(s2->h162 * 8 + 0x7FF0) << 16);
    }
    D_001B22A8[0] += 0x50;
}
