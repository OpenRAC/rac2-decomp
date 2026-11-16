#include "include_asm.h"

#include "common.h"
extern s32 func_PAL_L01_002BEC60(unsigned long, unsigned long);
extern float g_hero_move_speed_threshold;

void hero_set_move_state_by_speed_pal(void) {
    if (g_hero_move_speed_threshold < 0.054000005f)
        func_PAL_L01_002BEC60(0, 1);
    else
        func_PAL_L01_002BEC60(3, 1);
}

