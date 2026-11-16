#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *g_hero_moby;
extern int text_measure_width_small_scaled(u8 *, int, float);
extern u64 tex_get_effect_descriptor_us2(int);
extern void text_draw_scaled_us2(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_font_print_data[];
extern u8 g_screen_update_index;
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_moby_array_end __attribute__((sda));
extern u8 *g_moby_array __attribute__((sda));
extern u8 *g_hero_moby;

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_US2_0027FCB0 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void text_draw_centered_small_scaled_us2(int x, int y, u64 color, u8 *text, int length, float scale) {
    float draw_x, draw_y;
    u64 texture;

    draw_x = x - (text_measure_width_small_scaled(text, length, scale) >> 1);
    draw_y = y;
    texture = tex_get_effect_descriptor_us2(1);
    text_draw_scaled_us2(draw_x, draw_y, color, text, length, scale, texture, g_font_print_data);
}


/* Returns the scale (at most 1.0, at least the minimum) that makes the text fit within the width limit. */
float text_fit_scale_to_width_us2(u8 *text, int length, int limit, float minimum) {
    float scale = 1.0f;
    int width;

    if (text != 0) {
        width = text_measure_width_small_scaled(text, length, scale);
    } else {
        width = 0;
    }
    if (limit < width) {
        scale = (float)limit / (float)width;
        if (scale < minimum) {
            scale = minimum;
        }
    }
    return scale;
}

extern void FontPrintWindow_us2(float);

/* Calls the scaled window text print with a scale of 1.0. */
void text_print_window_unit_scale_us2(void) {
    FontPrintWindow_us2(1.0f);
}

