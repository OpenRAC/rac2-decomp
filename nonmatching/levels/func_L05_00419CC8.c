/* func_L05_00419CC8 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * Measured in src/levels/shared/L05_00419CC8-g8.c: 576/580 bytes.
 * US: 0/4 local places; PAL: ABSENT; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * The two division regions, scalar scheduling and copy/register lifetimes differ. Duplicate global reads were removed using measured captures; byte stores retain unsigned fields. Reopen with line-label/profile and allocator evidence.
 */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char *func_0029EFD0(int);
extern int func_00283CF0(float);
extern float func_002A7940(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L05_0041A230(void *);
extern float D_L05_001B1030 __attribute__((sda));
extern float D_L05_001B1034 __attribute__((sda));
extern float D_L05_001B1038 __attribute__((sda));
extern float D_L05_001B1054 __attribute__((sda));
extern float D_L05_001B1058 __attribute__((sda));

char *func_L05_00419CC8(char *parent, void *position, void *direction, int primary, int secondary, int orient, int variant, int kind, float scale)
{
    Vector up;
    char *object = func_0029EFD0(0xFFA);
    char *state;
    float speed;
    int frames;
    float beginning, ending;
    up.q = 0;
    up.f[2] = 1.0f;
    if (!object) return object;
    speed = D_L05_001B1030;
    state = *(char **)(object + 0x68);
    *(int *)(state + 0x30) = variant;
    speed *= 0.016666667f;
    if (variant) speed = D_L05_001B1034 * 0.016666667f;
    object[0x20] = 0;
    *(unsigned char *)(object + 0x30) = 255;
    frames = func_00283CF0(D_L05_001B1038 / speed);
    ending = D_L05_001B1058;
    beginning = D_L05_001B1054;
    *(char **)(state + 4) = parent;
    *(int *)state = frames;
    *(float *)(state + 0x3C) = beginning;
    *(float *)(state + 0x40) = (ending - beginning) / (float)frames;
    *(float *)(state + 8) = func_002A7940();
    *(float *)(state + 0xC) = scale;
    *(int *)(state + 0x38) = kind;
    if (*(int *)(state + 0x30)) {
        *(int *)(state + 0x20) = 0x00FF2020;
        *(int *)(state + 0x24) = 0x7FEF2020;
        *(int *)(state + 0x34) = 0;
    } else {
        *(int *)(state + 0x20) = primary;
        *(int *)(state + 0x24) = secondary | 0x7F000000;
    }
    if (!orient) {
        qcopy(object + 0xC0, parent + 0xC0);
        qcopy(object + 0xD0, parent + 0xD0);
        qcopy(object + 0xE0, parent + 0xE0);
        func_00282F20(state + 0x10, direction, speed);
    } else {
        func_00282F20(object + 0xC0, direction, 1.0f);
        func_00282DD8(object + 0xD0, object + 0xC0, &up);
        func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
        qcopy(state + 0x10, direction);
    }
    qcopy(object + 0x10, position);
    func_L00_002E6EF8(func_L05_0041A230, object);
    return object;
}