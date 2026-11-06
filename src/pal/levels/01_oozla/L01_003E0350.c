#include "include_asm.h"
#include "common.h"

/* func_PAL_L01_003E0710, the PAL copy of func_L01_003DC078: the same C, where speeds and
   accelerations grow by 6/5, and particle lifetimes take (x * 5 + 2) / 6 for 50 Hz. */
extern f32 func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern s32 func_002A8C28(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 func_L01_003120A8(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern f32 func_002A7878(f32, f32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283B98(f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern void func_002AF000(void *, f32, f32, f32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32);
extern u8 *func_002BAA28(void *, void *, void *, u32, u32, s32, s32, s32, s32);

void func_PAL_L01_003E0710(u8 *obj, s32 skip) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 end[4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    f32 acceleration[4] __attribute__((aligned(16)));
    f32 particlePos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 angle, yaw, distance, height;
    u8 *particle;

    distance = func_00282E80(obj + 0x10, *(u8 **)(state + 0x2F0) + 0x10);
    height = *(f32 *)(*(u8 **)(state + 0x2F0) + 0x18) - *(f32 *)(obj + 0x18);
    angle = func_00283BE0(func_00283248(distance, height), *(f32 *)(obj + 0xF4));
    if (angle > 0.3490659f) angle = 0.3490659f;
    else if (angle < -0.3490659f) angle = -0.3490659f;
    angle = func_00283B98(angle, *(f32 *)(obj + 0xF4));
    yaw = *(f32 *)(obj + 0xF8);

    func_0029FCC0(obj, 0, pos);
    func_00282F20(tmp, obj + 0xC0, -0.4f);
    func_00282CC0(pos, pos, tmp);
    func_00282F20(tmp, obj + 0xE0, 0.3f);
    func_00282CC0(pos, pos, tmp);

    if (*(s16 *)(*(u8 **)(state + 0x2F0) + 0xAA) == 0xB1A) {
        func_002A8C28(obj, pos, 1.0f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
        return;
    }

    particle = *(u8 **)(state + 0x3F0);
    if (particle) {
        if (particle[0] == 2 && particle[1] != 0x80) {
            distance = func_00282E80(pos, particle + 0x10);
            if (*(f32 *)(state + 0x3F4) < distance) *(f32 *)(state + 0x3F4) = distance;
        } else {
            *(u8 **)(state + 0x3F0) = 0;
            *(f32 *)(state + 0x3F4) = 3.0f;
        }
        func_002AF000(end, *(f32 *)(state + 0x3F4), yaw, angle);
        func_00282CC0(end, end, pos);
        func_L01_003120A8(obj, pos, end, (f32)state[0x34], 0x4000001, 1.0f, 0, 1, 0);
        func_002A8C28(obj, end, 0.3f, 0x4000001, (f32)state[0x34], 1.0f, 0, 1, 0);
    }
    if (skip) return;

    {
        s32 i, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned;

        velocity[3] = 0.2f;
        acceleration[3] = 1.0f;
        for (i = 0; i < 2; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x50608040;
            color2 = 0x10608040;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x30304020;
                color2 = 0x30304020;
            }
            qcopy(particlePos, pos);
            particlePos[0] += func_002A7878(-0.18f, 0.18f);
            particlePos[1] += func_002A7878(-0.18f, 0.18f);
            particlePos[2] += func_002A7878(-0.18f, 0.18f);
            func_002AF000(velocity, 0.18f, yaw, angle);
            velocity[2] += func_002A7878(0.009000001f, 0.011000001f);
            func_002AF000(acceleration, 0.010000001f,
                          func_00283B98(yaw, func_002A7878(-9.0f, 9.0f) * 0.017453294f), angle);
            acceleration[2] += func_002A7878(-0.036000002f, -0.044000003f);
            life = func_00283CF0((func_002A7878(2.0f, 4.0f) * 5.0f + 2.0f) * 0.16666667f);
            size = func_00283CF0((func_002A7878(20.0f, 24.0f) * 5.0f + 2.0f) * 0.16666667f);
            duration = func_00283CF0((func_002A7878(30.0f, 36.0f) * 5.0f + 2.0f) * 0.16666667f);
            spawned = func_002BAA28(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned) {
                if (!*(u8 **)(state + 0x3F0)) *(u8 **)(state + 0x3F0) = spawned;
                if (variant) spawned[3] = 0x48;
            }
        }
    }
    {
        s32 i, variant, life, size, duration;
        u32 color1, color2;
        u8 *spawned = 0;

        velocity[3] = 0.05f;
        acceleration[3] = 0.09f;
        for (i = 0; i < 3; i++) {
            variant = func_001163B0() & 1;
            color1 = 0x8050FF30;
            color2 = 0x3050FF30;
            if (!variant && (func_001163B0() & 1)) {
                color1 = 0x80306000;
                color2 = 0x30304000;
            }
            qcopy(particlePos, pos);
            particlePos[0] += func_002A7878(-0.24f, 0.24f);
            particlePos[1] += func_002A7878(-0.24f, 0.24f);
            particlePos[2] += func_002A7878(-0.24f, 0.24f);
            func_002AF000(velocity, 0.20000002f,
                          func_00283B98(yaw, func_002A7878(-18.0f, 18.0f) * 0.017453294f), angle);
            velocity[2] += func_002A7878(0.007f, 0.015000001f);
            func_002AF000(acceleration, 0.010000001f,
                          func_00283B98(yaw, func_002A7878(-4.0f, 4.0f) * 0.017453294f), angle);
            acceleration[2] += func_002A7878(-0.016800001f, -0.036000002f);
            life = func_00283CF0((func_002A7878(2.0f, 4.0f) * 5.0f + 2.0f) * 0.16666667f);
            size = func_00283CF0((func_002A7878(20.0f, 24.0f) * 5.0f + 2.0f) * 0.16666667f);
            duration = func_00283CF0((func_002A7878(100.0f, 120.00001f) * 5.0f + 2.0f) * 0.16666667f);
            spawned = func_002BAA28(particlePos, velocity, acceleration, color1, color2,
                                    life, size, duration, -1);
            if (spawned && variant) spawned[3] = 0x48;
        }
    }
}
