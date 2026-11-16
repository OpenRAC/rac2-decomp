#include "names.h"
/* func_PAL_L22_00401788, the PAL copy of func_L22_003FCF08, worded as func_PAL_L22_00402258 and built
   with gcse: 0.016666668f becomes 0.020000001f and the second argument of both func_002C2210 calls
   gets the 50 Hz scale. */
#include "common.h"
typedef int BurstVector __attribute__((mode(TI)));
extern float math_random_float_range(float,float), math_random_signed_float_range(float,float), math_random_angle(void);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecScale(void *,void *,float);
extern void add_vectors(void *,void *,void *);
extern void *part_spawn_ground_effect(void *,int,int,int,int,void *,int,float,float,float);
extern float g_spray_burst_arg __attribute__((sda));
extern float g_spray_burst_dist_min __attribute__((sda));
extern float g_spray_burst_dist_max __attribute__((sda));
extern float g_spray_burst_life_min __attribute__((sda));
extern float g_spray_burst_life_max __attribute__((sda));
extern int g_spray_ground_effect_left __attribute__((sda));
extern int g_spray_ground_effect_right __attribute__((sda));
extern int g_spray_ground_effect_type __attribute__((sda));
/* Emit two particles for each randomly perturbed point. */
void func_PAL_L22_00401788(float *position, float *direction, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float life, yaw, tilt, speed;
    int sign, remaining;
    for (remaining = 0; remaining < count; remaining++) {
        life = math_random_float_range(g_spray_burst_life_min, g_spray_burst_life_max);
        sign = math_random_int_below(2);
        if (sign == 0) sign--;
        yaw = math_random_angle();
        tilt = math_random_float_range(0.6981318f, 1.5358899f);
        speed = math_random_float_range(g_spray_burst_dist_min * 0.020000001f, g_spray_burst_dist_max * 0.020000001f);
        vec_build_spherical_offset(velocity, speed, yaw, tilt);
        *(BurstVector *)scaled = *(BurstVector *)direction;
        FastVecScale(scaled, direction, math_random_float_range(0.75f, 0.95f));
        add_vectors(difference, velocity, scaled);
        qcopy(point, position);
        point[0] += math_random_signed_float_range(0.0f, 0.0375f);
        point[1] += math_random_signed_float_range(0.0f, 0.0375f);
        point[2] += math_random_signed_float_range(0.0f, 0.0375f);
        part_spawn_ground_effect(point, ((s32)(g_spray_ground_effect_type) * 5 + 2) / 6, g_spray_ground_effect_left, 0, sign, velocity, 0, life * 0.1f, life, g_spray_burst_arg);
        part_spawn_ground_effect(point, ((s32)(g_spray_ground_effect_type) * 5 + 2) / 6, g_spray_ground_effect_right, 1, -sign, velocity, 0, life * 0.07f, life * 0.7f, g_spray_burst_arg);
    }
}
