/* func_L07_003F3E80 (1372 B). Opus xhigh v2090, 3 November 2026: 1368/1372 bytes, 0/1 places.
 * Tier: build in the -G8 unit L07_00389EB8-g8.c (-O2 -G8 -ffunction-sections); that unit already
 * declares func_0029F338(int), so drop that extern there. Needs the sda/MACRO_ADDR/SDATA externs below.
 * Case 0 (the whole particle loop) now matches: `speed` as a Vector (BLK stack MEM) passed as speed.f
 * is not copied to a pseudo by precompute_register_parameters (an ADDRESSOF f32 was: MEM cost 6 > 2),
 * so loop pass 2 counts 61 insns and hoists 210000.0f into $f25 like retail. Case-1 stores order
 * 0x98, 0x34, then 0x18 as retail.
 * Remaining 4 bytes, all case 1: (a) retail's func_002A77E0 then-arm is mult(C=1/60 in f1, -D in f0)
 * and its else-arm reloads D (lwc1 f1) before mult(D, C); here both arms fold to X*C and the else-arm
 * D load is deleted as redundant with the delay-slot load (fold/cse swap REAL_CST to the second
 * operand, so no plain source keeps C first). (b) retail loads D_L07_001B0E44 above the 0x24 store and
 * keeps 1/60 in f3; F() casts are not MEM_IN_STRUCT_P, so try struct-member accesses on `state`. */
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
extern void func_002A7750(void *, s32, s32), func_0029F338(int);
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
    Vector previous, displacement, origin, point, velocity, speed;
    f32 magnitude, life;
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
            speed.f[0] = magnitude;
            func_002AA2E8(speed.f, 0.0f, func_002A7878(2.0f, 6.0f) * (1.0f / 60.0f));
            func_00282F20(&velocity, &displacement, speed.f[0]);
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
            if (old >= 301) func_0029F338((int)object);
        }
        break;
    case 1:
        if (func_002B3868(object)) {
            func_002E5DA0(4, 0, object, 0xE5F);
            *(u32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            F(object, 0x18) += 0.333f;
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
            if (F(state, 0x28) <= 0.0f) { func_0029F338((int)object); return; }
        }
        F(state, 0x2C) += F(state, 0x30);
        if (F(state, 0x2C) > 1.0f) F(state, 0x2C) -= 1.0f;
        else if (F(state, 0x2C) < 0.0f) F(state, 0x2C) += 1.0f;
        func_L00_002E6CF0(func_L07_003F4578, object);
        break;
    }
}
