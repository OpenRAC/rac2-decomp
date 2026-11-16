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
extern unsigned char *g_part_tex_drifting, *g_part_tex_spark_trail_table;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float f);
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void *part_alloc(int);
extern unsigned char *g_part_tex_drifting;
extern int FloatToInt(float f);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

char *part_spawn_trail_2_pal(void *a0, void *a1, int a2, float f1)
{
    V4_Fc3cb9262 vec;
    Particle6DD8 *s0;
    int v;
    SplitVector *pos;

    s0 = part_alloc(0x5A);
    if (s0 != 0) {
        s0->x4 = 0x7FFFFFFF;
        s0->xC = 0x7FFFFFFF;
        v = FloatToInt(2.0f);
        s0->b9 = (char)(v + 0x20);
        s0->b3 = 0x48;
        s0->b1 = 3;
        s0->b2 = *g_part_tex_spark_trail_table;
        pos = &s0->v30;
        qcopy_nc(pos, a1);
        pos->f[3] = f1;
        qcopy_nc(&s0->v10, a0);
        vec_scale_to_length(&vec, pos, 0.9f);
        FastVecSub(&s0->v20, a0, &vec);
        s0->hA = a2;
        s0->v10.f[3] = 0.05f;
        s0->b8 = (char)(*(unsigned char *)&s0->hA - 0xC);
        s0->v20.f[3] = 2.0f;
    }
    return (char *)s0;
}
