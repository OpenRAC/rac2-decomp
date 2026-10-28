/* Nonmatching Grelbin particle emission reconstruction,2026-10-28.
 * No C coverage credit. Seven bounded US checks,0/1. Best728/728B with
 * -O2 -G0 -ffunction-sections; frame0xC0 and all operations match, with
 * remaining saved-register permutation among camera high-half,step pointer,
 * point pointer,phase-step and255 constant. First724B body missed the early
 * low8 narrowing. Named real float factors reproduce the three saved FP
 * constants; one explicit low8 alpha narrowing before conversion is needed.
 * Early pointer lifetimes worsen744B. Three final forms (late step pointer,
 * separate vectors / actual80B frame view) converge to the same728B tie.
 * Reopen only with independent original lifetime/allocator evidence.
 *
 * Actual constructors002C3150/002C2FD8 return particle pointers. Full raw
 * extents and actual002C3280 updater audited. 002A7A00 writes XYZ only:
 * the fourth velocity lane is copied by002C3150 and preserved by CC0, but
 * updater002C3280 uses velocity only as CC0's second input. vadd.xyz does
 * not semantically read that W, and the updater's bounds/lifetime logic
 * reads only XYZ. The source describes the observed unused4-byte lane;
 * it does not initialize it, invent padding, or treat it as a float value.
 * All semantically used XYZ inputs are initialized before use. Other
 * vectors are written as full16B by actual joint/subtract/normalize/add
 * helpers. Unknown tuning extents remain incomplete. One macro declaration
 * models the actual absolute / GP delay-slot counter reads and low8 view.
 */

#include "common.h"
/* A16-byte transfer record whose fourth hardware lane is copied but unused:
 * 002A7A00 writes XYZ;002C3150/002C3280 consume velocity only as CC0's second
 * input, whose W lane is excluded by vadd.xyz. No synthetic fourth-lane store. */
typedef struct { float xyz[3]; unsigned char unused_lane[4]; } RandomVelocityTransfer __attribute__((aligned(16)));
extern unsigned char D_L19_001B9A40[];
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern unsigned char D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern unsigned int D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern unsigned int D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);
extern unsigned int D_L19_001B2508[] __attribute__((sda));
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(float *, float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int), func_00282C48(float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern unsigned char *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *func_002C2FD8(float, void *, int, unsigned char, int, int, int, int);

void func_L19_00423270(unsigned char *object)
{
    float origin[4] __attribute__((aligned(16)));
    RandomVelocityTransfer velocity, increment;
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    unsigned int phase, color;
    int i, alpha, phaseStep;
    float scale;
    float colorFactor, midpoint, baseSize;
    if (*(short *)(object + 0xAA) == 0x11C7) {
        func_00282F20(point, object + 0xE0, 1.5f);
        func_00282CC0(origin, object + 0x10, point);
    } else func_0029FCC0(object, 0, origin);
    if (!func_002A77E0(4)) {
        func_002A7A00(velocity.xyz, D_L19_001B1ECC[0] * 0.01666666753590107f, D_L19_001B1ED0[0] * 0.01666666753590107f);
        alpha = D_L19_001B1EDC[0];
        func_002C3150(origin, &velocity, D_L19_001B1EE0[0], alpha, func_002A77E0(255), 0, D_L19_001B1EE8[0]);
        for (i = 2; i >= 0; i--) {
            func_002A7A00(increment.xyz, D_L19_001B1ED4[0] * 0.01666666753590107f, D_L19_001B1ED8[0] * 0.01666666753590107f);
            func_00282CC0(&velocity, &velocity, &increment);
            alpha = D_L19_001B1EDC[0];
            func_002C3150(origin, &velocity, D_L19_001B1EE4[0], alpha, func_002A77E0(255), 0, D_L19_001B1EEC[0]);
        }
    }
    func_00282CF0(point, D_L19_001B9A40, origin);
    colorFactor = 0.003921568859368563f;
    midpoint = 0.5f;
    baseSize = 3.0f;
    func_00282F20(point, point, -0.3f);
    func_00282F20(step, point, 0.1f);
    func_00282CC0(point, point, origin);
    i = 0;
    phaseStep = 0;
    phase = D_L19_001B2508[0];
    do {
        scale = func_00282C48(midpoint - func_00283CE0(255 - ((phase + phaseStep) & 255)) * colorFactor);
        color = func_00283D38(D_L19_001B1EF0[0], D_L19_001B1EF4[0], scale);
        alpha = *(unsigned char *)D_L19_001B2508;
        if (i & 2) alpha *= 2;
        if (i & 1) alpha = 255 - alpha;
        alpha = (unsigned char)alpha;
        scale = (func_00283CE0(i) + baseSize) * (*(float *)(object + 0x2C) / *(float *)(*(unsigned char **)(object + 0x24) + 0x24));
        func_002C2FD8(scale, point, color, alpha, D_L19_001B1F00[0], D_L19_001B1EFC[0], 2, 0);
        func_00282CC0(point, point, step);
        i++;
        phaseStep += 20;
        phase = D_L19_001B2508[0];
    } while (i < 4);
}
