#include "common.h"

extern int g_trail_particle_count_max __attribute__((sda));
extern float g_trail_position_jitter __attribute__((sda));
extern float g_trail_l18_speed_min __attribute__((sda));
extern float g_trail_l18_speed_max __attribute__((sda));
typedef struct ParticleSettings {
    s32 *colorRange;
    s16 *sizeRange;
    s16 *frameRange;
    u32 unknown0C;
    s32 frameCount;
    f32 speed;
} ParticleSettings;
/* The shared particle constructor reads this complete 24-byte settings record. */
extern ParticleSettings g_trail_particle_settings __attribute__((sda));
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void vec_add_random_offset(void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void *enemy_spawn_record(void *, void *, void *, int, int);

/* Spawns a random number of particles (one more than a draw bounded by D_L18_001B05D4)
   around the object's position (+0x10): each from the position jittered by
   D_L18_001B05C8 and a direction from the vector at +0xC0, scaled by minus a random
   value between D_L18_001B05CC and D_L18_001B05D0 divided by 60, with two more draws. */
void part_spawn_trail_particles(u8 *object)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    int count;
    int i;

    count = math_random_int_below(g_trail_particle_count_max) + 1;
    for (i = 0; i < count; i++) {
        qcopy(position, object + 0x10);
        vec_add_random_offset(position, g_trail_position_jitter);
        vec_scale_to_length(direction, object + 0xC0,
                      -(math_random_float_range(g_trail_l18_speed_min, g_trail_l18_speed_max) * 0.016666668f));
        enemy_spawn_record(position, direction, &g_trail_particle_settings, math_random_int_below(2),
                          math_random_int_range(-2, 2));
    }
}
