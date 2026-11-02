/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * Retained near miss, GPT-6.1 Sol (high), task v0978, 29 October 2026.
 * Compiler: pinned game EE-GCC 2.9-ee-991111b.
 * Profile: -O2 -G0 -ffunction-sections.
 * check.py: 1072/1076 bytes, 0/1 places in US, US2 and PAL.
 * No linked build was run; complete retail semantics remain unverified.
 *
 * New hypothesis from MATCHING-BLOCKERS.md (func_L00_00303418): ordinary
 * __attribute__((sda)) on D_001A79F0 reproduces the mixed GP/absolute reads.
 * The GP load fills the floating branch delay slot; the other load expands
 * absolutely. Reversing the equivalent 0x24CC and level-index selections also
 * reproduces retail's branch direction and argument setup. All variants stay
 * 1072 bytes, but these suffix instructions now agree apart from relocation
 * operands and the existing four-byte displacement of the whole suffix.
 *
 * Still missing: retail's dead lw v0,0x340(s1) at US 0x002BE938. Earlier base
 * lifetimes and action-14/action-0 store/address scheduling also differ.
 * No volatile qualifier, alias, artificial dependency or extra read was added.
 * Reopen only with evidence for the original field/control-flow contract or
 * supported compiler behavior retaining that dead read.
 *
 * Historical attempts: persistent base 1012, no-GCSE tie 1012, direct globals
 * 1072, G8/combined animation choice 1064 bytes. Do not repeat flag sweeps.
 * Required declarations are included below. The clear takes two GPR arguments;
 * the animation helper takes two GPR arguments and returns an integer boolean.
 * RAC1's apply_hero_selected_flags_and_state_transitions in
 * src/overlays/shared/hero_idle_and_animation.c corroborates the flag-update
 * and follow-up movement-state structure, but not the dead RAC2 +0x340 read.
 */
#include "common.h"

extern u8 D_00189E20[];
extern u8 D_001A7B0B;
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
    if (player[0x22BD] || action == -1)
        return;
    if (action == 2 && *(s16 *)(D_00189E20 + 0x1DE) == 0 &&
        (*(s16 *)(D_00189E20 + 0x34C) == 0 || *(float *)(D_00189E20 + 0x31C) < 2.5f)) {
        D_00189E20[0x1497] = 1;
        if (!D_00189E20[0x22B4] && D_001A7B0B)
            *(u16 *)(D_00189E20 + 0x348) = 1;
    }
    if (action == 14) {
        D_00189E20[0x1494] = 1;
        *(float *)(D_00189E20 + 0x330) = *(float *)(D_00189E20 + 0x318) + 0.2f;
        *(float *)(D_00189E20 + 0x24C4) = 0.2f;
    }
    if (action == 0) {
        float remaining = *(float *)(D_00189E20 + 0x330) - *(float *)(D_00189E20 + 0x318);
        *(float *)(D_00189E20 + 0x24C4) = remaining;
        if (remaining < 0.85f && remaining > 0.25f)
            D_00189E20[0x22B9] = 1;
        D_00189E20[0x1494] = 1;
    }
    if (action == 3)
        D_00189E20[0x1496] = 1;
    if (action == 11)
        D_00189E20[0x149B] = 1;
    if (action == 7)
        D_00189E20[0x1492] = 1;
    if (action == 13)
        D_00189E20[0x149C] = 1;
    if (action == 8)
        D_00189E20[0x149A] = 1;
    if (action == 12)
        D_00189E20[0x149A] = 1;

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
