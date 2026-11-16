#include "include_asm.h"

#include "common.h"
extern void swamp_beast_collect_nearby(void *, void **, int *);
extern void swamp_beast_clear_collected_marks(char **, int *);
extern void moby_follow_attached_target_pal(void *);
extern void enemy_update_wander_heading_pal(void *, void *, void *);

/* Doubles the two speeds while the object list is not empty, runs the two helpers
   and clamps the 0x1B8 rate to an eighth; the speeds are put back afterwards.
   The clamp needs -ffast-math (the retail's min.s): it is in a file of its own
   because the flag changes the other bodies of a shared unit. */
void swamp_beast_move_pal(u8 *moby, void *input) {
    u8 *state = *(u8 **)(moby + 0x68);
    void *list[16];
    int count = 0;
    f32 saved_speed_a, saved_speed_b;

    if (state[0x35D] != 0) {
        swamp_beast_collect_nearby(moby, list, &count);
    }
    saved_speed_a = *(f32 *)(state + 0x130);
    saved_speed_b = *(f32 *)(state + 0x138);
    if (count > 0) {
        *(f32 *)(state + 0x138) = saved_speed_b + saved_speed_b;
        *(f32 *)(state + 0x130) = saved_speed_a + saved_speed_a;
    }
    enemy_update_wander_heading_pal(moby, input, state + 0x110);
    moby_follow_attached_target_pal(moby);
    if (*(f32 *)(state + 0x1B8) > 0.10000001f) {
        f32 new_rate = *(f32 *)(state + 0x1B8) * 0.9f;

        *(f32 *)(state + 0x1B8) = (new_rate < 0.10000001f) ? new_rate : 0.10000001f;
    }
    *(f32 *)(state + 0x130) = saved_speed_a;
    *(f32 *)(state + 0x138) = saved_speed_b;
    if (state[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
}

extern int moby_turn_toward_target_and_step_pal(void *, void *, f32);

/* The same as func_L01_003B49D8, with the extra helper call the object asks for. */
int swamp_beast_move_with_speed_pal(u8 *moby, void *input, f32 *speed) {
    u8 *state = *(u8 **)(moby + 0x68);
    void *list[16];
    int count = 0;
    f32 saved_speed_a, saved_speed_b;
    int result;

    if (state[0x35D] != 0) {
        swamp_beast_collect_nearby(moby, list, &count);
    }
    saved_speed_a = *(f32 *)(state + 0x130);
    saved_speed_b = *(f32 *)(state + 0x138);
    if (count > 0) {
        *(f32 *)(state + 0x138) = saved_speed_b + saved_speed_b;
        *(f32 *)(state + 0x130) = saved_speed_a + saved_speed_a;
    }
    result = moby_turn_toward_target_and_step_pal(moby, input, *speed);
    moby_follow_attached_target_pal(moby);
    if (*(f32 *)(state + 0x1B8) > 0.10000001f) {
        f32 new_rate = *(f32 *)(state + 0x1B8) * 0.9f;

        *(f32 *)(state + 0x1B8) = (new_rate < 0.10000001f) ? new_rate : 0.10000001f;
    }
    *(f32 *)(state + 0x130) = saved_speed_a;
    *(f32 *)(state + 0x138) = saved_speed_b;
    if (state[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
    return result;
}
