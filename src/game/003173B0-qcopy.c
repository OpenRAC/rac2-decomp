#include "include_asm.h"
#include "names.h"

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_0031E7D8(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern void func_0031F210(void *, int, void *, int);

/* Draws a jagged lightning bolt between two points as a ribbon of 25 shaky points. */
void func_0031EFC8(char *object, char *state) {
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
        InterpolateCubicCurve_0031E7D8(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-0.1f, 0.1f);
        jitter.values[1] = RandomFloatRange(-0.1f, 0.1f);
        jitter.values[2] = RandomFloatRange(-0.1f, 0.1f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x88) >= 10)
        DrawVariableWidthTwoLayerRibbon(object, RandomIntRange(0x40, 0x80), points, 25);
    else
        DrawVariableWidthTwoLayerRibbon(object, RandomIntRange(0, 0x40), points, 25);
}
