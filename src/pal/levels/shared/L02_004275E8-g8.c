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
void moby_update_spinning_frame_orientation_pal(char *s2) {
    float buf[4];
    char *s0 = *(char **)(s2 + 0x68);
    char *s3 = s2 + 0x10;
    char *s1 = s0 + 0x10;

    vec_scale_to_length(buf, s0 + 0x40, 1.0f);
    math_build_axis_angle_quat(buf, buf, *(float *)(s0 + 0x30));
    FastVecScale(s1, s0, *(float *)(s0 + 0x60));
    vec_rotate_by_quaternion(s1, s1, buf);
    *(float *)(s0 + 0x20) = -*(float *)(s0 + 0x10);
    *(float *)(s0 + 0x24) = -*(float *)(s0 + 0x14);
    *(float *)(s0 + 0x28) = -*(float *)(s0 + 0x18);
    FastVecAdd(s1, s3, s1);
    FastVecAdd(s0 + 0x20, s3, s0 + 0x20);
    *(float *)(s0 + 0x30) =
        fast_subtract_rotations(*(float *)(s0 + 0x30), g_spinning_moby_rot_rate * 0.0003490659f);
    gfx_add_draw_callback_first(gfx_draw_beam_effect_passes, s2);
}
