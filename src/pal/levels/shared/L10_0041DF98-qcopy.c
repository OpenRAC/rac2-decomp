#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F419348;
extern s32 g_tail_marks_particle_first __attribute__((sda));
extern s32 g_tail_marks_particle_second __attribute__((sda));
extern s32 g_tail_marks_particle_third __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, char *);
extern void FastVecAdd(void *, void *, char *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail. */
void part_l10_spawn_tail_trail_marks_pal(char *moby)
{
    V4_F419348 dir, drift, tail, mark1, mark2, mark3, alt;
    float scale;

    dir.q = 0;
    dir.f[0] = -0.6f;
    dir.f[2] = 0.26f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    scale = 0.5f;
    if (*(u8 *)(moby + 0x20) == 1) {
        alt.q = 0;
        alt.f[0] = -0.15f;
        alt.f[2] = 0.06f;
        alt.f[3] = 1.0f;
        qcopy(&dir, &alt);
    }
    matrix_mul_vec3(&tail, &dir, moby + 0xC0);
    FastVecAdd(&tail, &tail, moby + 0x10);
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    vec_add_random_offset(&tail, 0.1f);
    vec_add_random_offset(&mark1, 0.1f);
    vec_add_random_offset(&mark2, 0.1f);
    vec_add_random_offset(&mark3, 0.1f);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * scale;
    part_spawn_object_relative_particle(moby, &mark1, &drift, &g_tail_marks_particle_first, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * scale;
    part_spawn_object_relative_particle(moby, &mark2, &drift, &g_tail_marks_particle_second, 1);
    drift.f[0] = -(math_random_float_range(30.0f, 40.0f) * 0.020000001f) * scale;
    part_spawn_object_relative_particle(moby, &mark3, &drift, &g_tail_marks_particle_third, 1);
}
