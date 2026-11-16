#include "include_asm.h"

#include "common.h"
extern void UpdateRotatingBouncingEffect(void);
extern void gfx_add_draw_callback_third(void *, void *);
extern void part_spawn_fading_spark(void);
typedef int BatchA_A17_s32;

/* func_L02_003D28E0 lives in the -g8 sibling: it reads five $gp-relative scalars. */

/* When the +0x3C counter of the object at +0x68 is clear, runs the reset, then the dispatch. */
void moby_reset_and_run_dispatch_pal(char *moby) {
    char *moby_ref = moby;

    if (*(BatchA_A17_s32 *)(*(BatchA_A17_s32 *)(moby_ref + 0x68) + 0x3C) == 0)
        UpdateRotatingBouncingEffect();
    gfx_add_draw_callback_third((void *)part_spawn_fading_spark, moby_ref);
}

