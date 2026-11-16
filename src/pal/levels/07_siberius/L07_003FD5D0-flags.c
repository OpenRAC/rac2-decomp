#include "include_asm.h"

#include "common.h"
extern void ship_attach_parts(void *);
extern void func_PAL_002AC3C0(void *, void *);
extern f32 IntToFloat(s32);
extern void hud_start_overlay(s32, s32, f32);
extern s32 math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, s32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern void func_PAL_002B14F8(void *, void *, s32, s32, f32);
extern void moby_update_eased_node(void *, void *, s32, f32, f32);
extern f32 vec_length_xy(void *);
extern void FastVecScale(void *, void *, f32);
extern f32 g_gun_muzzle_offset[4] __attribute__((sda));
extern f32 g_gun_aim_vector[4] __attribute__((sda));
extern f32 g_gun_pitch_limit __attribute__((sda));
extern f32 g_gun_aim_pitch_scale __attribute__((sda));

void siberius_gun_update_aim_pal(u8 *obj)
{
    f32 delta[4], pos[4];
    u8 *state = *(u8 **)(obj + 0x68);
    f32 angle, pitch, limit;
    if (obj[0x95] != 2) ship_attach_parts(obj);
    func_PAL_002AC3C0(obj, state + 0x160);
    if (obj[0x95] < 2) hud_start_overlay(6, 0, *(f32 *)(state + 0x20) / IntToFloat(*(s16 *)(state + 0x24)));
    (*(u16 *)(obj + 0x96))++;
    math_fast_float_d(state + 0x42C);
    matrix_mul_vec3(pos, g_gun_muzzle_offset, obj + 0xC0);
    FastVecAdd(pos, pos, obj + 0x10);
    FastVecSub(delta, state + 0x140, pos);
    vec_transform_by_object_or_given(obj, delta, delta, 0);
    angle = mat_fast_helper_a(delta[0], delta[1]);
    switch (obj[0x43]) { case 2: case 3: angle = fast_subtract_rotations(angle, 3.14159274f); break; }
    func_PAL_002B14F8(obj, state + 0x360, 2, 0, 2.5f);
    if (angle > 0.785398244f) angle = 0.785398244f;
    else if (angle < -0.785398244f) angle = -0.785398244f;
    *(f32 *)(state + 0x3C8) = angle * 0.5f;
    moby_update_eased_node(obj, state + 0x360, 2, 0.0432f, 0.43200004f);
    if ((u32)(obj[0x43] - 2) < 2) {
        pitch = mat_fast_helper_a(vec_length_xy(delta), delta[2]) * g_gun_aim_pitch_scale;
        limit = g_gun_pitch_limit * 0.0174532942f;
        if (pitch > limit) pitch = limit;
        else if (pitch < -limit) pitch = -limit;
        FastVecScale(state + 0x340, g_gun_aim_vector, pitch);
        *(f32 *)(state + 0x2C8) = angle * 0.5f;
    }
    moby_update_eased_node(obj, state + 0x2E0, 3, 0.0432f, 0.43200004f);
    moby_update_eased_node(obj, state + 0x260, 1, 0.0432f, 0.43200004f);
}
