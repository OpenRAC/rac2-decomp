#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float D_L17_001B023C __attribute__((sda));
extern float D_L17_001B0238 __attribute__((sda));
extern void func_00283698(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern float func_00282C48(float);
int func_L17_003C3A00(u8 *object,Vector *point)
{
    Vector origin;
    float matrix[16];
    Vector transformed,delta;
    origin.q=point->q;
    matrix_from_basis_rows(matrix,object+0xc0);
    FastVecSub(&delta,&origin,object+0x10);
    transformed.q=delta.q;
    transform_vector(&transformed,&transformed,matrix);
    if (func_00282C48(transformed.f[0])<D_L17_001B023C &&
        func_00282C48(transformed.f[1])<D_L17_001B0238 &&
        func_00282C48(origin.f[2]-*(float *)(object+0x18))<4.0f)
        if (*(float *)(object+0x18)-origin.f[2]>0.9f) return 1;
    return 0;
}
