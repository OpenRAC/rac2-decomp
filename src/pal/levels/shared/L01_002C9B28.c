#include "include_asm.h"

#include "common.h"
extern s32 SetHeroMoveState_pal(unsigned long, unsigned long);
extern float g_hero_move_speed_threshold;

/* Puts the hero in the idle move state when slow and the run state when fast (PAL). */
void hero_set_move_state_by_speed_pal(void) {
    if (g_hero_move_speed_threshold < 0.054000005f)
        SetHeroMoveState_pal(0, 1);
    else
        SetHeroMoveState_pal(3, 1);
}

