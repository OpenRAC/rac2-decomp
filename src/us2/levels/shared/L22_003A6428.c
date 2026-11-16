#include "include_asm.h"
#include "names.h"

extern void ref_L22_003A4FF8_00(void);

/* Calls a level helper and always says it worked (USA v2.00 copy). */
int level_call_helper_return_true_us2(void) {
    ref_L22_003A4FF8_00();
    return 1;
}

/* func_US2_L22_003A6448 lives in L22_003A6448-hud-g8.c. */
