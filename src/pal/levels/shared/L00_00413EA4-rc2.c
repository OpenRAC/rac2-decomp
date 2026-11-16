#include "include_asm.h"

#include "common.h"
extern s32 ref_L00_00410430_00(s32, s32);
extern s32 ref_L00_00410430_01(s32, s32, void *);
extern void *ref_L00_00410430_02(void *, s32, s32, void *, f32, f32, f32, f32);
extern s32 ref_L00_00410430_03(void *, s32);
extern u8 ref_L00_00410430_04[];
extern volatile s32 ref_L00_00410430_05;

/* Starts an effect on the object. Mode 0 creates a new one; other modes set up counters and start it differently. */
void charge_shot_start_effect_pal(void *moby, s32 param, s32 mode) {
    u8 *state = *(u8 **)((u8 *)moby + 0x68);
    void *result;
    s32 count_minus_one;
    if (mode == 0) {
        ref_L00_00410430_01(5, 0, moby);
        result = ref_L00_00410430_02(moby, param, *(s32 *)(state + 0), ref_L00_00410430_04 - 0x70E0, *(f32 *)(state + 8), 2.0f, 5.0f, 0.6f);
        if (result != 0) {
            ref_L00_00410430_00(-1, 1);
            ref_L00_00410430_05 = 1;
            *(void **)((u8 *)result + 0xB8) = moby;
        }
    } else {
        count_minus_one = mode - 1;
        *(s32 *)(state + 0x34) = mode;
        *(s32 *)(state + 0x28) = count_minus_one;
        *(s32 *)(state + 0x2C) = count_minus_one;
        ref_L00_00410430_01(5, 0, moby);
        ref_L00_00410430_03(moby, param);
    }
}
