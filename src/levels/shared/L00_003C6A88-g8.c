#include "names.h"
/* Beam-chain and pulse reset, following the corresponding
 * reset_beam_chain_and_pulse_state in OpenRAC/rac1-decomp (GPL-3.0).
 * Incomplete small-data arrays retain the measured absolute macro accesses;
 * scalar floats use GP addressing. The scrolling phases are cleared by bits.
 */
#include "common.h"
typedef int Q128 __attribute__((mode(TI)));

extern int g_sheepinator_l00_beam_reset[] MACRO_ADDR;
extern float g_aim_target_range __attribute__((sda));
extern float g_lightning_l00_segment_length_2 __attribute__((sda));
extern float g_ribbon_scroll_u __attribute__((sda));
extern float g_ribbon_scroll_v __attribute__((sda));
extern float g_ribbon_scroll_w __attribute__((sda));
extern int g_lightning_spin_angle[] MACRO_ADDR;
extern int g_lightning_spark_cooldown[] MACRO_ADDR;
extern int g_lightning_spark_active[] MACRO_ADDR;
extern Q128 g_lightning_spark_directions[] MACRO_ADDR;
extern Q128 g_lightning_beam_points[];
extern Q128 g_lightning_beam_offsets[];
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Resets the beam chain and its pulse timers the first time it is needed. Each chain point is moved back along the beam direction. */
void ResetBeamChainAndPulseState(char *owner)
{
    char shift[16] __attribute__((aligned(16)));
    char *vars;
    float step;
    int i;
    int slot;

    vars = *(char **)(owner + 0x68);
    if (g_sheepinator_l00_beam_reset[0] == 0)
        return;
    g_sheepinator_l00_beam_reset[0] = 0;
    step = g_aim_target_range / IntToFloat(12);
    g_lightning_l00_segment_length_2 = step;
    FastVecScale(&shift, owner + 0xC0, -step);
    qcopy(&g_lightning_beam_points[0], vars);
    for (i = 10; i >= 0; i--) {
        FastVecAdd(&g_lightning_beam_points[11 - i], &g_lightning_beam_offsets[11 - i], &shift);
    }
    *(int *)&g_ribbon_scroll_u = 0;
    *(int *)&g_ribbon_scroll_v = 0;
    *(int *)&g_ribbon_scroll_w = 0;
    g_lightning_spin_angle[0] = 0;
    g_lightning_spark_cooldown[0] = 0;
    for (slot = 0; slot < 3; slot++) {
        g_lightning_spark_active[slot] = 0;
        qcopy(&g_lightning_spark_directions[slot], shift);
    }
}
