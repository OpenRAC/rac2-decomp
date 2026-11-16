#include "include_asm.h"

#include "common.h"
typedef float V4_F411d00[4] __attribute__((aligned(16)));
extern float g_snivelak_lobbed_shot_offset __attribute__((sda));
extern float g_snivelak_lobbed_launch_rate __attribute__((sda));
extern float g_snivelak_lobbed_angle_min __attribute__((sda));
extern float g_snivelak_lobbed_angle_max[];
extern void vec_random_direction(void *, float, float);
extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern float weapon_compute_shot_launch_speed(void *, void *, s32, float, float);
extern char *SpawnExplosion_pal(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern char *part_spawn_spinning_fragment(s32, void *, void *, s32, float, float);

/* Fires the object's spark: builds a short ray from its frame, tilts it by the resident angle and hands it to the effect spawner. */
void snivelak_fire_lobbed_shot_pal(char *moby)
{
    V4_F411d00 rand_dir, muzzle, target, velocity;
    char *state = *(char **)(moby + 0x68);
    float rate, angle;

    vec_random_direction(rand_dir, 0.0f, 1.0f);
    matrix_mul_vec3(muzzle, &g_snivelak_lobbed_shot_offset, moby + 0xC0);
    FastVecAdd(muzzle, muzzle, moby + 0x10);
    FastVecAdd(muzzle, muzzle, rand_dir);
    FastVecScale(target, rand_dir, 3.0f);
    target[2] = 0.0f;
    FastVecAdd(target, target, *(char **)(state + 0x24C) + 0x10);
    rate = g_snivelak_lobbed_launch_rate * 0.020000001f;
    angle = math_random_float_range(g_snivelak_lobbed_angle_min, g_snivelak_lobbed_angle_max[0]) * 0.00040000002f;
    FastVecSub(velocity, target, muzzle);
    velocity[2] = 0.0f;
    vec_scale_to_length(velocity, velocity, rate);
    velocity[2] = weapon_compute_shot_launch_speed(muzzle, target, 0, g_snivelak_lobbed_launch_rate * 0.020000001f, -angle);
    SpawnExplosion_pal(muzzle, 0, 0x19, 0x14, 1.0f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0);
    part_spawn_spinning_fragment(*(s32 *)(state + 0x1F0), muzzle, velocity, 0, angle, (float)*(u8 *)(state + 0x36));
}
