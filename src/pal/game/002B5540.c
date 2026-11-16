#include "include_asm.h"
#include "names.h"

/* func_PAL_002B5540, the PAL copy of func_002B49B0: the same C, where the value takes the 50 Hz scale. */

typedef int s32;

extern int g_requested_setting_a __attribute__((sda));

/* Stores the requested setting A, scaled to 50 Hz. */
void request_set_setting_a_pal(int value) {
    g_requested_setting_a = ((s32)(value) * 5 + 2) / 6;
}
