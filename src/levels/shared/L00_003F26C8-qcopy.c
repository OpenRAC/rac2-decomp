#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_0031AA28(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
/* The renderer is func_0032BE30 at 23 places and func_L05_00398A38 at four. */
extern void ref_L00_003F26C8_00(void *, int, void *, int);

/* Builds a wobbly curve of 24 points between two end points, shakes each point by a small
   random amount, and draws it. */
void func_L00_003F26C8(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float fraction;
    for (i = 0; i < 24; i++) {
        fraction = IntToFloat(i) / IntToFloat(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        InterpolateCubicVector_L00(&points[i], state + 0x20, state + 0x30, &start, &end, fraction);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 10)
        ref_L00_003F26C8_00(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        ref_L00_003F26C8_00(object, RandomIntRange(0, 0x40), points, 25);
}
