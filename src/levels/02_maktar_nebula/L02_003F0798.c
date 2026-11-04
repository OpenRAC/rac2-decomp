/* func_L02_003F0798: the combat actor update (animation, steering and attack states).
   Its own unit for -frac2-hazard-labels: two branches target the mtc1 hazard nop. */
#include "common.h"
extern void func_002A7750(u8 *, int, int);
extern int func_002A77E0(int);
extern void func_002A7470(char *, int, int, int);
extern float func_00283248(float, float);
extern s32 func_002B3868(u8 *);
typedef int ActorVectorQuad __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; ActorVectorQuad q[0x260]; } Hero;
extern char D_00189E20[];
extern char *D_0018C2BC;
extern void func_L02_003F1298(char *);
extern void func_L02_003F1578(char *);
extern void func_L02_003F1608(char *);
extern void func_L02_003F18E8(char *);
extern void func_L02_003F1A88(char *, char *);
extern void func_L02_003F1B70(char *);
extern int func_L02_003F1BA8(char *);
extern char *func_L02_003FC098(char *);
extern s32 func_L02_003FC0B8(char *);
extern void func_L02_003FC248(char *, int, int);
extern int func_L00_003206B8(void *, int);
extern int func_L00_0042AB40(char *);
extern void func_L01_00321178(char *, char *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L02_003F16A8(char *);
extern float func_00282E80(void *, void *);
extern float func_00283C80(float, float);
extern int func_002B3890(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_002B5278(u8 *, float);
extern int func_002B4FF0(char *, float *, float);
extern int func_002B50E0(void *, void *, float);
extern float func_0029F530(char *);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);

extern int func_002B1C20(void *, void *);

/* Update the combat actor's animation, steering and attack-state transitions. */
void func_L02_003F0798(char *object) {
    float target[4] __attribute__((aligned(16)));
    char *state;
    char *target_object;
    int flags;
    float heading;
    float distance;
    float angle;
    float animation_frame;
    unsigned char phase;

    phase = *(u8 *)(object + 0x20);
    if (phase == 1) return;
    if (object == 0) return;
    if (phase == 0xFE) return;
    if (phase == 0xFD) return;
    state = *(char **)(object + 0x68);
    func_L02_003F1298(object);
    phase = *(u8 *)(object + 0x20);
    if (phase == 1 || phase == 0xFE || phase == 0xFD) return;
    if (*(s16 *)(state + 0x4EA) == 0) {
        *(char **)(state + 0x4B0) = 0;
        if (*(u8 *)(object + 0x95) == 4) {
            func_002A7750((u8 *)object, 4, 2);
            if (func_002A77E0(2)) {
                if (*(u8 *)(object + 0x43) != 2) func_002A7470(object, 2, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 3) func_002A7470(object, 3, 0, 10);
        }
    }
    if (*(char **)(state + 0x4B0) != 0) {
        *(ActorVectorQuad *)target = *(ActorVectorQuad *)(*(char **)(state + 0x4B0) + 0x10);
        target_object = *(char **)(state + 0x4B0);
        heading = func_00283248(*(float *)(target_object + 0x10) - *(float *)(object + 0x10),
                                *(float *)(target_object + 0x14) - *(float *)(object + 0x14));
    } else {
        *(ActorVectorQuad *)target = *(ActorVectorQuad *)(D_00189E20 + 0x80);
        heading = func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(float *)(object + 0x10),
                                ((Hero *)D_00189E20)->f[0x84 / 4] - *(float *)(object + 0x14));
    }
    distance = func_00282E80(object + 0x10, target);
    switch (*(u8 *)(object + 0x95)) {
    case 2:
        if (func_002B3890((u8 *)object)) {
            if (*(u8 *)(object + 0x43) != 11) func_002A7470(object, 11, 0, 10);
            *(u8 *)(object + 0xBC) = 0;
            func_002B60B0((u8 *)object, 0.002222222276031971f, 0.06666667014360428f,
                         0.0011635529808700085f, 0.10471977293491364f);
            func_L02_003F1A88(object, func_L02_003FC098(*(char **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (*(u8 *)(object + 0xBC) == 1 && *(u16 *)(object + 0x96) > 300) {
            switch (func_002A77E0(5)) {
            case 0: if (*(u8 *)(object + 0x43) != 2) func_002A7470(object, 2, 0, 10); break;
            case 1: if (*(u8 *)(object + 0x43) != 3) func_002A7470(object, 3, 0, 10); break;
            case 2: if (*(u8 *)(object + 0x43) != 4) func_002A7470(object, 4, 0, 10); break;
            case 3: if (*(u8 *)(object + 0x43) != 6) func_002A7470(object, 6, 0, 10); break;
            case 4: if (*(u8 *)(object + 0x43) != 7) func_002A7470(object, 7, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = func_002A77E0(100);
        }
        if (*(s16 *)(state + 0x4EA) != 0) {
            func_002A7750((u8 *)object, 5, 4);
            if (func_002A77E0(2)) {
                if (*(u8 *)(object + 0x43) != 1) func_002A7470(object, 1, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 5) func_002A7470(object, 5, 0, 10);
        }
        angle = func_00283248(target[0] - *(float *)(object + 0x10),
                             target[1] - *(float *)(object + 0x14));
        angle = func_00283C80(*(float *)(object + 0xF8), angle);
        if (angle > 2.7925272f) func_L02_003F1B70(object);
        if (*(u8 *)(object + 0xBC) == 0 && func_00282E80(object + 0x10, state + 0x4A0) < 0.5f)
            *(u8 *)(object + 0xBC) = 1;
        else
            func_L01_00321178(object, state + 0x4A0);
        break;
    case 5:
        flags = func_002B1C20(object, state + 0x60);
        if ((*(u8 *)(object + 0x42) == 16 && func_002A77E0(30) == 0) || (flags & 1)) {
            func_L02_003FC248(object, 0, -1);
            func_L02_003F18E8(object);
        } else if (flags & 2)
            func_002A7750((u8 *)object, 7, 4);
        break;
    }
    switch (*(u8 *)(object + 0x20)) {
    case 3:
        if (func_002B3868((u8 *)object)) {
            *(u8 *)(object + 0xBC) = 0;
            if (*(u8 *)(object + 0x43) != 2) func_002A7470(object, 2, 0, 0);
            *(int *)(state + 0x14C) = -1;
        }
        if (*(u8 *)(object + 0xBC) == 0 &&
            *(u16 *)(object + 0x96) > *(s16 *)(state + 0x4F0)) {
            if (*(u8 *)(object + 0x43) != 11) func_002A7470(object, 11, 0, 10);
            *(u8 *)(object + 0xBC) = 1;
        } else if (*(u8 *)(object + 0xBC) == 1) {
            if (func_L00_003206B8(object + 0x10, func_L02_003FC0B8(*(char **)(object + 0xB8)))) {
                func_002A7750((u8 *)object, 4, 2);
                *(int *)(state + 0x14C) = func_L00_0042AB40(*(char **)(object + 0xB8));
            }
            func_L01_00321178(object, func_L02_003FC098(*(char **)(object + 0xB8)));
        }
        break;
    case 5:
        if (*(u8 *)(object + 0x60) & 2) func_002A7750((u8 *)object, 7, -1);
        break;
    case 6:
        if (func_002B3868((u8 *)object)) {
            if (*(u8 *)(object + 0x43) != 10) func_002A7470(object, 10, 0, 10);
            func_002B60B0((u8 *)object, 0.004444444552063942f, 0.13333334028720856f,
                         0.006981317885220051f, 0.8377581834793091f);
        }
        func_002B5278((u8 *)object, heading);
        if (*(u8 *)(object + 0x60) & 2)
            func_002A7750((u8 *)object, *(s16 *)(state + 0x4EC), *(s16 *)(state + 0x4EE));
        break;
    case 7:
        if (func_002B3868((u8 *)object) && *(u8 *)(object + 0x43) != 11)
            func_002A7470(object, 11, 0, 15);
        if (*(u8 *)(object + 0x42) == 8 && distance > 15.0f) {
            if (*(u8 *)(object + 0x43) != 11) func_002A7470(object, 11, 0, 4);
            func_002B60B0((u8 *)object, 0.004444444552063942f, 0.13333334028720856f,
                         0.0011635529808700085f, 0.10471977293491364f);
        } else if (*(u8 *)(object + 0x42) == 11 && distance < 7.0f) {
            if (*(u8 *)(object + 0x43) != 8) func_002A7470(object, 8, 0, 4);
            func_002B60B0((u8 *)object, 0.004444444552063942f, 0.03333333507180214f,
                         0.0011635529808700085f, 0.10471977293491364f);
        }
        if (distance < 2.8f &&
            func_00283C80(*(float *)(object + 0xF8),
                          func_00283248(target[0] - *(float *)(object + 0x10),
                                        target[1] - *(float *)(object + 0x14))) < 0.38397247f) {
            func_002A7750((u8 *)object, 8, -1);
            if (*(u8 *)(object + 0x43) != 12) func_002A7470(object, 12, 4, 3);
            *(int *)(state + 0x4D0) = 0;
        } else if (distance > 2.8f) {
            if (!func_L02_003F1BA8(object))
                func_002B4FF0(object, target, *(float *)(state + 0x4B4));
        } else
            func_002B50E0(object, object + 0x10, heading);
        angle = func_00283248(target[0] - *(float *)(object + 0x10),
                             target[1] - *(float *)(object + 0x14));
        angle = func_00283C80(*(float *)(object + 0xF8), angle);
        if (angle > 2.7925272f) func_L02_003F1B70(object);
        break;
    case 8:
        if (*(u8 *)(object + 0x60) & 2) {
            *(float *)(state + 0x4CC) = 8.0f;
            if (D_0018C2BC == object) {
                func_002A7750((u8 *)object, 9, -1);
                if (*(u8 *)(object + 0x43) != 13) func_002A7470(object, 13, 0, 7);
            } else func_002A7750((u8 *)object, 7, -1);
        }
        animation_frame = func_0029F530(object);
        if (*(u8 *)(object + 0x42) == 12) {
            if (animation_frame >= 19.0f && animation_frame <= 25.0f) {
                func_002A8D70(object, 0, 0.35f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
                func_002A8D70(object, 1, 0.15f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
                func_002A8D70(object, 2, 0.15f, (float)*(u8 *)(state + 0x34), 0x10001, 1.0f, 0, 1, 0);
            }
            if (*(u8 *)(object + 0x42) == 12 && animation_frame >= 17.0f && animation_frame <= 25.0f) {
                func_L00_002E6CF0((void (*)(void *))func_L02_003F16A8, object);
                func_L02_003F1608(object);
                *(float *)(state + 0x4CC) = 25.0f;
            }
        }
        func_002B50E0(object, object + 0x10, heading);
        break;
    case 9:
        if (*(u8 *)(object + 0x60) & 2) func_002A7750((u8 *)object, 7, -1);
        break;
    }
    func_L02_003F1578(object);
}
