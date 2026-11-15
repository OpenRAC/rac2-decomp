#include "include_asm.h"
#include "names.h"
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Finds the direction pointing straight out of a small ring around a point. */
void func_L00_003A2408(char *object, void *position, void *out, float radius)
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
        p[0] = FastSinOrCosA(angle) * radius;
        p[2] = -FastSinOrCosB(angle) * radius;
        matrix_mul_vec3(p, p, object + 0xC0);
        FastVecAdd(p, p, position);
        p += 4;
    }
    FastVecSub(local + 208, local, position);
    FastVecSub(local + 224, local + 16, position);
    FastVecCross(out, local + 208, local + 224);
    vec_scale_to_length(out, out, 1.0f);
}
