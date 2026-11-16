#include "common.h"

extern int text_draw_fixed(u8 *, int, float);
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_str_font_texture[];

/* Draws a line of text centered on the given x position. */
void FontPrintCenterScaled(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (text_draw_fixed(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(3);
    FontPrintScaled(fx, fy, color, text, length, scale, texture, g_str_font_texture);
}
