#include "include_asm.h"

#include "common.h"
extern int PlayMobySound(int, int, char *);
extern void *moby_spawn_scaled_effect(float *, float);
extern void math_random_planar_offset(float *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern char *part_spawn_spark_2_pal(float *, float *, int, int);
extern float g_debris_spawn_height __attribute__((sda));

/* Makes a big burst of debris and particles flying outward when the machine crashes to the ground (PAL: 50 Hz timings). */
void part_spawn_crash_debris_pal(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4];
    float spawn[4];
    int n = 5;
    int i;
    char *p;

    PlayMobySound(2, 0, moby);
    qcopy(pos, moby + 0x10);
    g_debris_spawn_height = pos[2];
    moby_spawn_scaled_effect(pos, 11.25f);
    for (i = 0x59; i >= 0; i--) {
        math_random_planar_offset(vel, n * 0.040000003f);
        vel[2] = n * 0.020000001f * math_random_float_range(2.0f, 3.5f);
        spawn[0] = *(float *)(moby + 0x10) + vel[0] * 8.0f;
        spawn[1] = *(float *)(moby + 0x14) + vel[1] * 8.0f;
        spawn[2] = g_debris_spawn_height - math_random_float_range(0.0f, 0.2f);
        p = part_spawn_spark_2_pal(spawn, vel, math_random_int_below(2), n * math_random_int_range(0x5A, 0x78));
        if (p != 0)
            *(float *)(p + 0xC) = *(float *)(p + 0xC) * math_random_float_range(4.0f, 6.0f);
    }
}
