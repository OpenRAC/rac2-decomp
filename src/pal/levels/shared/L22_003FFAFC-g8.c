#include "include_asm.h"

#include "common.h"
typedef int BurstVector __attribute__((mode(TI)));
extern float math_random_float_range(float,float), math_random_signed_float_range(float,float), math_random_angle(void);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecScale(void *,void *,float);
extern void add_vectors(void *,void *,void *);
extern void *part_spawn_ground_effect(void *,int,int,int,int,void *,int,float,float,float);
extern float ref_L22_003FB9B8_00 __attribute__((sda));
extern float ref_L22_003FB9B8_01 __attribute__((sda));
extern float ref_L22_003FB9B8_02 __attribute__((sda));
extern float ref_L22_003FB9B8_03 __attribute__((sda));
extern int ref_L22_003FB9B8_04 __attribute__((sda));
extern int ref_L22_003FB9B8_05 __attribute__((sda));
extern float ref_L22_003FB9B8_06 __attribute__((sda));

/* Emit two particles for each randomly perturbed point. */
void func_PAL_L22_004001E8(float *position, float *direction, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float life, yaw, tilt, speed;
    int sign, remaining;
    for (remaining = 0; remaining < count; remaining++) {
        life = math_random_float_range(ref_L22_003FB9B8_00, ref_L22_003FB9B8_01);
        sign = math_random_int_below(2);
        if (sign == 0) sign--;
        yaw = math_random_angle();
        tilt = math_random_float_range(0.6981318f, 1.5358899f);
        speed = math_random_float_range(ref_L22_003FB9B8_02 * 0.020000001f, ref_L22_003FB9B8_03 * 0.020000001f);
        vec_build_spherical_offset(velocity, speed, yaw, tilt);
        *(BurstVector *)scaled = *(BurstVector *)direction;
        FastVecScale(scaled, direction, math_random_float_range(0.75f, 0.95f));
        add_vectors(difference, velocity, scaled);
        qcopy(point, position);
        point[0] += math_random_signed_float_range(0.0f, 0.0375f);
        point[1] += math_random_signed_float_range(0.0f, 0.0375f);
        point[2] += math_random_signed_float_range(0.0f, 0.0375f);
        part_spawn_ground_effect(point, 25, ref_L22_003FB9B8_04, 0, sign, velocity, 0, life * 0.1f, life, ref_L22_003FB9B8_06);
        part_spawn_ground_effect(point, 25, ref_L22_003FB9B8_05, 1, -sign, velocity, 0, life * 0.07f, life * 0.7f, ref_L22_003FB9B8_06);
    }
}
