#include "common.h"
extern void func_3109C8(u8 *, int, int);

extern float g_platform_scale_factor __attribute__((sda));
extern float g_platform_motion_param __attribute__((sda));
extern float g_platform_height_tolerance __attribute__((sda));
extern float g_platform_motion_param_b __attribute__((sda));
extern int g_frame_l07_counter __attribute__((sda));
extern int g_platform_wave_param_a __attribute__((sda));
extern int g_platform_wave_param_b;
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
    *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * g_platform_scale_factor;
    switch (moby[0x20]) {
    case 0:
        *(u16 *)(moby + 0x34) |= 0x1000;
        *(float *)(vars + 0x88) = 9.0f;
        *(int *)(vars + 0xDC) |= 1;
        func_3109C8(moby, 1, -1);
        break;
    case 1:
        func_31B828(moby, g_platform_motion_param, vars + 0x50, g_platform_height_tolerance, g_platform_motion_param_b, *(int *)(vars + 0xE0));
        lift_keep_height(moby);
        break;
    }
    if (moby[0x31]) {
        phase = func_2E5460(g_frame_l07_counter % 60);
        { float period = func_2E5460(60);
        phase *= 6.2831855f;
        phase /= period; }
        *(int *)(moby + 0x78) = func_31C970(g_platform_wave_param_a, g_platform_wave_param_b, phase - 3.1415927f);
    }
    func_2E4340(delta, moby + 0x10, pos);
    func_317618(vars + 0xA0, delta, old, moby + 0xF0);
}
