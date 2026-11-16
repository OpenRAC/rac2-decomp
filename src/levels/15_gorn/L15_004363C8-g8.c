#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } GornPoint;

extern int g_challenge_mode;
extern s32 g_gorn_exhaust_particle_a __attribute__((sda));
extern s32 g_gorn_exhaust_particle_b __attribute__((sda));
extern s32 g_gorn_exhaust_particle_c __attribute__((sda));

extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, char *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, s32);

/* Spawns three jittered particles at each of four transformed exhaust points. */
void part_l15_spawn_exhaust(char *obj)
{
    GornPoint dir, drift, tail, mark1, mark2, mark3, dir2, dir3, dir4;
    float k;

    if (g_challenge_mode == 2) return;
    dir.q = 0;
    dir.f[0] = -15.0f;
    dir.f[2] = 4.6f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    matrix_mul_vec3(&tail, &dir, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    k = 0.4f;
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &g_gorn_exhaust_particle_a, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &g_gorn_exhaust_particle_b, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &g_gorn_exhaust_particle_c, 1);
    dir2.q = 0;
    dir2.f[0] = -15.0f;
    dir2.f[2] = 2.0f;
    dir2.f[3] = 1.0f;
    matrix_mul_vec3(&tail, &dir2, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &g_gorn_exhaust_particle_a, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &g_gorn_exhaust_particle_b, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &g_gorn_exhaust_particle_c, 1);
    dir3.q = 0;
    dir3.f[0] = -10.0f;
    dir3.f[1] = 3.4f;
    dir3.f[2] = 1.05f;
    dir3.f[3] = 1.0f;
    matrix_mul_vec3(&tail, &dir3, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &g_gorn_exhaust_particle_a, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &g_gorn_exhaust_particle_b, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &g_gorn_exhaust_particle_c, 1);
    dir4.q = 0;
    dir4.f[0] = -10.0f;
    dir4.f[1] = -3.4f;
    dir4.f[2] = 1.05f;
    dir4.f[3] = 1.0f;
    matrix_mul_vec3(&tail, &dir4, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &g_gorn_exhaust_particle_a, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &g_gorn_exhaust_particle_b, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * k;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &g_gorn_exhaust_particle_c, 1);
}
