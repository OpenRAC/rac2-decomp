#include "common.h"

/* func_L07_003F3E80 needs -frac2-hazard-labels with -G8: retail keeps the case-1 join label on the
   mtc1 -> mul.s hazard nop. The two phase-step arms write one local; jump2 then cross-jumps their
   commutative-equal multiplies. */
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
extern int func_002E5DA0(s32, s32, void *, s32);
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

/* The state block at object + 0x68; only the fields this function touches are named. */
typedef struct {
    f32 position[4];
    f32 direction[4];
    u8 *attachment;
    f32 growth, strength, phase, phase_step;
} SiberiusTrailState;

void func_L07_003F3E80(u8 *object)
{
    Vector axis, up, direction;
    f32 rotation[12];
    Vector previous, displacement, origin, point, velocity, speed;
    f32 magnitude, life, step;
    SiberiusTrailState *trail = *(SiberiusTrailState **)(object + 0x68);
    s32 i, size, count;
    u32 color;
    switch (object[0x20]) {
    case 0:
        func_00282C98(&up);
        if (trail->attachment) func_00283098(&direction, trail->direction, trail->attachment + 0xC0);
        else qcopy(&direction, trail->direction);
        func_00282DD8(&axis, &up, &direction);
        func_002ACE78(&axis, &axis, D_L07_001B0E3C * 0.00029088825f);
        func_00283958(&axis, rotation);
        func_00283738(object + 0xC0, rotation, object + 0xC0);
        qcopy(&previous, object + 0x10);
        trail->direction[2] -= trail->direction[3];
        if (trail->attachment) {
            func_00282CC0(trail->position, trail->position, trail->direction);
            func_00283098(object + 0x10, trail->position, trail->attachment + 0xC0);
            func_00282CC0(object + 0x10, object + 0x10, trail->attachment + 0x10);
            func_00283098(&displacement, trail->direction, trail->attachment + 0xC0);
            func_00282CF0(&origin, object + 0x10, &displacement);
        } else {
            func_00282CC0(object + 0x10, object + 0x10, trail->direction);
            qcopy(&displacement, trail->direction);
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
            *(f32 *)(object + 0x18) += 0.333f;
            trail->growth = 0.1f;
            trail->strength = 1.0f;
            if (func_002A77E0(2)) step = -D_L07_001B0E4C * (1.0f / 60.0f);
            else step = D_L07_001B0E4C * (1.0f / 60.0f);
            trail->phase_step = step;
            trail->phase = func_002A7878(0.0f, 1.0f);
        }
        if (trail->attachment)
            func_002AD0E0(object, trail->attachment, object + 0x10, object + 0xF0, object + 0x10, object + 0xF0);
        trail->growth += D_L07_001B0E40 * (1.0f / 60.0f);
        if (trail->growth >= D_L07_001B0E44) {
            func_002AA2E8(&trail->strength, 0.0f, D_L07_001B0E48 * (1.0f / 60.0f));
            if (trail->strength <= 0.0f) { func_0029F338((int)object); return; }
        }
        trail->phase += trail->phase_step;
        if (trail->phase > 1.0f) trail->phase -= 1.0f;
        else if (trail->phase < 0.0f) trail->phase += 1.0f;
        func_L00_002E6CF0(func_L07_003F4578, object);
        break;
    }
}
