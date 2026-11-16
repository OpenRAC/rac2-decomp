#include "include_asm.h"
#include "names.h"



/* func_PAL_L01_0041BFF0, the PAL copy of func_L01_00416B30: the same data, where each timer goes through the
 * 50 Hz scale, so it counts up. */

#include "common.h"

extern s32 ref_L01_00416B30_00(s32);

/* Sets up the glow ring phases, speeds, timers and sizes of a gold bolt (PAL copy). */
void gold_bolt_glow_init_pal(void *moby) {
    s32 *vars = *(s32 **)((u8 *)moby + 0x68);
    f32 *values = (f32 *)((u8 *)vars + 0x20);
    s32 *slot;
    s32 count;

    for (count = 3; count >= 0; count--, values++) {
        *values = (f32)ref_L01_00416B30_00(0xFF);
    }

    slot = (s32 *)((u8 *)vars + 0x40);
    *(f32 *)((u8 *)vars + 0x30) = -1.0f;
    *(f32 *)((u8 *)vars + 0x34) = -2.25f;
    *(f32 *)((u8 *)vars + 0x38) = 1.25f;
    *(f32 *)((u8 *)vars + 0x3C) = 2.5f;

    for (count = 0; count < 4; count++) {
        slot[count] = ((count * 0x40 + 0x3F) * 5 + 2) / 6;
    }

    *(f32 *)((u8 *)vars + 0x50) = 2.5f;
    *(f32 *)((u8 *)vars + 0x54) = 3.0f;
    *(f32 *)((u8 *)vars + 0x5C) = 2.5f;
    *(f32 *)((u8 *)vars + 0x58) = 3.0f;
}
