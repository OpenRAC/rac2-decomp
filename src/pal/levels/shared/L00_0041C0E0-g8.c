#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void cam_compute_view_direction(void *, void *, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void *func_PAL_L00_00340CA0(float, void *, void *, int, int, int, int, float, int, int, int);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern char g_spark_burst_particle_def_c __attribute__((sda));
extern char g_spark_burst_particle_def_a __attribute__((sda));
extern char g_spark_burst_particle_def_b __attribute__((sda));
extern char g_spark_burst_particle_def_d __attribute__((sda));

/* Emits three effect particles at the object, then four spawns along its velocity at rising heights. */
void part_emit_spark_burst_at_moby_pal(char *object)
{
    Vec up, velocity, pos, pos2, pos3, pos4;
    char *state = *(char **)(object + 0x68);
    int i;
    float angle, random, life, speed, spread, frame;

    cam_compute_view_direction(object + 0x10, &up, 1);
    if (*(int *)(state + 4) != 0)
        return;
    frame = 0.020000001f;
    for (i = 0; i < 3; i++) {
        angle = math_random_float_range(-0.9599311948f, -1.3962635994f);
        random = math_random_angle();
        speed = math_random_float_range(0.0f, 0.5f);
        spread = 0.3f;
        frame = 0.020000001f;
        speed *= frame;
        vec_build_spherical_offset(&velocity, speed, random, angle);
        life = math_random_float_range(0.65f, 0.85f) * 210000.0f;
        pos.f[0] = *(float *)(object + 0x10) + math_random_signed_float_range(0.0f, spread);
        pos.f[1] = *(float *)(object + 0x14) + math_random_signed_float_range(0.0f, spread);
        pos.f[2] = *(float *)(object + 0x18) + math_random_signed_float_range(0.0f, spread);
        func_PAL_L00_00340CA0(life, &pos, &velocity, 0x4F808080, 0x08101010, math_random_int_range(29, 42), 1, 0.5f, 1, -1, 1);
    }
    cam_compute_view_direction(object + 0x10, &velocity, 1);
    vec_scale_to_length(&velocity, &velocity, 0.2f);
    qcopy_nc(&pos, object + 0x10);
    pos.f[2] += math_random_float_range(0.1f, 0.4f);
    part_spawn_object_relative_particle(object, &pos, &velocity, &g_spark_burst_particle_def_c, math_random_int_below(2));
    qcopy_nc(&pos2, object + 0x10);
    pos2.f[2] += math_random_float_range(0.9f, 1.2f);
    part_spawn_object_relative_particle(object, &pos2, &velocity, &g_spark_burst_particle_def_a, math_random_int_below(2));
    qcopy_nc(&pos3, object + 0x10);
    pos3.f[2] += math_random_float_range(0.8f, 1.5f);
    part_spawn_object_relative_particle(object, &pos3, &velocity, &g_spark_burst_particle_def_b, math_random_int_below(2));
    qcopy_nc(&pos4, object + 0x10);
    part_spawn_object_relative_particle(object, &pos4, &velocity, &g_spark_burst_particle_def_d, math_random_int_below(2));
}
