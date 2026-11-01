#include "include_asm.h"

#include "common.h"
extern f32 ref_L06_003E4F08_00 __attribute__((sda));
extern f32 ref_L06_003E4F08_01 __attribute__((sda));
extern f32 ref_L06_003E4F08_02 __attribute__((sda));
extern f32 ref_L06_003E4F08_03 __attribute__((sda));
extern f32 ref_L06_003E4F08_04 __attribute__((sda));
extern void ref_L06_003E4F08_05(void *, void *, void *, f32, f32, f32);
extern void ref_L06_003E4F08_06(void *, void *, void *, f32, f32, f32);

void func_PAL_L06_003E8568(void *arg0) {
    u8 temp_v1;
    s8 *temp_s0;

    temp_v1 = (*(u8 *)((s8 *)(arg0) + (0x20)));
    temp_s0 = (*(s8 **)((s8 *)(arg0) + (0x68)));
    if ((temp_v1 != 5) && (temp_v1 != 7)) {
        ref_L06_003E4F08_05(arg0, temp_s0 + 0xEC, temp_s0 + 0xE8, ref_L06_003E4F08_00, ref_L06_003E4F08_01 * 0.0003490659f, (*(f32 *)((s8 *)(temp_s0) + (0x108))));
    }
    ref_L06_003E4F08_06(arg0, temp_s0 + 0xF0, temp_s0 + 0xF4, ref_L06_003E4F08_02, ref_L06_003E4F08_03 * 0.0003490659f, ref_L06_003E4F08_04 * 0.0003490659f);
}
