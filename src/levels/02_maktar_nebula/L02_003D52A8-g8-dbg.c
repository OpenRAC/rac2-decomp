/* func_L02_003D52A8 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -g). */
#include "common.h"

extern float D_L02_001B01B8;
typedef int Vector __attribute__((mode(TI)));
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AAA00(void *, float, float, float, float, void *, int);


/* Moves the Chainblade into throwing position above the hero. Returns 0 if the spot is too high, 1 while moving and 2 once it has arrived. */
int func_L02_003D52A8(char *self) {
    float goalPosition[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float *goal = goalPosition;
    char *state = *(char **)(self + 0x68);
    float angle = 1.15f;
    float distance;
    float height;
    float sine;
    float cosine;
    *(Vector *)goalPosition = *(Vector *)(self + 0x10);
    distance = fast_vec_dist(goalPosition, *(char **)(state + 0x30C) + 0x10);
    sine = FastSinOrCosA(angle);
    cosine = FastSinOrCosB(angle);
    height = D_L02_001B01B8 + distance * sine / cosine;
    goal[2] = height - 4.2f;
    if (D_L02_001B01B8 + 5.0f < goal[2])
        return 0;
    if (goal[2] < D_L02_001B01B8 + 0.5f) {
        float scale = 4.7f / (goal[2] - D_L02_001B01B8 + 4.2f);
        FastVecSub(delta, self + 0x10, *(char **)(state + 0x30C) + 0x10);
        delta[2] = 0.0f;
        FastVecScale(delta, delta, scale);
        FastVecAdd(&goalPosition, &goalPosition, delta);
        StepValueTowardTarget(self + 0x10, state + 0x1B0, goal[0], 0.025f, 0.025f, 2.5000002f);
        StepValueTowardTarget(self + 0x14, state + 0x1B4, goal[1], 0.025f, 0.025f, 2.5000002f);
        ApproachTargetWithDirectionMode(self + 0xF8, FastMatrixHelperA(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.003490659f, 0.003490659f, 0.22107507f, state + 0x1C4, 0);
    } else {
        StepValueTowardTarget(self + 0x18, state + 0x1B8, goal[2], 0.025f, 0.025f, 2.5000002f);
        ApproachTargetWithDirectionMode(self + 0xF8, FastMatrixHelperA(*(float *)(*(char **)(state + 0x30C) + 0x10) - *(float *)(self + 0x10),
                         *(float *)(*(char **)(state + 0x30C) + 0x14) - *(float *)(self + 0x14)), 0.003490659f, 0.003490659f, 0.22107507f, state + 0x1C4, 0);
    }
    if (fast_vec_dist(self + 0x10, &goalPosition) < 0.0001f) {
        *(int *)(state + 0x1B8) = 0;
        return 2;
    }
    return 1;
}
