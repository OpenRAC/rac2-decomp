#include "include_asm.h"
#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003A1F68(void *, void *, void *, float);
extern void func_L00_003A2018(void *, void *, void *, void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_003A2668(void *, int, void *, int);

extern void ref_L00_003A2258_00(void *, void *, void *, void *, void *, float);
/* Draws a wavy beam between two points by building a jittery curve and drawing it as a ribbon. */
void func_L00_003A2258(char *object, char *pointA, char *pointB, char *curveData) {
    CurveVector points[11];
    CurveVector start, end, jitter;
    int i;
    float t;
    CurveWord128 *startTangent = (CurveWord128 *)(curveData + 0x50);
    CurveWord128 *endTangent = (CurveWord128 *)(curveData + 0x60);
    for (i = 0; i < 10; i++) {
        t = IntToFloat(i) / IntToFloat(9);
        LerpVectorExact(&points[i], pointA, pointB, t);
        start.word = *startTangent;
        end.word = *endTangent;
        FastVecAdd(&start, &start, pointA);
        FastVecAdd(&end, &end, pointB);
        ref_L00_003A2258_00(&points[i], pointA, pointB, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[1] = RandomFloatRange(-1.0f, 1.0f);
        jitter.values[2] = RandomFloatRange(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.04f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    DrawBeamRibbon_L00(object, 0x80, points, 11);
}
