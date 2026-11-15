#include "include_asm.h"
#include "names.h"

extern void FastVecAdd(char *first, char *second, char *third);
extern void vec_scale_to_length(char *dst, char *src, float x);
extern void math_build_axis_angle_quat(void *a, void *b, float f);
extern void FastVecScale(char *a, char *b, float f);
extern void vec_rotate_by_quaternion(char *a, char *b, char *c);
extern float fast_subtract_rotations(float a, float b);
extern void gfx_add_draw_callback_first(char *table, char *object);
extern char D_L09_003AEF78[];

/* rebuilds the object's orientation matrix from its stored angles and hands it to the stage */
void func_PAL_L09_003B26B8(char *object)
{
    char *p = *(char **)(object + 0x68);
    float m[4];
    char *q = object + 0x10;
    char *r = p + 0x10;

    vec_scale_to_length((char *)m, p + 0x30, 1.0f);
    math_build_axis_angle_quat(m, m, *(float *)(p + 0x5C));
    FastVecScale(r, p, *(float *)(p + 0x50));
    vec_rotate_by_quaternion(r, r, (char *)m);
    *(float *)(p + 0x20) = -*(float *)(p + 0x10);
    *(float *)(p + 0x24) = -*(float *)(p + 0x14);
    *(float *)(p + 0x28) = -*(float *)(p + 0x18);
    FastVecAdd(r, q, r);
    FastVecAdd(p + 0x20, q, p + 0x20);
    *(float *)(p + 0x5C) = fast_subtract_rotations(*(float *)(p + 0x5C), 0.37699118f);
    gfx_add_draw_callback_first(D_L09_003AEF78, object);
}

