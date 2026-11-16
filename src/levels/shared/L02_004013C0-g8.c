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

/* The EE ABI preserves the integer and FP argument banks independently. */
extern void part_spawn_growing_puff(void *, void *, float, u32, s32, s32);

/* Spawns a puff of effect at the object with a random speed and count. */
void SpawnActorPuff(void *moby_arg)
{
    void *moby = moby_arg;
    void *vars;
    int local[2];
    float speed;
    float random_value;
    int count;

    vars = *(void **)(moby + 0x68);
    random_value = math_random_float_range(g_puff_random_min, g_puff_random_max);
    speed = random_value * 210000.0f;
    count = math_random_int_range(*(unsigned char *)(vars + 0x75), *(unsigned char *)(vars + 0x76));
    if (*(short *)(moby + 0xAA) == 0xB5A /* moby class 2906 */) {
        local[0] = g_growing_puff_param_a;
        local[1] = g_growing_puff_param_b;
    } else {
        local[0] = g_puff_local_word0;
        local[1] = g_puff_local_word1;
    }
    part_spawn_growing_puff(moby + 0x10, g_zero_l02_vector, speed, g_growing_puff_param_a, g_growing_puff_param_b, count);
}


