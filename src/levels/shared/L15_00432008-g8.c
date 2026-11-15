#include "common.h"

extern s32 D_L15_001B1520 __attribute__((sda));
extern s32 D_L15_001B1520_4[] MACRO_ADDR;
extern u8 D_L15_001395B8[];

/* Caps four volume values at 127 and copies them into the sound settings table. */
void func_L15_00432008(void)
{
    if (D_L15_001B1520 > 0x7F)
        D_L15_001B1520 = 0x7F;
    if (D_L15_001B1520_4[1] > 0x7F)
        D_L15_001B1520_4[1] = 0x7F;
    if (D_L15_001B1520_4[2] > 0x7F)
        D_L15_001B1520_4[2] = 0x7F;
    if (D_L15_001B1520_4[3] > 0x7F)
        D_L15_001B1520_4[3] = 0x7F;

    D_L15_001395B8[0x6B] = D_L15_001B1520;
    D_L15_001395B8[0x6C] = D_L15_001B1520_4[1];
    D_L15_001395B8[0x6D] = D_L15_001B1520_4[2];
    D_L15_001395B8[0x6E] = D_L15_001B1520_4[3];
}
