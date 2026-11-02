/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Closer C3, 1 November 2026: 680/680, 5 rows, plain -O2 -G8. 0xE and 0x8000 share a2 only when 0x8000 is born at least one
 * insn after t[1]'s store dies (a gap of none conflicts in local-alloc), and sched1 issues 0x8000 in the first free ALU slot,
 * so retail has one more ALU insn in the block's first six cycles than we do. t[6] = 0x106 written in the block gives that
 * and a2 comes right, but 0x106 then ranks p24 over the la of D_001A6480 (p22): it lands before the la and takes t2, not v1.
 * Set in the earlier block it moves by update_equiv_regs after sched1, so it counts for nothing. A reused constant
 * local is cse'd away; cursor alias forms and split addresses tie or are worse.
 * Earlier: no asm fence: the tex or-chain over separate statements, D_001B22A8 as an incomplete MACRO_ADDR array read [0].
 */
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
        t[6] = 0x106;
        t[7] = 0;
        t[8] = (0x8000 - s2->h160 * 8) | ((long)(0x8000 - s2->h162 * 8) << 16);
        t[9] = (s2->h160 * 8 + 0x8000) | ((long)(s2->h162 * 8 + 0x7FF0) << 16);
    }
    D_001B22A8[0] += 0x50;
}
