#include "include_asm.h"
#include "names.h"

extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void *part_l01_spawn_glow(void *, int, int, float, float, int);

/* The func_L01_003BD410 puffs, `count` of them around the state's +0x380 point. */
void part_spawn_puffs_around_point(char *object, int count)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, i;

    state = *(char **)(object + 0x68);
    for (i = 0; i < count; i++) {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.6f);
        first = math_random_float_range(0.0f, 1.5f);
        second = math_random_float_range(1.5f, 5.5f);
        life = math_random_int_range(100, 160);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, state + 0x380);
        part_l01_spawn_glow(position, 0x30305020, 0x182810, first, second, life);
    }
}
