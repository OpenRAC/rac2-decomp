/* func_L07_003F3E80 (1372 B). Opus closer g1, 1 November 2026: 1360/1372 bytes, profile -O2 -G8
 * -ffunction-sections, about 30 rows after normalising registers. The tuning pairs are one word $gp
 * and one word absolute: an SDATA view plus a MACRO_ADDR array read at [1], which keeps the second
 * out of delay slots as retail does.
 * Main gap: retail hoists 210000.0f into $f25 (the extra 12 bytes: one more save, restore and load
 * order) and leaves 1/60 in the loop. loop.c's test is threshold * savings * lifetime >= insn_count,
 * and a move costs 3 of threshold. A scale local at the loop top hoists it first and then 1/60 too;
 * before the loop it hoists 1/60 alone, into $f26. Retail's six earlier moves come first, so this
 * constant needs one more lifetime or the loop one or two fewer insns.
 * The cooldown is a widened post-increment; per-arm `(1/60) * -D` and `D * (1/60)` cross-jump as retail. */
#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern void func_00282C98(void *), func_00282DD8(void *, void *, void *);
extern void func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *), func_002ACE78(void *, void *, f32);
extern void func_00283958(void *, void *), func_00283738(void *, void *, void *);
extern f32 func_00282DF0(void *), func_002A78D8(f32, f32), func_002A7878(f32, f32);
extern s32 func_002A7820(s32, s32), func_00283CF0(f32), func_002761F8(void *, void *, s32, void *, void *);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282F20(void *, void *, f32), func_00282D08(void *, void *, void *, f32);
extern void *func_002C16C0(void *, void *, s32, s32, s32, s32, f32, f32, f32, f32, f32);
extern void func_002A7750(void *, s32, s32), func_0029F338(void *);
extern s32 func_002B3868(void *), func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002E5DA0(s32, s32, void *, s32);
extern s32 func_002A77E0(s32);
extern void func_L07_003F4578(u8 *);
extern void func_L00_002E6CF0(void (*)(u8 *), u8 *);
extern u8 D_L07_001BF660[];
extern f32 D_L07_001B0E3C __attribute__((sda)), D_L07_001B0E40 __attribute__((sda));
extern f32 D_L07_001B0E44 __attribute__((sda)), D_L07_001B0E48 __attribute__((sda));
extern f32 D_L07_001B0E4C __attribute__((sda));
extern s32 D_L07_001B0E50 __attribute__((sda));
extern u32 D_L07_001B0E58 __attribute__((sda));
extern s32 D_L07_001B0E70[] MACRO_ADDR;
extern s32 D_L07_001B0E70_gp SDATA(D_L07_001B0E70);
extern f32 D_L07_001B0E78[] MACRO_ADDR;
extern f32 D_L07_001B0E78_gp SDATA(D_L07_001B0E78);

void func_L07_003F3E80(u8 *object)
{
    Vector axis, up, direction;
    f32 rotation[12];
    Vector previous, displacement, origin, point, velocity;
    f32 step, magnitude, life;
    u8 *state = *(u8 **)(object + 0x68);
    s32 i, size, count;
    u32 color;
    switch (object[0x20]) {
    case 0:
        func_00282C98(&up);
        if (*(u8 **)(state + 0x20)) func_00283098(&direction, state + 0x10, *(u8 **)(state + 0x20) + 0xC0);
        else qcopy(&direction, state + 0x10);
        func_00282DD8(&axis, &up, &direction);
        func_002ACE78(&axis, &axis, D_L07_001B0E3C * 0.00029088825f);
        func_00283958(&axis, rotation);
        func_00283738(object + 0xC0, rotation, object + 0xC0);
        qcopy(&previous, object + 0x10);
        F(state, 0x18) -= F(state, 0x1C);
        if (*(u8 **)(state + 0x20)) {
            func_00282CC0(state, state, state + 0x10);
            func_00283098(object + 0x10, state, *(u8 **)(state + 0x20) + 0xC0);
            func_00282CC0(object + 0x10, object + 0x10, *(u8 **)(state + 0x20) + 0x10);
            func_00283098(&displacement, state + 0x10, *(u8 **)(state + 0x20) + 0xC0);
            func_00282CF0(&origin, object + 0x10, &displacement);
        } else {
            func_00282CC0(object + 0x10, object + 0x10, state + 0x10);
            qcopy(&displacement, state + 0x10);
            qcopy(&origin, &previous);
        }
        magnitude = func_00282DF0(&displacement);
        for (i = 0; i < D_L07_001B0E50; i++) {
            size = func_002A7820(D_L07_001B0E70_gp, D_L07_001B0E70[1]);
            count = func_00283CF0(func_002A78D8(1.0f, 2.0f));
            life = func_002A7878(D_L07_001B0E78_gp, D_L07_001B0E78[1]) * 210000.0f;
            step = magnitude;
            func_002AA2E8(&step, 0.0f, func_002A7878(2.0f, 6.0f) * (1.0f / 60.0f));
            func_00282F20(&velocity, &displacement, step);
            func_00282D08(&point, object + 0x10, &origin, func_002A7878(0.0f, 1.0f));
            color = D_L07_001B0E58;
            func_002C16C0(&point, &velocity, size, (s32)color >> 24, color & 0xFFFFFF, count,
                         life, 500.0f, 1.0f, 0.0f, 1.0f);
        }
        if (func_002761F8(&previous, object + 0x10, 2, object, 0)) {
            qcopy(object + 0x10, D_L07_001BF660);
            func_002A7750(object, 1, -1);
        } else {
            unsigned int timer = *(u16 *)(object + 0x96);
            unsigned int old = timer++;
            *(u16 *)(object + 0x96) = timer;
            if (old >= 301) func_0029F338(object);
        }
        break;
    case 1:
        if (func_002B3868(object)) {
            func_002E5DA0(4, 0, object, 0xE5F);
            F(object, 0x18) += 0.333f;
            *(u32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            F(state, 0x24) = 0.1f;
            F(state, 0x28) = 1.0f;
            if (func_002A77E0(2)) F(state, 0x30) = (1.0f / 60.0f) * -D_L07_001B0E4C;
            else F(state, 0x30) = D_L07_001B0E4C * (1.0f / 60.0f);
            F(state, 0x2C) = func_002A7878(0.0f, 1.0f);
            if (*(u8 **)(state + 0x20))
                func_002AD0E0(object, *(u8 **)(state + 0x20), object + 0x10, object + 0xF0, object + 0x10, object + 0xF0);
        }
        F(state, 0x24) += D_L07_001B0E40 * (1.0f / 60.0f);
        if (F(state, 0x24) >= D_L07_001B0E44) {
            func_002AA2E8((f32 *)(state + 0x28), 0.0f, D_L07_001B0E48 * (1.0f / 60.0f));
            if (F(state, 0x28) <= 0.0f) { func_0029F338(object); return; }
        }
        F(state, 0x2C) += F(state, 0x30);
        if (F(state, 0x2C) > 1.0f) F(state, 0x2C) -= 1.0f;
        else if (F(state, 0x2C) < 0.0f) F(state, 0x2C) += 1.0f;
        func_L00_002E6CF0(func_L07_003F4578, object);
        break;
    }
}
