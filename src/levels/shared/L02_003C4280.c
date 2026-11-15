#include "common.h"

extern void func_00282CF0(float *out, const float *a, const float *b);
extern void func_00282F20(float *out, const float *in, float s);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern float func_00282E80(void *a, void *b);

typedef struct {
    char pad00[4];
    float value;
    int index;
    float limit;
    char *points;
} Path_003C4280;

void func_L02_003C4280(void *a0, int a1) {
    Path_003C4280 *state = *(Path_003C4280 **)((char *)a0 + 0x68);
    float buf[4];

    if (state->index == *(int *)state->points - 1) {
        state->index = 0;
        qcopy((char *)a0 + 0x10, state->points + 0x10);
    }
    if (a1 == 0) {
        if (state->limit < 480.0f) {
            state->value += (0.03333f / state->value) * 0.00016666666f;
        } else {
            state->value += (0.03333f / state->value) * 0.00008333333f;
        }
    } else {
        state->value = 0.4166667f;
    }
    FastVecSub(buf, (float *)(state->points + (state->index * 16 + 0x20)), (float *)((char *)a0 + 0x10));
    vec_scale_to_length(buf, buf, state->value);
    FastVecAdd((char *)a0 + 0x10, (char *)a0 + 0x10, buf);
    if (vec_distance_xy((char *)a0 + 0x10, state->points + (state->index * 16 + 0x20)) <= state->value * 0.88f)
        state->index += 1;
}
