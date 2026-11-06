#include "include_asm.h"



/* func_PAL_L01_0041BFF0, the PAL copy of func_L01_00416B30: the same data, where each timer goes through the
 * 50 Hz scale, so it counts up. */

#include "common.h"

extern s32 ref_L01_00416B30_00(s32);

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_0041BFF0);
