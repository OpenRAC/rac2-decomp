#include "include_asm.h"
#include "names.h"
extern char *g_scale_record_table __attribute__((section(".sdata")));
extern char *g_moby_pool_base __attribute__((section(".sdata")));
extern char *g_tie_class_table[];
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern float math_max_float(float, float);
extern void scale_vector(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
/* Sets up a size and scale record from a matrix block, and can mark it as done. */
void gfx_setup_scale_record(int index, int flag)
{
    char *rec = g_scale_record_table + index * 32;
    char *blk = g_moby_pool_base + index * 64;
    float a, m;
    matrix_mul_vec3(rec, g_tie_class_table[(unsigned char)rec[0x1D]] + 0x50, blk);
    a = FastVecLength(blk);
    a = math_max_float(a, FastVecLength(blk + 0x10));
    m = math_max_float(a, FastVecLength(blk + 0x20));
    *(float *)(rec + 0xC) = *(float *)(g_tie_class_table[(unsigned char)rec[0x1D]] + 0x5C) * m;
    scale_vector(rec, rec, *(float *)(blk + 0x3C));
    FastVecAdd(rec, rec, blk + 0x30);
    *(float *)(blk + 0xC) = 1.0f / FastVecLength(blk);
    *(float *)(blk + 0x1C) = 1.0f / FastVecLength(blk + 0x10);
    *(float *)(blk + 0x2C) = 1.0f / FastVecLength(blk + 0x20);
    if (flag != 0)
        rec[0x1E] = 1;
}
