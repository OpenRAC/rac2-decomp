#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float);
extern unsigned char *g_burst_particle_color_table;
extern float math_random_float_range(float f12, float f13);
typedef int Quad331CA0 __attribute__((mode(TI)));
typedef struct { unsigned char b0, b1, b2, b3; int color; unsigned char seed, alpha; unsigned short size; float life; union { Quad331CA0 q; float f[4]; } position; float payload[8]; } Particle331CA0;
extern Particle331CA0 *part_alloc(int kind);
extern float math_random_float_range(float low, float high);
extern int FloatToInt(float value);
extern unsigned char *g_burst_particle_color_table;

/* Spawns the burst particle of the given kind at position, carrying the velocity and the size scale in its payload. */
void part_l01_spawn_burst_2_pal(Quad331CA0 *position, int kind, Quad331CA0 *velocity, float scale)
{
    Quad331CA0 saved = *velocity;
    Quad331CA0 *velocity_copy = &saved;
    Particle331CA0 *particle = part_alloc(0x49);

    if (particle) {
        float life = 0.0f;
        int tint = 0;

        switch (kind) {
        case 0:
            math_random_float_range(0.25f, 0.25f);
            life = 0.12f;
            tint = 0x20;
            break;
        case 1:
            math_random_float_range(1.0f, 1.0f);
            life = 0.5f;
            tint = 0xD;
            break;
        }
        particle->size = 0x2E;
        particle->color = (tint << 24) | 0xFFFFFF;
        particle->alpha = FloatToInt(4.0f) + 0x20;
        particle->b1 = 0;
        particle->b3 = 0x48;
        particle->b2 = g_burst_particle_color_table[kind];
        particle->life = life * 210000.0f;
        particle->seed = math_random_float_range(0.0f, 360.0f);
        particle->position.q = *position;
        *(Quad331CA0 *)particle->payload = *velocity_copy;
        particle->payload[3] = scale;
    }
}


