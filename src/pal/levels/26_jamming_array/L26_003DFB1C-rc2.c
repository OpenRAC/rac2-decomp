#include "include_asm.h"

#include "common.h"
extern s8 ref_L26_003DC048_00[];
extern void ref_L26_003DC048_01(s8 *);
extern void ref_L26_003DC048_02(s8 *, s8 *);
extern f32 ref_L26_003DC048_03(f32, f32);
extern void ref_L26_003DC048_04(s8 *, s8 *, s32, s8 *, f32);

void func_PAL_L26_003E03D0(s8 *arg0) {
    s8 *temp_s0;
    f32 temp_f0;
    u16 temp_v1;

    temp_s0 = *(s8 **)(arg0 + 0x68);
    ref_L26_003DC048_01(temp_s0 + 0x220);
    ref_L26_003DC048_01(temp_s0 + 0x222);
    ref_L26_003DC048_02(arg0, temp_s0 + 0x278);
    if (*(u8 *)(arg0 + 0x95) == 2) {
        temp_f0 = ref_L26_003DC048_03(*(f32 *)(temp_s0 + 0x27C), 0.25132746f);
        *(f32 *)(temp_s0 + 0x27C) = temp_f0;
        ref_L26_003DC048_04(arg0, temp_s0 + 0x270, 1, ref_L26_003DC048_00, temp_f0);
    } else {
        temp_f0 = ref_L26_003DC048_03(*(f32 *)(temp_s0 + 0x27C), 0.013962637f);
        *(f32 *)(temp_s0 + 0x27C) = temp_f0;
        ref_L26_003DC048_04(arg0, temp_s0 + 0x270, 0, ref_L26_003DC048_00, temp_f0);
    }
    temp_v1 = *(u16 *)(arg0 + 0x96);
    if (temp_v1 <= 0xFFFE) {
        *(u16 *)(arg0 + 0x96) = temp_v1 + 1;
    }
}
