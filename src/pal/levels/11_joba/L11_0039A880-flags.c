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
extern ParticleSettings g_spray_particle_settings __attribute__((sda));
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern void vec_add_random_offset(f32 *, f32);
extern void *enemy_spawn_record(void *, void *, void *, void *, int);

/* Spawns one to five spray particles around the moby (PAL), each with a small random offset
   and a random frame. */
void part_spawn_particle_burst_pal(char *self) {
    f32 point[4];
    f32 direction[4];
    s32 count, i;
    *(Quad *)direction = 0;
    count = math_random_int_below(5);
    for (i = 0; i < count + 1; i++) {
        *(Quad *)point = *(Quad *)(self + 0x10);
        vec_add_random_offset(point, 0.1f);
        vec_add_random_offset(direction, 0.002f);
        enemy_spawn_record(point, direction, &g_spray_particle_settings, (void *)1, math_random_int_range(-5, 5));
    }
}
