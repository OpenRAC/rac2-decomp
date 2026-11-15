#include "common.h"

typedef float V4_F411d00[4] __attribute__((aligned(16)));

extern float D_L16_001B17A0 __attribute__((sda));
extern float D_L16_001B17B0 __attribute__((sda));
extern float D_L16_001B17B8 __attribute__((sda));
extern float D_L16_001B17BC[];

extern void vec_random_direction(void *, float, float);
extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern float weapon_compute_shot_launch_speed(void *, void *, s32, float, float);
extern s32 SpawnExplosion(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void part_spawn_spinning_fragment(s32, void *, void *, s32, float, float);

/* Fires the object's spark: builds a short ray from its frame, tilts it by the resident angle and hands it to the effect spawner. */
void snivelak_fire_lobbed_shot(char *moby)
{
    V4_F411d00 offset, start, goal, velocity;
    char *vars = *(char **)(moby + 0x68);
    float rate, angle;

    vec_random_direction(offset, 0.0f, 1.0f);
    matrix_mul_vec3(start, &D_L16_001B17A0, moby + 0xC0);
    FastVecAdd(start, start, moby + 0x10);
    FastVecAdd(start, start, offset);
    FastVecScale(goal, offset, 3.0f);
    goal[2] = 0.0f;
    FastVecAdd(goal, goal, *(char **)(vars + 0x24C) + 0x10);
    rate = D_L16_001B17B0 * 0.016666668f;
    angle = math_random_float_range(D_L16_001B17B8, D_L16_001B17BC[0]) * 0.00027777778f;
    FastVecSub(velocity, goal, start);
    velocity[2] = 0.0f;
    vec_scale_to_length(velocity, velocity, rate);
    velocity[2] = weapon_compute_shot_launch_speed(start, goal, 0, D_L16_001B17B0 * 0.016666668f, -angle);
    SpawnExplosion(start, 0, 0x19, 0x14, 1.0f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0);
    part_spawn_spinning_fragment(*(s32 *)(vars + 0x1F0), start, velocity, 0, angle, (float)*(u8 *)(vars + 0x36));
}
