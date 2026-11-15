#include "include_asm.h"
#include "names.h"
typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_interpolate(void *, void *, void *, float);
extern void math_interpolate_curve_point(void *, void *, void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void gfx_l00_draw_beam_ribbon(void *, int, void *, int);

extern void ref_L00_003E9780_00(void *, void *, void *, void *, void *, float);
/* Draws one crackling lightning arc between two points, bent along a curve with random wobble. */
void gfx_draw_lightning_arc(char *object, char *startPoint, char *endPoint, char *curveData) {
    CurveVector points[11];
    CurveVector start, end, jitter;
    int i;
    float t;
    CurveWord128 *startTangent = (CurveWord128 *)(curveData + 0x50);
    CurveWord128 *endTangent = (CurveWord128 *)(curveData + 0x60);
    for (i = 0; i < 10; i++) {
        t = IntToFloat(i) / IntToFloat(9);
        vec_interpolate(&points[i], startPoint, endPoint, t);
        start.word = *startTangent;
        end.word = *endTangent;
        FastVecAdd(&start, &start, startPoint);
        FastVecAdd(&end, &end, endPoint);
        ref_L00_003E9780_00(&points[i], startPoint, endPoint, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[1] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[2] = math_random_float_range(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.04f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    gfx_l00_draw_beam_ribbon(object, 0x80, points, 11);
}
