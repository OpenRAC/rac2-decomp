#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern s32 func_002AD0B0(u8 *);
extern void func_00282CC0(void *, void *, void *), func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, f32);
extern f32 func_00282DF0(void *), func_00282C10(f32), func_00282DB0(void *, void *);
extern void func_002AC9F8(void *, f32), func_002AD6F0(void *, void *, void *, void *);
extern f32 func_002AA548(f32 *, f32 *, f32, f32, f32, f32);
extern f32 func_00283B98(f32, f32), func_00283198(f32), func_00282E80(void *, void *);
extern f32 D_L07_001B0C60 __attribute__((sda)), D_L07_001B0C64 __attribute__((sda));
extern f32 D_L07_001B0C68 __attribute__((sda)), D_L07_001B0C6C __attribute__((sda));
extern f32 D_L07_001B0C70 __attribute__((sda)), D_L07_001B0C74 __attribute__((sda));
extern f32 D_L07_001B0C78 __attribute__((sda)), D_L07_001B0C7C __attribute__((sda));
extern f32 D_L07_001B0C80 __attribute__((sda)), D_L07_001B0C84 __attribute__((sda));
extern f32 D_L07_001B0C88 __attribute__((sda));

f32 func_L07_003EEE28(u8 *object)
{
    Vector oldPosition, oldRotation, target, difference, step, correction, delta;
    u8 *state = *(u8 **)(object + 0x68), *support;
    f32 rate, distance, amount, maximum, value, nextAngle, nextStep;
    qcopy(&oldPosition, object + 0x10);
    qcopy(&oldRotation, object + 0xF0);
    support = *(u8 **)(state + 0x110);
    if (support) {
        func_00282CC0(state + 0xF0, state + 0xF0, (u8 *)func_002AD0B0(support) + 0x10);
        func_00283098(&target, state + 0xD0, *(u8 **)(state + 0x110) + 0xC0);
        func_00282CC0(&target, &target, *(u8 **)(state + 0x110) + 0x10);
        F(state, 0xE8) = F(*(u8 **)(state + 0x110), 0xF8);
    } else qcopy(&target, state + 0xD0);
    func_00282CF0(&difference, &target, state + 0xF0);
    rate = D_L07_001B0C78 * (1.0f / 3600.0f);
    distance = func_00282DF0(&difference);
    amount = func_00282C10(distance * rate * 0.5f);
    maximum = D_L07_001B0C7C;
    maximum *= (1.0f / 60.0f);
    if (maximum < amount) amount = maximum;
    if (amount < distance) func_00282F20(&step, &difference, amount);
    else qcopy(&step, &difference);
    func_00282CF0(&correction, &step, state + 0xC0);
    func_002AC9F8(&correction, rate);
    func_00282CC0(state + 0xC0, state + 0xC0, &correction);
    func_00282CC0(state + 0xF0, state + 0xF0, state + 0xC0);
    value = func_00282DB0(object + 0xD0, state + 0xC0);
    func_002AA548((f32 *)(state + 0xE0), (f32 *)(state + 0x11C), value * D_L07_001B0C80,
                 D_L07_001B0C84 * 0.0000048481374f, D_L07_001B0C84 * 0.0000048481374f,
                 D_L07_001B0C88 * 0.00029088825f);
    qcopy(object + 0x10, state + 0xF0);
    qcopy(object + 0xF0, state + 0xE0);
    value = func_00283B98(F(state, 0x100), D_L07_001B0C6C * 0.00029088825f);
    nextStep = D_L07_001B0C70 * 0.00029088825f;
    nextAngle = F(state, 0x104);
    F(state, 0x100) = value;
    value = func_00283B98(nextAngle, nextStep);
    nextStep = D_L07_001B0C74 * 0.00029088825f;
    nextAngle = F(state, 0x108);
    F(state, 0x104) = value;
    F(state, 0x108) = func_00283B98(nextAngle, nextStep);
    value = func_00283198(F(state, 0x100)) * 0.017453294f;
    F(object, 0xF0) = func_00283B98(F(object, 0xF0), D_L07_001B0C60 * value);
    value = func_00283198(F(state, 0x104)) * 0.017453294f;
    F(object, 0xF4) = func_00283B98(F(object, 0xF4), D_L07_001B0C64 * value);
    F(object, 0x18) += D_L07_001B0C68 * func_00283198(F(state, 0x108)) + F(state, 0x118);
    func_00282CF0(&delta, object + 0x10, &oldPosition);
    func_002AD6F0(state + 0x50, &delta, &oldRotation, object + 0xF0);
    return func_00282E80(state + 0xF0, &target);
}
