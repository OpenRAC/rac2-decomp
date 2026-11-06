/* func_L03_0041DAD0, USA v1.01, level 03. Near miss, 528/528 bytes, 0/1, 7 rows.
 * Profile: -O2 -G8 -ffunction-sections, in its own unit (e.g. src/levels/03_endako/L03_0041DAD0-g8.c).
 * 6 November 2026: the three globals are plain again (the earlier `const` on two of them was an
 * experiment, not evidence), and the three rate stores go through a struct view of the state, so
 * they are MEM_IN_STRUCT and no longer anti-depend on the $gp loads. Written as three direct
 * products in store order, every instruction is in retail's place; left is one register swap:
 * retail gives the first load (D_L03_001B1BC0) $f3 and the 1/60 constant $f2, this gives the
 * load $f2 and the constant $f3 (+0x16C, +0x180, +0x1AC..+0x1C8). Tried on the current compiler
 * without improving on that: the previous load-locals form (9 rows with the struct view), products
 * through m1..m3 locals in store order (9), and the globals as one float[3] (over -G8, so they
 * leave $gp). Reopen with a source shape that changes the local-alloc order of the first load and
 * the 1/60 constant.
 * Earlier notes (superseded where inconsistent):
 *  opus-1 near miss (func_L03_0041DAD0), USA v1.01, level 03.
 * Profile: -O2 -G8 -ffunction-sections, in its own unit (e.g. src/levels/03_endako/L03_0041DAD0-g8.c);
 * it reaches D_L03_001B1BC0..C8 through $gp. func_L03_0041E240 is in L03_003F09C0-g8.c (extern here).
 * Best check.py: 528/528 bytes, 0/1 places, 8 instructions differ: every register and every
 * other instruction now agrees; only the li.s of 0.00027777778 (lui/ori/mtc1 $f4) is scheduled
 * after the D_L03_001B1BC0 load instead of after the D_L03_001B1BC8 load (+0x188..+0x1A0).
 * With all three globals plain (the previous draft) 11 instructions differ: the float registers
 * of the three loads and two constants, product and store order.
 * Analysis (sched dumps plus a local-alloc model): retail's registers need the constant to be
 * born early in sched1 (before the second load), so that local-alloc ranks it last; with the
 * three loads plain, every store anti-depends on them (4 dependents each, versus 2 for the
 * constant) and sched1 puts the three loads first. Declaring D_L03_001B1BC4/C8 const (unchanging
 * MEMs, no anti-dependence) gives the retail registers, but then sched2 keeps the constant
 * early, while retail's sched2 put the loads first (as plain loads would). The const on two of
 * the three externs is an experiment, not evidence; the retail ordering needs a different
 * dependence picture in sched1 than in sched2. Tried without effect: -fno-sched-interblock,
 * direct stores (they serialize load/mul/store), other load/product/store orders. 
 */
#include "common.h"
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern float D_L03_001B1BC0 __attribute__((sda));
extern float D_L03_001B1BC4 __attribute__((sda));
extern float D_L03_001B1BC8 __attribute__((sda));
extern u8 D_L03_001B9980[];
extern void func_0029F338(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002A93B0(void *);
extern float func_00282E48(void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern void func_L03_0041E240(u8 *);

typedef struct { u8 pad[0x120]; f32 rate[3]; } RateView;

void func_L03_0041DAD0(u8 *self) {
    u8 *st = *(u8 **)(self + 0x68);
    f32 ga, gb, gc, m1, m2, m3;

    if (self[0x20] == 0) {
        st[0x48] = func_00283CF0(20.0f);
        st[0x4A] = func_00283CF0(14.399999618530273f);
        st[0x60] = 7;
        *(f32 *)(st + 0x8C) = 0.4000000059604645f;
        *(s32 *)(st + 0x98) = 3;
        *(f32 *)(st + 0x80) = 0.5f;
        *(f32 *)(st + 0x84) = 0.5f;
        *(f32 *)(st + 0x90) = *(f32 *)(self + 0x18) - 2.0f;
        *(s32 *)(st + 0x138) |= 0x15;
        *(f32 *)(st + 0x134) = 0.05000000074505806f;
        *(f32 *)(st + 0x104) = 0.25f;
        *(f32 *)(st + 0x100) = 0.5f;
        *(f32 *)(st + 0x108) = 0.75f;
        *(f32 *)(st + 0x10C) = 0.75f;
        *(f32 *)(st + 0x110) = 0.7853982448577881f;
        *(f32 *)(st + 0x130) = 0.523598849773407f;
        st[0x28] = 3;
        *(s32 *)(st + 0x1D8) = -1;
        *(s32 *)(st + 0x350) = -1;
        if (*(s32 *)(st + 0x210) == -1) {
            func_0029F338(self);
            return;
        }
        func_002A7750(self, 1, 0);
        if (self[0x43] != 0)
            func_002A7470(self, 0, 0, 0);
    }
    if (self[0x31] != 0) {
        if (func_00282E48(self + 0x10, D_L03_001B9980) < 48.0f) {
            func_002A93B0(self);
            self[0x6F] = 0x2D;
        }
    }
    ((RateView *)st)->rate[0] = D_L03_001B1BC4 * 0.00027777778450399637f;
    ((RateView *)st)->rate[1] = D_L03_001B1BC8 * 0.00027777778450399637f;
    ((RateView *)st)->rate[2] = D_L03_001B1BC0 * 0.01666666753590107f;
    if (func_002B0ED8(self, st + 0x50, 0))
        func_L03_0041E240(self);
    func_002B3BA8(self, *(s32 *)(st + 0x214), 0, 0, 16.0f, 0.0f);
}
