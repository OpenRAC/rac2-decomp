#include "include_asm.h"

#include "common.h"
extern void ref_L09_003F0378_00(void);
extern s32 ref_L09_003F0378_01(f32);
extern void ref_L09_003F0378_02(void *, s32, s32, s32);
extern void ref_L09_003F0378_03(void *, s32, s32);
extern s32 ref_L09_003F0378_04(void *, s32, s32);
extern f32 ref_L09_003F0378_05(void *, s32);
extern void ref_L09_003F0378_06(void *, void *);
extern void ref_L09_003F0378_07(void *, s32);
extern void ref_L09_003F0378_08(void *, s32, s32, s32, f32, f32);

void func_PAL_L09_003F49E8(void *arg0) {
    void *temp_s2;
    s32 temp_s0;
    s32 func_result;
    s32 temp_cond ;
    void *var_s3;
    f32 temp_f0;
    f32 temp_f1;

    temp_s2 = *(void **)((s8 *)arg0 + 0x68);
    if (*(u8 *)((s8 *)arg0 + 0x95) == 0) {
        var_s3 = (s8 *)temp_s2 + 0x70;
        ref_L09_003F0378_00();
    } else {
        var_s3 = (s8 *)temp_s2 + 0x70;
        temp_s0 = 0;
        func_result = ref_L09_003F0378_04(arg0, 0x10000, 0);
        temp_cond = *(s16 *)((s8 *)temp_s2 + 0x26) < 1;
        temp_s0 = temp_cond ? func_result : temp_s0;
        temp_f1 = ref_L09_003F0378_05(arg0, temp_s0);
        if (temp_s0 != 0) {
            if (temp_f1 > 0.0f) {
                temp_f0 = *(f32 *)((s8 *)temp_s2 + 0x20) - temp_f1;
                *(f32 *)((s8 *)temp_s2 + 0x20) = temp_f0;
                if (temp_f0 <= 0.0f) {
                    ref_L09_003F0378_03(arg0, 6, 4);
                } else {
                    *(s8 *)((s8 *)temp_s2 + 0x77) = (s8)(ref_L09_003F0378_01(temp_f1 * 20.0f) + 0x64);
                    ref_L09_003F0378_06(arg0, var_s3);
                    if (*(u8 *)((s8 *)arg0 + 0x43) != 4) {
                        ref_L09_003F0378_02(arg0, 4, 0, 1);
                    }
                    ref_L09_003F0378_03(arg0, 5, -1);
                }
            }
        }
        *(u8 *)((s8 *)arg0 + 0xA8) = 0xFF;
    }
    ref_L09_003F0378_07(arg0, (s32)var_s3);
    ref_L09_003F0378_08(arg0, *(s32 *)((s8 *)temp_s2 + 0x8C), 0, 0, 0.0f, 0.0f);
}
