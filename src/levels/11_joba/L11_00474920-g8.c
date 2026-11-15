#include "names.h"
typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern u8 *g_moby_l11_table;
extern int D_L11_001A8FF4;
extern int D_L11_001B30C8;
extern int D_L11_001B2AAC __attribute__((sda));
extern float D_L11_001B2AA0 __attribute__((sda));
extern float D_L11_001B2AA4 __attribute__((sda));
extern float D_L11_001B2AA8 __attribute__((sda));
extern float D_L11_001B2AB0 __attribute__((sda));
extern int moby_is_state_at_least_2(u8 *);
extern int math_fast_helper_a(float *, float);
extern void moby_start_idle_anim_variant(u8 *);
extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void anim_start_blended(u8 *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern u8 *arena_get_center_point(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);

/* Updates an arena crowd member (moby class 4718): it switches between idle, cheering and clapping as the crowd excitement rises and falls. */
void arena_crowd_update(u8 *object) {
    float bounds[4];
    float center[4];
    int *state = *(int **)(object + 0x68);
    u8 *target;
    float level, angle, heading, delta;
    int animation;
    if (!moby_is_state_at_least_2(g_moby_l11_table + *state * 0x100)) return;
    *(Quadword *)center = 0;
    center[0] = *(float *)(object + 0x10);
    center[1] = *(float *)(object + 0x14);
    center[2] = *(float *)(object + 0x18);
    center[3] = 5.0f;
    *(Quadword *)bounds = *(Quadword *)center;
    if (math_fast_helper_a(bounds, 255.0f) <= 0 || D_L11_001A8FF4) {
        *(unsigned short *)(object + 0x32) = 0;
        return;
    }
    *(unsigned short *)(object + 0x32) = 255;
    moby_start_idle_anim_variant(object);
    target = (u8 *)(*state * 0x100 + (int)g_moby_l11_table);
    level = *(float *)(*(u8 **)(target + 0x68) + 0x14C);
    switch (object[0x20]) {
    case 1:
        if (flag_set_first_pending(object) && object[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended(object, animation, 0, 10);
        }
        if (level > D_L11_001B2AA8 && !math_random_int_below(60)) {
            moby_set_state(object, 2, -1);
        } else if (level < D_L11_001B2AA0 && !math_random_int_below(60)) {
            moby_set_state(object, 3, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != math_random_int_below(2) + 2) {
                animation = math_random_int_below(2);
                anim_start_blended(object, animation + 2, 0, 10);
            }
            return;
        }
        if (level < D_L11_001B2AA4 && !math_random_int_below(60)) moby_set_state(object, 1, -1);
        break;
    case 3:
        angle = ((float)(D_L11_001B30C8 % D_L11_001B2AAC) * -6.2831855f) / (float)D_L11_001B2AAC + 3.1415927f;
        delta = *(float *)(object + 0x10) - *(float *)arena_get_center_point(target);
        target = arena_get_center_point(g_moby_l11_table + *state * 0x100);
        heading = mat_fast_helper_a(delta, *(float *)(object + 0x14) - *(float *)(target + 4));
        if (FastDiffRots(heading, angle) < D_L11_001B2AB0 ||
            FastDiffRots(heading, FastAddRotations(angle, 3.1415927f)) < D_L11_001B2AB0) {
            if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended(object, animation, 0, 10);
        }
        if (level > D_L11_001B2AA4 && !math_random_int_below(60)) moby_set_state(object, 1, -1);
        break;
    }
}
