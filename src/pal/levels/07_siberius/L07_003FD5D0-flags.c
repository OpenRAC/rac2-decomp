#include "include_asm.h"

#include "common.h"
extern void ship_attach_parts(void *);
extern void gfx_update_color_fade_pal(void *, void *);
extern f32 IntToFloat(s32);
extern void hud_start_overlay(s32, s32, f32);
extern s32 math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, s32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern void value_set_and_smooth_pal(void *, void *, s32, s32, f32);
extern void moby_update_eased_node(void *, void *, s32, f32, f32);
extern f32 vec_length_xy(void *);
extern void FastVecScale(void *, void *, f32);
extern f32 g_gun_muzzle_offset[4] __attribute__((sda));
extern f32 g_gun_aim_vector[4] __attribute__((sda));
extern f32 g_gun_pitch_limit __attribute__((sda));
extern f32 g_gun_aim_pitch_scale __attribute__((sda));

/* Updates a Siberius gun enemy: turns its body and head joints to face the player within limits (PAL). */
void siberius_gun_update_aim_pal(u8 *moby)
{
    f32 delta[4], position[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 angle, pitch, limit;
    if (moby[0x95] != 2) ship_attach_parts(moby);
    gfx_update_color_fade_pal(moby, vars + 0x160);
    if (moby[0x95] < 2) hud_start_overlay(6, 0, *(f32 *)(vars + 0x20) / IntToFloat(*(s16 *)(vars + 0x24)));
    (*(u16 *)(moby + 0x96))++;
    math_fast_float_d(vars + 0x42C);
    matrix_mul_vec3(position, g_gun_muzzle_offset, moby + 0xC0);
    FastVecAdd(position, position, moby + 0x10);
    FastVecSub(delta, vars + 0x140, position);
    vec_transform_by_object_or_given(moby, delta, delta, 0);
    angle = mat_fast_helper_a(delta[0], delta[1]);
    switch (moby[0x43]) { case 2: case 3: angle = fast_subtract_rotations(angle, 3.14159274f); break; }
    value_set_and_smooth_pal(moby, vars + 0x360, 2, 0, 2.5f);
    if (angle > 0.785398244f) angle = 0.785398244f;
    else if (angle < -0.785398244f) angle = -0.785398244f;
    *(f32 *)(vars + 0x3C8) = angle * 0.5f;
    moby_update_eased_node(moby, vars + 0x360, 2, 0.0432f, 0.43200004f);
    if ((u32)(moby[0x43] - 2) < 2) {
        pitch = mat_fast_helper_a(vec_length_xy(delta), delta[2]) * g_gun_aim_pitch_scale;
        limit = g_gun_pitch_limit * 0.0174532942f;
        if (pitch > limit) pitch = limit;
        else if (pitch < -limit) pitch = -limit;
        FastVecScale(vars + 0x340, g_gun_aim_vector, pitch);
        *(f32 *)(vars + 0x2C8) = angle * 0.5f;
    }
    moby_update_eased_node(moby, vars + 0x2E0, 3, 0.0432f, 0.43200004f);
    moby_update_eased_node(moby, vars + 0x260, 1, 0.0432f, 0.43200004f);
}
