#include "include_asm.h"

#include "common.h"
extern s32 ref_L00_0037E5F0_literal_0;
extern s32 ref_L00_0037E5F0_00;
extern s32 g_001B26B4 __attribute__((sda));
extern f32 g_001B26B0 __attribute__((sda));

f32 func_PAL_L00_00381328(f32 fparg0) {
    f32 temp;
    f32 var_f1 = 0.0f;

    if (ref_L00_0037E5F0_00 != 0) {
        return 0.0f;
    }
    temp = g_001B26B0 - fparg0;
    g_001B26B0 = temp;
    if (temp < 0.0f) {
        var_f1 = -temp;
        *(s32*)(&ref_L00_0037E5F0_literal_0) = 0;
    }
    g_001B26B4 = 0xC;
    return var_f1;
}
