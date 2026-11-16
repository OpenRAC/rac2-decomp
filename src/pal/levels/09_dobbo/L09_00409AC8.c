#include "include_asm.h"




#include "common.h"
extern int moby_l01_turn_toward_target(char *, char *);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern s32 func_325E78(char *moby, s32 target);
extern f32 func_2EA578(char *moby, char *target);
extern f32 func_2EA3E0(f32 x);

/* Moves the object toward a point, using one of two movement helpers depending on the mode. */
int dobbo_move_toward_point_pal(char *moby, char *target, s32 use_speed) {
    char *vars = *(char **)(moby + 0x68);
    int result;
    if (use_speed == 0) {
        result = moby_l01_turn_toward_target(moby, target);
    } else {
        result = moby_turn_toward_target_and_step(moby, (float *)target, *(f32 *)(vars + 0x33C));
    }
    return result;
}

extern int FastDecTimer(char *vars);
extern void moby_update_eased_node(char *moby, char *target, s32 use_speed, f32 f12, f32 f13);
extern void value_set_and_smooth_pal(char *moby, char *target, s32 use_speed, s32 a3, f32 f12);
extern s32 moby_count_group_not_in_state(s32 moby, s32 target);

/* Counts down the object's two timers, bumps its frame counter and updates its two effects (PAL: 50 Hz rates). */
void dobbo_tick_timers_effects_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    u16 ticks;
    FastDecTimer(vars + 0x330);
    FastDecTimer(vars + 0x332);
    ticks = *(u16 *)(moby + 0x96);
    if (ticks < 0xFFFF) {
        *(u16 *)(moby + 0x96) = ticks + 1;
    }
    moby_update_eased_node(moby, vars + 0x280, 0, 0.0432f, 0.43200004f);
    value_set_and_smooth_pal(moby, vars + 0x360, 0, 1, 1.5f);
}

