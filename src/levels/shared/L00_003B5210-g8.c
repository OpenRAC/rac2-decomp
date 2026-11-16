#include "names.h"
/* func_L00_003B5210 (180 bytes, 27 levels): for each of the four slots with a count,
   rebuilds its effect record from the slot's level scaled by the global factor. The two
   short tables are read through the absolute macro (MACRO_ADDR); the count-up index
   becomes the retail count-down loop. */
#include "common.h"
extern short g_jitter_trail_timers[] MACRO_ADDR;
extern short g_jitter_trail_alphas[] MACRO_ADDR;
extern float g_jitter_trail_alpha_scale;
extern char g_trail_points[];
extern float g_jitter_trail_core_width __attribute__((sda));
extern float g_jitter_trail_halo_width __attribute__((sda));
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_l00_draw_ribbon_with_halo_2(void *, int, int, int, float, float, float);
void jitter_trail_draw(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (g_jitter_trail_timers[i] != 0) {
            int v = FloatToInt(IntToFloat(g_jitter_trail_alphas[i]) * g_jitter_trail_alpha_scale);
            gfx_l00_draw_ribbon_with_halo_2(g_trail_points + i * 0x50, v, v, 5, g_jitter_trail_core_width, g_jitter_trail_halo_width, 0.2f);
        }
    }
}
