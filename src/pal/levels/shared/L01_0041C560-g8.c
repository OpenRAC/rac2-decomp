#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *, void *, void *);
extern float g_sparkle_drift_a_min __attribute__((sda));
extern float g_sparkle_drift_a_max __attribute__((sda));
extern float g_sparkle_drift_b_min __attribute__((sda));
extern float g_sparkle_drift_b_max __attribute__((sda));
extern unsigned char g_sparkle_l01_alpha_2 __attribute__((sda));
extern int g_sparkle_particle_type_a __attribute__((sda));
extern int g_sparkle_particle_type_b __attribute__((sda));
extern float g_sparkle_scale_a __attribute__((sda));
extern float g_sparkle_scale_b __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);

/* builds the tilt of a hanging chain over three steps and draws it */
void part_spawn_sparkle_drift_pal(char *moby)
{
    TI128 position, drift_a, drift_b;
    int i;
    int alpha;

    if (*(unsigned char *)(moby + 0x20) == 1) {
        FastVecScale(&position, moby, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(moby, 0, &position);
    }
    i = 2;
    vec_random_direction(&drift_a, g_sparkle_drift_a_min * 0.020000001f, g_sparkle_drift_a_max * 0.020000001f);
    alpha = g_sparkle_l01_alpha_2;
    part_spawn_hero_relative(&position, &drift_a, g_sparkle_particle_type_a, alpha, math_random_int_below(255), 0, g_sparkle_scale_a);
    do {
        i--;
        vec_random_direction(&drift_b, g_sparkle_drift_b_min * 0.020000001f, g_sparkle_drift_b_max * 0.020000001f);
        FastVecAdd(&drift_a, &drift_a, &drift_b);
        alpha = g_sparkle_l01_alpha_2;
        part_spawn_hero_relative(&position, &drift_a, g_sparkle_particle_type_b, alpha, math_random_int_below(255), 0, g_sparkle_scale_b);
    } while (i >= 0);
}
