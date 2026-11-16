#include "common.h"

extern float g_snivelak_muzzle_offset[4] __attribute__((sda));
extern float g_snivelak_shot_speed __attribute__((sda));
extern u8 g_snivelak_shot_origin[] __attribute__((nosda));
extern void moby_transform_joint_point(void *, s32, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *SpawnEA7Moby(void *, void *, void *, s32, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Fires two shots from the boss's body toward the player, one straight and one with a small random offset. */
void snivelak_fire_body_shots(u8 *moby)
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
    moby_transform_joint_point(*(void **)(state + 0x1F0), 2, matrix);
    transform_vector(origin, g_snivelak_muzzle_offset, matrix);
    FastVecSub(direction, g_snivelak_shot_origin, origin);
    vec_scale_to_length(direction, direction, g_snivelak_shot_speed * scale);
    SpawnEA7Moby(moby, direction, origin, 0, (float)state[0x34]);
    angle = math_random_angle();
    radius = math_random_float_range(zero, 4.0f);
    FastVecSub(direction, g_snivelak_shot_origin, moby + 0x10);
    vec_scale_to_length(direction, direction, -4.0f);
    FastVecAdd(direction, direction, g_snivelak_shot_origin);
    offset[0] = math_fast_sin_or_cos_a(angle) * radius;
    offset[1] = math_fast_sin_or_cos_b(angle) * radius;
    offset[2] = zero;
    FastVecAdd(direction, direction, offset);
    FastVecSub(direction, direction, origin);
    vec_scale_to_length(direction, direction, g_snivelak_shot_speed * scale);
    SpawnEA7Moby(moby, direction, origin, 0, (float)state[0x34]);
}
