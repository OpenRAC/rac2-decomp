#include "common.h"

extern float func_00283CE0(int);
extern u32 D_L04_001B2E84_1 MACRO_ADDR;
extern int D_L04_001B2E70 MACRO_ADDR;
extern int D_L04_001B2E7C MACRO_ADDR;
extern float D_L04_001B2E80 MACRO_ADDR;
extern int ref_L04_003C6FE8_00 SDATA(ref_L04_003C6FE8_00);
extern float ref_L04_003C6FE8_01 SDATA(ref_L04_003C6FE8_01);
extern float ref_L04_003C6FE8_02 SDATA(ref_L04_003C6FE8_02);

/* Update for a water timer object: starts a 60-frame countdown, then keeps scrolling the water texture. */
void func_L04_003C6FE8(u8 *moby)
{
    int frames;

    switch (moby[0x20]) {
    case 0:
        frames = 0x3C;
        D_L04_001B2E84_1 = 0;
        moby[0x20] = 1;
        moby[0x30] = 0xFF;
        D_L04_001B2E70 = frames;
        ref_L04_003C6FE8_00 = frames;
        {
            float duration = IntToFloat(frames);
            ref_L04_003C6FE8_01 = 1.0f / duration;
        }
        D_L04_001B2E7C = frames;
        D_L04_001B2E80 = 0.016666668f;
        break;
    case 1:
        {
            float scroll = ref_L04_003C6FE8_02 - 0.0025f;

            ref_L04_003C6FE8_02 = scroll;
            if (scroll <= -8.0f)
                ref_L04_003C6FE8_02 = scroll + 8.0f;
        }
        break;
    }
}
