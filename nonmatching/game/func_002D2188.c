/* 2 November 2026, remaining-function review: nonmatching; no linked credit.
 * Profile: -O2 -G8 -fno-expensive-optimizations -ffunction-sections -fno-builtin.
 * US check: 580/592 bytes, 0/28 placements.
 * Matched0027FAA8 returns signed int. Correcting the ignored text-draw result ties at 580/592,0/28. Missing retail unused saved s1/0x30 frame and FP rounding lifetimes remain.
 */
/*
 * v1665 (Claude Opus 5.5, xhigh, 30 October 2026): 580/592 bytes, 0/28 USA v1.01 places.
 * Profile: -O2 -G8 -fno-expensive-optimizations -ffunction-sections -fno-builtin, as func_002D1E70.
 * Build it as its own unit. MACRO_ADDR on D_001ABD68 gives retail's table sequence exactly.
 *
 * Blocker: retail saves $s1 and never uses it (frame 0x30), the size gap apart from one word. A
 * boot scan finds 8 functions saving a GPR they never touch. Three are libgcc unwinder routines;
 * of the other five, four contain cvt.w.s (func_002D2188, func_002D3FA0, func_00326A10,
 * func_0032F3D0) against 84 of 3,126 boot functions overall; func_0034A4E0 does not. Suspect, not
 * proven: fix_truncsfsi2 clobbers an SI match_scratch its R5900 template never prints, so a reload
 * register can be marked live with no visible use. This cc1 gives that scratch $v0 (.greg:
 * "Spilling reg 2"), so reproducing $s1 may need a compiler-side answer, not a C spelling.
 *
 * Also different: retail's rounding chains are serial (scale $f1, 0.5 $f2, $f0 reused, scratch $f3
 * then $f1). One float variable alone gives $f4/$f1 as cvt.w.s scratch, and with a hoisted `half`
 * $f3/$f1 as in retail, but neither reproduces its scale/constant order.
 * The sltu order before func_002CE5D0 and the ori/mov.s order at the third draw differ although
 * func_002D1E70 matches with the same source; calls do not end a block here, so these may follow
 * from the prologue. Not a fix: a shared colour local (folded), an inline rounding helper (tie),
 * a hoisted `half` local ($f21, 588 bytes), scheduler-off profiles ($f21, wrong order).
 */
#include "common.h"

extern void func_0027C540(s32);
extern void func_0027C660(void);
extern s32 func_0027FAA8(s32, s32, u64, s32, s32);
extern s32 func_00288FB8(s32);
extern void func_0028FC48(s32, s32, s32, s32, u64, s32);
extern void func_002CE5D0(s32, s32);
extern void func_00300A00(s32, s32, f32, f32, f32, f32, f32);
extern s32 func_00336D50(s32, s32);
extern s32 D_001A8CFC;
extern s32 D_001A7340;
extern f32 D_001B23A8;
extern f32 D_001B23A4;
extern s32 D_001ABA6C __attribute__((sda));
extern s32 D_001ABA68 __attribute__((sda));
extern struct { s16 text; s16 reserved; } D_001ABD68[] MACRO_ADDR;

s32 func_002D2188(void) {
    f32 z;
    s32 r;
    s32 center;

    func_0027C540(0);
    z = 0.0f;
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDE);
    func_00300A00(r, 0x60442D00, (f32)(D_001A7340 / 2), (f32)D_001ABA6C, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDF);
    func_00300A00(r, 0x60241700, (f32)(D_001A7340 / 2), (f32)D_001ABA6C, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xE0);
    func_00300A00(r, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)D_001ABA6C, 1.0f, D_001B23A8, z);
    func_002CE5D0(D_001ABA68 != 0, D_001ABA68 != 5);
    func_0028FC48(66, (s32)(D_001B23A4 * 330.0f + 0.5f), 463, (s32)(D_001B23A4 * 332.0f + 0.5f), 0x55F0C070, 0);
    center = D_001A7340 / 2;
    func_0027FAA8(center, 311, (u64)0x80F0F0F0, func_00288FB8(D_001ABD68[D_001ABA68].text), -1);
    func_0027FAA8(0x1B0, 0x177, (u64)0x80F0F0F0, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
