#include "common.h"

extern int func_003A0948(int, int, char *);
extern void *moby_spawn_scaled_effect(float *, float);
extern void math_random_planar_offset(float *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern char *part_spawn_spark_2(float *, float *, int, int);
extern float D_L06_001B37CC __attribute__((sda));

/* Makes a big burst of debris and particles flying outward when the machine crashes to the ground. */
void part_spawn_crash_debris(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4];
    float spawn[4];
    int n = 5;
    int i;
    char *particle;

    func_003A0948(2, 0, self);
    qcopy(pos, self + 0x10);
    D_L06_001B37CC = pos[2];
    moby_spawn_scaled_effect(pos, 11.25f);
    for (i = 0x59; i >= 0; i--) {
        math_random_planar_offset(vel, n * 0.03333333507180214f);
        vel[2] = n * 0.01666666753590107f * math_random_float_range(2.0f, 3.5f);
        spawn[0] = *(float *)(self + 0x10) + vel[0] * 8.0f;
        spawn[1] = *(float *)(self + 0x14) + vel[1] * 8.0f;
        spawn[2] = D_L06_001B37CC - math_random_float_range(0.0f, 0.2f);
        particle = part_spawn_spark_2(spawn, vel, math_random_int_below(2), n * math_random_int_range(0x5A, 0x78));
        if (particle != 0)
            *(float *)(particle + 0xC) = *(float *)(particle + 0xC) * math_random_float_range(4.0f, 6.0f);
    }
}
