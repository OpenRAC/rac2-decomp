#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern char *moby_get_private_value_2(u8 *);
extern void FastVecAdd(void *, void *, void *), matrix_mul_vec3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, f32);
extern f32 FastVecLength(void *), square_root(f32), FastVecDot(void *, void *);
extern void vec_clamp_length(void *, f32), mat_combine_and_store(void *, void *, void *, void *);
extern f32 math_step_value_toward_target(f32 *, f32 *, f32, f32, f32, f32);
extern f32 FastAddRotations(f32, f32), math_fast_sin_or_cos_b(f32), vec_distance_xy(void *, void *);
extern f32 D_L07_001B0C60 __attribute__((sda)), D_L07_001B0C64 __attribute__((sda));
extern f32 D_L07_001B0C68 __attribute__((sda)), D_L07_001B0C6C __attribute__((sda));
extern f32 D_L07_001B0C70 __attribute__((sda)), D_L07_001B0C74 __attribute__((sda));
extern f32 D_L07_001B0C78 __attribute__((sda)), D_L07_001B0C7C __attribute__((sda));
extern f32 D_L07_001B0C80 __attribute__((sda)), D_L07_001B0C84 __attribute__((sda));
extern f32 D_L07_001B0C88 __attribute__((sda));

f32 func_PAL_L07_003F3290(u8 *object)
{
    Vector oldPosition, oldRotation, target, difference, step, correction, delta;
    u8 *state = *(u8 **)(object + 0x68), *support;
    f32 rate, distance, amount, maximum, value, nextAngle, nextStep;
    qcopy(&oldPosition, object + 0x10);
    qcopy(&oldRotation, object + 0xF0);
    support = *(u8 **)(state + 0x110);
    if (support) {
        FastVecAdd(state + 0xF0, state + 0xF0, (u8 *)moby_get_private_value_2(support) + 0x10);
        matrix_mul_vec3(&target, state + 0xD0, *(u8 **)(state + 0x110) + 0xC0);
        FastVecAdd(&target, &target, *(u8 **)(state + 0x110) + 0x10);
        F(state, 0xE8) = F(*(u8 **)(state + 0x110), 0xF8);
    } else qcopy(&target, state + 0xD0);
    FastVecSub(&difference, &target, state + 0xF0);
    rate = D_L07_001B0C78 * (0.00040000002f);
    distance = FastVecLength(&difference);
    amount = square_root(distance * rate * 0.5f);
    maximum = D_L07_001B0C7C;
    maximum *= (0.020000001f);
    if (maximum < amount) amount = maximum;
    if (amount < distance) vec_scale_to_length(&step, &difference, amount);
    else qcopy(&step, &difference);
    FastVecSub(&correction, &step, state + 0xC0);
    vec_clamp_length(&correction, rate);
    FastVecAdd(state + 0xC0, state + 0xC0, &correction);
    FastVecAdd(state + 0xF0, state + 0xF0, state + 0xC0);
    value = FastVecDot(object + 0xD0, state + 0xC0);
    math_step_value_toward_target((f32 *)(state + 0xE0), (f32 *)(state + 0x11C), value * D_L07_001B0C80,
                 D_L07_001B0C84 * 6.981318e-06f, D_L07_001B0C84 * 6.981318e-06f,
                 D_L07_001B0C88 * 0.0003490659f);
    qcopy(object + 0x10, state + 0xF0);
    qcopy(object + 0xF0, state + 0xE0);
    value = FastAddRotations(F(state, 0x100), D_L07_001B0C6C * 0.0003490659f);
    nextStep = D_L07_001B0C70 * 0.0003490659f;
    nextAngle = F(state, 0x104);
    F(state, 0x100) = value;
    value = FastAddRotations(nextAngle, nextStep);
    nextStep = D_L07_001B0C74 * 0.0003490659f;
    nextAngle = F(state, 0x108);
    F(state, 0x104) = value;
    F(state, 0x108) = FastAddRotations(nextAngle, nextStep);
    value = math_fast_sin_or_cos_b(F(state, 0x100)) * 0.017453294f;
    F(object, 0xF0) = FastAddRotations(F(object, 0xF0), D_L07_001B0C60 * value);
    value = math_fast_sin_or_cos_b(F(state, 0x104)) * 0.017453294f;
    F(object, 0xF4) = FastAddRotations(F(object, 0xF4), D_L07_001B0C64 * value);
    F(object, 0x18) += D_L07_001B0C68 * math_fast_sin_or_cos_b(F(state, 0x108)) + F(state, 0x118);
    FastVecSub(&delta, object + 0x10, &oldPosition);
    mat_combine_and_store(state + 0x50, &delta, &oldRotation, object + 0xF0);
    return vec_distance_xy(state + 0xF0, &target);
}
