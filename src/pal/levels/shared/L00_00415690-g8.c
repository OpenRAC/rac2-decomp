#include "names.h"
/* func_PAL_L00_00415690, the PAL copy of func_L00_00410888: the same C, where 0.016666668f
   becomes 0.020000001f, 0.0022222223f becomes 0.0032000002f, both lives take the 50 Hz scale
   and the second loop is written counting up (check_dbra_loop reverses it, which sets its
   counter after the hoisted divisor, as retail does).
   -fno-sched-interblock: retail's first loop has no interblock motion. The second loop gets
   none anyway, being over the scheduler's 100-LUID region limit; this source's first loop is
   only 82. */
#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern char *part_spawn_trail_2(void *, void *, int, float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);
extern void *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);
extern char g_hero_matrix[];

typedef struct {
    char pad[0x110];
    float velocity[4];
    char pad2[0x220];
    int flag;
} EffectHero;

extern EffectHero g_hero_state;
extern float g_burst_rotation_angle __attribute__((sda));
extern float g_burst_spread __attribute__((sda));
extern int g_burst_count_min __attribute__((sda));
extern int g_burst_count_max __attribute__((sda));
extern int g_burst_kind __attribute__((sda));
extern float g_burst_extra_param __attribute__((sda));
extern float g_burst_life_min __attribute__((sda));
extern float g_burst_life_max __attribute__((sda));
extern float g_burst_jitter_min __attribute__((sda));
extern float g_burst_scale __attribute__((sda));
extern float g_burst_speed __attribute__((sda));

/* Emit two groups of particles around the object, rotating each emission direction. */
void func_PAL_L00_00415690(char *object, int mode)
{
    float rotation[4], direction[4], basis[4], position[4], point[4], velocity[4], offset[4];
    float angle, jitter, scale, speed, spread;
    int i, j, life, kind, life2;

    *(EffectVector *)basis = 0;
    basis[0] = 0.3f;
    basis[1] = -1.0f;
    basis[3] = 1.0f;
    matrix_mul_vec3(basis, basis, object + 0xc0);
    angle = 0.0f;
    FastVecAdd(position, object + 0x10, basis);
    math_apply_axis_rotation_to_quat(basis, g_hero_matrix, g_hero_matrix + 0x10, 0.349065899848938f);
    qcopy(direction, basis);
    for (i = 0; i < mode * 20 + 20; i++) {
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186f));
        FastVecScale(offset, direction, math_random_float_range(7.0f, 60.0f) * 0.020000001f);
        life = (math_random_int_range(10, 30) * 5 + 2) / 6;
        point[0] = position[0] + math_random_signed_float_range(0.0f, 0.2f);
        point[1] = position[1] + math_random_signed_float_range(0.0f, 0.2f);
        point[2] = position[2] + math_random_signed_float_range(0.0f, 0.2f);
        part_spawn_trail_2(point, offset, life, 0.0032000002f);
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, g_hero_matrix, angle);
            vec_rotate_by_quaternion(direction, basis, rotation);
        }
    }

    math_apply_axis_rotation_to_quat(basis, g_hero_matrix, g_hero_matrix + 0x10, g_burst_rotation_angle * 0.017453294f);
    angle = 0.0f;
    qcopy(direction, basis);
    /* Only external calls read this local vector after its clear. */
    qzero_nc(offset);
    if (g_hero_state.flag)
        FastVecScale(offset, g_hero_state.velocity, 1.7f);
    scale = g_burst_scale;
    speed = g_burst_speed;
    spread = g_burst_spread;
    if (mode) {
        scale = 2.0f;
        speed = 10000.0f;
        spread = 0.8f;
    }
    for (j = 0; j < 20; j++) {
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186f));
        FastVecScale(velocity, direction,
                      math_random_float_range(g_burst_life_min * 0.020000001f,
                                    g_burst_life_max * 0.020000001f));
        FastVecAdd(velocity, velocity, offset);
        kind = (g_burst_kind * 5 + 2) / 6;
        life2 = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        point[0] = position[0] + math_random_signed_float_range(0.0f, spread);
        point[1] = position[1] + math_random_signed_float_range(0.0f, spread);
        point[2] = position[2] + math_random_signed_float_range(0.0f, spread);
        jitter = math_random_float_range(g_burst_jitter_min, scale) * 210000.0f;
        FastVecSub(point, point, velocity);
        part_spawn_burst(point, velocity, kind, g_burst_count_min, g_burst_count_max,
                      life2, jitter, speed, g_burst_extra_param, 0.0f, 0.0f);
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, g_hero_matrix, angle);
            vec_rotate_by_quaternion(direction, basis, rotation);
        }
    }
}
