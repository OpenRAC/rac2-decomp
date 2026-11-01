#include "include_asm.h"

#include "common.h"
typedef int BossQuadword __attribute__((mode(TI)));
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(float *, float *, float);
extern void func_002A7750(u8 *, int, int);

/* Starts a projectile with its velocity, gravity and perpendicular turn vector. */
void func_PAL_L16_004188D0(u8 *moby, float *velocity, float gravity)
{
    float up[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    *(BossQuadword *)state = *(BossQuadword *)velocity;
    *(float *)(state + 0x34) = gravity;
    *(BossQuadword *)up = 0;
    up[2] = 1.0f;
    func_00282DD8(state + 0x20, up, velocity);
    func_002ACE78((float *)(state + 0x20), (float *)(state + 0x20), 0.06981318f);
    func_002A7750(moby, 2, -1);
}
