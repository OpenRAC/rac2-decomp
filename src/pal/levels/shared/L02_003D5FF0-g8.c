/* func_PAL_L02_003D5FF0, the PAL copy of func_L02_003D1FA0: the same C, where 1/60 becomes 0.02, the lifetime 60 becomes 50
   and the last particle argument is scaled by 1.44 (6/5 squared). */
#include "common.h"
extern float D_L02_001B0164 __attribute__((sda)), D_L02_001B0168 __attribute__((sda));
extern float D_L02_001B0150 __attribute__((sda)), D_L02_001B0154 __attribute__((sda)), D_L02_001B0158 __attribute__((sda)), D_L02_001B015C __attribute__((sda)), D_L02_001B0160 __attribute__((sda));
extern float D_L02_001BA500[];
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern int func_002A77E0(int), func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282F20(void *, void *, float);
extern void func_002ACEC0(float, void *, void *, void *);
extern char *func_002C2210(float, void *, int, float, int, int, int, void *, int, float);
/* Emits two particles per iteration, with opposite signed orientation. */
void func_PAL_L02_003D5FF0(float *pos, int count) {
    float vel[4] __attribute__((aligned(16)));
    float out[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    int i, sign;
    char *particle;
    func_00282CF0(dir, D_L02_001BA500, pos);
    func_00282F20(offset, dir, 0.3f);
    dir[2] = 0.0f;
    axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    for (i=0;i<count;i++) {
        scale = func_002A7878(D_L02_001B0164, D_L02_001B0168);
        sign = func_002A77E0(2); if (!sign) sign--;
        func_002ACEC0(func_002A7878(-1.047197699546814f, 1.047197699546814f), vel, dir, axis);
        func_00282F20(vel, vel, func_002A7878(D_L02_001B0150, D_L02_001B0154) * 0.020000001f);
        vel[2] = func_002A7878(D_L02_001B0158, D_L02_001B015C) * 0.020000001f;
        func_00282CC0(out, pos, offset);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        particle = func_002C2210(scale * 0.1f, out, 50, scale, 0x7F007F40, 0, sign, vel, 0, D_L02_001B0160 * 1.44f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(scale * 0.07f, out, 50, scale * 0.7f, 0x047F047F, 1, -sign, vel, 0, D_L02_001B0160 * 1.44f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}
