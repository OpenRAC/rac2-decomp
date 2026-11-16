#include "include_asm.h"
#include "common.h"
extern s32 ref_L12_00427C58_00;
extern void ref_L12_00427C58_01();
extern void ref_L12_00427C58_02();
extern void ref_L12_00427C58_03(f32);

/* Moves the object one step using one of three shared movement routines, chosen by a level flag and the mode. */
void moby_step_shared_movement_pal(void *moby, s32 unused, s32 mode) {
    s8 *vars;

    vars = *(s8 **)((s8 *)moby + 0x68);
    if (ref_L12_00427C58_00 != 0) {
        ref_L12_00427C58_01();
        return;
    }
    if (mode == 0) {
        ref_L12_00427C58_02();
        return;
    }
    ref_L12_00427C58_03(*(f32 *)(vars + 0x33C));
}
