#include "names.h"
/* func_PAL_L00_003BB200, the PAL copy of func_L00_003B7680: the same C, where expr 0.016666668f becomes 0.020000001f; scale func_002A7820(D_L00_001AFB0C[1], D_L00_001AFB0C[2]). */
#include "common.h"

typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;

extern OBJ2 *g_active_pickup_object __attribute__((sda));

typedef struct OBJ3 {
    char pad0[0x98];
    int f98;
} OBJ3;

extern OBJ3 *g_saved_special_mobys[];

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_hero_relative(void *, void *, int, int, float, int, int);
extern int g_explosion_particle_count __attribute__((sda));
extern float g_explosion_l00_speed_min __attribute__((sda));
extern float g_explosion_l00_speed_max;
extern int g_sparkle_kind_ranges[] __attribute__((sda));
extern float g_sparkle_hero_param_b;
extern int g_explosion_particle_colors[2] __attribute__((sda));

/* Throws out a burst of small coloured particles from a position, like an explosion. (PAL: 50 Hz
 * timings) */
void part_l00_spawn_explosion_particles_pal(char *object, float *position)
{
    float point[4], velocity[4];
    int i;
    for (i = 0; i < g_explosion_particle_count; i++) {
        unsigned char kind, random;
        int *color;
        vec_random_direction(point, 0.0f, 0.333f);
        FastVecAdd(point, point, position);
        vec_random_direction(velocity, g_explosion_l00_speed_min * (0.020000001f), g_explosion_l00_speed_max * (0.020000001f));
        kind = (((int)(math_random_int_range(g_sparkle_kind_ranges[1], g_sparkle_kind_ranges[2])) * 5 + 2) / 6);
        color = &g_explosion_particle_colors[(unsigned char)object[0xbc]];
        random = math_random_int_below(255);
        part_spawn_hero_relative(point, velocity, *color, kind, g_sparkle_hero_param_b, random, 0);
    }
}

