#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern float g_ground_height __attribute__((nosda));
extern float ref_L01_00397EB0_00 __attribute__((sda));
extern float ref_L01_00397EB0_01 __attribute__((sda));
extern unsigned char ref_L01_00397EB0_02 __attribute__((sda));
extern int ref_L01_00397EB0_03 __attribute__((sda));
extern float ref_L01_00397EB0_04 __attribute__((sda));
extern float ref_L01_00397EB0_05 __attribute__((sda));
extern float ref_L01_00397EB0_06 __attribute__((sda));
extern int ref_L01_00397EB0_07 __attribute__((sda));
extern float ref_L01_00397EB0_08 __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);

/* Spawns three small sparkles at the moby unless it is below the ground height (PAL: 50 Hz drift scale). */
void part_spawn_sparkle_trail_above_ground_pal(char *moby)
{
    TI128 spark_pos, drift_a, drift_b;
    int i;
    int alpha;

    if (*(unsigned char *)(moby + 0x20) == 1) {
        FastVecScale(&spark_pos, moby, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(moby, 0, &spark_pos);
        if (((float *)&spark_pos)[2] < g_ground_height) return;
    }
    i = 2;
    vec_random_direction(&drift_a, ref_L01_00397EB0_00 * 0.020000001f, ref_L01_00397EB0_01 * 0.020000001f);
    alpha = ref_L01_00397EB0_02;
    part_spawn_hero_relative(&spark_pos, &drift_a, ref_L01_00397EB0_03, alpha, math_random_int_below(255), 0, ref_L01_00397EB0_04);
    do {
        i--;
        vec_random_direction(&drift_b, ref_L01_00397EB0_05 * 0.020000001f, ref_L01_00397EB0_06 * 0.020000001f);
        FastVecAdd(&drift_a, &drift_a, &drift_b);
        alpha = ref_L01_00397EB0_02;
        part_spawn_hero_relative(&spark_pos, &drift_a, ref_L01_00397EB0_07, alpha, math_random_int_below(255), 0, ref_L01_00397EB0_08);
    } while (i >= 0);
}
