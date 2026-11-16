#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern float g_rising_particle_jitter __attribute__((sda));
extern float g_rising_particle_speed_min __attribute__((sda));
extern float g_rising_particle_speed_max __attribute__((sda));
extern float g_rising_particle_height_offset __attribute__((sda));
extern float g_rising_particle_push_length __attribute__((sda));
extern char g_rising_particle_spawn_record[4] __attribute__((sda));
extern char g_camera_l02_position[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *, void *, void *, void *, int);

/* Spawns count particles at the point raised by D_L02_001B0524 and pushed along the vector
   from D_L02_001BA500, each with a random upward speed (a sixtieth of the range D_L02_001B051C ..
   D_L02_001B0520) and the particle kind that func_002A77E0 picks for 2. */
void part_spawn_rising_pal(char *point, int count) {
    float vel[4];
    float pos[4];
    float push[4];
    int i;

    *(TI128 *)vel = 0;
    *(TI128 *)pos = *(TI128 *)point;
    pos[2] += g_rising_particle_height_offset;
    pos[3] = 0;
    FastVecSub(push, g_camera_l02_position, pos);
    push[2] = 0;
    vec_scale_to_length(push, push, g_rising_particle_push_length);
    FastVecAdd(pos, pos, push);
    for (i = 0; i < count; i++) {
        vec_add_random_offset(pos, g_rising_particle_jitter);
        vel[2] = math_random_float_range(g_rising_particle_speed_min, g_rising_particle_speed_max) * 0.020000001f;
        enemy_spawn_record(pos, vel, g_rising_particle_spawn_record, (void *)math_random_int_below(2), 1);
    }
}
