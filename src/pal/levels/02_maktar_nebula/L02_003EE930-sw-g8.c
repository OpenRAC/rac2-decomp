#include "include_asm.h"

#include "common.h"
extern int D_L02_001B0D50 __attribute__((sda));
extern int D_L02_001B0D54 __attribute__((sda));
extern float D_L02_001B0D58 __attribute__((sda));
extern float D_L02_001B0D5C __attribute__((sda));
extern int D_L02_001B30C8;
typedef struct { unsigned char pad[3]; unsigned char active; } OwnerFlagView;
extern OwnerFlagView D_001395B8 __attribute__((nosda));
extern char D_00188660[], D_00189F10[];
extern void func_L02_003EAA68(void *);
extern int func_002B38B8(void *);
extern void func_0029B3E0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L02_003EAD38(void *);
extern float func_00282C48(float);
extern int func_L02_003EAE10(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002833F0(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00283B98(float, float);
extern int func_L02_003EAFC8(void *);
extern void func_002E59F8(int);
extern void func_L02_003EB098(void *);
extern float func_002AA2E8(float *, float, float);
extern void func_00282F20(void *, void *, float);
extern int func_L02_003EB138(void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L02_003EB258(char *);
typedef union { int i[0x20]; float f[0x20]; } PlatState;

/* Updates the platform's activation, swing, travel and scrolling surface. */
void func_PAL_L02_003EE930(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float angles[4], rotation[12], inverse[16], offset[4];
    float speed, distance, target;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
    func_L02_003EAA68(actor);
    return;
    case 2:
    if (D_L02_001B0D50 == 0) {
        unsigned int timer, next;
        if (!func_002B38B8(actor)) return;
        next = *(unsigned short *)(actor + 0x96);
        timer = next;
        next++;
        *(unsigned short *)(actor + 0x96) = next;
        if (timer < 6) return;
    }
    if (*(int *)(state + 4)) { D_001395B8.active = 1; func_0029B3E0(0, -1); }
    *(int *)(state + 0x2C) = func_002E5CF8(0, 4, actor);
    func_L02_003EAD38(actor);
    return;
    case 3:
    if (!(func_00282C48((float)D_L02_001B30C8 - **(float **)(state + 0x28)) > 8.0f)) return;
    if (func_L02_003EAE10(actor)) {
        **(float **)(state + 0x28) = (float)D_L02_001B30C8;
        func_002A7750(actor, 4, -1);
        *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
        *(float *)(state + 0xC) = 0;
    }
    return;
    case 4:
    speed = 0.024f;
    if (func_002B3868(actor)) speed = 6e+01f;
    qzero(angles);
    angles[2] = *(float *)(state + 0x3C);
    func_002833F0(rotation, angles);
    func_00283698(inverse, rotation);
    func_00282CF0(offset, actor + 0x10, state + 0x30);
    func_00283098(offset, offset, inverse);
    distance = func_00282C48(offset[1]);
    if (distance <= func_00282C48(*(float *)(state + 0xC))) {
        offset[1] = 0;
        func_002A7750(actor, 5, -1);
    } else func_002AA548(offset + 1, state + 0xC, 0.0f, speed, speed, 1.2f);
    func_00283098(offset, offset, rotation);
    func_00282CC0(actor + 0x10, state + 0x30, offset);
    return;
    case 5:
    if (func_002B3868(actor)) {
        qcopy(state + 0x40, actor + 0x10);
        *(float *)(state + 0x10) = 0;
        *(float *)(state + 0xC) = 0;
    }
    distance = func_00282C48(*(float *)(state + 0x10) - 1.0f);
    if (distance < func_00282C48(*(float *)(state + 0xC))) {
        *(float *)(state + 0x10) = 1.0f;
        func_002A7750(actor, 6, -1);
    } else func_002AA548(state + 0x10, state + 0xC, 1.0f, 0.004f, 0.004f, 0.20000002f);
    func_00282D08(actor + 0x10, state + 0x40, state + 0x30, *(float *)(state + 0x10));
    *(float *)(actor + 0xF8) = func_00283B98(*(float *)(state + 0x3C), (1.0f - *(float *)(state + 0x10)) * 1.5707965f);
    *(float *)(actor + 0xF0) = (1.0f - *(float *)(state + 0x10)) * 3.1415927f;
    return;
    case 7:
    if (func_L02_003EAFC8(actor)) {
        int index = *(int *)(state + 0x2C);
        if (index != -1) {
            char *slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74)) func_002E59F8(index);
        }
        *(int *)(state + 0x2C) = -1;
        func_L02_003EB098(actor);
        func_002A7750(actor, 8, -1);
    }
    return;
    case 8:
    target = (float)D_L02_001B0D54 * 0.080000006f;
    func_002AA2E8(&D_L02_001B0D58, target, 0.0064000003f);
    func_00282F20(angles, actor + 0xD0, D_L02_001B0D58);
    if (func_L02_003EB138(actor, angles)) {
        if (D_L02_001B0D58 == target) {
            if (func_00282DB0(D_00189F10, angles) < -0.001f) {
                if (++((PlatState *)state)->i[8] > 25) D_L02_001B0D54 = -D_L02_001B0D54;
            } else ((PlatState *)state)->i[8] = 0;
        } else ((PlatState *)state)->i[8] = 0;
    }
    ((PlatState *)state)->f[5] = func_00283B98(((PlatState *)state)->f[5], D_L02_001B0D5C * 0.0003490659f);
    ((PlatState *)state)->f[6] += D_L02_001B0D58 * 0.5f;
    if (((PlatState *)state)->f[6] > 1.0f) ((PlatState *)state)->f[6] -= 1.0f;
    else if (((PlatState *)state)->f[6] < -1.0f) ((PlatState *)state)->f[6] += 1.0f;
    func_002AA2E8(&((PlatState *)state)->f[7], 1.0f, 0.020000001f);
    func_L00_002E6CF0(func_L02_003EB258, actor);
    case 1:
    case 6:
        return;
    }
}
