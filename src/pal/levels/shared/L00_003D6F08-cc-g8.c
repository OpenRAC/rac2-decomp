/* func_PAL_L00_003D6F08, the PAL copy of func_L00_003D2ED0: the same C, where scale D_L00_001B021C; scale D_L00_001B020C. */
#include "common.h"
typedef struct { float x, y, z, w; } EffectVector;
extern short D_L00_001B2AF0[] MACRO_ADDR;
extern char D_L00_00247310[], D_L00_00247450[];
extern short D_L00_001B2AF8, D_L00_001B2AFA;
extern char g_camera_l00_position[];
extern char D_0018A580[];
extern short g_screen_adjust_offsets[];
extern float D_L00_001B01BC __attribute__((sda)), D_L00_001B01C0 __attribute__((sda)), D_L00_001B01C4 __attribute__((sda)), D_L00_001B01C8 __attribute__((sda));
extern int D_L00_001B021C __attribute__((sda)), D_L00_001B020C __attribute__((sda));
extern float D_L00_001B0208 __attribute__((sda)), D_L00_001B0210 __attribute__((sda));
extern void DrawScrollingRibbonWithFadedEnds(void *, int, int, int, float, float, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecSub(void *, void *,void *);
extern void FastVecAdd(void *, void *,void *);
extern void FastVecCross(void *, void *,void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *,void *);
extern void vec_add_random_offset(void *, float);
extern void gfx_init_quad_packet_state(void *, int, int,int);
extern void draw_world_quad(void *, void *, int);
extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int,int, int, unsigned int);
/* Update four effect strips, then draw the active radial ring and fading quad. */
void func_PAL_L00_003D6F08(char *object)
{
    char render[0x90];
    EffectVector position, axis, direction;
    struct { EffectVector points[20], offset, center, radial, rotated; int color; } effect;
    int color;
    int i, remaining;
    short *indices = D_L00_001B2AF0;
    char *records = D_L00_00247310;
    char *context = *(char **)(object + 0x68);
    float fade;
    float radius, spread;
    for (remaining = 3; remaining >= 0; indices++, records += 0x50, remaining--)
        DrawScrollingRibbonWithFadedEnds(records, *indices, *indices, 5, D_L00_001B01BC, D_L00_001B01C0, 0.2f);
    DrawScrollingRibbonWithFadedEnds(D_L00_00247450, D_L00_001B2AF8, D_L00_001B2AF8, 5, D_L00_001B01C4, D_L00_001B01C8, 0.2f);
    DrawScrollingRibbonWithFadedEnds(D_L00_00247450 + 0x50, D_L00_001B2AFA, D_L00_001B2AFA, 5, D_L00_001B01C4, D_L00_001B01C8, 0.2f);
    qcopy(&position, context + 0x10);
    cam_compute_view_direction(&position, &axis, 1);
    FastVecSub(&direction, g_camera_l00_position, &position);
    fade = 1.0f;
    vec_scale_to_length(&direction, &direction, fade);
    if (*(int *)(context + 0x44)) {
        if (*(int *)(context + 0x44) < (((int)(D_L00_001B021C) * 5 + 2) / 6))
            fade = IntToFloat(*(int *)(context + 0x44)) * *(float *)(context + 0x48);
        effect.color = FloatToInt(fade * 64.0f);
        radius = (1.0f - fade) * 10.0f + 0.05f;
        spread = (1.0f - fade) * 0.5f;
        FastVecScale(&effect.offset, D_0018A580, (1.0f - fade)* 32.0f);
        FastVecAdd(&effect.center, &position, &effect.offset);
        for (i = 0; i < 20; i++) {
            math_build_axis_angle_quat(&effect.rotated, &direction, IntToFloat(i)* 0.3141593f);
            vec_rotate_by_quaternion(&effect.radial, &axis, &effect.rotated);
            FastVecScale(&effect.radial, &effect.radial, radius);
            vec_add_random_offset(&effect.radial, spread);
            FastVecAdd(&effect.points[i], &effect.center, &effect.radial);
        }
        DrawScrollingRibbonWithFadedEnds(effect.points, effect.color, effect.color, 20, 0.3f, 1.2f, 0.2f);
    }
    if (*(int *)(context + 0x28)) {
        if (*(int *)(context + 0x28) < (((int)(D_L00_001B020C) * 5 + 2) / 6))
            fade = IntToFloat(*(int *)(context + 0x28)) * *(float *)(context + 0x2C);
        else fade = 1.0f;
        gfx_init_quad_packet_state(render, 11, 1, 128);
        color = (FloatToInt(fade * 255.0f) << 24) | 0x808080;
        *(int *)(render+0x4C)=color;
        *(int *)(render+0x48)=color;
        *(int *)(render+0x44)=color;
        *(int *)(render+0x40)=color;
        *(int *)(render+0x50)=0;
        *(int *)(render+0x54)=0;
        *(int *)(render+0x58)=0;
        *(float *)(render+0x5C)=1.0f;
        *(float *)(render+0x60)=1.0f;
        *(int *)(render+0x64)=0;
        *(float *)(render+0x68)=1.0f;
        *(float *)(render+0x6C)=1.0f;
        FastVecScale(&effect.points[0], &direction, -0.1f);
        FastVecAdd(&effect.points[1], g_camera_l00_position, &effect.points[0]);
        FastVecCross(&effect.points[2], &direction, &axis);
        vec_scale_to_length(&effect.points[2], &effect.points[2], D_L00_001B0208);
        FastVecCross(&effect.points[3], &effect.points[2], &direction);
        vec_scale_to_length(&effect.points[3], &effect.points[3], D_L00_001B0208);
        FastVecAdd(&effect.points[4], &effect.points[1], &effect.points[3]);
        FastVecAdd(render, &effect.points[4], &effect.points[2]);
        FastVecSub(render+0x10, &effect.points[4], &effect.points[2]);
        FastVecSub(&effect.points[4], &effect.points[1], &effect.points[3]);
        FastVecAdd(render+0x20, &effect.points[4], &effect.points[2]);
        FastVecSub(render+0x30, &effect.points[4], &effect.points[2]);
        draw_world_quad(render, 0, 0);
        color = (FloatToInt(D_L00_001B0210 * fade) << 24) | 0x808080;
        *(int *)(render+0x4C)=color;
        *(int *)(render+0x48)=color;
        *(int *)(render+0x44)=color;
        *(int *)(render+0x40)=color;
        VU1_addGSregister(66, 72);
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9],0,g_screen_adjust_offsets[0xA8],*(unsigned int *)(render+0x40));
    }
}
