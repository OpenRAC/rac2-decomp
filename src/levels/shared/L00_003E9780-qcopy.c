#include "include_asm.h"
#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003E9490(void *, void *, void *, float);
extern void func_L00_003E9540(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_003E9B90(void *, int, void *, int);

extern void ref_L00_003E9780_00(void *, void *, void *, void *, void *, float);
/* Draws one crackling lightning arc between two points, bent along a curve with random wobble. */
void func_L00_003E9780(char *object, char *startPoint, char *endPoint, char *curveData) {
    CurveVector points[11];
    CurveVector start, end, jitter;
    int i;
    float t;
    CurveWord128 *startTangent = (CurveWord128 *)(curveData + 0x50);
    CurveWord128 *endTangent = (CurveWord128 *)(curveData + 0x60);
    for (i = 0; i < 10; i++) {
        t = IntToFloat(i) / IntToFloat(9);
        InterpolateVector(&points[i], startPoint, endPoint, t);
        start.word = *startTangent;
        end.word = *endTangent;
        FastVecAdd(&start, &start, startPoint);
        FastVecAdd(&end, &end, endPoint);
        ref_L00_003E9780_00(&points[i], startPoint, endPoint, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.04f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    DrawBeamRibbon_L00_2(object, 0x80, points, 11);
}
