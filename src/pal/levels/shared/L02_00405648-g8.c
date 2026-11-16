#include "include_asm.h"

#include "common.h"
extern float g_puff_random_min __attribute__((sda));
extern float g_puff_random_max;
extern int g_growing_puff_param_a __attribute__((sda));
extern int g_growing_puff_param_b __attribute__((nosda));
extern int g_puff_local_word0 __attribute__((nosda));
extern int g_puff_local_word1 __attribute__((nosda));
extern char g_zero_l02_vector[];
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void part_spawn_growing_puff_pal(void *, void *, float, u32, s32, s32);

/* Spawns one projectile puff at the object with a random size and lifetime (PAL: 5/6 lifetime). */
void spawn_actor_puff_pal(void *moby)
{
    void *moby_ref = moby;
    void *vars;
    int params[2];
    float spawn_scale;
    float random_value;
    int life;

    vars = *(void **)(moby_ref + 0x68);
    random_value = math_random_float_range(g_puff_random_min, g_puff_random_max);
    spawn_scale = random_value * 210000.0f;
    life = ((s32)(math_random_int_range(*(unsigned char *)(vars + 0x75), *(unsigned char *)(vars + 0x76))) * 5 + 2) / 6;
    if (*(short *)(moby_ref + 0xAA) == 0xB5A) {
        params[0] = g_growing_puff_param_a;
        params[1] = g_growing_puff_param_b;
    } else {
        params[0] = g_puff_local_word0;
        params[1] = g_puff_local_word1;
    }
    part_spawn_growing_puff_pal(moby_ref + 0x10, g_zero_l02_vector, spawn_scale, g_growing_puff_param_a, g_growing_puff_param_b, life);
}
