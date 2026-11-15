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

extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern void ref_0031EC68_00(void *);
extern Vector4 g_camera_eye_state;

/* A two-strip beam from start to end (the func_L00_0038ADD0 layout): textures 0x2F and
   0x30, the alpha in the top byte of both colours, the strip's u running from u0 to u0+1,
   half width at the far end. */
void gfx_draw_two_strip_beam(Vector4 *start, Vector4 *end, int unused2, int alpha, int unused4, int mode,
                   float width, float unused, float u0)
{
    Beam first, second;
    Vector4 basis[4], nearSize, farSize;

    first.tex = GetEffectTextureDescriptor(0x2F);
    first.test = ((unsigned long)mode << 2) | 0x8000000040UL;
    first.alpha = 0xFF9000000260UL;
    first.color[2] = first.color[3] = 0x800000;
    first.color[0] = first.color[1] = (alpha << 24) + 0x800000;
    first.tag = 0;
    second.tex = GetEffectTextureDescriptor(0x30);
    nearSize.bits = 0;
    farSize.bits = 0;
    second.alpha = 0xFF9000000260UL;
    second.test = 0x8000000048UL;
    second.color[2] = second.color[3] = 0x800000;
    second.color[0] = second.color[1] = (alpha << 24) + 0xFFFFFF;
    second.tag = 0;
    nearSize.f[3] = 1;
    farSize.f[3] = 1;
    nearSize.f[2] = width;
    farSize.f[2] = width;
    ref_0031EC68_00(&first);
    ref_0031EC68_00(&second);
    first.uv[0] = u0; first.uv[1] = 0; first.uv[2] = u0; first.uv[3] = 1;
    first.uv[4] = u0 + 1; first.uv[5] = 0; first.uv[6] = u0 + 1; first.uv[7] = 1;
    second.uv[0] = u0; second.uv[1] = 0; second.uv[2] = u0; second.uv[3] = 1;
    second.uv[4] = u0 + 1; second.uv[5] = 0; second.uv[6] = u0 + 1; second.uv[7] = 1;
    FastVecSub(&basis[0], end, start); vec_scale_to_length(&basis[0], &basis[0], 1);
    FastVecSub(&basis[1], &g_camera_eye_state, start); FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1); FastVecCross(&basis[1], &basis[0], &basis[2]);
    basis[3].bits = start->bits;
    first.point[0].bits = nearSize.bits; second.point[0].bits = farSize.bits;
    FastVecScale(&first.point[1], &first, -1); FastVecScale(&second.point[1], &second, -1);
    transform_vector(&first, &first, basis); transform_vector(&first.point[1], &first.point[1], basis);
    transform_vector(&second, &second, basis); transform_vector(&second.point[1], &second.point[1], basis);
    basis[3].bits = end->bits;
    nearSize.f[2] *= 0.5f; farSize.f[2] *= 0.5f;
    first.point[2].bits = nearSize.bits; second.point[2].bits = farSize.bits;
    FastVecScale(&first.point[3], &first.point[2], -1); FastVecScale(&second.point[3], &second.point[2], -1);
    transform_vector(&first.point[2], &first.point[2], basis); transform_vector(&first.point[3], &first.point[3], basis);
    transform_vector(&second.point[2], &second.point[2], basis); transform_vector(&second.point[3], &second.point[3], basis);
    draw_world_quad(&first, 0, 0); draw_world_quad(&second, 0, 0);
}
