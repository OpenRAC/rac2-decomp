#include "names.h"
typedef unsigned char u8;
typedef unsigned long u64;
extern int text_measure_width_small(u8 *, int);
extern int text_measure_width_medium(u8 *, int);
extern int text_measure_width_large(u8 *, int);
extern u64 GetEffectTextureDescriptor(int);
extern void text_draw_line(int, int, u64, u8 *, int, u64, u8 *);
extern u8 g_font_glyphs_small[];
extern u8 g_font_glyphs_medium[];
extern u8 g_font_glyphs_large[];

/* Draws right-aligned text ending at x, in the small font. */
void text_draw_right_aligned_small(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= text_measure_width_small(text, length);
    font = GetEffectTextureDescriptor(1);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_small);
}

/* Draws right-aligned text ending at x, in the medium font. */
void text_draw_right_aligned_medium(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= text_measure_width_medium(text, length);
    font = GetEffectTextureDescriptor(2);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_medium);
}

/* Draws text centered on x in the small font and returns where it starts. */
int text_draw_centered_small(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= text_measure_width_small(text, length) >> 1;
    font = GetEffectTextureDescriptor(1);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_small);
    return x;
}

/* Draws text centered on x in the medium font and returns where it starts. */
int text_draw_centered_medium(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= text_measure_width_medium(text, length) >> 1;
    font = GetEffectTextureDescriptor(2);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_medium);
    return x;
}

/* Draws text centered on x in the large font and returns where it starts. */
int text_draw_centered_large(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= text_measure_width_large(text, length) >> 1;
    font = GetEffectTextureDescriptor(3);
    text_draw_line(x, y, style, text, length, font, g_font_glyphs_large);
    return x;
}
