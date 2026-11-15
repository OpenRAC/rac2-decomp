#include "common.h"
extern s32 func_002A77E0(s32);
extern void func_0029FCC0(void *, s32, void *);
extern float func_002A7878(float, float);
extern void func_L16_0041F1F0(void *, void *, void *, s32, float, float);

/* Drops a small falling shot from one of the boss's two attach points. */
void func_L16_00411ED0(u8 *owner)
{
    u8 *state = *(u8 **)(owner + 0x68);
    float point[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float speed;
    TransformMobyJointToWorld(owner, RandomIntBelow(2), point);
    qzero_nc(acceleration);
    speed = RandomFloatRange(5.0f, 10.0f);
    acceleration[2] = -(speed * (1.0f / 60.0f));
    SpawnSpinningFragment(owner, point, acceleration, 1,
                      1.0f / 180.0f, (float)state[0x36]);
}
