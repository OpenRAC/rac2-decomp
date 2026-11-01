#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern u8 D_00189EA0[];
extern u8 *func_L18_003F75E8(int, int *);
extern int func_002B3868(void *);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_00282C88(void *);
extern void func_002ACB48(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L18_003F76F0(void *, void *, void *);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int func_L11_00439D78(float, float, float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float D_L18_001B1530 __attribute__((sda));
extern float D_L18_001B1534 __attribute__((sda));
extern float D_L18_001B1538 __attribute__((sda));
extern float D_L18_001B153C __attribute__((sda));
extern float D_L18_001B1540 __attribute__((sda));
extern float D_L18_001B1544 __attribute__((sda));
extern float D_L18_001B1548 __attribute__((sda));
extern int D_L18_001B154C __attribute__((sda));
extern float D_L18_001B1550 __attribute__((sda));
extern int D_L18_001B1554 __attribute__((sda));
extern float D_L18_001B1558 __attribute__((sda));
extern float D_L18_001B155C __attribute__((sda));
extern u8 D_L18_001B1560[16] __attribute__((sda));
typedef struct {
    float angles[4];
    int firstId,  secondId,  group;
    float restHeight,  verticalSpeed,  period,  amplitude;
    int spawnCount;
} LauncherState;
typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0x47];
    LauncherState *vars;
    u8 pad6c[0x2A];
    u16 timer;
    u8 pad98[0x58];
    float rotation[4];
} LauncherObject;

void func_PAL_L18_00434BE0(u8 *a)
{
    float velocity[4], position[4];
    int count1, count2, count, i;
    u8 *p;
    LauncherObject *object = (LauncherObject *)a;
    LauncherState *s = object->vars;
    float zero, duration;

    switch (object->state) {
    case 0:
        s->restHeight = object->position[2];
        func_002A7750(a, 1, -1);
        break;
    case 1:
        if (s->firstId != -1 && func_002ACBC8(D_00189EA0, s->firstId)) {
            func_L18_003F75E8(s->group, &count1);
            if (count1 >= 4)
                func_002A7750(a, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(a)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            zero = object->rotation[0];
            object->position[2] = s->restHeight;
            s->verticalSpeed += func_002A7878(zero, D_L18_001B1530 * 0.020000001f);
            s->angles[0] = func_002A7878(zero, D_L18_001B1534 * 0.0003490659f);
            s->angles[1] = func_002A7878(zero, D_L18_001B1538 * 0.0003490659f);
            object->position[2] = s->restHeight;
            func_002E5CF8(0, 0, a);
        }
        if (object->position[2] >= s->restHeight) {
            object->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L18_001B155C * 0.00040000002f;
            if (s->verticalSpeed > 0) {
                object->rotation[0] = func_00283B98(s->angles[0], object->rotation[0]);
                object->rotation[1] = func_00283B98(s->angles[1], object->rotation[1]);
            } else {
                object->rotation[0] = func_00283B98(-s->angles[0], object->rotation[0]);
                object->rotation[1] = func_00283B98(-s->angles[1], object->rotation[1]);
            }
        } else {
            func_002A7750(a, 2, -1);
        }
        if (s->secondId != -1 && func_002ACBC8(D_00189EA0, s->secondId)) {
            func_L18_003F75E8(s->group, &count2);
            if (count2 >= 4)
                func_002A7750(a, 3, -1);
        }
        break;
    case 3:
        if (func_002B3868(a)) {
            object->rotation[0] = 0;
            object->rotation[1] = 0;
            object->position[2] = s->restHeight;
            count = 50;
            for (i = 0; i < s->spawnCount && count > 0; i++) {
                p = func_L18_003F75E8(s->group, &count);
                if (p) {
                    func_00282C88(velocity);
                    velocity[2] = D_L18_001B153C * 0.020000001f;
                    func_002ACB48(velocity, D_L18_001B1540 * 0.020000001f);
                    func_00282CC0(position, a + 0x10, D_L18_001B1560);
                    func_L18_003F76F0(p, position, velocity);
                    *(u8 **)(p + 0xB8) = a;
                }
            }
            if (i) {
                func_PAL_L00_003FB330(a + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1,
                              1.0f, 20.0f, 1, 1, 0, 0);
                func_002E5CF8(0, 0, a);
                s->verticalSpeed += func_002A7878(D_L18_001B1544, D_L18_001B1548) * 0.020000001f;
                duration = (float)func_L11_00439D78(object->position[2], s->restHeight,
                                                   s->verticalSpeed, D_L18_001B155C * 0.00040000002f);
                s->angles[0] = (float)func_002A77E0(D_L18_001B154C) * 6.28318548f / duration;
                s->angles[1] = (float)func_002A77E0(D_L18_001B154C) * 6.28318548f / duration;
                s->angles[2] = (float)func_002A77E0(D_L18_001B154C) * 6.28318548f / duration;
            }
        }
        if (object->position[2] >= s->restHeight) {
            object->position[2] += s->verticalSpeed;
            s->verticalSpeed -= D_L18_001B155C * 0.00040000002f;
            object->rotation[0] = func_00283B98(s->angles[0], object->rotation[0]);
            object->rotation[1] = func_00283B98(s->angles[1], object->rotation[1]);
            object->rotation[2] = func_00283B98(s->angles[2], object->rotation[2]);
        } else {
            func_002A7750(a, 4, -1);
        }
        break;
    case 4:
        if (func_002B3868(a)) {
            func_00282C88(s);
            func_00282C88(a + 0xF0);
            object->position[2] = s->restHeight;
            s->period = func_00283CE0(D_L18_001B1554);
            s->amplitude = D_L18_001B1558;
            func_002E5CF8(0, 0, a);
        }
        if (s->amplitude >= 0.1f) {
            object->rotation[0] = s->amplitude * func_00283198(func_00283C28(
                func_00283CE0(object->timer) * 6.28318548f / s->period));
            object->rotation[1] = s->amplitude * func_00283180(func_00283C28(
                func_00283CE0(object->timer) * 6.28318548f / s->period));
            s->amplitude *= D_L18_001B1550;
            s->period *= D_L18_001B1550;
        } else {
            object->rotation[0] = object->rotation[1] = object->rotation[2] = 0.0f;
            func_002A7750(a, 5, -1);
        }
    }
    if (object->timer <= 0xFFFE)
        ++object->timer;
}
