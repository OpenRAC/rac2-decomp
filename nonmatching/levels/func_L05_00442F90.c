/* func_L05_00442F90 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_00442F90-g8.c: 508/524 bytes.
 * US: 0/4 local places; PAL: ABSENT; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * Mask/zero initialization, division and trigonometric call scheduling differ. Callee vector widths and FPR contracts were read from retail. Reopen with source/profile evidence.
 */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector up, start, cross, third, result; } RotationScratch;
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float func_00283CE0(int);
extern void func_002AB600(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282978(void *);
extern float func_00282C48(float);
extern float func_002A7C00(float, float, float);
extern void func_00283810(void *, void *, void *, float);
extern void func_00283958(void *, void *);
extern unsigned short D_L05_001B1BC8 __attribute__((sda));
extern unsigned short D_L05_001B1BC4 __attribute__((sda));

int func_L05_00442F90(char *object)
{
    RotationScratch scratch;
    char *state = *(char **)(object + 0x70) + 0x50;
    char *from;
    char *to;
    float angle;
    float fraction;
    scratch.up.q = 0;
    scratch.up.f[3] = 1.0f;
    scratch.up.f[2] = 1.0f;
    angle = func_00282DB0(&scratch.up, object + 0x20);
    if ((*(unsigned long long *)(state + 0x18) & 0x00FFFFFF00000000ULL) == 0x0002000000000000ULL) {
        angle = 1.57079632679f - func_002831B0(angle);
        *(float *)(state + 0x24) = angle;
        if (angle < 1.57079637051f) *(short *)(state + 0x1C) = D_L05_001B1BC8;
        else *(short *)(state + 0x1C) = D_L05_001B1BC4;
        *(float *)(state + 0x20) = 1.0f / func_00283CE0(*(short *)(state + 0x1C));
    }
    if (!*(short *)(state + 0x1C)) return 0;
    to = state + 0x30;
    from = state + 0x40;
    func_002AB600(to, object);
    qcopy(&scratch.start, object);
    func_00282DD8(&scratch.cross, &scratch.start, &scratch.up);
    func_00282F20(&scratch.cross, &scratch.cross, 1.0f);
    func_00282DD8(&scratch.third, &scratch.cross, &scratch.start);
    func_002AB600(from, &scratch.start);
    if (func_00282978(state + 0x1C)) {
        state[0x1E] = 0;
        return 1;
    }
    angle = func_00282C48(func_00282DB0(&scratch.up, object));
    if (angle >= 0.75f) {
        state[0x1E] = 0;
        return 1;
    }
    fraction = func_002A7C00(0.0f, 1.0f, func_00283CE0(*(short *)(state + 0x1C)) * *(float *)(state + 0x20));
    func_00283810(&scratch.result, from, to, fraction);
    func_00283958(&scratch.result, object);
    return 1;
}