#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern u8 g_font_glyphs_medium[];

extern int text_measure_width_scaled(u8 *, int, u8 *, float);

/* PAL's own sibling of func_0027F288: the same scaled width, with the table of func_0027F198. */
int text_measure_width_medium_scaled(u8 *text, int length, float scale) {
    return text_measure_width_scaled(text, length, g_font_glyphs_medium, scale);
}
