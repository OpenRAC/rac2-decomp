#include "common.h"

extern short g_jitter_trail_timers[];
extern short g_jitter_trail_counts[];
extern short g_jitter_trail_flags[];
extern int g_jitter_trail_param_a __attribute__((nosda));
extern int g_jitter_trail_param_b __attribute__((nosda));
extern int g_jitter_trail_reset_value_a __attribute__((sda));
extern int g_jitter_trail_reset_value_b __attribute__((sda));
extern float g_jitter_trail_alpha_scale __attribute__((sda));

/* Resets the four slots of each of three short tables and clears the paired latches. */
void jitter_trail_reset_slots(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        g_jitter_trail_timers[i] = 2;
        g_jitter_trail_counts[i] = 2;
        g_jitter_trail_flags[i] = 1;
    }
    g_jitter_trail_param_a = g_jitter_trail_reset_value_a;
    g_jitter_trail_param_b = g_jitter_trail_reset_value_b;
    g_jitter_trail_alpha_scale = 1.0f;
}
