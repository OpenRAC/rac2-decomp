#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);

extern void ref_L00_003BC228_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_003BC228_01(void *, int, void *, int);

/* Builds a wobbly 16-point curve from a state block and draws it as a lightning bolt. */
void func_L00_003BC228(char *object, char *state) {
    CurveVector points[17];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 16; i++) {
        t = IntToFloat(i) / IntToFloat(15);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        ref_L00_003BC228_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-0.5f, 0.5f);
        jitter.values[1] = RandomFloatRange(-0.5f, 0.5f);
        jitter.values[2] = RandomFloatRange(-0.5f, 0.5f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x88) >= 10)
        ref_L00_003BC228_01(object, RandomIntRange(0x40, 0x80), points, 17);
    else
        ref_L00_003BC228_01(object, RandomIntRange(0, 0x40), points, 17);
}
