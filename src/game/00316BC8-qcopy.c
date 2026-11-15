#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7AE0(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern void func_00316E08(void *, int, void *, int);
extern void func_0032BE30(void *, int, void *, int);

/* Builds a 25-point curve with a little random shake and draws it as a lightning bolt. */
void func_00316BC8(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 24; i++) {
        t = IntToFloat(i) / IntToFloat(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        CatmullRomVector(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x88) >= 7)
        DrawLightningRibbon_00316E08(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        DrawLightningRibbon_00316E08(object, RandomIntRange(0, 0x40), points, 25);
}

/* Builds a 25-point curve with a little random shake and draws it as a lightning bolt, the second version. */
void func_0032BBF0(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 24; i++) {
        t = IntToFloat(i) / IntToFloat(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        CatmullRomVector(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 10)
        DrawBeamRibbon_0032BE30(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        DrawBeamRibbon_0032BE30(object, RandomIntRange(0, 0x40), points, 25);
}
