#include "names.h"
/* func_PAL_L00_00388038, the PAL copy of func_L00_003851A0: the same C, where scale func_002A7820(D_L00_001AEE90, D_L00_001AEE94). */
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

/* Spawns the particles for a goal score: a few sparks flying out from the given position (PAL: 50 Hz timings). */
void part_spawn_goal_score_pal(void *unused, void *source)
{
    char buffer[0x20];
    int i;
    for (i = 0; i < g_goal_score_particle_count; i++) {
        char *second = buffer + 0x10;
        float scale = 0.020000001f;
        int state, random;
        vec_random_direction(buffer, 0.0f, 0.0333000011742115f);
        FastVecAdd(buffer, buffer, source);
        vec_random_direction(second, g_goal_score_speed_min * scale, g_goal_score_speed_max * scale);
        state = (unsigned char)(((int)(math_random_int_range(g_goal_score_state_min, g_goal_score_state_max)) * 5 + 2) / 6);
        random = (unsigned char)math_random_int_below(255);
        part_spawn_hero_relative(buffer, second, g_goal_score_particle_type, state, random, 0, g_goal_score_spawn_float);
    }
}

extern int g_goal_hit_state_min SDATA(D_L00_001AEE38);
extern float g_goal_hit_speed_min SDATA(D_L00_001AEE10);
extern float g_goal_hit_float_a SDATA(D_L00_001AEE20);
extern unsigned int g_goal_hit_particle_table[4] SDATA(D_L00_001AEE28);

