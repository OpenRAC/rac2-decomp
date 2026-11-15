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
    f32 savedSpeedA, savedSpeedB;

    if (vars[0x35D] != 0) {
        swamp_beast_collect_nearby(object, list, &count);
    }
    savedSpeedA = *(f32 *)(vars + 0x130);
    savedSpeedB = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = savedSpeedB + savedSpeedB;
        *(f32 *)(vars + 0x130) = savedSpeedA + savedSpeedA;
    }
    enemy_update_wander_heading(object, input, vars + 0x110);
    moby_follow_attached_target(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = savedSpeedA;
    *(f32 *)(vars + 0x138) = savedSpeedB;
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
    f32 savedSpeedA, savedSpeedB;
    int result;

    if (vars[0x35D] != 0) {
        swamp_beast_collect_nearby(object, list, &count);
    }
    savedSpeedA = *(f32 *)(vars + 0x130);
    savedSpeedB = *(f32 *)(vars + 0x138);
    if (count > 0) {
        *(f32 *)(vars + 0x138) = savedSpeedB + savedSpeedB;
        *(f32 *)(vars + 0x130) = savedSpeedA + savedSpeedA;
    }
    result = moby_turn_toward_target_and_step(object, input, *speed);
    moby_follow_attached_target(object);
    if (*(f32 *)(vars + 0x1B8) > 0.083333336f) {
        f32 scaled = *(f32 *)(vars + 0x1B8) * 0.9f;

        *(f32 *)(vars + 0x1B8) = (scaled < 0.083333336f) ? scaled : 0.083333336f;
    }
    *(f32 *)(vars + 0x130) = savedSpeedA;
    *(f32 *)(vars + 0x138) = savedSpeedB;
    if (vars[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
    return result;
}
