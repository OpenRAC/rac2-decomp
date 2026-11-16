#include "common.h"

extern s32 g_feltzin_challenge_data __attribute__((sda));
extern s32 D_L05_001B1350_4[] MACRO_ADDR;
extern u8 g_feltzin_save_counts[];

/* Caps each of the four mission counters at 127 and saves them in the save data. */
void feltzin_mission_clamp_save_counts(void) {
    if (g_feltzin_challenge_data > 0x7F) g_feltzin_challenge_data = 0x7F;
    if (D_L05_001B1350_4[1] > 0x7F) D_L05_001B1350_4[1] = 0x7F;
    if (D_L05_001B1350_4[2] > 0x7F) D_L05_001B1350_4[2] = 0x7F;
    if (D_L05_001B1350_4[3] > 0x7F) D_L05_001B1350_4[3] = 0x7F;

    g_feltzin_save_counts[0x61] = g_feltzin_challenge_data;
    g_feltzin_save_counts[0x62] = D_L05_001B1350_4[1];
    g_feltzin_save_counts[0x63] = D_L05_001B1350_4[2];
    g_feltzin_save_counts[0x64] = D_L05_001B1350_4[3];
}
