#include "include_asm.h"
#include "common.h"

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_hero_relative(void *, void *, unsigned int, int, int, int, float);
extern int g_goal_score_particle_count SDATA(D_L00_001AEE68);
extern float g_goal_score_speed_min SDATA(D_L00_001AEE70);
extern unsigned int g_goal_score_particle_type SDATA(D_L00_001AEE6C);
extern float g_goal_score_speed_max;
extern float g_goal_score_spawn_float;
extern int g_goal_score_state_min;
extern int g_goal_score_state_max;


/* Spawns a burst of particles at the given position when a goal is scored. */
void part_spawn_goal_score(void *unused, void *source)
{
    char buffer[0x20];
    int i;
    for (i = 0; i < g_goal_score_particle_count; i++) {
        char *second = buffer + 0x10;
        float scale = 0.01666666753590107f;
        int state, random;
        vec_random_direction(buffer, 0.0f, 0.0333000011742115f);
        FastVecAdd(buffer, buffer, source);
        vec_random_direction(second, g_goal_score_speed_min * scale, g_goal_score_speed_max * scale);
        state = (unsigned char)math_random_int_range(g_goal_score_state_min, g_goal_score_state_max);
        random = (unsigned char)math_random_int_below(255);
        part_spawn_hero_relative(buffer, second, g_goal_score_particle_type, state, random, 0, g_goal_score_spawn_float);
    }
}

extern int g_goal_hit_state_min SDATA(D_L00_001AEE38);
extern int g_goal_hit_state_max;
extern int g_goal_hit_state_alt_min;
extern int g_goal_hit_state_alt_max;
extern float g_goal_hit_speed_min SDATA(D_L00_001AEE10);
extern float g_goal_hit_speed_max;
extern float g_goal_hit_float_a SDATA(D_L00_001AEE20);
extern float g_goal_hit_float_b;
extern unsigned int g_goal_hit_particle_table[4] SDATA(D_L00_001AEE28);

/* Spawns two particle effects at the position, coloured by which player owns the object. */
void part_spawn_goal_hit(unsigned char *object, void *position)
{
    char buffer[16];
    unsigned int *table = g_goal_hit_particle_table;
    void *data = *(void **)(object + 0x68);
    int state = (unsigned char)math_random_int_range(g_goal_hit_state_min, g_goal_hit_state_max);
    unsigned int *entry = table + object[0xBC] * 2;
    int random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(position, data, entry[0], state, random, 0, g_goal_hit_float_a);
    vec_random_direction(buffer, g_goal_hit_speed_min * 0.01666666753590107f, g_goal_hit_speed_max * 0.01666666753590107f);
    {
        int state2 = (unsigned char)math_random_int_range(g_goal_hit_state_alt_min, g_goal_hit_state_alt_max);
        unsigned int *entry2 = (unsigned int *)((char *)table + ((object[0xBC] << 3) | 4));
        int random2 = (unsigned char)math_random_int_below(255);
        part_spawn_hero_relative(position, buffer, entry2[0], state2, random2, 0, g_goal_hit_float_b);
    }
}
