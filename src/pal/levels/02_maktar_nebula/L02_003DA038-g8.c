#include "include_asm.h"

#include "common.h"
extern void transform_vector(void *, void *, void *);
extern void moby_transform_joint_point(char *, int, void *);
extern void moby_transform_joint_to_world(char *, int, void *);
extern int math_random_int_below(int);
extern float g_chainblade_debris_offset_a[4] SDATA(D_L02_001B02C0);
extern float g_chainblade_debris_offset_b[4] SDATA(D_L02_001B0200);
extern float g_chainblade_debris_delta_length __attribute__((sda));
extern float g_chainblade_debris_jitter_b __attribute__((sda));
extern float g_chainblade_burst_speed_base __attribute__((sda));
extern float g_chainblade_burst_speed_range __attribute__((sda));
extern int g_chainblade_burst_particle_count __attribute__((sda));
extern char g_chainblade_spawn_record_c[] SDATA(D_L02_001B0290);
extern float g_chainblade_debris_speed_base __attribute__((sda));
extern float g_chainblade_debris_speed_range __attribute__((sda));
extern int g_chainblade_debris_count_scale __attribute__((sda));
extern float g_chainblade_debris_jitter_a __attribute__((sda));
extern char g_chainblade_spawn_record_a[] SDATA(D_L02_001B0230);
extern char g_chainblade_spawn_record_b[] SDATA(D_L02_001B0260);
extern char g_camera_l02_position[];
extern float FastVecLength(void *);
extern float math_random_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern void *enemy_spawn_record(void *, void *, void *, int, int);

/* Spawns the particle bursts of one joint (func_L02_003D46B8 calls it for joints 2 and 3, the
 * second mirrored): the joint's position and matrix give the origin and the emission axis,
 * the length of the state's vector at +0x1B0 sets a 0..1 strength, and two offset points (the
 * first pulled horizontally towards D_L02_001BA500) emit D_L02_001B02B0 particles and a
 * strength-scaled number of particle pairs. The random term is an argument of each velocity
 * call, as in retail: hoisted into its own statement, the second loop's preheader copies swap
 * places. */
void SpawnJointParticleBursts_pal(char *self, int joint, int mirror) {
    float origin[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset_a[4] __attribute__((aligned(16)));
    float offset_b[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float strength;
    int i;
    moby_transform_joint_to_world(self, joint, origin);
    moby_transform_joint_point(self, joint, matrix);
    qcopy(direction, matrix + 8);
    strength = FastVecLength(*(char **)(self + 0x68) + 0x1B0) * 2.7777777f +
               math_random_float_range(0.0f, 0.1f);
    if (strength > 1.0f) strength = 1.0f;
    else if (strength < 0.0f) strength = 0.0f;
    qcopy(offset_a, g_chainblade_debris_offset_a);
    qcopy(offset_b, g_chainblade_debris_offset_b);
    if (mirror) {
        offset_a[1] = -offset_a[1];
        offset_b[1] = -offset_b[1];
    }
    transform_vector(position, offset_a, matrix);
    FastVecAdd(position, position, origin);
    FastVecSub(delta, g_camera_l02_position, position);
    delta[2] = 0.0f;
    vec_scale_to_length(delta, delta, g_chainblade_debris_delta_length);
    FastVecAdd(position, position, delta);
    for (i = 0; i < g_chainblade_burst_particle_count; i++) {
        vec_scale_to_length(velocity, direction,
                      -((g_chainblade_burst_speed_base + math_random_float_range(0.0f, strength * g_chainblade_burst_speed_range)) *
                        0.020000001f));
        vec_add_random_offset(position, g_chainblade_debris_jitter_b);
        enemy_spawn_record(position, velocity, g_chainblade_spawn_record_c, math_random_int_below(2), 1);
    }
    transform_vector(position, offset_b, matrix);
    FastVecAdd(position, position, origin);
    for (i = 0; (float)i < strength * (float)g_chainblade_debris_count_scale + 2.0f; i++) {
        vec_scale_to_length(velocity, direction,
                      -((g_chainblade_debris_speed_base + math_random_float_range(0.0f, strength * g_chainblade_debris_speed_range)) *
                        0.020000001f));
        vec_add_random_offset(position, g_chainblade_debris_jitter_a);
        enemy_spawn_record(position, velocity, g_chainblade_spawn_record_a, math_random_int_below(2), 1);
        vec_scale_to_length(velocity, direction,
                      -((g_chainblade_debris_speed_base + math_random_float_range(0.0f, strength * g_chainblade_debris_speed_range)) *
                        0.020000001f));
        vec_add_random_offset(position, g_chainblade_debris_jitter_a);
        enemy_spawn_record(position, velocity, g_chainblade_spawn_record_b, math_random_int_below(2), 1);
    }
}
