#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } RibbonVector;
struct RibbonQuad { RibbonVector position[4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern float D_L11_001BA8C0[4];
extern float D_L11_001AECFC __attribute__((sda));
extern long long func_0027C878(int);
extern void ref_L11_00397E68_00(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern float func_00283CE0(int);

/* Draws a fixed-UV ribbon and a scaled scrolling layer along a point chain. */
void func_L11_00397E68(RibbonVector *points, int count, int flags, u32 color0, u32 color1, float width, float scale) {
    RibbonVector basis[4];
    struct RibbonQuad mainQuad, innerQuad;
    RibbonVector template0, template1;
    float u, nextU;
    int i;
    mainQuad.texture = GetEffectTextureDescriptor(0x2B);
    mainQuad.flags = ((u64)(u32)flags << 32) | 0x68;
    mainQuad.giftag = 0xFF9000000260ULL;
    mainQuad.clear = 0;
    mainQuad.color[0] = mainQuad.color[1] = mainQuad.color[2] = mainQuad.color[3] = color0;
    ref_L11_00397E68_00((char *)&mainQuad);
    mainQuad.uv[0][0] = 0.0f; mainQuad.uv[0][1] = 0.0f;
    mainQuad.uv[1][0] = 0.0f; mainQuad.uv[1][1] = 1.0f;
    mainQuad.uv[2][0] = 1.0f; mainQuad.uv[2][1] = 0.0f;
    mainQuad.uv[3][0] = 1.0f; mainQuad.uv[3][1] = 1.0f;
    innerQuad.texture = GetEffectTextureDescriptor(0x2B);
    innerQuad.giftag = 0xFF9000000260ULL;
    innerQuad.clear = 0;
    innerQuad.flags = ((u64)(long)(flags / 3) << 32) | 0x68;
    innerQuad.color[0] = innerQuad.color[1] = innerQuad.color[2] = innerQuad.color[3] = color1;
    ref_L11_00397E68_00((char *)&innerQuad);
    innerQuad.uv[0][0] = 0.0f; innerQuad.uv[0][1] = 0.0f;
    innerQuad.uv[1][0] = 0.0f; innerQuad.uv[1][1] = 1.0f;
    innerQuad.uv[2][0] = D_L11_001AECFC; innerQuad.uv[2][1] = 0.0f;
    innerQuad.uv[3][0] = D_L11_001AECFC; innerQuad.uv[3][1] = 1.0f;
    template0.q = 0;
    template1.q = 0;
    template0.f[3] = 1.0f;
    template1.f[3] = 1.0f;
    template0.f[2] = width;
    template1.f[2] = width * scale;
    FastVecSub(&basis[0], &points[1], &points[0]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecSub(&basis[1], D_L11_001BA8C0, &points[0]);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    FastVecCross(&basis[1], &basis[0], &basis[2]);
    qcopy(&basis[3], &points[0]);
    qcopy(&mainQuad.position[0], &template0);
    FastVecScale(&mainQuad.position[1], &mainQuad.position[0], -1.0f);
    transform_vector(&mainQuad.position[0], &mainQuad.position[0], basis);
    transform_vector(&mainQuad.position[1], &mainQuad.position[1], basis);
    qcopy(&innerQuad.position[0], &template1);
    FastVecScale(&innerQuad.position[1], &innerQuad.position[0], -1.0f);
    transform_vector(&innerQuad.position[0], &innerQuad.position[0], basis);
    transform_vector(&innerQuad.position[1], &innerQuad.position[1], basis);
    for (i = 1; i < count - 1; i++) {
        qcopy(&mainQuad.position[2], &template0);
        FastVecScale(&mainQuad.position[3], &mainQuad.position[2], -1.0f);
        qcopy(&innerQuad.position[2], &template1);
        FastVecScale(&innerQuad.position[3], &innerQuad.position[2], -1.0f);
        FastVecSub(&basis[0], &points[i + 1], &points[i]);
        vec_scale_to_length(&basis[0], &basis[0], 1.0f);
        FastVecSub(&basis[1], D_L11_001BA8C0, &points[i]);
        FastVecCross(&basis[2], &basis[1], &basis[0]);
        vec_scale_to_length(&basis[2], &basis[2], 1.0f);
        FastVecCross(&basis[1], &basis[0], &basis[2]);
        qcopy(&basis[3], &points[i]);
        transform_vector(&mainQuad.position[2], &mainQuad.position[2], basis);
        transform_vector(&mainQuad.position[3], &mainQuad.position[3], basis);
        transform_vector(&innerQuad.position[2], &innerQuad.position[2], basis);
        transform_vector(&innerQuad.position[3], &innerQuad.position[3], basis);
        if (i == count - 2) {
            mainQuad.color[2] = 0; mainQuad.color[3] = 0;
            innerQuad.color[2] = 0; innerQuad.color[3] = 0;
        }
        draw_world_quad(&mainQuad, 0, 0);
        draw_world_quad(&innerQuad, 0, 0);
        u = D_L11_001AECFC * IntToFloat(i);
        nextU = u + D_L11_001AECFC;
        if (u >= 1.0f) {
            u -= 1.0f;
            nextU -= 1.0f;
        }
        innerQuad.uv[0][0] = u; innerQuad.uv[1][0] = u;
        innerQuad.uv[2][0] = nextU; innerQuad.uv[3][0] = nextU;
        qcopy(&mainQuad.position[0], &mainQuad.position[2]);
        qcopy(&mainQuad.position[1], &mainQuad.position[3]);
        qcopy(&innerQuad.position[0], &innerQuad.position[2]);
        qcopy(&innerQuad.position[1], &innerQuad.position[3]);
    }
}
