#include "names.h"
/* func_L02_003D52A8 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -g). */
#include "common.h"

extern float g_chainblade_ground_height;
typedef int Vector __attribute__((mode(TI)));
extern float fast_vec_dist(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);


/* Moves the Chainblade into throwing position above the hero. Returns 0 if the spot is too high, 1 while moving and 2 once it has arrived. */
int chainblade_move_to_throw_position(char *self) {
    float goal_position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float *goal = goal_position;
    char *state = *(char **)(self + 0x68);
    float angle = 1.15f;
    float distance;
    float height;
    float sine;
    float cosine;
    *(Vector *)goal_position = *(Vector *)(self + 0x10);
    distance = fast_vec_dist(goal_position, *(char **)(state + 0x30C) + 0x10);
    sine = math_fast_sin_or_cos_a(angle);
    cosine = math_fast_sin_or_cos_b(angle);
    height = g_chainblade_ground_height + distance * sine / cosine;
    goal[2] = height - 4.2f;
    if (g_chainblade_ground_height + 5.0f < goal[2])
        return 0;
    if (goal[2] < g_chainblade_ground_height + 0.5f) {
        float scale = 4.7f / (goal[2] - g_chainblade_ground_height + 4.2f);
        FastVecSub(delta, self + 0x10, *(char **)(state + 0x30C) + 0x10);
        delta[2] = 0.0f;
        FastVecScale(delta, delta, scale);
        FastVecAdd(&goal_position, &goal_position, delta);
        math_step_value_toward_target(self + 0x10, state + 0x1B0, goal[0], 0.025f, 0.025f, 2.5000002f);
        math_step_value_toward_target(self + 0x14, state + 0x1B4, goal[1], 0.025f, 0.025f, 2.5000002f);
        math_approach_target_with_direction_mode(self + 0xF8, mat_fast_helper_a(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.003490659f, 0.003490659f, 0.22107507f, state + 0x1C4, 0);
    } else {
        math_step_value_toward_target(self + 0x18, state + 0x1B8, goal[2], 0.025f, 0.025f, 2.5000002f);
        math_approach_target_with_direction_mode(self + 0xF8, mat_fast_helper_a(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.003490659f, 0.003490659f, 0.22107507f, state + 0x1C4, 0);
    }
    if (fast_vec_dist(self + 0x10, &goal_position) < 0.0001f) {
        *(int *)(state + 0x1B8) = 0;
        return 2;
    }
    return 1;
}
