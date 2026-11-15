#include "include_asm.h"
#include "names.h"

/* Emit the collision burst and six fragments, then retire the triggering object. */
extern void SpawnExplosionEffects(char *, char *, int, float, float, int, int, int,
                          float, float, float, float, int, float, int, int, int, int, int);
extern void vec_random_direction(float *, float, float);
extern float math_fabs(float);
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, int);

extern char *part_find_owned_effect_slot(char *, int, int);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);
extern void FastVecAdd(char *, char *, char *);
extern char D_L06_001A8F20[] __attribute__((sda));
/* When hit, bursts the object into a flash and six flying fragments, then removes it. */
void fragments_burst_on_hit(char *obj)
{
    float fragmentVel[4];
    char *hit = (char *)part_find_owned_effect_slot(obj, 0x4010000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5 /* moby class 4069 */) {
        PlayMobySound(0, 0, obj);
        SpawnExplosionEffects(obj, obj + 0x10, 0, 0.0f, 0.0f, 10, 3, 9,
                      4.0f, 2.0f, 9.0f, 0.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 1, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 4, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 8, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 16, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 32, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        vec_random_direction(fragmentVel, 0.06666667014360428f, 0.10000000894069672f);
        fragmentVel[2] = math_fabs(fragmentVel[2]) * 1.5f;
        FastVecAdd((char *)fragmentVel, (char *)fragmentVel, D_L06_001A8F20);
        part_spawn_masked_debris(obj, 64, fragmentVel, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        moby_mark_spawned(obj);
    }
    *(unsigned char *)(obj + 0xA8) = 255;
}
