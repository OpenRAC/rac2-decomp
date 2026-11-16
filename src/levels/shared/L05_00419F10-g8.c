#include "common.h"

typedef int BurstVector __attribute__((mode(TI)));
extern float g_sprite_burst_speed_min __attribute__((sda));
extern float g_sprite_burst_speed_max __attribute__((sda));
extern float g_sprite_burst_lift_min __attribute__((sda));
extern float g_sprite_burst_lift_max __attribute__((sda));
extern float g_sprite_burst_ground_param __attribute__((sda));
extern float g_sprite_burst_size_min __attribute__((sda));
extern float g_sprite_burst_size_max __attribute__((sda));
extern char g_origin_vec[];
extern u8 *g_particle_params_table[] NOT_SDA;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_ground_effect(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern int FloatToInt(float);

/* Emits count pairs of sprites (func_002C2210) at a jittered pos, each heading along
   the direction to D_L05_001B96C0 turned by a random angle about the up axis. */
/* Throws out pairs of small sprites from a position, flying in slightly different directions. */
void part_spawn_sprite_pair_burst(float *pos, int count, int color, char *owner)
{
    float dir[4], tmp[4], toward[4], up[4], half[4];
    int i, sign;
    float size, angle;
    char *sprite;

    *(BurstVector *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    if (*(int *)(*(char **)(owner + 0x68) + 0x30)) {
        g_sprite_burst_speed_min = 0.1f;
        g_sprite_burst_speed_max = 6.0f;
        g_sprite_burst_lift_min = 2.0f;
        g_sprite_burst_lift_max = 10.0f;
    }
    FastVecSub(toward, g_origin_vec, pos);
    vec_scale_to_length(half, toward, 0.5f);
    toward[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(g_sprite_burst_size_min, g_sprite_burst_size_max);
        sign = math_random_int_below(2);
        if (!sign)
            sign = sign - 1;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(dir, toward, up, angle);
        vec_scale_to_length(dir, dir, math_random_float_range(g_sprite_burst_speed_min, g_sprite_burst_speed_max) * (1.0f / 60.0f));
        dir[2] = math_random_float_range(g_sprite_burst_lift_min, g_sprite_burst_lift_max) * (1.0f / 60.0f);
        FastVecAdd(tmp, pos, half);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        sprite = part_spawn_ground_effect(pos, 60, size * 0.1f, size, color, 0, sign, dir, g_sprite_burst_ground_param, 0);
        if (sprite) {
            sprite[2] = g_particle_params_table[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
        sprite = part_spawn_ground_effect(pos, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, dir,
                               g_sprite_burst_ground_param, 0);
        if (sprite) {
            sprite[2] = g_particle_params_table[97][6];
            sprite[9] = FloatToInt(4.0f) + 0x70;
        }
    }
}
