#include "common.h"

extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_range(int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
/* The FP and integer argument banks keep their order independently. */
extern void *part_spawn_hero_relative(void *, void *, int, float, unsigned char, unsigned char, int);

extern float g_particle_pair_height __attribute__((sda));
extern float g_particle_pair_speed __attribute__((sda));
extern float g_particle_pair_lift_speed[] __attribute__((sda));
/* Each range contains adjacent lower and upper bounds. */
extern int g_particle_pair_value_range[] __attribute__((sda));
extern float g_particle_pair_scale_range[] __attribute__((sda));
extern int g_particle_pair_kind __attribute__((sda));

/* Emit two particles at opposite local offsets, including platform motion. */
void entity_spawn_particle_pair(char *moby)
{
    float carryDelta[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(moby + 0x68);
    int side;

    qzero_nc(angles);
    if (*(void **)(state + 0x260)) {
        moby_transform_point_and_rotation_by_parent(moby, *(void **)(state + 0x260), moby + 0x10, angles, carryDelta, angles);
        FastVecSub(carryDelta, carryDelta, moby + 0x10);
    } else {
        qzero_nc(carryDelta);
    }
    for (side = 0; side < 2; side++) {
        int randomValue, randomByte;
        float scale;

        qzero_nc(position);
        position[2] = g_particle_pair_height;
        if (!side)
            position[2] = -position[2];
        vec_random_direction(velocity, g_particle_pair_speed * (1.0f / 60.0f),
                      g_particle_pair_lift_speed[0] * (1.0f / 60.0f));
        FastVecAdd(velocity, velocity, carryDelta);
        randomValue = math_random_int_range(g_particle_pair_value_range[0], g_particle_pair_value_range[1]);
        matrix_mul_vec3(position, position, moby + 0xC0);
        randomValue = (unsigned char)randomValue;
        FastVecAdd(position, position, moby + 0x10);
        scale = math_random_float_range(g_particle_pair_scale_range[0], g_particle_pair_scale_range[1]);
        randomByte = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, g_particle_pair_kind, scale, randomValue, (unsigned char)randomByte, 0);
    }
}
