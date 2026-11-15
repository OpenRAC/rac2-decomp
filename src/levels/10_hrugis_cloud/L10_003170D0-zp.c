#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_001B251C[] __attribute__((sda));
extern void hrugis_beam_init(u8 *);
extern void DrawHrugisBeamEffect(u8 *);
extern void moby_l00_update_empty_3(void);
extern void *state_get_stored_pointer_value();
extern u8 *moby_get_motion_data(u8 *);
extern void level_append_object(u8 *, void *, int, int);
extern int moby_process_collision_hit(u8 *, int, int, int);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 func_00309B38(f32, f32);
extern void moby_transform_joint_point(u8 *, int, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);

/* Update of the beam moby. It starts up, then each frame it follows a joint of its target
   moby, slowly turns around its own axis and draws the beam. */
void hrugis_beam_update(u8 *moby) {
    f32 up_vector[4] __attribute__((aligned(16)));
    f32 joint_matrix[4][4] __attribute__((aligned(16)));
    f32 new_position[4] __attribute__((aligned(16)));
    f32 spin_quat[4] __attribute__((aligned(16)));
    f32 spin_matrix[12] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *forward;
    f32 *right;
    f32 angle;
    u8 *target;

    *(TI128 *)up_vector = 0;
    up_vector[2] = 1.0f;
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (state_get_stored_pointer_value() == 0) {
            return;
        }
        hrugis_beam_init(moby);
        if (*(int *)(vars + 0x268) != 0) {
            level_append_object(moby, moby_l00_update_empty_3, 0, 0);
        }
        *(f32 *)(vars + 0x27C) = math_random_angle();
        break;
    case 1:
        forward = moby + 0xC0;
        right = (f32 *)(moby + 0xD0);
        *(int *)(moby_get_motion_data(moby) + 0x14C) = 0;
        angle = func_00309B38(*(f32 *)(vars + 0x27C), 0.011635531f);
        target = D_001B251C[0] + (*(int *)(vars + 0x260) << 8);
        *(f32 *)(vars + 0x27C) = angle;
        moby_transform_joint_point(target, *(int *)(vars + 0x26C), joint_matrix);
        vec_scale_to_length(new_position, joint_matrix[1], 50.0f);
        FastVecAdd(new_position, joint_matrix[3], new_position);
        vec_scale_to_length(forward, joint_matrix[1], -1.0f);
        FastVecCross(right, forward, up_vector);
        vec_scale_to_length(right, right, 1.0f);
        FastVecCross(moby + 0xE0, right, forward);
        FastVecScale(spin_quat, forward, math_fast_sin_or_cos_b(*(f32 *)(vars + 0x27C) * 0.5f));
        spin_quat[3] = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x27C) * 0.5f);
        quaternion_to_rotation_basis(spin_quat, spin_matrix);
        multiply_matrix3x3(forward, spin_matrix, forward);
        qcopy(moby + 0x10, new_position);
        moby_process_collision_hit(moby, 0, 0, 0);
        break;
    }
    gfx_add_draw_callback_third(DrawHrugisBeamEffect, moby);
}
