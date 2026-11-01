/* Closer i, 1 November 2026: ported from func_L15_00432A60; 1492/1492 bytes with 0.0f and 1.0f held in locals, and i == count - 1 in the core loop, but about 100 rows of register rotation remain. Retail keeps points + 1 in a stack slot, and zero in f22. Ten variants of the locals did not close it. */
/* Gorn variant of the colored polyline ribbon renderer. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } RibbonPacket;
extern char D_L10_001B9680[];
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int), func_002FC560(int, u64);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
/* Draws the ribbon (texture 14) and its camera-facing halo (texture 16) along
 * the point chain. Each colour carries its own alpha and fades to the bare
 * colour at both ends. The EE ABI independently orders integer and FP
 * arguments: count is a3, innerColor t0, outerColor t1, coreWidth f12,
 * width f13 and extend f14. */
void func_L10_0039DA48(Vector *points, u32 alpha, u32 outerAlpha, float coreWidth, float width, float extend, int count, u32 innerColor, u32 outerColor) {
    RibbonPacket core, halo;
    Vector normal, widthVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float zero, one;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i;
    u32 coreColor, haloColor;
    core.texture = func_0027C878(14);
    coreColor = innerColor | (alpha << 24);
    core.flags = 0x8000000048ULL;
    core.mode = 0xFF9000000260ULL;
    core.primitive = 0;
    core.color[3] = coreColor; core.color[2] = coreColor;
    core.color[1] = coreColor; core.color[0] = coreColor;
    halo.texture = func_0027C878(16);
    haloColor = outerColor | (outerAlpha << 24);
    halo.flags = core.flags; halo.mode = core.mode; halo.primitive = core.primitive;
    halo.color[3] = haloColor; halo.color[2] = haloColor;
    halo.color[1] = haloColor; halo.color[0] = haloColor;
    zero = 0.0f;
    one = 1.0f;
    halo.uv[0] = zero; halo.uv[1] = zero; halo.uv[2] = zero; halo.uv[3] = one;
    halo.uv[4] = one; halo.uv[5] = zero; halo.uv[6] = one; halo.uv[7] = one;
    core.uv[0] = zero; core.uv[1] = zero; core.uv[2] = zero; core.uv[3] = one;
    core.uv[4] = one; core.uv[5] = zero; core.uv[6] = one; core.uv[7] = one;
    func_00282CF0(&eye, points, D_L10_001B9680);
    func_00282CF0(&tangent, points + 1, points);
    func_00282DD8(&normal, &tangent, &eye);
    initialLength = func_00282DF0(&normal);
    if (initialLength != zero) initialLength = one / initialLength;
    func_00282D30(&normal, &normal, coreWidth * initialLength);
    func_00282CC0(&core.vertex[0], points, &normal);
    func_00282CF0(&core.vertex[1], points, &normal);
    for (i = 1; i < count - 1; i++) {
        func_00282CF0(&eye, points + i, D_L10_001B9680);
        func_00282CF0(&tangent, points + i + 1, points + i);
        func_00282DD8(&normal, &tangent, &eye);
        length = func_00282DF0(&normal);
        if (length != zero) length = one / length;
        func_00282D30(&normal, &normal, coreWidth * length);
        func_00282CC0(&core.vertex[2], points + i, &normal);
        func_00282CF0(&core.vertex[3], points + i, &normal);
        if (i == 1) { core.color[1] = innerColor; core.color[0] = innerColor; }
        else if (i == count - 1) { core.color[3] = innerColor; core.color[2] = innerColor; }
        else if (i == 2) { core.color[1] = coreColor; core.color[0] = coreColor; }
        func_00280B90(&core, 0, 0);
        qcopy(&core.vertex[0], &core.vertex[2]); qcopy(&core.vertex[1], &core.vertex[3]);
    }
    for (i = 0; i < count - 1; i++) {
        func_00282CF0(&firstRay, points + i, D_L10_001B9680);
        func_00282CF0(&lastRay, points + i + 1, D_L10_001B9680);
        firstLength = func_00282DF0(&firstRay);
        lastLength = func_00282DF0(&lastRay);
        if (lastLength < firstLength) {
            if (lastLength == 0) { qcopy(&lastRay, &firstRay); }
            else func_00282D30(&lastRay, &lastRay, firstLength / lastLength);
        } else if (firstLength == 0) { qcopy(&firstRay, &lastRay); }
        else func_00282D30(&firstRay, &firstRay, lastLength / firstLength);
        func_00282CC0(&first, D_L10_001B9680, &firstRay);
        func_00282CC0(&last, D_L10_001B9680, &lastRay);
        func_00282CF0(&tangent, &last, &first);
        func_00282D30(&extension, &tangent, extend);
        func_00282CF0(&first, &first, &extension);
        func_00282CC0(&last, &last, &extension);
        func_00282CF0(&toEye, D_L10_001B9680, &first);
        func_00282DD8(&normal, &toEye, &tangent);
        haloLength = func_00282DF0(&normal);
        if (haloLength != 0) haloLength = 1.0f / haloLength;
        func_00282D30(&widthVector, &normal, width * haloLength);
        func_00282CC0(&halo.vertex[0], &first, &widthVector);
        func_00282CF0(&halo.vertex[1], &first, &widthVector);
        func_00282CC0(&halo.vertex[2], &last, &widthVector);
        func_00282CF0(&halo.vertex[3], &last, &widthVector);
        if (i == 0) { halo.color[1] = outerColor; halo.color[0] = outerColor; }
        else if (i == count - 2) { halo.color[3] = outerColor; halo.color[2] = outerColor; }
        else if (i == 1) { halo.color[1] = haloColor; halo.color[0] = haloColor; }
        func_00280B90(&halo, 0, 0);
    }
    func_002FC560(0x47, 0x5360B);
}
