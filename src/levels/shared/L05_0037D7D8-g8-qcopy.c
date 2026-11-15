#include "include_asm.h"
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;

extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern void func_L00_003EA860(void *);
extern Vector4 D_L05_001B96C0;

/* A single strip of the func_L00_0038ADD0 kind from start to end, one colour, a caller
   texture, the same width at both ends and each end's basis taken from that end. */
void func_L05_0037D7D8(Vector4 *start, Vector4 *end, unsigned int color, int texture, float width)
{
    Beam strip;
    Vector4 basis[4], size;

    strip.tex = GetEffectTextureDescriptor(texture);
    size.bits = 0;
    strip.alpha = 0xFF9000000260UL;
    strip.test = 0x8000000048UL;
    strip.color[3] = strip.color[2] = strip.color[1] = strip.color[0] = color;
    size.f[2] = width;
    strip.tag = 0;
    size.f[3] = 1;
    func_L00_003EA860(&strip);
    strip.uv[0] = 0; strip.uv[1] = 0; strip.uv[2] = 0; strip.uv[3] = 1;
    strip.uv[4] = 1; strip.uv[5] = 0; strip.uv[6] = 1; strip.uv[7] = 1;
    FastVecSub(&basis[0], end, start); vec_scale_to_length(&basis[0], &basis[0], 1);
    FastVecSub(&basis[1], &D_L05_001B96C0, start); FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1); FastVecCross(&basis[1], &basis[0], &basis[2]);
    basis[3].bits = start->bits;
    strip.point[0].bits = size.bits;
    FastVecScale(&strip.point[1], &strip, -1);
    transform_vector(&strip, &strip, basis); transform_vector(&strip.point[1], &strip.point[1], basis);
    FastVecSub(&basis[0], end, start); vec_scale_to_length(&basis[0], &basis[0], 1);
    FastVecSub(&basis[1], &D_L05_001B96C0, end); FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1); FastVecCross(&basis[1], &basis[0], &basis[2]);
    basis[3].bits = end->bits;
    strip.point[2].bits = size.bits;
    FastVecScale(&strip.point[3], &strip.point[2], -1);
    transform_vector(&strip.point[2], &strip.point[2], basis); transform_vector(&strip.point[3], &strip.point[3], basis);
    draw_world_quad(&strip, 0, 0);
}
