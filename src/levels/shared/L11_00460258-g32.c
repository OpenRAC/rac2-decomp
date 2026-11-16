#include "names.h"
typedef unsigned int u32;
struct ParticleSettings {
    int *colors;
    short *sizes;
    short *range;
    int unknown0C;
    int lifetime;
    float jitter;
};
extern float g_spark_ring_speed_min __attribute__((sda));
extern float g_spark_ring_speed_max __attribute__((sda));
extern float g_spark_ring_rise_min __attribute__((sda));
extern float g_spark_ring_rise_max __attribute__((sda));
extern u32 g_spark_particle_texture __attribute__((sda));
extern struct ParticleSettings g_spark_ring_particle_settings __attribute__((sda));
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void *enemy_spawn_record(void *, void *, void *, void *, int);
extern void *part_spawn_gravity_fade(void *, void *, int, u32, int, int, int, float, float, float, int);
extern float FastAddRotations(float, float);

/* Spawns a ring of sparks and puffs around a position, spread evenly in angle with random speeds. */
void part_l11_spawn_spark_ring(void *position, int count) {
    float velocity[4];
    float step = 6.2831854820251465f / IntToFloat(count);
    float angle = math_random_float_range(-3.1415927410125732f, 3.1415927410125732f);
    float speed;
    int sparksLeft, sparkKind, sparkOffset;
    if (count > 0) {
        sparksLeft = count;
        do {
            sparksLeft--;
            speed = math_random_float_range(g_spark_ring_speed_min, g_spark_ring_speed_max) * 0.01666666753590107f;
            velocity[0] = speed * math_fast_sin_or_cos_a(angle);
            velocity[1] = speed * math_fast_sin_or_cos_b(angle);
            velocity[2] = math_random_float_range(g_spark_ring_rise_min, g_spark_ring_rise_max) * 0.01666666753590107f;
            sparkKind = math_random_int_below(2);
            sparkOffset = math_random_int_range(-2, 2);
            enemy_spawn_record(position, velocity, &g_spark_ring_particle_settings, (void *)sparkKind, sparkOffset);
            velocity[2] = 0.0f;
            part_spawn_gravity_fade(position, velocity, 60, g_spark_particle_texture, 3, 48, 0, math_random_float_range(5.0f, 6.0f) * 210000.0f, 0.0f, 0.0f, 0);
            angle = FastAddRotations(angle, step);
        } while (sparksLeft);
    }
}
