#include "include_asm.h"

#include "common.h"
extern void FastVecSub(float *out, const float *a, const float *b);
extern void vec_scale_to_length(float *out, const float *in, float s);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern float vec_distance_xy(void *a, void *b);
typedef struct {
    char pad00[4];
    float value;
    int index;
    float limit;
    char *points;
} Path_003C4280;

void func_PAL_L02_003C7F88(void *a0, int a1) {
    Path_003C4280 *state = *(Path_003C4280 **)((char *)a0 + 0x68);
    float buf[4];

    if (state->index == *(int *)state->points - 1) {
        state->index = 0;
        qcopy((char *)a0 + 0x10, state->points + 0x10);
    }
    if (a1 == 0) {
        if (state->limit < 4.8e+02f) {
            state->value += (0.03333f / state->value) * 0.00020000001f;
        } else {
            state->value += (0.03333f / state->value) * 0.000100000005f;
        }
    } else {
        state->value = 0.50000006f;
    }
    FastVecSub(buf, (float *)(state->points + (state->index * 16 + 0x20)), (float *)((char *)a0 + 0x10));
    vec_scale_to_length(buf, buf, state->value);
    FastVecAdd((char *)a0 + 0x10, (char *)a0 + 0x10, buf);
    if (vec_distance_xy((char *)a0 + 0x10, state->points + (state->index * 16 + 0x20)) <= state->value * 0.88f)
        state->index += 1;
}
