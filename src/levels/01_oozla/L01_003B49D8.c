#include "include_asm.h"
#include "common.h"

extern void swamp_beast_collect_nearby(void *, void **, int *);

extern void swamp_beast_clear_collected_marks(char **, int *);

extern void moby_follow_attached_target(void *);

extern void enemy_update_wander_heading(void *, void *, void *);

extern int moby_turn_toward_target_and_step(void *, void *, f32);

/* Doubles the two speeds while the object list is not empty, runs the two helpers
   and clamps the 0x1B8 rate to an eighth; the speeds are put back afterwards.
   The clamp needs -ffast-math (the retail's min.s): it is in a file of its own
   because the flag changes the other bodies of a shared unit. */
/* Moves a swimming creature for one frame. It moves faster while it is touching other objects, and limits how fast it can turn. */
void swamp_beast_move(u8 *object, void *input) {
    u8 *vars = *(u8 **)(object + 0x68);
    void *list[16];
    int count = 0;
    f32 saved_speed_a, saved_speed_b;

    if (vars[0x35D] != 0) {
        swamp_beast_collect_nearby(object, list, &count);
    }
    saved_speed_a = *(f32 *)(vars + 0x130);
    saved_speed_b = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = saved_speed_b + saved_speed_b;
        *(f32 *)(vars + 0x130) = saved_speed_a + saved_speed_a;
    }
    enemy_update_wander_heading(object, input, vars + 0x110);
    moby_follow_attached_target(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = saved_speed_a;
    *(f32 *)(vars + 0x138) = saved_speed_b;
    if (vars[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
}

/* The same as func_L01_003B49D8, with the extra helper call the object asks for. */
/* Same as the function above but uses a different move helper and returns its result. */
int swamp_beast_move_with_speed(u8 *object, void *input, f32 *speed) {
    u8 *vars = *(u8 **)(object + 0x68);
    void *list[16];
    int count = 0;
    f32 saved_speed_a, saved_speed_b;
    int result;

    if (vars[0x35D] != 0) {
        swamp_beast_collect_nearby(object, list, &count);
    }
    saved_speed_a = *(f32 *)(vars + 0x130);
    saved_speed_b = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = saved_speed_b + saved_speed_b;
        *(f32 *)(vars + 0x130) = saved_speed_a + saved_speed_a;
    }
    result = moby_turn_toward_target_and_step(object, input, *speed);
    moby_follow_attached_target(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = saved_speed_a;
    *(f32 *)(vars + 0x138) = saved_speed_b;
    if (vars[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
    return result;
}
