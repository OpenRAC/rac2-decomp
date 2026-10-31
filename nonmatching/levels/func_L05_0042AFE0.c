/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections -g.
 * us: 0/4; us2: 0/4; pal: 0/4.
 * 724/724 bytes after the measured entry repair, 0/4 in each release. Callback address
 * constructions in AC30 and its PAL counterpart establish the live F1 load before the prologue
 * in all twelve placements. C emits that load naturally. First mismatch+0x20: actor-save/store
 * and later branch-likely load scheduling. Default and debug profiles tie. No C or handwritten-
 * assembly credit.
 * Reopen: New actor/phase scheduling evidence on the corrected entry, not a fabricated FP formal.
 */
#include "common.h"
extern u8 D_L05_001B1680[] SDATA(D_L05_001B1680);
extern float func_00283180(float), func_00283198(float);
extern void func_L05_0042BB10(void *);
extern void func_L05_0042B2C0(void *, void *, int, int,
                           float, float, float, float, float, float);
#define PHASE_FIELD(i) (*(float *)(D_L05_001B1680 + 4 * (i)))
#define DRAW_WORD(i) (*(int *)(D_L05_001B1680 + 4 * (i)))

/* The registered callback entry includes the first phase load before the prologue. */
void func_L05_0042AFE0(u8 *actor)
{
    float direction[4] __attribute__((aligned(16)));
    PHASE_FIELD(21) += PHASE_FIELD(22);
    if (PHASE_FIELD(21) > 7.0f) PHASE_FIELD(21) -= 7.0f;
    else if (PHASE_FIELD(21) < -7.0f) PHASE_FIELD(21) += 7.0f;
    PHASE_FIELD(26) += PHASE_FIELD(27);
    if (PHASE_FIELD(26) > 7.0f) PHASE_FIELD(26) -= 7.0f;
    else if (PHASE_FIELD(26) < -7.0f) PHASE_FIELD(26) += 7.0f;
    PHASE_FIELD(31) += PHASE_FIELD(32);
    if (PHASE_FIELD(31) > 7.0f) PHASE_FIELD(31) -= 7.0f;
    else if (PHASE_FIELD(31) < -7.0f) PHASE_FIELD(31) += 7.0f;
    PHASE_FIELD(33) += PHASE_FIELD(34);
    if (PHASE_FIELD(33) > 7.0f) PHASE_FIELD(33) -= 7.0f;
    else if (PHASE_FIELD(33) < -7.0f) PHASE_FIELD(33) += 7.0f;
    PHASE_FIELD(35) += PHASE_FIELD(36);
    if (PHASE_FIELD(35) > 7.0f) PHASE_FIELD(35) -= 7.0f;
    else if (PHASE_FIELD(35) < -7.0f) PHASE_FIELD(35) += 7.0f;
    direction[0] = func_00283180(*(float *)(actor + 0xF8));
    direction[1] = func_00283198(*(float *)(actor + 0xF8));
    direction[2] = 0.0f;
    func_L05_0042BB10(actor);
    func_L05_0042B2C0(actor + 0x10, direction, DRAW_WORD(38), DRAW_WORD(10),
                     PHASE_FIELD(8), PHASE_FIELD(1), PHASE_FIELD(20) * 0.03225806355f,
                     PHASE_FIELD(19) * 0.2f, 0.0f, PHASE_FIELD(21));
    func_L05_0042B2C0(actor + 0x10, direction, DRAW_WORD(37), DRAW_WORD(9),
                     PHASE_FIELD(7), PHASE_FIELD(0), PHASE_FIELD(14) * 0.03225806355f,
                     PHASE_FIELD(13) * 0.2f, PHASE_FIELD(31), PHASE_FIELD(21));
    func_L05_0042B2C0(actor + 0x10, direction, DRAW_WORD(40), DRAW_WORD(12),
                     PHASE_FIELD(7), PHASE_FIELD(0), PHASE_FIELD(18) * 0.03225806355f,
                     PHASE_FIELD(17) * 0.2f, PHASE_FIELD(33), PHASE_FIELD(26));
    func_L05_0042B2C0(actor + 0x10, direction, DRAW_WORD(39), DRAW_WORD(11),
                     PHASE_FIELD(7), PHASE_FIELD(0), PHASE_FIELD(16) * 0.03225806355f,
                     PHASE_FIELD(15) * 0.2f, PHASE_FIELD(35), PHASE_FIELD(21));
}
