#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern u64 GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 g_font_glyphs_medium[];

/* Scaled FontPrint: the text is drawn at (x, y) with font texture 2. */
/* Scaled text draw: the text is drawn at (x, y) with font texture 2, medium glyphs (PAL). */
void text_draw_scaled_medium_pal(float x, float y, u64 color, u8 *text, int length, float scale) {
    u64 texture;

    texture = GetEffectTextureDescriptor(2);
    FontPrintScaled_pal(x, y, color, text, length, scale, texture, g_font_glyphs_medium);
}
