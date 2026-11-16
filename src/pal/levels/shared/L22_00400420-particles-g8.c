/* func_PAL_L22_00400420, the PAL copy of func_L22_003FBBF0: the same C, where the slots'
   initial value is an int scaled for 50 Hz, computed in a count-up loop. */
#include "common.h"

typedef int TI __attribute__((mode(TI)));
typedef struct {
    u8 pad[0x40];
    unsigned short initialValues[4];
    u8 pad48[8];
    float randomValues[4];
    void * particles[8];
} Controller;

extern int ref_L22_003FBBF0_00 __attribute__((sda));
extern float ref_L22_003FBBF0_01 __attribute__((sda));
extern u8 * g_effect_owner_moby;
extern u8 g_effect_anchor_table[], g_effect_anchor_axes[];
extern int math_random_int_below(int);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);

/* Initialize the particle slots and their direction tables. */
void func_PAL_L22_00400420(u8 * obj) {
    Controller * ctl = *(Controller **)(obj + 0x68);
    int i;
    float a, b;

    for (i = 0; i < 4; i++) ctl->randomValues[i] = (float)math_random_int_below(255);
    for (i = 0; i < 4; i++)
        ctl->initialValues[i] = ((s32)(ref_L22_003FBBF0_00) * 5 + 2) / 6;
    for (i = 7; i >= 0; i--) ctl->particles[i] = 0;
    if (g_effect_owner_moby == 0) {
        u8 * x = obj + 0xC0, *y, *z = obj + 0xE0;
        u8 * v, *w;
        euler_rotation_basis(x, obj + 0xF0);
        g_effect_owner_moby = obj;
        obj[0x30] = 255;
        v = g_effect_anchor_table;
        vec_scale_to_length(v, x, ref_L22_003FBBF0_01);
        w = g_effect_anchor_axes;
        *(TI *)w = *(TI *)z;
        y = obj + 0xD0;
        vec_scale_to_length(v + 0x10, y, ref_L22_003FBBF0_01);
        *(TI *)(w + 0x10) = *(TI *)x;
        vec_scale_to_length(v + 0x20, z, ref_L22_003FBBF0_01);
        *(TI *)(w + 0x20) = *(TI *)y;
        FastVecAdd(v + 0x30, x, z);
        vec_scale_to_length(v + 0x30, v + 0x30, ref_L22_003FBBF0_01);
        FastVecCross(w + 0x30, v + 0x30, y);
        FastVecAdd(v + 0x40, x, y);
        vec_scale_to_length(v + 0x40, v + 0x40, ref_L22_003FBBF0_01);
        FastVecCross(w + 0x40, v + 0x40, z);
        FastVecSub(v + 0x50, y, z);
        vec_scale_to_length(v + 0x50, v + 0x50, ref_L22_003FBBF0_01);
        FastVecCross(w + 0x50, v + 0x50, x);
        FastVecSub(v + 0x60, x, z);
        vec_scale_to_length(v + 0x60, v + 0x60, ref_L22_003FBBF0_01);
        FastVecCross(w + 0x60, v + 0x60, y);
        FastVecSub(v + 0x70, x, y);
        vec_scale_to_length(v + 0x70, v + 0x70, ref_L22_003FBBF0_01);
        FastVecCross(w + 0x70, v + 0x70, z);
    }
    a = math_random_float_range(0.0f, 6.2831855f);
    b = math_random_float_range(-1.5707964f, 1.5707964f);
    vec_build_spherical_offset((u8 *)ctl + 0x10, 1.0f, a, b);
    *(float *)((u8 *)ctl + 0x1C) = math_random_signed_float_range(0.785398f, 1.5707964f);
}
