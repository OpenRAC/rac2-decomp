#include "common.h"

/* A unit of its own: func_PAL_00280218 is placed from C in the boot only. Its level
 * copies are func_L08_002F5CB8, so a same-unit call would not link in the levels. */
extern void text_draw_centered_small_scaled(int, int, u64, u8 *, int, float);
extern float text_calc_fit_scale(u8 *, int, int, float);

/* func_PAL_00280218, shrunk to fit: func_PAL_00280358 gives the scale that brings the
 * text down to max_width, no smaller than min_scale. min_scale stays in its register
 * for that call, so no instruction moves it. */
void text_draw_centered_small_fitted(int x, int y, u64 color, u8 *text, int length, int max_width, float min_scale) {
    text_draw_centered_small_scaled(x, y, color, text, length, text_calc_fit_scale(text, length, max_width, min_scale));
}
