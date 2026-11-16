#include "common.h"
typedef int Q128 __attribute__((mode(TI)));

extern int g_sheepinator_l00_beam_reset_2[] MACRO_ADDR;
extern float g_sheepinator_beam_range __attribute__((sda));
extern float g_sheepinator_segment_length __attribute__((sda));
extern float g_sheepinator_beam_scroll_x __attribute__((sda));
extern float g_sheepinator_beam_scroll_y __attribute__((sda));
extern float g_sheepinator_beam_scroll_z __attribute__((sda));
extern int g_sheepinator_spin_angle[] MACRO_ADDR;
extern int g_sheepinator_spark_cooldown[] MACRO_ADDR;
extern int g_sheepinator_spark_active[] MACRO_ADDR;
extern Q128 g_sheepinator_spark_directions[] MACRO_ADDR;
extern Q128 g_sheepinator_beam_points[];
extern Q128 g_sheepinator_beam_offsets[];
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Resets the Sheepinator beam: sets up the start points of its twelve segments and clears its sparks. */
void sheepinator_reset_beam(char *owner)
{
    char local[16] __attribute__((aligned(16)));
    char *inner;
    float rate;
    int i;
    int j;

    inner = *(char **)(owner + 0x68);
    if (g_sheepinator_l00_beam_reset_2[0] == 0)
        return;
    g_sheepinator_l00_beam_reset_2[0] = 0;
    rate = g_sheepinator_beam_range / IntToFloat(12);
    g_sheepinator_segment_length = rate;
    FastVecScale(&local, owner + 0xC0, -rate);
    qcopy(&g_sheepinator_beam_points[0], inner);
    for (i = 10; i >= 0; i--) {
        FastVecAdd(&g_sheepinator_beam_points[11 - i], &g_sheepinator_beam_offsets[11 - i], &local);
    }
    *(int *)&g_sheepinator_beam_scroll_x = 0;
    *(int *)&g_sheepinator_beam_scroll_y = 0;
    *(int *)&g_sheepinator_beam_scroll_z = 0;
    g_sheepinator_spin_angle[0] = 0;
    g_sheepinator_spark_cooldown[0] = 0;
    for (j = 0; j < 3; j++) {
        g_sheepinator_spark_active[j] = 0;
        qcopy(&g_sheepinator_spark_directions[j], local);
    }
}
