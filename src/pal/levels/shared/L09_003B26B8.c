#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(char *first, char *second, char *third);
extern void vec_scale_to_length(char *dst, char *src, float x);
extern void math_build_axis_angle_quat(void *a, void *b, float f);
extern void FastVecScale(char *a, char *b, float f);
extern void vec_rotate_by_quaternion(char *a, char *b, char *c);
extern float fast_subtract_rotations(float a, float b);
extern void gfx_add_draw_callback_first(char *table, char *object);
extern char g_projectile_draw_callback[];

/* rebuilds the object's orientation matrix from its stored angles and hands it to the stage */
void projectile_update_orientation_pal(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float quat[4];
    char *position = object + 0x10;
    char *offset = vars + 0x10;

    vec_scale_to_length((char *)quat, vars + 0x30, 1.0f);
    math_build_axis_angle_quat(quat, quat, *(float *)(vars + 0x5C));
    FastVecScale(offset, vars, *(float *)(vars + 0x50));
    vec_rotate_by_quaternion(offset, offset, (char *)quat);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    FastVecAdd(offset, position, offset);
    FastVecAdd(vars + 0x20, position, vars + 0x20);
    *(float *)(vars + 0x5C) = fast_subtract_rotations(*(float *)(vars + 0x5C), 0.37699118f);
    gfx_add_draw_callback_first(g_projectile_draw_callback, object);
}

