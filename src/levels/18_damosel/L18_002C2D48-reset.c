#include "common.h"

/* The two arms on 0x340 are one in retail: jump2 cross-jumps them, the branch goes and its load
   stays as a dead lw that also ends the extended block, so the hero address is rebuilt. */

extern char g_hero_state[];

extern void mem_fast_helper_b(void *, int);
extern u8 D_L18_001A7B0B MACRO_ADDR;

/* Re-initialises the 16-byte block at 0x1490 and then, from the saved mode in it, raises the matching flags. */
void hero_reset_mode_flags(void)
{
    char *heroBase = g_hero_state;
    s16 savedMode = *(s16 *)(heroBase + 0x1490);
    u8 savedFlag = *(u8 *)(heroBase + 0x149D);
    mem_fast_helper_b(heroBase + 0x1490, 16);
    *(u8 *)(heroBase + 0x149D) = savedFlag;
    *(s16 *)(heroBase + 0x1490) = savedMode;
    *(u8 *)(heroBase + 0x22B9) = 0;
    *(s16 *)(heroBase + 0x348) = 0;
    if (*(u8 *)(heroBase + 0x22BD) != 0)
        return;
    if (*(int *)(heroBase + 0x340) != 0) {
        if (savedMode == -1)
            return;
    } else {
        if (savedMode == -1)
            return;
    }
    {
        if (savedMode == 2) {
            char *hero = g_hero_state;
            if (*(s16 *)(hero + 0x1DE) == 0 && (*(s16 *)(hero + 0x34C) == 0 || *(float *)(hero + 0x31C) < 2.5f)) {
                *(u8 *)(hero + 0x1497) = 1;
                if (*(u8 *)(hero + 0x22B4) == 0 && D_L18_001A7B0B != 0)
                    *(s16 *)(hero + 0x348) = 1;
            }
        }
        if (savedMode == 0xE) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x1494) = 1;
            *(float *)(hero + 0x24C4) = 0.2f;
            *(float *)(hero + 0x330) = *(float *)(hero + 0x318) + 0.2f;
        }
        if (savedMode == 0) {
            float comboTime;
            char *hero = g_hero_state;
            comboTime = *(float *)(hero + 0x330) - *(float *)(hero + 0x318);
            *(float *)(hero + 0x24C4) = comboTime;
            if (comboTime < 0.85f && comboTime > 0.25f)
                *(u8 *)(hero + 0x22B9) = 1;
            hero = g_hero_state;
            *(u8 *)(hero + 0x1494) = 1;
        }
        if (savedMode == 7) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x1492) = 1;
        }
        if (savedMode == 8) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x149A) = 1;
        }
        if (savedMode == 0xC) {
            char *hero = g_hero_state;
            *(u8 *)(hero + 0x149A) = 1;
        }
    }
}
