#include "include_asm.h"
#include "names.h"
typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector vertices[4]; unsigned int colors[4]; float uv[8]; long zero, texture, state, flags; } Packet;
typedef struct {
    short current, end, active, unused06;
    float first, second, opacity;
    int unused14, effect, flash, unused20, unused24, unused28, unused2C, unused30, unused34, visible;
} Context;
typedef struct { unsigned char prefix[0x150]; short width, height; } Screen;
extern Screen g_screen_adjust_offsets;
extern Vector g_camera_l00_position;
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern void ref_L00_00415AA0_00(void *, float, float, float, float, float, int, int);
extern void cam_compute_view_direction(char *, char *, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

static inline float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

/* Flashes the screen white near the end of the effect, draws a glow, and shows a small sprite that fades with a timer. */
void screen_flash_and_glow_draw(char *object)
{
    Packet packet;
    Vector up, difference, unit, center, horizontal, vertical, corner;
    Context *context = *(Context **)(object + 0x68);
    float amount, opacity, width;
    int delta;
    unsigned int color;

    if (context->end - context->current < 2 && context->active != 0 && context->flash != 0) {
        VU1_addGSregister(0x42, 0x48);
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.height, 0, g_screen_adjust_offsets.width, 0xFFFFFFFF80808080UL);
    }
    if (context->effect != 0) {
        delta = context->end - context->current;
        if (delta < 10) {
            amount = lerp(context->first, context->second, (float)delta * 0.1f);
            ref_L00_00415AA0_00(object + 0x10, amount, 0.5f, 0.0f, 0.0f, 0.0f, 60, 0);
        } else if ((unsigned short)(context->current - 46) < 4) {
            amount = lerp(context->first, context->second, (float)(context->current - 45) * 0.1f);
            ref_L00_00415AA0_00(object + 0x10, amount, 0.5f, 0.0f, 0.0f, 0.0f, 60, 0);
        }
    }
    if (context->active != 0) {
        width = 0.075f;
        cam_compute_view_direction(object + 0x10, (char *)&up, 1);
        opacity = IntToFloat(context->active);
        opacity *= context->opacity;
        gfx_init_quad_packet_state(&packet, 11, 4, 0x80);
        color = ((unsigned int)FloatToInt(opacity * 255.0f) << 24) | 0xFFFFFFu;
        packet.colors[3] = color;
        packet.colors[2] = color;
        packet.colors[1] = color;
        packet.colors[0] = color;
        packet.uv[0] = 0.0f;
        packet.uv[1] = 0.0f;
        packet.uv[2] = 0.0f;
        packet.uv[3] = 1.0f;
        packet.uv[4] = 1.0f;
        packet.uv[5] = 0.0f;
        packet.uv[6] = 1.0f;
        packet.uv[7] = 1.0f;
        FastVecSub(&difference, object + 0x10, &g_camera_l00_position);
        vec_scale_to_length(&unit, &difference, 0.1f);
        FastVecAdd(&center, &g_camera_l00_position, &unit);
        FastVecCross(&horizontal, &difference, &up);
        vec_scale_to_length(&horizontal, &horizontal, width);
        FastVecCross(&vertical, &horizontal, &difference);
        vec_scale_to_length(&vertical, &vertical, width);
        FastVecAdd(&corner, &center, &vertical);
        FastVecAdd(&packet.vertices[0], &corner, &horizontal);
        FastVecSub(&packet.vertices[1], &corner, &horizontal);
        FastVecSub(&corner, &center, &vertical);
        FastVecAdd(&packet.vertices[2], &corner, &horizontal);
        FastVecSub(&packet.vertices[3], &corner, &horizontal);
        draw_world_quad(&packet, 0, 0);
    }
}
