#include "common.h"
extern s32 math_random_int_below(s32);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern float math_random_float_range(float, float);
extern void part_spawn_spinning_fragment(void *, void *, void *, s32, float, float);

/* Drops a small falling shot from one of the boss's two attach points. */
void snivelak_drop_falling_shot(u8 *owner)
{
    u8 *state = *(u8 **)(owner + 0x68);
    float point[4] __attribute__((aligned(16)));
    float acceleration[4] __attribute__((aligned(16)));
    float speed;
    moby_transform_joint_to_world(owner, math_random_int_below(2), point);
    qzero_nc(acceleration);
    speed = math_random_float_range(5.0f, 10.0f);
    acceleration[2] = -(speed * (1.0f / 60.0f));
    part_spawn_spinning_fragment(owner, point, acceleration, 1,
                      1.0f / 180.0f, (float)state[0x36]);
}
