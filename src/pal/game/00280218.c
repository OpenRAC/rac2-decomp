#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *g_hero_moby;
extern int text_measure_width_small_scaled(u8 *, int, float);
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_font_print_data[];
extern u8 g_screen_update_index;
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_moby_array_end __attribute__((sda));
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_hero_moby;

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_PAL_0027FB48 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void text_draw_centered_small_scaled(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (text_measure_width_small_scaled(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(1);
    FontPrintScaled_pal(fx, fy, color, text, length, scale, texture, g_font_print_data);
}


/* Scale that fits text into maxWidth, never below minScale and never above 1. */
float text_calc_fit_scale(u8 *text, int length, int maxWidth, float minScale) {
    int width;
    float scale;

    scale = 1.0f;
    if (text != 0) {
        width = text_measure_width_small_scaled(text, length, scale);
    } else {
        width = 0;
    }
    if (maxWidth < width) {
        scale = (float)maxWidth / (float)width;
        if (scale < minScale) {
            scale = minScale;
        }
    }
    return scale;
}

extern int text_measure_width_medium_scaled(u8 *, int, float);
extern u8 g_font_glyph_table_small[];

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_PAL_0027FB48 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void text_draw_centered_medium_scaled(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (text_measure_width_medium_scaled(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(2);
    FontPrintScaled_pal(fx, fy, color, text, length, scale, texture, g_font_glyph_table_small);
}


extern void FontPrintWindow_pal(float);

/* Prints text in a window at the default scale of 1. */
void text_window_print_unit_scale(void) {
    FontPrintWindow_pal(1.0f);
}

