#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);

extern void ref_L00_00412230_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_00412230_01(void *, int, void *, int);

/* Builds a jagged lightning bolt of 25 points between two ends, with small random wobble, and draws it. */
void func_L00_00412230(char *object, char *state) {
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
        ref_L00_00412230_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0xA8) >= 10)
        ref_L00_00412230_01(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        ref_L00_00412230_01(object, RandomIntRange(0, 0x40), points, 25);
}

extern void ref_L00_00417868_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_00417868_01(void *, int, void *, int);

/* Builds a jagged lightning bolt of 25 points between two ends, with small random wobble, and draws it. */
void func_L00_00417868(char *object, char *state) {
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
        ref_L00_00417868_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 10)
        ref_L00_00417868_01(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        ref_L00_00417868_01(object, RandomIntRange(0, 0x40), points, 25);
}


extern void ref_L05_00430318_00(void *, void *, void *, void *, void *, float);
extern void ref_L05_00430318_01(void *, int, void *, int);

/* Builds a jagged lightning bolt of 25 points between two ends, with small random wobble, and draws it. */
void func_L05_00430318(char *object, char *state) {
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
        ref_L05_00430318_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 10)
        ref_L05_00430318_01(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        ref_L05_00430318_01(object, RandomIntRange(0, 0x40), points, 25);
}
