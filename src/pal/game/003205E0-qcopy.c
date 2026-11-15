#include "include_asm.h"
#include "names.h"

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void math_interpolate_cubic_curve(void *, void *, void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
extern void DrawVariableWidthTwoLayerRibbon(void *, int, void *, int);

void func_PAL_003205E0(char *object, char *state) {
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
        math_interpolate_cubic_curve(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = math_random_float_range(-0.1f, 0.1f);
        jitter.values[1] = math_random_float_range(-0.1f, 0.1f);
        jitter.values[2] = math_random_float_range(-0.1f, 0.1f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x88) >= 8)
        DrawVariableWidthTwoLayerRibbon(object, math_random_int_range(0x40, 0x80), points, 25);
    else
        DrawVariableWidthTwoLayerRibbon(object, math_random_int_range(0, 0x40), points, 25);
}
