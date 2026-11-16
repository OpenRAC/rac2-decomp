#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *, int, int);
extern float g_platform_scale_factor __attribute__((sda));
extern float g_platform_motion_param __attribute__((sda));
extern float g_platform_height_tolerance __attribute__((sda));
extern float g_platform_motion_param_b __attribute__((sda));
extern int g_frame_l07_counter __attribute__((sda));
extern int g_platform_wave_param_a __attribute__((sda));
extern int g_platform_wave_param_b;
extern void pushable_moby_update_pal(u8 *, float, u8 *, float, float, int);
extern void lift_keep_height_pal(u8 *);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

void platform_update_pal(u8 *o)
{
    float pos[4], old[4], delta[4];
    u8 *m = *(u8 **)(o + 0x68);
    float phase;
    qcopy(pos, o + 0x10);
    qcopy(old, o + 0xF0);
    *(float *)(o + 0x2C) = *(float *)(*(u8 **)(o + 0x24) + 0x24) * g_platform_scale_factor;
    switch (o[0x20]) {
    case 0:
        *(u16 *)(o + 0x34) |= 0x1000;
        *(float *)(m + 0x88) = 9.0f;
        *(int *)(m + 0xDC) |= 1;
        moby_set_state(o, 1, -1);
        break;
    case 1:
        pushable_moby_update_pal(o, g_platform_motion_param, m + 0x50, g_platform_height_tolerance, g_platform_motion_param_b, *(int *)(m + 0xE0));
        lift_keep_height_pal(o);
        break;
    }
    if (o[0x31]) {
        phase = IntToFloat(g_frame_l07_counter % 50);
        { float period = IntToFloat(50);
        phase *= 6.2831855f;
        phase /= period; }
        *(int *)(o + 0x78) = PulseColor(g_platform_wave_param_a, g_platform_wave_param_b, phase - 3.1415927f);
    }
    FastVecSub(delta, o + 0x10, pos);
    mat_combine_and_store(m + 0xA0, delta, old, o + 0xF0);
}
