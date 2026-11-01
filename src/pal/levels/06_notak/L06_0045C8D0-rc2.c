#include "include_asm.h"

#include "common.h"
extern void *ref_L06_00457920_00(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void ref_L06_00457920_01(s32, s32, f32);
extern s32 ref_L06_00457920_02;
extern s8 ref_L06_00457920_03[];

void func_PAL_L06_0045CA40(void *arg0) {
    void *temp_s0;
    s32 temp_a0;
    s32 var_s2;

    var_s2 = 0;
    do {
        temp_s0 = ref_L06_00457920_00(arg0, 2, (*(s16 *)((s8 *)(arg0) + (0xAA))), var_s2, (s8 *)arg0 + 0x10, (s8 *)arg0 + 0xF0, &ref_L06_00457920_02, 0xFF, 0.0f, 10.0f);
        var_s2 += 1;
        if (temp_s0 != 0) {
            temp_a0 = (*(s32 *)((s8 *)(temp_s0) + (0x68)));
            ref_L06_00457920_01(temp_a0, temp_a0 + 0x20, 0.0024f);
            (*(s32 *)((s8 *)(temp_s0) + (0x64))) = (s32)ref_L06_00457920_03;
        }
    } while (var_s2 < 0xF);
}
