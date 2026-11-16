#include "common.h"

typedef int Quadword_0030DE88 __attribute__((mode(TI)));
typedef union {
    Quadword_0030DE88 bits;
    float f[4];
} Vec4_0030DE88;

extern float g_beam_particle_speed __attribute__((sda));
extern char g_hero_matrix[];

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_random_direction(void *, float, float);
extern float math_fabs(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern int beam_get_glow_color(void);
extern void *part_spawn_ground_effect(void *, float, float, s32, s32, s32, s32, void *, float, s32);

/* Sprays a burst of small coloured spark particles from just in front of the object. */
void SpawnEffectBurst(u8 *moby, int count)
{
    Vec4_0030DE88 origin;
    Vec4_0030DE88 velocity;
    int i;

    origin.bits = 0;
    origin.f[1] = -0.9f;
    matrix_mul_vec3(&origin, &origin, moby + 0xC0);
    FastVecAdd(&origin, &origin, moby + 0x10);
    for (i = 0; i < count; i++) {
        int spin;
        int colour;
        float inner;
        float size;
        float life;
        vec_random_direction(&velocity, 0.0f, g_beam_particle_speed);
        velocity.f[0] = math_fabs(velocity.f[0]);
        matrix_mul_vec3(&velocity, &velocity, g_hero_matrix);
        spin = math_random_int_range(-8, 8);
        inner = 0.3f;
        size = math_random_float_range(0.2f, 0.6f);
        life = size * inner;
        colour = beam_get_glow_color() | 0x7F000000;
        part_spawn_ground_effect(&origin, life, size, 0xF, colour, 0, spin, &velocity, 0.0f, 0);
        colour = 0x307F7F7F;
        part_spawn_ground_effect(&origin, size * 0.15f, size * 0.5f, 0xF, colour, 0, -spin, &velocity, 0.0f, 0);
    }
}
