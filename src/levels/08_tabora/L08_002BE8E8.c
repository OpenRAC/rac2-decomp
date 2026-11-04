/* func_L08_002BE8E8: the level 8 copy of the hero trigger reset (func_L18_002CA350 in
 * src/levels/18_damosel/L18_002C2D48-reset.c is the level 18 copy). As there, the two arms on
 * the busy field at +0x340 are one in retail: jump2 cross-jumps them, the branch goes and its
 * load stays as the dead lw, which also ends the extended block, so later blocks rebuild the
 * hero address (docs/MATCHING-BLOCKERS.md, "jump2 cross-jumps two arms that end the same").
 * The rebase of `h` before the 0x1494 store is retail's address rebuild there.
 */
#include "common.h"

extern u8 D_00189E20[];
extern u8 D_001A7B0B __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern void func_00282A88(void *, s32);
extern float func_00282C48(float);
extern s32 func_L08_002D2ED8(s32, s32);

/* Preserve the selected action while refreshing its transient trigger flags. */
void func_L08_002BE8E8(void)
{
    u8 *player = D_00189E20;
    s16 action = *(s16 *)(player + 0x1490);
    u8 saved = player[0x149D];

    func_00282A88(player + 0x1490, 16);
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
            u8 *m = D_00189E20;
            if (*(s16 *)(m + 0x1DE) == 0 && (*(s16 *)(m + 0x34C) == 0 || *(float *)(m + 0x31C) < 2.5f)) {
                m[0x1497] = 1;
                if (m[0x22B4] == 0 && D_001A7B0B != 0)
                    *(s16 *)(m + 0x348) = 1;
            }
        }
        if (action == 14) {
            u8 *h = D_00189E20;
            h[0x1494] = 1;
            *(float *)(h + 0x24C4) = 0.2f;
            *(float *)(h + 0x330) = *(float *)(h + 0x318) + 0.2f;
        }
        if (action == 0) {
            float d;
            u8 *h = D_00189E20;
            d = *(float *)(h + 0x330) - *(float *)(h + 0x318);
            *(float *)(h + 0x24C4) = d;
            if (d < 0.85f && d > 0.25f)
                h[0x22B9] = 1;
            h = D_00189E20;
            h[0x1494] = 1;
        }
        if (action == 3) {
            u8 *h = D_00189E20;
            h[0x1496] = 1;
        }
        if (action == 11) {
            u8 *h = D_00189E20;
            h[0x149B] = 1;
        }
        if (action == 7) {
            u8 *h = D_00189E20;
            h[0x1492] = 1;
        }
        if (action == 13) {
            u8 *h = D_00189E20;
            h[0x149C] = 1;
        }
        if (action == 8) {
            u8 *h = D_00189E20;
            h[0x149A] = 1;
        }
        if (action == 12) {
            u8 *h = D_00189E20;
            h[0x149A] = 1;
        }
    }

    if (D_00189E20[0x149C] && *(s32 *)(D_00189E20 + 0x2294) != 0x7C &&
        func_00282C48(*(float *)(D_00189E20 + 0x330) - (*(float *)(D_00189E20 + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(D_00189E20 + 0x330) - *(float *)(D_00189E20 + 0x88) > 0.0f &&
        (*(float *)(D_00189E20 + 0x118) < 0.0f || *(s32 *)(D_00189E20 + 0x2294) == 0x7B)) {
        func_L08_002D2ED8(0x7C, 1);
    } else if (D_00189E20[0x1496] && *(s32 *)(D_00189E20 + 0x2294) != 0x65 &&
        *(s32 *)(D_00189E20 + 0x2294) != 0x78 &&
        func_00282C48(*(float *)(D_00189E20 + 0x334) - (*(float *)(D_00189E20 + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(D_00189E20 + 0x334) - *(float *)(D_00189E20 + 0x88) > 0.0f &&
        (*(s32 *)(D_00189E20 + 0x2294) != 0x66 || D_00189E20[0x49E]) &&
        (*(float *)(D_00189E20 + 0x118) < 0.0f || *(s32 *)(D_00189E20 + 0x2294) == 0x7B)) {
        if (!*(s32 *)(D_00189E20 + 0x24CC))
            func_L08_002D2ED8(0x78, 1);
        else
            func_L08_002D2ED8(0x65, 1);
    } else if (D_00189E20[0x149B] && *(s32 *)(D_00189E20 + 0x2294) != 0x78 &&
        *(s32 *)(D_00189E20 + 0x2294) != 0x74 &&
        func_00282C48(*(float *)(D_00189E20 + 0x334) - (*(float *)(D_00189E20 + 0x88) + 0.25f)) < 1.0f &&
        *(float *)(D_00189E20 + 0x334) - *(float *)(D_00189E20 + 0x88) > 0.0f &&
        (*(float *)(D_00189E20 + 0x118) < 0.0f || *(s32 *)(D_00189E20 + 0x2294) == 0x7B)) {
        if (D_001A79F0 == 13)
            func_L08_002D2ED8(0x74, 1);
        else
            func_L08_002D2ED8(0x78, 1);
    }
}
