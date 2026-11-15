#include "common.h"

extern s32 D_L05_001B1350 __attribute__((sda));
extern s32 D_L05_001B1350_4[] MACRO_ADDR;
extern u8 D_L05_001395B8[];

/* Caps each of the four mission counters at 127 and saves them in the save data. */
void feltzin_mission_clamp_save_counts(void) {
    if (D_L05_001B1350 > 0x7F) D_L05_001B1350 = 0x7F;
    if (D_L05_001B1350_4[1] > 0x7F) D_L05_001B1350_4[1] = 0x7F;
    if (D_L05_001B1350_4[2] > 0x7F) D_L05_001B1350_4[2] = 0x7F;
    if (D_L05_001B1350_4[3] > 0x7F) D_L05_001B1350_4[3] = 0x7F;

    D_L05_001395B8[0x61] = D_L05_001B1350;
    D_L05_001395B8[0x62] = D_L05_001B1350_4[1];
    D_L05_001395B8[0x63] = D_L05_001B1350_4[2];
    D_L05_001395B8[0x64] = D_L05_001B1350_4[3];
}
