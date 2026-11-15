#include "include_asm.h"

#include "common.h"
extern void vec_scale_to_length(char *a0, void *a1, float f12);
extern void math_build_axis_angle_quat(void *a0, void *a1, float f12);
extern void FastVecScale(char *a0, void *a1, float f12);
extern void vec_rotate_by_quaternion(void *a0, void *a1, void *a2);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern float fast_subtract_rotations(float a, float b);
extern void gfx_add_draw_callback_first(void *a0, void *a1);
extern void joba_effect_update_particles(char *p);
extern float D_L11_001B1FFC __attribute__((sda));

/* Rebuilds the state's offset block from its rotation and installs the next handler. */
void func_PAL_L11_0045F9F8(char *p)
{
    char *q = *(char **)(p + 0x68);
    float v[4];

    vec_scale_to_length((char *)v, q + 0x40, 1.0f);
    math_build_axis_angle_quat(v, v, *(float *)(q + 0x30));
    FastVecScale(q + 0x10, q, *(float *)(q + 0x60));
    vec_rotate_by_quaternion(q + 0x10, q + 0x10, v);
    *(float *)(q + 0x20) = -*(float *)(q + 0x10);
    *(float *)(q + 0x24) = -*(float *)(q + 0x14);
    *(float *)(q + 0x28) = -*(float *)(q + 0x18);
    FastVecAdd(q + 0x10, p + 0x10, q + 0x10);
    FastVecAdd(q + 0x20, p + 0x10, q + 0x20);
    *(float *)(q + 0x30) = fast_subtract_rotations(*(float *)(q + 0x30),
                                         D_L11_001B1FFC * 0.0003490659f);
    gfx_add_draw_callback_first(joba_effect_update_particles, p);
}
