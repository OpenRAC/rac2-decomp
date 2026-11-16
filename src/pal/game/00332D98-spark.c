#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float v[4]; } EffectVector;
typedef struct Gf2540 {
    char pad0[0xD4];
    unsigned char *fD4;
    char pad1[0x16C - 0xD8];
    unsigned char *f16C;
} Gf2540;
typedef struct Gparticle {
    char pad0[2];
    unsigned char f2;
} Gparticle;
extern Gf2540 g_particle_texture_table;
extern char g_default_effect_vector[] __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern Gparticle *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);

/* The size is set once ahead of the loop, so gcse's constant propagation writes it directly
 * into both calls and it is not hoisted into a callee-saved register. */
void SpawnRandomParticlePairs_pal(TI128 *a0, void *velocity)
{
    EffectVector base;
    float vel[3];
    float pos[3];
    int i;
    int rnd;
    Gparticle *p;
    float size = 35700.0f;

    qcopy(&base, a0);
    FastVecScale(vel, velocity, 0.5f);
    FastVecAdd(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + math_random_signed_float_range(0.005f, 0.035f);
        pos[1] = base.v[1] + math_random_signed_float_range(0.005f, 0.035f);
        pos[2] = base.v[2] + math_random_signed_float_range(0.005f, 0.035f);
        rnd = math_random_int_below(0xFF);
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 3, 0x808080, rnd, 0x7F, 0x3F, size, size, 0.0f, 1);
        if (p != 0)
            p->f2 = g_particle_texture_table.f16C[1];
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 3, 0x406080, rnd, 0x10, 8, size, size, 0.0f, 1);
        if (p != 0)
            p->f2 = *g_particle_texture_table.fD4;
    } while (i >= 0);
}
