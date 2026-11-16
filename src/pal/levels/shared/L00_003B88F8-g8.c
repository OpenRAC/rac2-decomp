#include "common.h"

extern short g_jitter_trail_timers[];
extern short g_jitter_trail_counts[];
extern short g_jitter_trail_flags[];
extern int g_jitter_trail_param_a __attribute__((nosda));
extern int g_jitter_trail_param_b __attribute__((sda));
extern int g_jitter_trail_reset_value_a __attribute__((sda));
extern int g_jitter_trail_reset_value_b __attribute__((sda));
extern float g_jitter_trail_alpha_scale __attribute__((nosda));

/* func_PAL_L00_003B88F8, the PAL copy of func_L00_003B4E88: the same C, with both latches scaled to 50 Hz. */
void func_PAL_L00_003B88F8(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        g_jitter_trail_timers[i] = 2;
        g_jitter_trail_counts[i] = 2;
        g_jitter_trail_flags[i] = 1;
    }
    g_jitter_trail_param_a = ((s32)(g_jitter_trail_reset_value_a) * 5 + 2) / 6;
    g_jitter_trail_param_b = ((s32)(g_jitter_trail_reset_value_b) * 5 + 2) / 6;
    g_jitter_trail_alpha_scale = 1.0f;
}
