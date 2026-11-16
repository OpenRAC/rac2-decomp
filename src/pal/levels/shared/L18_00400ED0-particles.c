#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
typedef int Quad __attribute__((mode(TI)));
typedef struct ParticleSettings {
    void *colorRange;
    void *sizeRange;
    short *frameRange;
    s32 reserved;
    s32 frameCount;
    f32 speed;
} ParticleSettings;
extern f32 g_upward_particle_offset[4] __attribute__((sda));
extern ParticleSettings g_upward_particle_settings __attribute__((sda));
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void vec_add_random_offset(f32 *, f32);
extern void *enemy_spawn_record(void *, void *, void *, void *, int);

/* Spawns a few upward-moving particles from the object's transformed effect point. */
void part_spawn_upward_pal(char *self) {
    f32 point[4];
    f32 direction[4];
    s32 count, i, kind;
    *(Quad *)direction = 0;
    direction[2] = 1.0f;
    count = math_random_int_below(2);
    for (i = 0; i < count + 1; i++) {
        matrix_mul_vec3(point, g_upward_particle_offset, self + 0xC0);
        FastVecAdd(point, point, self + 0x10);
        vec_add_random_offset(point, 0.5f);
        vec_scale_to_length(direction, direction, math_random_float_range(8.0f, 12.0f) * 0.020000001f);
        vec_add_random_offset(direction, 0.080000006f);
        kind = math_random_int_below(2);
        enemy_spawn_record(point, direction, &g_upward_particle_settings, (void *)kind, math_random_int_range(-2, 2));
    }
}

extern ParticleSettings g_spray_particle_settings __attribute__((sda));

/* Emits a small randomized spray from the object's saved effect origin. */
void part_spawn_spray_pal(char *self) {
    f32 point[4];
    f32 direction[4];
    char *state = *(char **)(self + 0x68);
    s32 count, i;
    *(Quad *)direction = 0;
    count = math_random_int_below(5);
    for (i = 0; i < count + 1; i++) {
        *(Quad *)point = *(Quad *)(state + 0x90);
        vec_add_random_offset(point, 0.5f);
        vec_add_random_offset(direction, 0.010000001f);
        enemy_spawn_record(point, direction, &g_spray_particle_settings, (void *)1, math_random_int_range(-5, 5));
    }
}
