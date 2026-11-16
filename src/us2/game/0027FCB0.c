#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern u64 tex_get_effect_descriptor_us2(int);
extern void text_draw_scaled_us2(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_font_glyphs_small[];

/* Draws a string in the small font at a float position and scale. func_US2_0027FFF0 has no USA v1.01 twin: a wrapper like func_0027F980 that draws at a float
   position and scale through func_US2_0027FCB0, without subtracting the text width. */
void text_draw_small_scaled_us2(float x, float y, u64 color, u8 *text, int length, float scale) {
    u64 texture;

    texture = tex_get_effect_descriptor_us2(1);
    text_draw_scaled_us2(x, y, color, text, length, scale, texture, g_font_glyphs_small);
}
