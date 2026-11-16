#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern int math_random_int_below(int);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void FastVecSub(void *, const void *, const void *);
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern Vector g_effect_color_table __attribute__((sda));
extern unsigned char *g_particle_color_ptr_b;
extern unsigned char *g_particle_color_ptr_a;
extern int g_frame_l20_counter[] __attribute__((sda));

/* Throws glowing particles around the object and a few small ones along a line toward its target. (PAL version) */
void EmitJitteredParticleTrail_pal(unsigned char *object) {
    Vector delta, position, jitter;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int shade = math_random_int_below(255);
    int count;
    float size;
    particle = part_spawn_gravity_fade(object + 0x10, &g_effect_color_table, 2, 0x202080, shade, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *g_particle_color_ptr_b;
    }
    particle = part_spawn_gravity_fade(object + 0x10, &g_effect_color_table, 2, 0x202080, (shade + 128) % 255, 64, 16,
                            420000.0f, 420000.0f, 0.0f, 0);
    if (particle) {
        particle[2] = *g_particle_color_ptr_b;
    }
    FastVecSub(&delta, object + 0x10, state);
    FastVecScale(&delta, &delta, 0.1f);
    qcopy(&position, state);
    count = 4;
    do {
        --count;
        shade = math_random_int_below(255);
        size = math_random_float_range(0.1f, 0.3f);
        jitter.f[0] = position.f[0] + math_random_signed_float_range(0.0f, 0.05f);
        jitter.f[1] = position.f[1] + math_random_signed_float_range(0.0f, 0.05f);
        jitter.f[2] = position.f[2] + math_random_signed_float_range(0.0f, 0.05f);
        part_spawn_gravity_fade(&jitter, &g_effect_color_table, 12, 0x808080, shade, 32, 0,
                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
        FastVecAdd(&position, &position, &delta);
    } while (count >= 0);
    if (g_frame_l20_counter[0] % 10 == 0) {
        particle = part_spawn_gravity_fade(object + 0x10, &g_effect_color_table, 25, 0x202080, 0, 32, 0,
                                2100.0f, 420000.0f, 0.0f, 0);
        if (particle) {
            particle[2] = *g_particle_color_ptr_a;
        }
    }
}
