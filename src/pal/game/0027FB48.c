#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_font_glyphs_small[];

/* Scaled FontPrint: the text is drawn at (x, y) with font texture 1. */
void text_draw_small_scaled(float x, float y, u64 color, u8 *text, int length, float scale) {
    u64 texture;

    texture = GetEffectTextureDescriptor(1);
    FontPrintScaled_pal(x, y, color, text, length, scale, texture, g_font_glyphs_small);
}
