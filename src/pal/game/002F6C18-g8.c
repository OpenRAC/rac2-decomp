#include "include_asm.h"
#include "names.h"
extern float g_mode_fade_scale __attribute__((sda));
extern float g_screen_fade;
extern void FadeToBlack(int);

/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */
void game_set_slowdown_factor_pal(void)
{
    g_mode_fade_scale = 1.2f;
    if (g_screen_fade < 1.0f)
        FadeToBlack(5);
}
