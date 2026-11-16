#include "include_asm.h"
#include "names.h"

extern float g_spinning_moby_rot_rate __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float fast_subtract_rotations(float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_draw_beam_effect_passes(int);

/* Rebuilds the record's second frame and folds the resident angle step in. */
void moby_update_spinning_frame_orientation_pal(char *moby) {
    float buf[4];
    char *vars = *(char **)(moby + 0x68);
    char *moby_pos = moby + 0x10;
    char *vars_pos = vars + 0x10;

    vec_scale_to_length(buf, vars + 0x40, 1.0f);
    math_build_axis_angle_quat(buf, buf, *(float *)(vars + 0x30));
    FastVecScale(vars_pos, vars, *(float *)(vars + 0x60));
    vec_rotate_by_quaternion(vars_pos, vars_pos, buf);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    FastVecAdd(vars_pos, moby_pos, vars_pos);
    FastVecAdd(vars + 0x20, moby_pos, vars + 0x20);
    *(float *)(vars + 0x30) =
        fast_subtract_rotations(*(float *)(vars + 0x30), g_spinning_moby_rot_rate * 0.0003490659f);
    gfx_add_draw_callback_first(gfx_draw_beam_effect_passes, moby);
}
