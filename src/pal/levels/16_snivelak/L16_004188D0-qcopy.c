#include "include_asm.h"

#include "common.h"
typedef int BossQuadword __attribute__((mode(TI)));
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(float *, float *, float);
extern void moby_set_state(u8 *, int, int);

/* Starts a projectile with its velocity, gravity and perpendicular turn vector. */
void snivelak_launch_projectile_pal(u8 *moby, float *velocity, float gravity)
{
    float up[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    *(BossQuadword *)state = *(BossQuadword *)velocity;
    *(float *)(state + 0x34) = gravity;
    *(BossQuadword *)up = 0;
    up[2] = 1.0f;
    FastVecCross(state + 0x20, up, velocity);
    vec_set_direction_with_complement((float *)(state + 0x20), (float *)(state + 0x20), 0.06981318f);
    moby_set_state(moby, 2, -1);
}
