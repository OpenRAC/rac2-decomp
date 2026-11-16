#include "include_asm.h"
#include "common.h"
extern s32 ref_L12_00427C58_00;
extern void ref_L12_00427C58_01();
extern void ref_L12_00427C58_02();
extern void ref_L12_00427C58_03(f32);

void moby_step_shared_movement_pal(void *arg0, s32 a1, s32 arg2) {
    s8 *t;

    t = *(s8 **)((s8 *)arg0 + 0x68);
    if (ref_L12_00427C58_00 != 0) {
        ref_L12_00427C58_01();
        return;
    }
    if (arg2 == 0) {
        ref_L12_00427C58_02();
        return;
    }
    ref_L12_00427C58_03(*(f32 *)(t + 0x33C));
}
