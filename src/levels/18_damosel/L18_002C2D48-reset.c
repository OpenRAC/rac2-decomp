#include "common.h"

/* The two arms on 0x340 are one in retail: jump2 cross-jumps them, the branch goes and its load
   stays as a dead lw that also ends the extended block, so the hero address is rebuilt. */

extern char g_hero_state[];

extern void mem_fast_helper_b(void *, int);
extern u8 D_L18_001A7B0B MACRO_ADDR;

/* Re-initialises the 16-byte block at 0x1490 and then, from the saved mode in it, raises the matching flags. */
void hero_reset_mode_flags(void)
{
    char *hero_base = g_hero_state;
    s16 saved_mode = *(s16 *)(hero_base + 0x1490);
    u8 saved_flag = *(u8 *)(hero_base + 0x149D);
    mem_fast_helper_b(hero_base + 0x1490, 16);
    *(u8 *)(hero_base + 0x149D) = saved_flag;
    *(s16 *)(hero_base + 0x1490) = saved_mode;
    *(u8 *)(hero_base + 0x22B9) = 0;
    *(s16 *)(hero_base + 0x348) = 0;
    if (*(u8 *)(hero_base + 0x22BD) != 0)
        return;
    if (*(int *)(hero_base + 0x340) != 0) {
        if (saved_mode == -1)
            return;
    } else {
        if (saved_mode == -1)
            return;
    }
    {
        if (saved_mode == 2) {
            char *hero = g_hero_state;
            if (*(s16 *)(hero + 0x1DE) == 0 && (*(s16 *)(hero + 0x34C) == 0 || *(float *)(hero + 0x31C) < 2.5f)) {
                *(u8 *)(hero + 0x1497) = 1;
                if (*(u8 *)(hero + 0x22B4) == 0 && D_L18_001A7B0B != 0)
                    *(s16 *)(hero + 0x348) = 1;
            }
        }
        if (saved_mode == 0xE) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x1494) = 1;
            *(float *)(hero + 0x24C4) = 0.2f;
            *(float *)(hero + 0x330) = *(float *)(hero + 0x318) + 0.2f;
        }
        if (saved_mode == 0) {
            float combo_time;
            char *hero = g_hero_state;
            combo_time = *(float *)(hero + 0x330) - *(float *)(hero + 0x318);
            *(float *)(hero + 0x24C4) = combo_time;
            if (combo_time < 0.85f && combo_time > 0.25f)
                *(u8 *)(hero + 0x22B9) = 1;
            hero = g_hero_state;
            *(u8 *)(hero + 0x1494) = 1;
        }
        if (saved_mode == 7) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x1492) = 1;
        }
        if (saved_mode == 8) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x149A) = 1;
        }
        if (saved_mode == 0xC) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x149A) = 1;
        }
    }
}
