#include "include_asm.h"

#include "common.h"
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_str_font_texture[];
extern u8 g_font_glyph_table_scaled[];

extern int text_measure_width_scaled(u8 *, int, u8 *, float);

/* func_PAL_L18_00304BD8, the level copy of func_PAL_0027F790: the same C, with this program's table. */
int text_measure_width_scaled_l18_pal(u8 *text, int length, float scale) {
    return text_measure_width_scaled(text, length, g_font_glyph_table_scaled, scale);
}

/* Draws a line of text centered on the given x position. */
void FontPrintCenterScaled_pal(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (text_measure_width_scaled_l18_pal(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(3);
    FontPrintScaled_pal(fx, fy, color, text, length, scale, texture, g_font_glyph_table_scaled);
}

