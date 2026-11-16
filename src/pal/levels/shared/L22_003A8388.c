#include "include_asm.h"
#include "names.h"

extern void ref_L22_003A4FF8_00(void);

/* Calls a level helper and returns 1, so the hook it is stored as always reports success. */
int level_call_helper_return_true_pal(void) {
    ref_L22_003A4FF8_00();
    return 1;
}

/* func_PAL_L22_003A83A8 lives in L22_003A83A8-hud-g8.c. */

