#include "common.h"

/* A unit of its own: func_PAL_00280218 is placed from C in the boot only. Its level
 * copies are func_L08_002F5CB8, so a same-unit call would not link in the levels. */
extern void func_PAL_00280218(int, int, u64, u8 *, int, float);
extern float func_PAL_00280358(u8 *, int, int, float);

/* func_PAL_00280218, shrunk to fit: func_PAL_00280358 gives the scale that brings the
 * text down to max_width, no smaller than min_scale. min_scale stays in its register
 * for that call, so no instruction moves it. */
void func_PAL_002802D8(int x, int y, u64 color, u8 *text, int length, int max_width, float min_scale) {
    func_PAL_00280218(x, y, color, text, length, func_PAL_00280358(text, length, max_width, min_scale));
}
