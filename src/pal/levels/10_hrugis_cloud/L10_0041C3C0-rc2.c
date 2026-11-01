#include "include_asm.h"

#include "common.h"
#define NULL 0
extern void *ref_L10_004176C0_00();
extern void ref_L10_004176C0_01(s32, s32, s8 *, s32);
extern void ref_L10_004176C0_02(s8 *, s32, s32, f32, s32, f32, f32, f32, s32, s32, s32);
extern s32 ref_L10_004176C0_03(s32, s32);

void func_PAL_L10_0041C3C0(s8 *arg0) {
    s8 *s1;
    s8 *v;

    s1 = *(s8 **)(arg0 + 0x68);
    v = (s8 *)ref_L10_004176C0_00();
    if (v != NULL && *(s32 *)(v + 0x120) != 0 && *(s32 *)(s1 + 0x2E4) == 0) {
        ref_L10_004176C0_01(0, 0, arg0, 0xF86);
        ref_L10_004176C0_02(arg0, 0x6000FF00, 1, 0.5f, 0, 2.0f, 0.9f, 1.3f, 0x1E, 2, *(s32 *)(s1 + 0x2C0));
        ref_L10_004176C0_02(arg0, 0x6000FF00, 1, 0.5f, 0, 2.0f, 0.9f, 1.3f, 0x1E, 2, *(s32 *)(s1 + 0x2C4));
        *(s32 *)(s1 + 0x2E4) = ((s32)(ref_L10_004176C0_03(0x32, 0x78)) * 5 + 2) / 6;
    }
}
