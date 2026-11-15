#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_001B251C[] __attribute__((sda));
extern void func_PAL_L10_003FA370(u8 *);
extern void DrawHrugisBeamEffect(u8 *);
extern void moby_l00_update_empty_2(void);
extern void *state_get_stored_pointer_value();
extern u8 *moby_get_motion_data(u8 *);
extern void level_append_object(u8 *, void *, int, int);
extern int moby_process_collision_hit(u8 *, int, int, int);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 FastAddRotations(f32, f32);
extern void moby_transform_joint_point(u8 *, int, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);

void func_PAL_L10_003FA158(u8 *a0) {
    f32 v0[4] __attribute__((aligned(16)));
    f32 a[4][4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    f32 e[4] __attribute__((aligned(16)));
    f32 q[12] __attribute__((aligned(16)));
    u8 *s5 = *(u8 **)(a0 + 0x68);
    u8 *s3;
    f32 *s1;
    f32 ang;
    u8 *obj;

    *(TI128 *)v0 = 0;
    v0[2] = 1.0f;
    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        if (state_get_stored_pointer_value() == 0) {
            return;
        }
        func_PAL_L10_003FA370(a0);
        if (*(int *)(s5 + 0x268) != 0) {
            level_append_object(a0, moby_l00_update_empty_2, 0, 0);
        }
        *(f32 *)(s5 + 0x27C) = math_random_angle();
        break;
    case 1:
        s3 = a0 + 0xC0;
        s1 = (f32 *)(a0 + 0xD0);
        *(int *)(moby_get_motion_data(a0) + 0x14C) = 0;
        ang = FastAddRotations(*(f32 *)(s5 + 0x27C), 0.013962637f);
        obj = D_001B251C[0] + (*(int *)(s5 + 0x260) << 8);
        *(f32 *)(s5 + 0x27C) = ang;
        moby_transform_joint_point(obj, *(int *)(s5 + 0x26C), a);
        vec_scale_to_length(d, a[1], 50.0f);
        FastVecAdd(d, a[3], d);
        vec_scale_to_length(s3, a[1], -1.0f);
        FastVecCross(s1, s3, v0);
        vec_scale_to_length(s1, s1, 1.0f);
        FastVecCross(a0 + 0xE0, s1, s3);
        FastVecScale(e, s3, math_fast_sin_or_cos_b(*(f32 *)(s5 + 0x27C) * 0.5f));
        e[3] = math_fast_sin_or_cos_a(*(f32 *)(s5 + 0x27C) * 0.5f);
        quaternion_to_rotation_basis(e, q);
        multiply_matrix3x3(s3, q, s3);
        qcopy(a0 + 0x10, d);
        moby_process_collision_hit(a0, 0, 0, 0);
        break;
    }
    gfx_add_draw_callback_third(DrawHrugisBeamEffect, a0);
}
