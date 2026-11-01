#include "include_asm.h"

#include "common.h"
extern int func_002E5CF8(int, int, char *);
extern void *func_00312D58(float *, float);
extern void func_L02_0031E9E8(float *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern char *func_PAL_002C0838(float *, float *, int, int);
extern float D_L06_001B37CC __attribute__((sda));

void func_PAL_L06_0046A350(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4];
    float spawn[4];
    int n = 5;
    int i;
    char *p;

    func_002E5CF8(2, 0, self);
    qcopy(pos, self + 0x10);
    D_L06_001B37CC = pos[2];
    func_00312D58(pos, 11.25f);
    for (i = 0x59; i >= 0; i--) {
        func_L02_0031E9E8(vel, n * 0.040000003f);
        vel[2] = n * 0.020000001f * func_002A7878(2.0f, 3.5f);
        spawn[0] = *(float *)(self + 0x10) + vel[0] * 8.0f;
        spawn[1] = *(float *)(self + 0x14) + vel[1] * 8.0f;
        spawn[2] = D_L06_001B37CC - func_002A7878(0.0f, 0.2f);
        p = func_PAL_002C0838(spawn, vel, func_002A77E0(2), n * func_002A7820(0x5A, 0x78));
        if (p != 0)
            *(float *)(p + 0xC) = *(float *)(p + 0xC) * func_002A7878(4.0f, 6.0f);
    }
}
