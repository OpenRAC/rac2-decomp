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
extern f32 g_spin_x_rate __attribute__((sda)), g_spin_y_rate __attribute__((sda));
extern f32 g_bob_l07_amplitude __attribute__((sda)), g_rotation_base_step __attribute__((sda));
extern f32 g_rotation_step_a __attribute__((sda)), g_rotation_step_b __attribute__((sda));
extern f32 g_motion_rate __attribute__((sda)), g_motion_maximum __attribute__((sda));
extern f32 g_motion_scale __attribute__((sda)), g_turn_l07_limit __attribute__((sda));
extern f32 g_turn_accel_limit __attribute__((sda));

f32 SteerTowardTarget_pal(u8 *object)
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
    rate = g_motion_rate * (0.00040000002f);
    distance = FastVecLength(&difference);
    amount = square_root(distance * rate * 0.5f);
    maximum = g_motion_maximum;
    maximum *= (0.020000001f);
    if (maximum < amount) amount = maximum;
    if (amount < distance) vec_scale_to_length(&step, &difference, amount);
    else qcopy(&step, &difference);
    FastVecSub(&correction, &step, state + 0xC0);
    vec_clamp_length(&correction, rate);
    FastVecAdd(state + 0xC0, state + 0xC0, &correction);
    FastVecAdd(state + 0xF0, state + 0xF0, state + 0xC0);
    value = FastVecDot(object + 0xD0, state + 0xC0);
    math_step_value_toward_target((f32 *)(state + 0xE0), (f32 *)(state + 0x11C), value * g_motion_scale,
                 g_turn_l07_limit * 6.981318e-06f, g_turn_l07_limit * 6.981318e-06f,
                 g_turn_accel_limit * 0.0003490659f);
    qcopy(object + 0x10, state + 0xF0);
    qcopy(object + 0xF0, state + 0xE0);
    value = FastAddRotations(F(state, 0x100), g_rotation_base_step * 0.0003490659f);
    nextStep = g_rotation_step_a * 0.0003490659f;
    nextAngle = F(state, 0x104);
    F(state, 0x100) = value;
    value = FastAddRotations(nextAngle, nextStep);
    nextStep = g_rotation_step_b * 0.0003490659f;
    nextAngle = F(state, 0x108);
    F(state, 0x104) = value;
    F(state, 0x108) = FastAddRotations(nextAngle, nextStep);
    value = math_fast_sin_or_cos_b(F(state, 0x100)) * 0.017453294f;
    F(object, 0xF0) = FastAddRotations(F(object, 0xF0), g_spin_x_rate * value);
    value = math_fast_sin_or_cos_b(F(state, 0x104)) * 0.017453294f;
    F(object, 0xF4) = FastAddRotations(F(object, 0xF4), g_spin_y_rate * value);
    F(object, 0x18) += g_bob_l07_amplitude * math_fast_sin_or_cos_b(F(state, 0x108)) + F(state, 0x118);
    FastVecSub(&delta, object + 0x10, &oldPosition);
    mat_combine_and_store(state + 0x50, &delta, &oldRotation, object + 0xF0);
    return vec_distance_xy(state + 0xF0, &target);
}
