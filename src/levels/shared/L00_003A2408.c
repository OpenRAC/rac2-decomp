#include "include_asm.h"
#include "names.h"
extern float IntToFloat(int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Finds the direction pointing straight out of a small ring around a point. */
void vec_compute_ring_normal(char *object, void *position, void *out, float radius)
{
    char local[240];
    float *p;
    float angle;
    float step;
    int i;
    step = IntToFloat(11);
    step = 6.2831855f / step;
    angle = 0.0f;
    p = (float *)local;
    for (i = 1; i >= 0; --i) {
        angle = FastAddRotations(angle, step);
        p[3] = 0.0f;
        p[1] = 0.0f;
        p[0] = math_fast_sin_or_cos_a(angle) * radius;
        p[2] = -math_fast_sin_or_cos_b(angle) * radius;
        matrix_mul_vec3(p, p, object + 0xC0);
        FastVecAdd(p, p, position);
        p += 4;
    }
    FastVecSub(local + 208, local, position);
    FastVecSub(local + 224, local + 16, position);
    FastVecCross(out, local + 208, local + 224);
    vec_scale_to_length(out, out, 1.0f);
}
