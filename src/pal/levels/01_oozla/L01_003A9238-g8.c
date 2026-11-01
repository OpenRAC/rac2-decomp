#include "include_asm.h"

#include "common.h"
extern float D_L01_001B2F48 __attribute__((sda));
extern float func_002A89A8(void *, int, float);
extern void *func_00312D58(void *, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern void func_PAL_002C0838(void *, void *, int, int);

void func_PAL_L01_003A96A8(char *object)
{
    float center[4], velocity[4], position[4];
    float angle, radius;
    int i, j, type, lifetime;
    int scale = 2;

    qcopy(center, (object + 0x10));
    center[2] = D_L01_001B2F48 = func_002A89A8(object + 0x10, 0, 0.5f);
    func_00312D58(center, 4.5f);
    for (i = 4; i >= 0; --i) {
        velocity[0] = *(float *)(object + 0x10) + scale * func_002A7878(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + scale * func_002A7878(-0.3f, 0.3f);
        velocity[2] = D_L01_001B2F48;
        func_002C19D8(velocity, &D_L01_001B2F48, -1, scale * func_002A7878(0.3f, 0.6f), 5250.0f);
    }
    for (j = 39; j >= 0; --j) {
        angle = func_002A7940();
        radius = scale * func_002A7878(0.0f, 0.060000002f);
        velocity[0] = func_00283180(angle) * radius;
        velocity[1] = func_00283198(angle) * radius;
        velocity[2] = scale * func_002A7878(0.040000003f, 0.10000001f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = D_L01_001B2F48 - func_002A7878(0.0f, 0.2f);
        type = func_002A77E0(2);
        lifetime = func_002A7820(90, 120);
        func_PAL_002C0838(position, velocity, type, scale * lifetime);
    }
}
