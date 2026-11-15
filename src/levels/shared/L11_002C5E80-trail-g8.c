#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } RibbonPacket;
extern char D_L11_001BA8C0[];
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int), func_002FC560(int, u64);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float D_L11_001B2600 __attribute__((sda)), D_L11_001B2610 __attribute__((sda));
extern int D_L11_001B2630 __attribute__((sda)), D_L11_001B2634 __attribute__((sda));
extern u32 D_L11_001B2608 __attribute__((sda)), D_L11_001B260C __attribute__((sda));
/* Draws the narrow ribbon and its camera-facing halo along the point chain.
 * The EE ABI independently orders integer and FP arguments: count is a3,
 * unused is f12, width is f13, and extend is f14. */
void func_L11_0046C1E0(Vector *points, u32 color, u32 outerColor, float unused, float width, float extend, int count) {
    RibbonPacket core, halo;
    Vector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i;
    u32 coreColor, haloColor;
    const float zero = 0.0f;
    core.texture = GetEffectTextureDescriptor(D_L11_001B2630);
    coreColor = D_L11_001B2608 | (color << 24);
    core.flags = 0x8000000048ULL;
    core.mode = 0xFF9000000260ULL;
    core.primitive = 0;
    core.color[3] = coreColor; core.color[2] = coreColor;
    core.color[1] = coreColor; core.color[0] = coreColor;
    halo.texture = GetEffectTextureDescriptor(D_L11_001B2634);
    halo.flags = core.flags; halo.mode = core.mode; halo.primitive = core.primitive;
    haloColor = D_L11_001B260C | (outerColor << 24);
    halo.color[3] = haloColor; halo.color[2] = haloColor;
    halo.color[1] = haloColor; halo.color[0] = haloColor;
    halo.uv[0] = zero; halo.uv[1] = zero; halo.uv[2] = zero; halo.uv[3] = 1;
    halo.uv[4] = 1; halo.uv[5] = zero; halo.uv[6] = 1; halo.uv[7] = 1;
    core.uv[0] = D_L11_001B2600; core.uv[1] = zero; core.uv[2] = D_L11_001B2600; core.uv[3] = 1;
    core.uv[4] = D_L11_001B2600 + 1.0f; core.uv[5] = zero; core.uv[6] = D_L11_001B2600 + 1.0f; core.uv[7] = 1;
    FastVecSub(&eye, points, D_L11_001BA8C0);
    FastVecSub(&tangent, points + 1, points);
    FastVecCross(&normal, &tangent, &eye);
    initialLength = FastVecLength(&normal);
    if (initialLength != zero) initialLength = 1.0f / initialLength;
    FastVecScale(&normal, &normal, D_L11_001B2610 * initialLength);
    FastVecAdd(&core.vertex[0], points, &normal);
    FastVecSub(&core.vertex[1], points, &normal);
    for (i = 1; i < count - 1; i++) {
        float coreZero = 0.0f;
        FastVecSub(&eye, points + i, D_L11_001BA8C0);
        FastVecSub(&tangent, points + i + 1, points + i);
        FastVecCross(&normal, &tangent, &eye);
        length = FastVecLength(&normal);
        if (length != coreZero) length = 1.0f / length;
        FastVecScale(&normal, &normal, D_L11_001B2610 * length);
        FastVecAdd(&core.vertex[2], points + i, &normal);
        FastVecSub(&core.vertex[3], points + i, &normal);
        if (i == 1) { core.color[1] = D_L11_001B2608; core.color[0] = D_L11_001B2608; }
        else if (i == count - 2) { core.color[3] = D_L11_001B2608; core.color[2] = D_L11_001B2608; }
        else if (i == 2) { core.color[1] = coreColor; core.color[0] = coreColor; }
        draw_world_quad(&core, 0, 0);
        qcopy(&core.vertex[0], &core.vertex[2]); qcopy(&core.vertex[1], &core.vertex[3]);
    }
    for (i = 0; i < count - 2; i++) {
        float haloZero = 0.0f;
        FastVecSub(&firstRay, points + i, D_L11_001BA8C0);
        FastVecSub(&lastRay, points + i + 1, D_L11_001BA8C0);
        firstLength = FastVecLength(&firstRay);
        lastLength = FastVecLength(&lastRay);
        if (lastLength < firstLength) {
            if (lastLength == haloZero) { qcopy(&lastRay, &firstRay); }
            else FastVecScale(&lastRay, &lastRay, firstLength / lastLength);
        } else if (firstLength == haloZero) { qcopy(&firstRay, &lastRay); }
        else FastVecScale(&firstRay, &firstRay, lastLength / firstLength);
        FastVecAdd(&first, D_L11_001BA8C0, &firstRay);
        FastVecAdd(&last, D_L11_001BA8C0, &lastRay);
        FastVecSub(&tangent, &last, &first);
        FastVecScale(&extension, &tangent, extend);
        FastVecSub(&first, &first, &extension);
        FastVecAdd(&last, &last, &extension);
        FastVecSub(&toEye, D_L11_001BA8C0, &first);
        FastVecCross(&normal, &toEye, &tangent);
        haloLength = FastVecLength(&normal);
        if (haloLength != haloZero) haloLength = 1.0f / haloLength;
        FastVecScale(&widthVector, &normal, width * haloLength);
        FastVecAdd(&halo.vertex[0], &first, &widthVector);
        FastVecSub(&halo.vertex[1], &first, &widthVector);
        FastVecAdd(&halo.vertex[2], &last, &widthVector);
        FastVecSub(&halo.vertex[3], &last, &widthVector);
        if (i == 0) { halo.color[1] = D_L11_001B260C; halo.color[0] = D_L11_001B260C; }
        else if (i == count - 3) { halo.color[3] = D_L11_001B260C; halo.color[2] = D_L11_001B260C; }
        else if (i == 1) { halo.color[1] = haloColor; halo.color[0] = haloColor; }
        draw_world_quad(&halo, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}
