#include "include_asm.h"


#include "common.h"
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void add_vectors(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_ground_effect(void *, int, unsigned int, int, int, void *, float, float, float, int);
typedef unsigned int L04Quad __attribute__((mode(TI)));
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);

void func_PAL_L04_00410678(L04Quad *position, L04Quad *direction, int count, int mode)
{
    float velocity[4], point[4], scaled[4], result[4];
    float size, angle, pitch;
    int sign, i;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.025f, 0.5f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_angle();
        pitch = math_random_float_range(0.6981318f, 1.5358899f);
        vec_build_spherical_offset(velocity, math_random_float_range(0.015000001f, 0.030000001f), angle, pitch);
        *(L04Quad *)scaled = *direction;
        FastVecScale(scaled, direction, math_random_float_range(0.75f, 0.95f));
        if (mode) {
            velocity[0] *= 5.0f;
            velocity[1] *= 5.0f;
            size *= 3.0f;
        }
        add_vectors(result, velocity, scaled);
        qcopy(point, position);
        point[0] += math_random_signed_float_range(0.0f, 0.0375f);
        point[1] += math_random_signed_float_range(0.0f, 0.0375f);
        point[2] += math_random_signed_float_range(0.0f, 0.0375f);
        part_spawn_ground_effect(point, 25, 0x7f207f7f, 0, sign, velocity, size * 0.1f, size, 0.003f, 0);
        part_spawn_ground_effect(point, 25, 0x7f7f7f7f, 1, -sign, velocity, size * 0.07f, size * 0.7f, 0.003f, 0);
    }
}



/* func_PAL_L04_00410E40 lives in L04_00410E40-hud-g8.c. */
