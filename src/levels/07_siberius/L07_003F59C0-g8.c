#include "common.h"
extern void func_3109C8(u8 *, int, int);

extern float D_L07_001B0F44 __attribute__((sda));
extern float D_L07_001B0F38 __attribute__((sda));
extern float D_L07_001B0F3C __attribute__((sda));
extern float D_L07_001B0F40 __attribute__((sda));
extern int D_L07_001B1E08 __attribute__((sda));
extern int D_L07_001B0F30 __attribute__((sda));
extern int D_L07_001B0F34;
extern void func_31B828(u8 *, float, u8 *, float, float, int);
extern void lift_keep_height(u8 *);
extern float func_2E5460(int);
extern int func_31C970(int, int, float);
extern void func_2E4340(void *, void *, void *);
extern void func_317618(void *, void *, void *, void *);

/* Updates the moving platform: starts it up, moves it along its path and makes it pulse in colour. */
void platform_update(u8 *moby)
{
    float pos[4], old[4], delta[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    float phase;
    qcopy(pos, moby + 0x10);
    qcopy(old, moby + 0xF0);
    *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * D_L07_001B0F44;
    switch (moby[0x20]) {
    case 0:
        *(u16 *)(moby + 0x34) |= 0x1000;
        *(float *)(vars + 0x88) = 9.0f;
        *(int *)(vars + 0xDC) |= 1;
        func_3109C8(moby, 1, -1);
        break;
    case 1:
        func_31B828(moby, D_L07_001B0F38, vars + 0x50, D_L07_001B0F3C, D_L07_001B0F40, *(int *)(vars + 0xE0));
        lift_keep_height(moby);
        break;
    }
    if (moby[0x31]) {
        phase = func_2E5460(D_L07_001B1E08 % 60);
        { float period = func_2E5460(60);
        phase *= 6.2831855f;
        phase /= period; }
        *(int *)(moby + 0x78) = func_31C970(D_L07_001B0F30, D_L07_001B0F34, phase - 3.1415927f);
    }
    func_2E4340(delta, moby + 0x10, pos);
    func_317618(vars + 0xA0, delta, old, moby + 0xF0);
}
