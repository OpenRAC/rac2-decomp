#include "common.h"

/* A unit of its own: func_US2_00280380 is placed from C in the boot only. Its level
 * copies are func_L08_002F5CB8, so a same-unit call would not link in the levels. */
extern void text_draw_centered_small_scaled_us2(int, int, u64, u8 *, int, float);
extern float text_fit_scale_to_width_us2(u8 *, int, int, float);

/* func_US2_00280380, shrunk to fit: func_US2_002804C0 gives the scale that brings the
 * text down to max_width, no smaller than min_scale. min_scale stays in its register
 * for that call, so no instruction moves it. */
void text_draw_shrunk_to_width_us2(int x, int y, u64 color, u8 *text, int length, int max_width, float min_scale) {
    text_draw_centered_small_scaled_us2(x, y, color, text, length, text_fit_scale_to_width_us2(text, length, max_width, min_scale));
}
