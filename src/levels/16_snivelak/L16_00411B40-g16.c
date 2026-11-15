#include "common.h"

extern float D_L16_001B16D0[4] __attribute__((sda));
extern float D_L16_001B16E0 __attribute__((sda));
extern u8 D_L16_00189EF0[] __attribute__((nosda));
extern void func_0029FC20(void *, s32, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L13_0040DC20(void *, void *, void *, s32, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

/* Fires two shots from the boss's body toward the player, one straight and one with a small random offset. */
void func_L16_00411B40(u8 *moby)
{
    float matrix[16];
    float origin[4];
    float direction[4];
    float offset[4];
    u8 *state;
    float angle;
    float radius;
    float zero = 0.0f;
    float scale = 0.016666668f;
    state = *(u8 **)(moby + 0x68);
    TransformMobyJointPoint(*(void **)(state + 0x1F0), 2, matrix);
    transform_vector(origin, D_L16_001B16D0, matrix);
    FastVecSub(direction, D_L16_00189EF0, origin);
    vec_scale_to_length(direction, direction, D_L16_001B16E0 * scale);
    SpawnEA7Moby(moby, direction, origin, 0, (float)state[0x34]);
    angle = RandomAngle();
    radius = RandomFloatRange(zero, 4.0f);
    FastVecSub(direction, D_L16_00189EF0, moby + 0x10);
    vec_scale_to_length(direction, direction, -4.0f);
    FastVecAdd(direction, direction, D_L16_00189EF0);
    offset[0] = FastSinOrCosA(angle) * radius;
    offset[1] = FastSinOrCosB(angle) * radius;
    offset[2] = zero;
    FastVecAdd(direction, direction, offset);
    FastVecSub(direction, direction, origin);
    vec_scale_to_length(direction, direction, D_L16_001B16E0 * scale);
    SpawnEA7Moby(moby, direction, origin, 0, (float)state[0x34]);
}
