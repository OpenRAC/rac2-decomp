#include "common.h"

/* Resident fields accessed by the paired particle emitter. */
typedef struct {
    char pad0[128];
    float x;
    float y;
    char pad88[16];
    float angle;
    char pad9c[660];
    float z;
    char pad334[1812];
    unsigned short counter;
} ParticleResidentFields;
extern ParticleResidentFields D_00189E20_20;
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void *part_spawn_random_tinted_effect(float, float, float *, float *, float *);

/* Every so often, puffs out two small particles to the sides of the hero. */
void part_emit_hero_side_particles(char *emitInterval, int threshold)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float turn;
    float size;
    int count;
    int i;


    count = D_00189E20_20.counter + 1;
    D_00189E20_20.counter = count;
    if (threshold < (short)count) {
        for (i = 0; i < 2; i++) {
            if (i == 0)
                turn = FastAddRotations(D_00189E20_20.angle, 0.785398006f);
            else
                turn = fast_subtract_rotations(D_00189E20_20.angle, 0.785398006f);
            velocity[0] = math_fast_sin_or_cos_a(turn) * 0.0100000007f;
            velocity[1] = math_fast_sin_or_cos_b(turn) * 0.0100000007f;
            position[0] = D_00189E20_20.x + velocity[0] * 18.0f;
            position[1] = D_00189E20_20.y + velocity[1] * 18.0f;
            position[2] = D_00189E20_20.z;
            velocity[2] = 0.0f;
            velocity[0] = velocity[0] - math_fast_sin_or_cos_a(D_00189E20_20.angle) * 0.0250000022f;
            velocity[1] = velocity[1] - math_fast_sin_or_cos_b(D_00189E20_20.angle) * 0.0250000022f;
            size = math_random_float_range(0.4f, 0.5f);
            part_spawn_random_tinted_effect(size, i == 0 ? 2.0f : -2.0f, position, velocity, &D_00189E20_20.z);
            D_00189E20_20.counter = emitInterval == 0 ? 0 : math_random_int_below((int)emitInterval);
        }
    }
}
