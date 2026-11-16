#include "common.h"

/* The counter pair gives a ratio; the three bytes and four floats are interpolated with it and
   stored in the record. Retail reaches the byte and float tables through the assembler's
   absolute macro form (MACRO_ADDR arrays), also when the load lands in a call's delay slot. */
extern int g_screen_fade_timer __attribute__((sda));
extern int g_screen_fade_duration __attribute__((sda));
extern float g_screen_l00_fade_scale __attribute__((sda));

extern unsigned char g_fog_color_r[] MACRO_ADDR;
extern unsigned char g_fog_color_g[] MACRO_ADDR;
extern unsigned char g_fog_color_b[] MACRO_ADDR;
extern float g_screen_l00_fade_scale_2[] MACRO_ADDR;
extern float g_fog_near[] MACRO_ADDR;
extern float g_fog_far[] MACRO_ADDR;
extern float g_fog_near_intensity[] MACRO_ADDR;
extern float g_fog_far_intensity[] MACRO_ADDR;

/* Measured fields of the record the fade writes. */
typedef struct {
    char pad_00[0x218];
    float f218, f21C;
    char pad_220[8];
    float f228, f22C;
    int i230, i234, i238;
} L00FadeRecord;
extern L00FadeRecord g_hud_float_params;

extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void UpdateViewContext(void);

/* Fades the screen settings toward their end values while a countdown runs. */
void cam_update_screen_fade(void)
{
    float ratio;

    if (g_screen_fade_timer <= 0) {
        return;
    }
    math_fast_float_d(&g_screen_fade_timer);
    ratio = IntToFloat(g_screen_fade_timer) / IntToFloat(g_screen_fade_duration);
    g_hud_float_params.i230 =
        FloatToInt(IntToFloat(g_fog_color_r[0]) + (255.0f - IntToFloat(g_fog_color_r[0])) * ratio);
    g_hud_float_params.i234 =
        FloatToInt(IntToFloat(g_fog_color_g[0]) + (255.0f - IntToFloat(g_fog_color_g[0])) * ratio);
    g_hud_float_params.i238 =
        FloatToInt(IntToFloat(g_fog_color_b[0]) + (255.0f - IntToFloat(g_fog_color_b[0])) * ratio);
    g_hud_float_params.f218 = g_fog_near[0] + -g_fog_near[0] * ratio;
    g_hud_float_params.f21C =
        g_fog_far[0] + (g_screen_l00_fade_scale_2[0] * (g_screen_l00_fade_scale * 1024.0f) - g_fog_far[0]) * ratio;
    g_hud_float_params.f228 = g_fog_near_intensity[0] + (255.0f - g_fog_near_intensity[0]) * ratio;
    g_hud_float_params.f22C = g_fog_far_intensity[0] + (100.0f - g_fog_far_intensity[0]) * ratio;
    UpdateViewContext();
}
