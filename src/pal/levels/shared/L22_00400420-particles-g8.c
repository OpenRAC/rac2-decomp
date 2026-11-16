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
void part_init_effect_slots_pal(u8 * obj) {
    Controller * vars = *(Controller **)(obj + 0x68);
    int i;
    float angle, pitch;

    for (i = 0; i < 4; i++) vars->randomValues[i] = (float)math_random_int_below(255);
    for (i = 0; i < 4; i++)
        vars->initialValues[i] = ((s32)(ref_L22_003FBBF0_00) * 5 + 2) / 6;
    for (i = 7; i >= 0; i--) vars->particles[i] = 0;
    if (g_effect_owner_moby == 0) {
        u8 * axis_x = obj + 0xC0, *axis_y, *axis_z = obj + 0xE0;
        u8 * anchors, *anchor_axes;
        euler_rotation_basis(axis_x, obj + 0xF0);
        g_effect_owner_moby = obj;
        obj[0x30] = 255;
        anchors = g_effect_anchor_table;
        vec_scale_to_length(anchors, axis_x, ref_L22_003FBBF0_01);
        anchor_axes = g_effect_anchor_axes;
        *(TI *)anchor_axes = *(TI *)axis_z;
        axis_y = obj + 0xD0;
        vec_scale_to_length(anchors + 0x10, axis_y, ref_L22_003FBBF0_01);
        *(TI *)(anchor_axes + 0x10) = *(TI *)axis_x;
        vec_scale_to_length(anchors + 0x20, axis_z, ref_L22_003FBBF0_01);
        *(TI *)(anchor_axes + 0x20) = *(TI *)axis_y;
        FastVecAdd(anchors + 0x30, axis_x, axis_z);
        vec_scale_to_length(anchors + 0x30, anchors + 0x30, ref_L22_003FBBF0_01);
        FastVecCross(anchor_axes + 0x30, anchors + 0x30, axis_y);
        FastVecAdd(anchors + 0x40, axis_x, axis_y);
        vec_scale_to_length(anchors + 0x40, anchors + 0x40, ref_L22_003FBBF0_01);
        FastVecCross(anchor_axes + 0x40, anchors + 0x40, axis_z);
        FastVecSub(anchors + 0x50, axis_y, axis_z);
        vec_scale_to_length(anchors + 0x50, anchors + 0x50, ref_L22_003FBBF0_01);
        FastVecCross(anchor_axes + 0x50, anchors + 0x50, axis_x);
        FastVecSub(anchors + 0x60, axis_x, axis_z);
        vec_scale_to_length(anchors + 0x60, anchors + 0x60, ref_L22_003FBBF0_01);
        FastVecCross(anchor_axes + 0x60, anchors + 0x60, axis_y);
        FastVecSub(anchors + 0x70, axis_x, axis_y);
        vec_scale_to_length(anchors + 0x70, anchors + 0x70, ref_L22_003FBBF0_01);
        FastVecCross(anchor_axes + 0x70, anchors + 0x70, axis_z);
    }
    angle = math_random_float_range(0.0f, 6.2831855f);
    pitch = math_random_float_range(-1.5707964f, 1.5707964f);
    vec_build_spherical_offset((u8 *)vars + 0x10, 1.0f, angle, pitch);
    *(float *)((u8 *)vars + 0x1C) = math_random_signed_float_range(0.785398f, 1.5707964f);
}
