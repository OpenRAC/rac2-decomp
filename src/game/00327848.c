#include "include_asm.h"
/* func_00327848: func_00327848 with the turn state in the record (+0x34 flag, +0x38 slack). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char ref_00327848_00[];

extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, char *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, char *);
extern void func_00282DD8(void *, void *, void *);
extern float func_002831B0(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);

/* Steers the object's heading toward the vector stored in its record: builds the aim vector, measures the angle to the current heading and turns the heading by a tenth of the remainder. */
void func_00327848(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[12] __attribute__((aligned(16)));
    char *rec = *(char **)(obj + 0x68);
    char *dir, *face;
    float cosine;

    a[0] = *(float *)(rec + 0x10);
    a[1] = *(float *)(rec + 0x14);
    a[2] = 0.0f;
    a[3] = 0.0f;
    *(s32 *)(rec + 0x34) = 0;
    *(float *)(rec + 0x38) = *(float *)(rec + 0x38) * 0.7f;
    if (FastVecLength(a) != 0.0f) {
        dir = obj + 0xE0;
        face = obj + 0xC0;
        vec_scale_to_length(a, a, 1.0f);
        matrix_mul_vec3(a, a, ref_00327848_00);
        cosine = FastVecDot(a, dir);
        FastVecScale(b, dir, cosine);
        FastVecSub(a, a, b);
        vec_scale_to_length(a, a, 1.0f);
        vec_scale_to_length(c, a, 10.0f);
        FastVecAdd(c, c, obj + 0x10);
        FastVecCross(d, face, a);
        if (FastVecLength(d) == 0.0f)
            qcopy(d, face);
        cosine = FastVecDot(face, a);
        *(float *)(rec + 0x38) = 1.0f - cosine;
        if (cosine > 0.75f)
            *(s32 *)(rec + 0x34) = 1;
        cosine = 1.5707964f - FastAngleHelper(cosine);
        cosine = cosine * 0.1f;
        FastVecScale(e, d, FastSinOrCosB(cosine));
        e[3] = FastSinOrCosA(cosine);
        quaternion_to_rotation_basis(e, f);
        multiply_matrix3x3(face, f, face);
    }
}
