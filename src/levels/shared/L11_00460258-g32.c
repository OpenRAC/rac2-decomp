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
extern float D_L11_001B22D0 __attribute__((sda));
extern float D_L11_001B22D4 __attribute__((sda));
extern float D_L11_001B22D8 __attribute__((sda));
extern float D_L11_001B22DC __attribute__((sda));
extern u32 D_L11_001B22C0 __attribute__((sda));
extern struct ParticleSettings D_L11_001B2300 __attribute__((sda));
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
            speed = math_random_float_range(D_L11_001B22D0, D_L11_001B22D4) * 0.01666666753590107f;
            velocity[0] = speed * math_fast_sin_or_cos_a(angle);
            velocity[1] = speed * math_fast_sin_or_cos_b(angle);
            velocity[2] = math_random_float_range(D_L11_001B22D8, D_L11_001B22DC) * 0.01666666753590107f;
            sparkKind = math_random_int_below(2);
            sparkOffset = math_random_int_range(-2, 2);
            enemy_spawn_record(position, velocity, &D_L11_001B2300, (void *)sparkKind, sparkOffset);
            velocity[2] = 0.0f;
            part_spawn_gravity_fade(position, velocity, 60, D_L11_001B22C0, 3, 48, 0, math_random_float_range(5.0f, 6.0f) * 210000.0f, 0.0f, 0.0f, 0);
            angle = FastAddRotations(angle, step);
        } while (sparksLeft);
    }
}
