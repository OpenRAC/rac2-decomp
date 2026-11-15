#include "include_asm.h"
#include "names.h"
extern char *D_001B2514 __attribute__((section(".sdata")));
extern char *D_001B251C __attribute__((section(".sdata")));
extern char *D_L00_00226700[];
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_L00_002EE050(float, float);
extern void func_00282D60(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* Sets up a size and scale record from a matrix block, and can mark it as done. */
void func_L00_0036AE00(int index, int flag)
{
    char *rec = D_001B2514 + index * 32;
    char *blk = D_001B251C + index * 64;
    float a, m;
    matrix_mul_vec3(rec, D_L00_00226700[(unsigned char)rec[0x1D]] + 0x50, blk);
    a = FastVecLength(blk);
    a = MaxFloat(a, FastVecLength(blk + 0x10));
    m = MaxFloat(a, FastVecLength(blk + 0x20));
    *(float *)(rec + 0xC) = *(float *)(D_L00_00226700[(unsigned char)rec[0x1D]] + 0x5C) * m;
    scale_vector(rec, rec, *(float *)(blk + 0x3C));
    FastVecAdd(rec, rec, blk + 0x30);
    *(float *)(blk + 0xC) = 1.0f / FastVecLength(blk);
    *(float *)(blk + 0x1C) = 1.0f / FastVecLength(blk + 0x10);
    *(float *)(blk + 0x2C) = 1.0f / FastVecLength(blk + 0x20);
    if (flag != 0)
        rec[0x1E] = 1;
}
