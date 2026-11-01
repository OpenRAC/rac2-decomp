#include "include_asm.h"

#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int x4;
    unsigned char b8, b9;
    short hA;
    int xC;
    SplitVector v10, v20, v30;
} Particle6DD8;
extern unsigned char *D_001F25F4, *D_001F26A8;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float f);
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void *func_002B9030(int);
extern unsigned char *D_001F25F4;
extern int func_00283CF0(float f);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

char *func_PAL_002C7B18(void *a0, void *a1, int a2, float f1)
{
    V4_Fc3cb9262 vec;
    Particle6DD8 *s0;
    int v;
    SplitVector *pos;

    s0 = func_002B9030(0x5A);
    if (s0 != 0) {
        s0->x4 = 0x7FFFFFFF;
        s0->xC = 0x7FFFFFFF;
        v = func_00283CF0(2.0f);
        s0->b9 = (char)(v + 0x20);
        s0->b3 = 0x48;
        s0->b1 = 3;
        s0->b2 = *D_001F26A8;
        pos = &s0->v30;
        qcopy_nc(pos, a1);
        pos->f[3] = f1;
        qcopy_nc(&s0->v10, a0);
        func_00282F20(&vec, pos, 0.9f);
        func_00282CF0(&s0->v20, a0, &vec);
        s0->hA = a2;
        s0->v10.f[3] = 0.05f;
        s0->b8 = (char)(*(unsigned char *)&s0->hA - 0xC);
        s0->v20.f[3] = 2.0f;
    }
    return (char *)s0;
}
