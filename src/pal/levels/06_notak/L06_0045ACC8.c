#include "include_asm.h"
#include "names.h"


extern void SpawnExplosionEffects_pal(char *, char *, int, float, float, int, int, int,
                          float, float, float, float, int, float, int, int, int, int, int);
extern void vec_random_direction(float *, float, float);
extern float math_fabs(float);
extern void part_spawn_masked_debris_pal(char *, int, float *, float, float, float, float, int);
extern char *part_find_owned_effect_slot(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);
extern void FastVecAdd(char *, char *, char *);
extern char g_effect_vector[] __attribute__((sda));

/* When hit, bursts into a flash and six flying fragments, then removes itself. */
void fragments_burst_on_hit_pal(char *moby)
{
    float fragment_vel[4];
    char *hit = (char *)part_find_owned_effect_slot(moby, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        PlayMobySound(0, 0, moby);
        SpawnExplosionEffects_pal(moby, moby + 0x10, 0, 0.0f, 0.0f, 10, 3, 9,
                      4.0f, 2.0f, 9.0f, 0.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 1, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 4, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 8, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 16, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 32, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragment_vel, 0.080000006f, 0.120000005f);
        fragment_vel[2] = math_fabs(fragment_vel[2]) * 1.5f;
        FastVecAdd((char *)fragment_vel, (char *)fragment_vel, g_effect_vector);
        part_spawn_masked_debris_pal(moby, 64, fragment_vel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        moby_mark_spawned(moby);
    }
    *(unsigned char *)(moby + 0xA8) = 255;
}


