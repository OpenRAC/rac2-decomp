#include "names.h"
/* func_L08_002BE8E8: the level 8 copy of the hero trigger reset (func_L18_002CA350 in
 * src/levels/18_damosel/L18_002C2D48-reset.c is the level 18 copy). As there, the two arms on
 * the busy field at +0x340 are one in retail: jump2 cross-jumps them, the branch goes and its
 * load stays as the dead lw, which also ends the extended block, so later blocks rebuild the
 * hero address (docs/contributing/matching-blockers.md, "jump2 cross-jumps two arms that end the same").
 * The rebase of `h` before the 0x1494 store is retail's address rebuild there.
 */
#include "common.h"

extern u8 g_hero_state[];
extern u8 D_001A7B0B __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern void mem_fast_helper_b(void *, s32);
extern float math_fabs(float);
extern s32 hero_l08_enter_state(s32, s32);

/* Preserve the selected action while refreshing its transient trigger flags. */
void hero_refresh_action_triggers(void)
{
    u8 *player = g_hero_state;
    s16 action = *(s16 *)(player + 0x1490);
    u8 saved = player[0x149D];

    mem_fast_helper_b(player + 0x1490, 16);
    *(s16 *)(player + 0x1490) = action;
    player[0x149D] = saved;
    player[0x22B9] = 0;
    *(u16 *)(player + 0x348) = 0;
    if (player[0x22BD])
        return;
    if (*(s32 *)(player + 0x340) != 0) {
        if (action == -1)
            return;
    } else {
        if (action == -1)
            return;
    }
    {
        if (action == 2) {
            u8 *m = g_hero_state;
            if (*(s16 *)(m + 0x1DE) == 0 && (*(s16 *)(m + 0x34C) == 0 || *(float *)(m + 0x31C) < 2.5f)) {
                m[0x1497] = 1;
                if (m[0x22B4] == 0 && D_001A7B0B != 0)
                    *(s16 *)(m + 0x348) = 1;
            }
        }
        if (action == 14) {
            u8 *h = g_hero_state;
            h[0x1494] = 1;
            *(float *)(h + 0x24C4) = 0.2f;
            *(float *)(h + 0x330) = *(float *)(h + 0x318) + 0.2f;
        }
        if (action == 0) {
            float d;
            u8 *h = g_hero_state;
            d = *(float *)(h + 0x330) - *(float *)(h + 0x318);
            *(float *)(h + 0x24C4) = d;
            if (d < 0.85f && d > 0.25f)
                h[0x22B9] = 1;
            h = g_hero_state;
            h[0x1494] = 1;
        }
        if (action == 3) {
            u8 *h = g_hero_state;
            h[0x1496] = 1;
        }
        if (action == 11) {
            u8 *h = g_hero_state;
            h[0x149B] = 1;
        }
        if (action == 7) {
            u8 *h = g_hero_state;
            h[0x1492] = 1;
        }
        if (action == 13) {
            u8 *h = g_hero_state;
            h[0x149C] = 1;
        }
        if (action == 8) {
            u8 *h = g_hero_state;
            h[0x149A] = 1;
        }
        if (action == 12) {
            u8 *h = g_hero_state;
            h[0x149A] = 1;
        }
    }

    if (g_hero_state[0x149C] && *(s32 *)(g_hero_state + 0x2294) != 0x7C &&
        math_fabs(*(float *)(g_hero_state + 0x330) - (*(float *)(g_hero_state + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(g_hero_state + 0x330) - *(float *)(g_hero_state + 0x88) > 0.0f &&
        (*(float *)(g_hero_state + 0x118) < 0.0f || *(s32 *)(g_hero_state + 0x2294) == 0x7B)) {
        hero_l08_enter_state(0x7C, 1);
    } else if (g_hero_state[0x1496] && *(s32 *)(g_hero_state + 0x2294) != 0x65 &&
        *(s32 *)(g_hero_state + 0x2294) != 0x78 &&
        math_fabs(*(float *)(g_hero_state + 0x334) - (*(float *)(g_hero_state + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(g_hero_state + 0x334) - *(float *)(g_hero_state + 0x88) > 0.0f &&
        (*(s32 *)(g_hero_state + 0x2294) != 0x66 || g_hero_state[0x49E]) &&
        (*(float *)(g_hero_state + 0x118) < 0.0f || *(s32 *)(g_hero_state + 0x2294) == 0x7B)) {
        if (!*(s32 *)(g_hero_state + 0x24CC))
            hero_l08_enter_state(0x78, 1);
        else
            hero_l08_enter_state(0x65, 1);
    } else if (g_hero_state[0x149B] && *(s32 *)(g_hero_state + 0x2294) != 0x78 &&
        *(s32 *)(g_hero_state + 0x2294) != 0x74 &&
        math_fabs(*(float *)(g_hero_state + 0x334) - (*(float *)(g_hero_state + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(g_hero_state + 0x334) - *(float *)(g_hero_state + 0x88) > 0.0f &&
        (*(float *)(g_hero_state + 0x118) < 0.0f || *(s32 *)(g_hero_state + 0x2294) == 0x7B)) {
        if (g_current_map_index == 13)
            hero_l08_enter_state(0x74, 1);
        else
            hero_l08_enter_state(0x78, 1);
    }
}
