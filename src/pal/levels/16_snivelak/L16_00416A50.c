#include "include_asm.h"




#include "common.h"
extern s32 func_002A77E0(s32);
extern void func_0029FCC0(void *, s32, void *);
extern float func_002A7878(float, float);
extern void func_L16_0041F1F0(void *, void *, void *, s32, float, float);

void func_PAL_L16_00417020(u8 *owner)
{
    u8 *state = *(u8 **)(owner + 0x68);
    float point[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float t;
    func_0029FCC0(owner, func_002A77E0(2), point);
    qzero_nc(acceleration);
    t = func_002A7878(5.0f, 10.0f);
    acceleration[2] = -(t * (0.020000001f));
    func_L16_0041F1F0(owner, point, acceleration, 1,
                      0.008f, (float)state[0x36]);
}

