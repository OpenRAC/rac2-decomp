#include "include_asm.h"
#include "names.h"
typedef struct {
    float v[3];
    float scale;
    void *owner;
    float f14;
    int f18;
    int f1C;
    float f20;
    int f24;
    float f28;
    float f2C;
} Rec_3CB538;

extern Rec_3CB538 *D_L00_001B2AD4 __attribute__((section(".sdata")));
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void vec_scale_to_length(void *, void *, float);
extern int func_001163B0(void);

/* Starts one new particle in the first free slot, with a random direction, life time and size. */
void part_spawn_pool_particle(void *owner)
{
    Rec_3CB538 *particle;
    int i;

    for (i = 0; i < 64; i++) {
        particle = &D_L00_001B2AD4[i];
        if (particle->owner == 0) {
            particle->v[0] = math_random_float_range(-1.0f, 1.0f);
            particle->v[1] = math_random_float_range(-1.0f, 1.0f);
            particle->v[2] = math_random_float_range(-1.0f, 1.0f);
            vec_scale_to_length(particle, particle, particle->f14);
            particle->f1C = particle->f18 = math_random_int_range(0x14, 0x32);
            particle->f20 = math_random_float_range(-1.0f, 1.0f);
            particle->owner = owner;
            particle->f24 = 0;
            particle->f28 = (func_001163B0() & 1) ? -1.0f : 1.0f;
            particle->f2C = 1.0f;
            particle->f14 = math_random_float_range(0.7f, 0.9f);
            return;
        }
    }
}
