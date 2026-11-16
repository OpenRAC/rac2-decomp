#include "names.h"
/* func_PAL_L00_004007B0, the PAL copy of func_L00_003FBF78: the same C, where the duration
   D_L00_001B0B60 becomes (D_L00_001B0B60 * 5 + 2) / 6. The division guard of that scale must
   end reorg's forward search from the first call (retail keeps its slot empty), hence
   -frac2-sticky-volatile-refs on this unit. */
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
    float fog_near, fog_far;
    char pad_220[8];
    float near_intensity, far_intensity;
    int color_r, color_g, color_b;
} L00FadeRecord;
extern L00FadeRecord g_hud_float_params;

extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void UpdateViewContext(void);

/* Fades the fog colour and distances toward white while the screen fade timer runs (PAL: 50 Hz duration). */
void cam_update_screen_fade_pal(void)
{
    float ratio;

    if (g_screen_fade_timer <= 0) {
        return;
    }
    math_fast_float_d(&g_screen_fade_timer);
    ratio = IntToFloat(g_screen_fade_timer) / IntToFloat(((g_screen_fade_duration * 5 + 2) / 6));
    g_hud_float_params.color_r =
        FloatToInt(IntToFloat(g_fog_color_r[0]) + (255.0f - IntToFloat(g_fog_color_r[0])) * ratio);
    g_hud_float_params.color_g =
        FloatToInt(IntToFloat(g_fog_color_g[0]) + (255.0f - IntToFloat(g_fog_color_g[0])) * ratio);
    g_hud_float_params.color_b =
        FloatToInt(IntToFloat(g_fog_color_b[0]) + (255.0f - IntToFloat(g_fog_color_b[0])) * ratio);
    g_hud_float_params.fog_near = g_fog_near[0] + -g_fog_near[0] * ratio;
    g_hud_float_params.fog_far =
        g_fog_far[0] + (g_screen_l00_fade_scale_2[0] * (g_screen_l00_fade_scale * 1024.0f) - g_fog_far[0]) * ratio;
    g_hud_float_params.near_intensity = g_fog_near_intensity[0] + (255.0f - g_fog_near_intensity[0]) * ratio;
    g_hud_float_params.far_intensity = g_fog_far_intensity[0] + (100.0f - g_fog_far_intensity[0]) * ratio;
    UpdateViewContext();
}
