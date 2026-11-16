#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float g_platform_half_width __attribute__((sda));
extern float g_platform_half_height __attribute__((sda));
extern void matrix_from_basis_rows(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void transform_vector(void *,void *,void *);
extern float math_fabs(float);
/* Checks whether a point is just under an object and inside its footprint. Returns 1 if so. */
int platform_is_point_below(u8 *object,Vector *point)
{
    Vector origin;
    float matrix[16];
    Vector transformed,delta;
    origin.q=point->q;
    matrix_from_basis_rows(matrix,object+0xc0);
    FastVecSub(&delta,&origin,object+0x10);
    transformed.q=delta.q;
    transform_vector(&transformed,&transformed,matrix);
    if (math_fabs(transformed.f[0])<g_platform_half_width &&
        math_fabs(transformed.f[1])<g_platform_half_height &&
        math_fabs(origin.f[2]-*(float *)(object+0x18))<4.0f)
        if (*(float *)(object+0x18)-origin.f[2]>0.9f) return 1;
    return 0;
}
