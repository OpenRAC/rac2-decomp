/* Retained C reconstruction; not linked or counted.
 * Tier: GPT-6.1 Sol, high effort (v0703, 29 October 2026).
 * Profile: pinned game compiler, -O2 -G8 -ffunction-sections.
 * USA v1.01: 1504/1492 bytes, 0/2 places. No other releases checked here.
 * The previous draft's historical 1484-byte result becomes 1508 bytes under
 * this pinned profile. This attempt uses the existing matched ribbon renderer's
 * aligned vector/packet layout and separate initial/core/glow lengths. Expressing
 * the core normalization as a conditional expression saves four bytes, but its
 * 0x260 frame differs from retail's 0x270. Allocation, loop FP constants and
 * scheduling still differ. The ordinary conditional form gets the prologue and
 * initial normal calculation right at 1508 bytes, then differs at the core loop.
 * The matched sibling's qcopy/hazard profile and non-clobbering carried-vertex
 * copies do not improve it; -fno-rerun-loop-opt gives 1504 with worse allocation,
 * and -fno-gcse gives 1532. A reciprocal helper/temporary gives 1512.
 * Reopen with independent core-loop normalization/constant lifetime evidence;
 * no padding, fabricated volatile accesses or compiler changes were used.
 * All required declarations follow below. Restore the INCLUDE_ASM in src/.
 *
 * closer D, 1 November 2026: 1492/1492 bytes, 26 words, all one s7/fp swap, under func_L00_0040D058's flags
 * (-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-hazard-labels). Local `one` and `zero`, set
 * before the first loop, give retail's f20 and f22. Retail has points in fp and the &normal copy in s7; a pointer
 * parameter, statement order and a forced bucket sweep tie. Priority only: a permuter job is worth trying.
 */

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } StripVector;
typedef struct { StripVector vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } StripPacket;
extern char D_L10_001B9680[];
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int), func_002FC560(u32, u64);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *), func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
/* Draws textured core and camera-facing glow quads along a segmented strip. */
void func_L10_0039DA48(void *path, int alpha, int outerAlpha, int count, float coreWidth, float width, float extend, int innerColor, int outerColor) {
    StripVector *points = path;
    StripPacket core, halo;
    StripVector normal, widthStripVector, eye, tangent, first, last, firstRay, lastRay, toEye, extension;
    float length, initialLength, haloLength, firstLength, lastLength;
    int i; float one, zero;
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
    halo.uv[0] = 0; halo.uv[1] = 0; halo.uv[2] = 0; halo.uv[3] = 1;
    halo.uv[4] = 1; halo.uv[5] = 0; halo.uv[6] = 1; halo.uv[7] = 1;
    core.uv[0] = 0; core.uv[1] = 0; core.uv[2] = 0; core.uv[3] = 1;
    core.uv[4] = 1; core.uv[5] = 0; core.uv[6] = 1; core.uv[7] = 1;
    func_00282CF0(&eye, points, D_L10_001B9680);
    func_00282CF0(&tangent, points + 1, points);
    func_00282DD8(&normal, &tangent, &eye);
    initialLength = func_00282DF0(&normal);
    if (initialLength != 0) initialLength = 1.0f / initialLength;
    func_00282D30(&normal, &normal, coreWidth * initialLength);
    func_00282CC0(&core.vertex[0], points, &normal);
    func_00282CF0(&core.vertex[1], points, &normal);
    one = 1.0f; zero = 0.0f;
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
        func_00282D30(&widthStripVector, &normal, width * haloLength);
        func_00282CC0(&halo.vertex[0], &first, &widthStripVector);
        func_00282CF0(&halo.vertex[1], &first, &widthStripVector);
        func_00282CC0(&halo.vertex[2], &last, &widthStripVector);
        func_00282CF0(&halo.vertex[3], &last, &widthStripVector);
        if (i == 0) { halo.color[1] = outerColor; halo.color[0] = outerColor; }
        else if (i == count - 2) { halo.color[3] = outerColor; halo.color[2] = outerColor; }
        else if (i == 1) { halo.color[1] = haloColor; halo.color[0] = haloColor; }
        func_00280B90(&halo, 0, 0);
    }
    func_002FC560(0x47, 0x5360B);
}
