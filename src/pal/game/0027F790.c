#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern u8 D_00263EF0[];

extern int text_measure_width_scaled(u8 *, int, u8 *, float);

/* PAL's own sibling of func_0027F288: the same scaled width, with the table of func_0027F198. */
int func_PAL_0027F790(u8 *text, int length, float scale) {
    return text_measure_width_scaled(text, length, D_00263EF0, scale);
}
