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
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern void ref_L02_004230B0_00(void *);
extern Vector4 D_L02_001BA500;
extern unsigned int D_L02_001B1FE0 __attribute__((sda));
extern unsigned int D_L02_001B1FE4 __attribute__((sda));

/* The func_L09_003AF9E8 spark with its colours from two level words (the second one's
   edge masked to RGB) and the owner's scale at +0x60. */
/* Draws a short bright spark streak starting at a point, with a wider glow behind it. */
void func_L02_004230B0(char *object, Vector4 *start)
{
    Beam first, second;
    Vector4 basis[4], end, nearSize, farSize;
    char *work = *(char **)(object + 0x68);
    float width;
    unsigned long test;

    end.f[0] = RandomFloatRange(-1, 1);
    end.f[1] = RandomFloatRange(-1, 1);
    end.f[2] = RandomFloatRange(-1, 1);
    vec_scale_to_length(&end, &end, RandomFloatRange(0.25f, 0.65f));
    FastVecAdd(&end, start, &end);
    first.tex = GetEffectTextureDescriptor(23);
    first.alpha = 0xFF9000000260UL;
    first.tag = 0;
    test = ((unsigned long)(Rand() % 2 + 1) << 2) | 0x8000000040UL;
    first.color[0] = first.color[1] = D_L02_001B1FE0;
    first.color[2] = first.color[3] = D_L02_001B1FE0;
    first.test = test;
    second.tex = GetEffectTextureDescriptor(23);
    nearSize.bits = 0;
    farSize.bits = 0;
    second.alpha = 0xFF9000000260UL;
    second.test = 0x8000000048UL;
    second.tag = 0;
    second.color[0] = second.color[1] = D_L02_001B1FE4;
    second.color[2] = second.color[3] = D_L02_001B1FE4 & 0xFFFFFF;
    nearSize.f[3] = 1;
    farSize.f[3] = 1;
    width = RandomFloatRange(0.1f, 0.2f);
    nearSize.f[2] = width;
    farSize.f[2] = width + width;
    nearSize.f[2] *= *(float *)(work + 0x60);
    farSize.f[2] *= *(float *)(work + 0x60);
    ref_L02_004230B0_00(&first);
    ref_L02_004230B0_00(&second);
    if (Rand() & 1) {
        first.uv[0] = 0; first.uv[1] = 0; first.uv[2] = 0; first.uv[3] = 1;
        first.uv[4] = 1; first.uv[5] = 0; first.uv[6] = 1; first.uv[7] = 1;
        second.uv[0] = 0; second.uv[1] = 0; second.uv[2] = 0; second.uv[3] = 1;
        second.uv[4] = 1; second.uv[5] = 0; second.uv[6] = 1; second.uv[7] = 1;
    } else {
        first.uv[0] = 0; first.uv[1] = 1; first.uv[2] = 0; first.uv[3] = 0;
        first.uv[4] = 1; first.uv[5] = 1; first.uv[6] = 1; first.uv[7] = 0;
        second.uv[0] = 0; second.uv[1] = 1; second.uv[2] = 0; second.uv[3] = 0;
        second.uv[4] = 1; second.uv[5] = 1; second.uv[6] = 1; second.uv[7] = 0;
    }
    FastVecSub(&basis[0], &end, start); vec_scale_to_length(&basis[0], &basis[0], 1);
    FastVecSub(&basis[1], &gCameraPosition_L02, start); FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1); FastVecCross(&basis[1], &basis[0], &basis[2]);
    basis[3].bits = start->bits;
    first.point[0].bits = nearSize.bits; second.point[0].bits = farSize.bits;
    FastVecScale(&first.point[1], &first, -1); FastVecScale(&second.point[1], &second, -1);
    transform_vector(&first, &first, basis); transform_vector(&first.point[1], &first.point[1], basis);
    transform_vector(&second, &second, basis); transform_vector(&second.point[1], &second.point[1], basis);
    basis[3].bits = end.bits; nearSize.f[2] *= 0.15f; farSize.f[2] = nearSize.f[2] + nearSize.f[2];
    first.point[2].bits = nearSize.bits; second.point[2].bits = farSize.bits;
    FastVecScale(&first.point[3], &first.point[2], -1); FastVecScale(&second.point[3], &second.point[2], -1);
    transform_vector(&first.point[2], &first.point[2], basis); transform_vector(&first.point[3], &first.point[3], basis);
    transform_vector(&second.point[2], &second.point[2], basis); transform_vector(&second.point[3], &second.point[3], basis);
    draw_world_quad(&first, 0, 0); draw_world_quad(&second, 0, 0);
}
