#include "common.h"

extern s32 g_challenge_completed_a __attribute__((sda));
extern s32 D_L15_001B1520_4[] MACRO_ADDR;
extern u8 g_sound_volume_slots[];

/* Caps four volume values at 127 and copies them into the sound settings table. */
void snd_clamp_copy_volumes(void)
{
    if (g_challenge_completed_a > 0x7F)
        g_challenge_completed_a = 0x7F;
    if (D_L15_001B1520_4[1] > 0x7F)
        D_L15_001B1520_4[1] = 0x7F;
    if (D_L15_001B1520_4[2] > 0x7F)
        D_L15_001B1520_4[2] = 0x7F;
    if (D_L15_001B1520_4[3] > 0x7F)
        D_L15_001B1520_4[3] = 0x7F;

    g_sound_volume_slots[0x6B] = g_challenge_completed_a;
    g_sound_volume_slots[0x6C] = D_L15_001B1520_4[1];
    g_sound_volume_slots[0x6D] = D_L15_001B1520_4[2];
    g_sound_volume_slots[0x6E] = D_L15_001B1520_4[3];
}
