#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F418BA0;
extern s32 g_small_tail_particle_first __attribute__((sda));
extern s32 g_small_tail_particle_second __attribute__((sda));
extern s32 g_small_tail_particle_third __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, char *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail. */
void part_spawn_small_tail_trail_pal(char *obj)
{
    V4_F418BA0 dir, drift, tail, mark1, mark2, mark3;
    float k;

    dir.q = 0;
    dir.f[0] = -0.45f;
    dir.f[2] = 0.25f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    matrix_mul_vec3(&tail, &dir, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    k = 0.5f;
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * k;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &g_small_tail_particle_first, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * k;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &g_small_tail_particle_second, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * k;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &g_small_tail_particle_third, 1);
}
