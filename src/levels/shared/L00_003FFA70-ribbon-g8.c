#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; int color[4]; float uv[8]; u64 primitive, texture, mode, flags; } RibbonPacket;
extern char D_L00_001B8DC0[];
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int), func_002FC560(int, u64);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float D_L00_001B0EFC __attribute__((sda)), D_L00_001B0EE4 __attribute__((sda));
extern int D_L00_001B0F14 __attribute__((sda)), D_L00_001B0F18 __attribute__((sda));
extern int D_L00_001B0EF0 __attribute__((sda));
/* Draws the narrow ribbon and its camera-facing halo along the point chain.
 * The core takes its colour from D_L00_001B0EF0 with alpha coreAlpha; the halo
 * is haloRgb with alpha haloAlpha, fading to haloRgb alone at both ends.
 * The EE ABI independently orders integer and FP arguments: count is a3,
 * haloRgb is t0, unused is f12, width is f13, and extend is f14. */
void func_L00_004073D8(Vector *points, int coreAlpha, int haloAlpha, float unused, float width, float extend, int count, int haloRgb) {
    RibbonPacket core, halo;
    Vector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i;
    int coreColor, haloColor;
    core.texture = GetEffectTextureDescriptor(D_L00_001B0F14);
    coreColor = D_L00_001B0EF0 | (coreAlpha << 24);
    core.flags = 0x8000000048ULL;
    core.mode = 0xFF9000000260ULL;
    core.primitive = 0;
    core.color[3] = coreColor; core.color[2] = coreColor;
    core.color[1] = coreColor; core.color[0] = coreColor;
    halo.texture = GetEffectTextureDescriptor(D_L00_001B0F18);
    haloColor = haloRgb | (haloAlpha << 24);
    halo.flags = core.flags; halo.mode = core.mode; halo.primitive = core.primitive;
    halo.color[3] = haloColor; halo.color[2] = haloColor;
    halo.color[1] = haloColor; halo.color[0] = haloColor;
    halo.uv[0] = 0; halo.uv[1] = 0; halo.uv[2] = 0; halo.uv[3] = 1;
    halo.uv[4] = 1; halo.uv[5] = 0; halo.uv[6] = 1; halo.uv[7] = 1;
    core.uv[0] = D_L00_001B0EFC; core.uv[1] = 0; core.uv[2] = D_L00_001B0EFC; core.uv[3] = 1;
    core.uv[4] = D_L00_001B0EFC + 1.0f; core.uv[5] = 0; core.uv[6] = D_L00_001B0EFC + 1.0f; core.uv[7] = 1;
    FastVecSub(&eye, points, gCameraPosition_L00);
    FastVecSub(&tangent, points + 1, points);
    FastVecCross(&normal, &tangent, &eye);
    initialLength = FastVecLength(&normal);
    if (initialLength != 0) initialLength = 1.0f / initialLength;
    FastVecScale(&normal, &normal, D_L00_001B0EE4 * initialLength);
    FastVecAdd(&core.vertex[0], points, &normal);
    FastVecSub(&core.vertex[1], points, &normal);
    for (i = 1; i < count - 1; i++) {
        FastVecSub(&eye, points + i, gCameraPosition_L00);
        FastVecSub(&tangent, points + i + 1, points + i);
        FastVecCross(&normal, &tangent, &eye);
        length = FastVecLength(&normal);
        if (length != 0) length = 1.0f / length;
        FastVecScale(&normal, &normal, D_L00_001B0EE4 * length);
        FastVecAdd(&core.vertex[2], points + i, &normal);
        FastVecSub(&core.vertex[3], points + i, &normal);
        if (i == 1) { core.color[1] = D_L00_001B0EF0; core.color[0] = D_L00_001B0EF0; }
        else if (i == count - 2) { core.color[3] = D_L00_001B0EF0; core.color[2] = D_L00_001B0EF0; }
        else if (i == 2) { core.color[1] = coreColor; core.color[0] = coreColor; }
        draw_world_quad(&core, 0, 0);
        qcopy(&core.vertex[0], &core.vertex[2]); qcopy(&core.vertex[1], &core.vertex[3]);
    }
    for (i = 0; i < count - 1; i++) {
        FastVecSub(&firstRay, points + i, gCameraPosition_L00);
        FastVecSub(&lastRay, points + i + 1, gCameraPosition_L00);
        firstLength = FastVecLength(&firstRay);
        lastLength = FastVecLength(&lastRay);
        if (lastLength < firstLength) {
            if (lastLength == 0) { qcopy(&lastRay, &firstRay); }
            else FastVecScale(&lastRay, &lastRay, firstLength / lastLength);
        } else if (firstLength == 0) { qcopy(&firstRay, &lastRay); }
        else FastVecScale(&firstRay, &firstRay, lastLength / firstLength);
        FastVecAdd(&first, gCameraPosition_L00, &firstRay);
        FastVecAdd(&last, gCameraPosition_L00, &lastRay);
        FastVecSub(&tangent, &last, &first);
        FastVecScale(&extension, &tangent, extend);
        FastVecSub(&first, &first, &extension);
        FastVecAdd(&last, &last, &extension);
        FastVecSub(&toEye, gCameraPosition_L00, &first);
        FastVecCross(&normal, &toEye, &tangent);
        haloLength = FastVecLength(&normal);
        if (haloLength != 0) haloLength = 1.0f / haloLength;
        FastVecScale(&widthVector, &normal, width * haloLength);
        FastVecAdd(&halo.vertex[0], &first, &widthVector);
        FastVecSub(&halo.vertex[1], &first, &widthVector);
        FastVecAdd(&halo.vertex[2], &last, &widthVector);
        FastVecSub(&halo.vertex[3], &last, &widthVector);
        if (i == 0) { halo.color[1] = haloRgb; halo.color[0] = haloRgb; }
        else if (i == count - 2) { halo.color[3] = haloRgb; halo.color[2] = haloRgb; }
        else if (i == 1) { halo.color[1] = haloColor; halo.color[0] = haloColor; }
        draw_world_quad(&halo, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}

