#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { int count; int reserved[3]; Vector points[0]; } Path;
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
/* The EE keeps integer and FP argument order in independent register banks. */
extern void scale_vector_radius(float, void *, const void *) __asm__("func_00282F20");
extern void func_00282CC0(void *, const void *, const void *);
extern const Vector D_0018A0E0;
extern const Path *D_L00_001FDA80[];
extern float func_00282DB0(const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);
extern float func_00282C48(float);
extern float func_00282DF0(const void *);

/* Push the point away from the active edges while retaining its plane height. */
/* Pushes a point away from the edges of a path so it stays a set distance from them. Returns 1 if the point was moved. */
int func_L00_003425F8(int pathIndex, const Vector *point, Vector *out, float radius) {
    Vector relative, displacement, position, segment, unit, cross, planePart;
    int hit = 0;
    const Path *path;
    int i;
    float height, side, length, along;
    const Vector *start;
    qcopy(&position, point);
    path = D_L00_001FDA80[pathIndex];
    height = FastVecDot(&position, &D_0018A0E0);
    for (i = 0; i < path->count - 1; ++i) {
        if (path->points[i].f[3] == 0.0f && path->points[i + 1].f[3] == 0.0f)
            continue;
        start = &path->points[i];
        FastVecSub(&relative, &position, start);
        FastVecSub(&segment, &path->points[i + 1], start);
        along = FastVecDot(&relative, &D_0018A0E0);
        vec_scale_to_length(&planePart, &D_0018A0E0, along);
        FastVecSub(&relative, &relative, &planePart);
        vec_scale_to_length(&planePart, &D_0018A0E0, FastVecDot(&segment, &D_0018A0E0));
        FastVecSub(&segment, &segment, &planePart);
        vec_scale_to_length(&unit, &segment, 1.0f);
        FastVecCross(&cross, &relative, &unit);
        side = FloatAbs(FastVecDot(&cross, &D_0018A0E0));
        if (!(side > radius)) {
            length = FastVecLength(&segment);
            along = FastVecDot(&relative, &unit);
            if (length < along || along < 0.0f) {
                if (FastVecLength(&relative) < radius) {
                    vec_scale_to_length(&displacement, &relative, radius);
                    FastVecAdd(&position, &displacement, start);
                    hit = 1;
                }
            } else {
                hit = 1;
                vec_scale_to_length(&planePart, &unit, along);
                FastVecSub(&displacement, &relative, &planePart);
                scale_vector_radius(radius, &displacement, &displacement);
                FastVecAdd(&displacement, &displacement, &planePart);
                FastVecAdd(&position, &displacement, start);
            }
        }
    }
    if (hit) {
        height -= FastVecDot(&position, &D_0018A0E0);
        vec_scale_to_length(&segment, &D_0018A0E0, height);
        FastVecAdd(out, &position, &segment);
    }
    return hit;
}
