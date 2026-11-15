#include "common.h"
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char g_hero_position[];
extern char *D_L08_001B29DC[] __attribute__((sda));
extern int math_random_int_below(int);
extern int GetFirstMobyInGroup(void *, int, int, int);
extern int GetNextMobyInGroup(void *, void *, int, int);
extern void crawler_pick_walk_target(char *);

/* Picks a new walking goal for the Spitting Dune Crawler, steers it away from nearby creatures and its mount, then refines the goal. */
void crawler_choose_goal(char *object) {
    float delta[4];
    char *other;
    char *state = *(char **)(object + 0x68);

    if (*(int *)(state + 0x44C) && vec_distance_xy(object + 0x10, g_hero_position) < 8.0f) {
        FastVecSub(delta, object + 0x10, g_hero_position);
        delta[2] = 0;
        vec_scale_to_length(delta, delta, 8.0f);
        FastVecAdd(state + 0x3F0, object + 0x10, delta);
    } else if (*(int *)(state + 0x254) != 2 && !math_random_int_below(2)) {
        *(float *)(state + 0x3F0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
        {
            float y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
            *(float *)(state + 0x3F8) = 0;
            *(float *)(state + 0x3F4) = y;
            FastVecAdd(state + 0x3F0, state + 0x3F0, g_hero_position);
        }
    } else {
        *(float *)(state + 0x3F0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 8.0f;
        {
            float y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 8.0f;
            *(float *)(state + 0x3F8) = 0;
            *(float *)(state + 0x3F4) = y;
            FastVecAdd(state + 0x3F0, state + 0x3F0, object + 0x10);
        }
    }
    other = 0;
    GetFirstMobyInGroup(&other, (unsigned char)object[0x21], 0, 0);
    while (other) {
        float distance = vec_distance_xy(object + 0x10, other + 0x10);
        if (distance < 3.0f) {
            FastVecSub(delta, object + 0x10, other + 0x10);
            vec_scale_to_length(delta, delta, 4.0f / distance);
            FastVecAdd(state + 0x3F0, state + 0x3F0, delta);
        }
        GetNextMobyInGroup(&other, other, 0, 0);
    }
    if (*(int *)(state + 0x468) != -1) {
        char *mount = D_L08_001B29DC[0] + (*(int *)(state + 0x468) << 8);
        if (mount && (unsigned char)mount[0x20] != 0xFE && (unsigned char)mount[0x20] != 0xFD &&
            (vec_distance_xy(object + 0x10, mount + 0x10) < 3.6f ||
             vec_distance_xy(state + 0x3F0, D_L08_001B29DC[0] + (*(int *)(state + 0x468) << 8) + 0x10) < 3.6f)) {
            FastVecSub(delta, object + 0x10, D_L08_001B29DC[0] + (*(int *)(state + 0x468) << 8) + 0x10);
            delta[2] = 0;
            vec_scale_to_length(delta, delta, 5.0f);
            FastVecAdd(state + 0x3F0, delta, object + 0x10);
        }
    }
    *(float *)(state + 0x3F8) = *(float *)(object + 0x18);
    crawler_pick_walk_target(object);
}
