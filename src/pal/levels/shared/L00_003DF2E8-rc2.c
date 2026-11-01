#include "include_asm.h"

#include "common.h"
extern s8 D_00189E20[];
extern f32 ref_L00_003DC1C0_00 __attribute__((sda));
extern f32 ref_L00_003DC1C0_01 __attribute__((sda));
extern f32 ref_L00_003DC1C0_02 __attribute__((sda));
extern f32 ref_L00_003DC1C0_03 __attribute__((sda));
extern s32 ref_L00_003DC1C0_04(s32, s32, s32, s32, f32, f32, f32, f32);
extern f32 ref_L00_003DC1C0_05(f32, f32);
extern void ref_L00_003DC1C0_06(s32, s32, s32, f32);
extern void ref_L00_003DC1C0_07(s32, s32, s32, s32, f32, f32, f32, f32);

s32 func_PAL_L00_003E0390(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s8 *b;
    s32 temp_s0;
    s32 temp_s1;

    b = D_00189E20;
    temp_s1 = ref_L00_003DC1C0_04(*(s32 *)(b + 0x2290) + 0xC0, 5, 0, arg3, ref_L00_003DC1C0_01, *(f32 *)(b + 0x98), 0.39269909f, 0.39269909f);
    ref_L00_003DC1C0_07(arg1, arg0 + 0x10, temp_s1, 0, ref_L00_003DC1C0_02, ref_L00_003DC1C0_05(ref_L00_003DC1C0_02, ref_L00_003DC1C0_01), ref_L00_003DC1C0_00 * 0.020000001f, ref_L00_003DC1C0_03 * 0.00040000002f);
    if (temp_s1 == 0) {
        temp_s0 = *(s32 *)(b + 0x2290) + 0xE0;
        ref_L00_003DC1C0_06(arg1, arg1, temp_s0, ref_L00_003DC1C0_05(-0.19634955f, 0.19634955f));
    }
    return temp_s1;
}
