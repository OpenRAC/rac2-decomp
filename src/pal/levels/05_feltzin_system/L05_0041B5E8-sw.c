#include "include_asm.h"

#include "common.h"
extern char *func_002ED688(char *);
extern void func_L05_00416E08(char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282C88(char *);
extern void func_0029FCC0(char *, int, char *);
extern void func_L05_00415EE8(int, int);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int func_00282948(void *);
extern int func_L05_0037AFD0(void *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002AB600(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_002A7790(float);
extern void func_00283810(void *, void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_L05_00416EC0(char *, int);
extern void func_PAL_L05_0041BC50(char *, char *);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void func_0029F338(void *);
extern int func_L05_00417088(char *);

void func_PAL_L05_0041B5E8(char *object)
{
    char matrix[0x30];
    char delta[0x10], rot0[0x10], rot1[0x10], rot2[0x10], point[0x10];
    Vec up;
    char *target, *position;
    char *sub = *(char **)(object + 0x68);
    target = func_002ED688(*(char **)(sub + 0x50));
    up.q = 0;
    up.f[2] = 1.0f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(int *)(object + 0x98) = 0;
        object[0x20] = 1;
        /* fall through */
    case 1:
        func_L05_00416E08(object);
        if (!func_L05_0037AFD0(*(char **)(sub + 0x50))) object[0x20] = 4;
        break;
    case 2: {
        char *forward = object + 0xC0;
        char *right;
        char *normal;
        char *velocity;
        char *drift;
        float fraction;
        qcopy(sub, forward);
        right = object + 0xD0;
        qcopy(sub + 0x10, right);
        normal = object + 0xE0;
        qcopy(sub + 0x20, normal);
        position = object + 0x10;
        velocity = sub + 0x40;
        func_002833F0(matrix, velocity);
        func_00283738(forward, forward, matrix);
        func_002AB600(rot0, forward);
        func_00282CF0(delta, *(char **)(target + 0x120) + 0x10, position);
        func_00282F20(forward, delta, 1.0f);
        func_00282DD8(right, forward, &up);
        func_00282F20(right, right, *(int *)(sub + 0x54) ? -1.0f : 1.0f);
        drift = sub + 0x30;
        func_00282DD8(normal, right, forward);
        func_002AB600(rot1, forward);
        fraction = func_00283CE0(*(int *)(sub + 0x58));
        fraction /= func_00283CE0(150);
        func_00283810(rot2, rot0, rot1, func_002A7790(1.0f - fraction));
        func_00283958(rot2, forward);
        func_L05_00416EC0(object, 0);
        func_00282CC0(position, drift, position);
        func_00282D30(drift, drift, .99f);
        func_00282D30(velocity, velocity, .99f);
        if (*(int *)(sub + 0x58) < 45) *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
        if (func_00282948(sub + 0x58)) {
            object[0x20] = 3;
            func_00282C88(velocity);
            *(int *)(sub + 0x5C) = 0;
        }
        break;
    }
    case 3: {
        char *forward = object + 0xC0;
        char *right;
        char *normal;
        char *drift;
        if (!*(unsigned char *)(object + 0x31)) object[0x20] = 4;
        qcopy(sub, forward);
        right = object + 0xD0;
        qcopy(sub + 0x10, right);
        normal = object + 0xE0;
        qcopy(sub + 0x20, normal);
        func_0029FCC0(object, 0, delta);
        func_00282CF0(delta, *(char **)(target + 0x120) + 0x10, delta);
        func_00282F20(forward, delta, 1.0f);
        func_00282DD8(right, forward, &up);
        func_00282F20(right, right, *(int *)(sub + 0x54) ? -1.0f : 1.0f);
        drift = sub + 0x30;
        func_00282DD8(normal, right, forward);
        *(int *)(object + 0xCC) = 0;
        *(int *)(object + 0xDC) = 0;
        *(int *)(object + 0xEC) = 0;
        func_00282F20(delta, delta, *(float *)(sub + 0x5C));
        func_00282CC0(delta, delta, drift);
        func_L05_00416EC0(object, 0);
        func_0029FCC0(object, 0, point);
        func_00282CC0(object + 0x10, delta, object + 0x10);
        func_00282D30(drift, drift, .99f);
        *(float *)(sub + 0x5C) += 0.14f;
        func_PAL_L05_0041BC50(object, point);
        break;
    }
    case 4:
        func_PAL_002AD288(object, object + 0x10, -1, 3.0f, 13.0f);
        func_L05_00415EE8(*(int *)(sub + 0x50), *(int *)(sub + 0x54));
        func_0029F338(object);
        return;
    }
    func_L05_00417088(object);
}
