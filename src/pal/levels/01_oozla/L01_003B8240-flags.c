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
void swamp_beast_move_pal(u8 *arg0, void *arg1) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);
    void *list[16];
    int count = 0;
    f32 f20, f21;

    if (s0[0x35D] != 0) {
        swamp_beast_collect_nearby(arg0, list, &count);
    }
    f20 = *(f32 *)(s0 + 0x130);
    f21 = *(f32 *)(s0 + 0x138);
    if (count > 0) {
        *(f32 *)(s0 + 0x138) = f21 + f21;
        *(f32 *)(s0 + 0x130) = f20 + f20;
    }
    enemy_update_wander_heading_pal(arg0, arg1, s0 + 0x110);
    moby_follow_attached_target_pal(arg0);
    if (*(f32 *)(s0 + 0x1B8) > 0.10000001f) {
        f32 v = *(f32 *)(s0 + 0x1B8) * 0.9f;

        *(f32 *)(s0 + 0x1B8) = (v < 0.10000001f) ? v : 0.10000001f;
    }
    *(f32 *)(s0 + 0x130) = f20;
    *(f32 *)(s0 + 0x138) = f21;
    if (s0[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
}

extern int moby_turn_toward_target_and_step_pal(void *, void *, f32);

/* The same as func_L01_003B49D8, with the extra helper call the object asks for. */
int swamp_beast_move_with_speed_pal(u8 *arg0, void *arg1, f32 *arg2) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);
    void *list[16];
    int count = 0;
    f32 f20, f21;
    int r;

    if (s0[0x35D] != 0) {
        swamp_beast_collect_nearby(arg0, list, &count);
    }
    f20 = *(f32 *)(s0 + 0x130);
    f21 = *(f32 *)(s0 + 0x138);
    if (count > 0) {
        *(f32 *)(s0 + 0x138) = f21 + f21;
        *(f32 *)(s0 + 0x130) = f20 + f20;
    }
    r = moby_turn_toward_target_and_step_pal(arg0, arg1, *arg2);
    moby_follow_attached_target_pal(arg0);
    if (*(f32 *)(s0 + 0x1B8) > 0.10000001f) {
        f32 v = *(f32 *)(s0 + 0x1B8) * 0.9f;

        *(f32 *)(s0 + 0x1B8) = (v < 0.10000001f) ? v : 0.10000001f;
    }
    *(f32 *)(s0 + 0x130) = f20;
    *(f32 *)(s0 + 0x138) = f21;
    if (s0[0x35D] != 0) {
        swamp_beast_clear_collected_marks(list, &count);
    }
    return r;
}
