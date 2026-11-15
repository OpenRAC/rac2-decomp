#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F418588;

extern s32 D_L10_001B0F50 __attribute__((sda));
extern s32 D_L10_001B0F60 __attribute__((sda));
extern s32 D_L10_001B0F70 __attribute__((sda));

extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, char *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void part_spawn_object_relative_particle(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail. */
void part_spawn_large_tail_trail(char *obj)
{
    V4_F418588 dir, drift, tail, mark1, mark2, mark3;
    float drift_scale;

    dir.q = 0;
    dir.f[0] = -2.1f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    matrix_mul_vec3(&tail, &dir, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    drift_scale = 0.8f;
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * drift_scale;
    part_spawn_object_relative_particle(obj, &mark1, &drift, &D_L10_001B0F50, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * drift_scale;
    part_spawn_object_relative_particle(obj, &mark2, &drift, &D_L10_001B0F60, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.016666668f) * drift_scale;
    part_spawn_object_relative_particle(obj, &mark3, &drift, &D_L10_001B0F70, 1);
}
