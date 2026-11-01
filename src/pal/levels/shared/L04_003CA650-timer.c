#include "include_asm.h"

#include "common.h"
extern float func_00283CE0(int);
extern u32 D_L04_001B2E84_1 MACRO_ADDR;
extern int D_L04_001B2E70 MACRO_ADDR;
extern int D_L04_001B2E7C MACRO_ADDR;
extern float D_L04_001B2E80 MACRO_ADDR;
extern int ref_L04_003C6FE8_00 SDATA(ref_L04_003C6FE8_00);
extern float ref_L04_003C6FE8_01 SDATA(ref_L04_003C6FE8_01);
extern float ref_L04_003C6FE8_02 SDATA(ref_L04_003C6FE8_02);

void func_PAL_L04_003CA650(u8 *a0)
{
    int v;

    switch (a0[0x20]) {
    case 0:
        v = 0x32;
        D_L04_001B2E84_1 = 0;
        a0[0x20] = 1;
        a0[0x30] = 0xFF;
        D_L04_001B2E70 = v;
        ref_L04_003C6FE8_00 = v;
        {
            float duration = func_00283CE0(v);
            ref_L04_003C6FE8_01 = 1.0f / duration;
        }
        D_L04_001B2E7C = v;
        D_L04_001B2E80 = 0.02f;
        break;
    case 1:
        {
            float t = ref_L04_003C6FE8_02 - 0.003f;

            ref_L04_003C6FE8_02 = t;
            if (t <= -8.0f)
                ref_L04_003C6FE8_02 = t + 8.0f;
        }
        break;
    }
}
