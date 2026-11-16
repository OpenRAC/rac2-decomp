#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char g_tail_trail_particle_a __attribute__((sda));
extern char g_tail_trail_particle_b __attribute__((sda));
extern char g_tail_trail_particle_c __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, int);

/* Builds a unit vector pointing back along the object's -0.8 axis, rotated into the world, then
   fires three bursts, one from each of three copies of it, each with a random upward kick
   in the second vector's first word. */
void tail_trail_spawn_burst_pal(char *object)
{
    float dir[4];
    float drift[4];
    float tail[4];
    float mark1[4];
    float mark2[4];
    float mark3[4];
    float rand_speed;
    float half;

    *(TI128 *)dir = 0;
    *(TI128 *)drift = 0;
    dir[0] = -0.8f;
    dir[3] = 1.0f;
    matrix_mul_vec3(tail, dir, object + 0xC0);
    half = 0.5f;
    FastVecAdd(tail, tail, object + 0x10);
    tail[3] = 0.0f;
    *(TI128 *)mark1 = *(TI128 *)tail;
    *(TI128 *)mark2 = *(TI128 *)tail;
    *(TI128 *)mark3 = *(TI128 *)tail;
    vec_add_random_offset(tail, 0.1f);
    vec_add_random_offset(mark1, 0.1f);
    vec_add_random_offset(mark2, 0.1f);
    vec_add_random_offset(mark3, 0.1f);
    rand_speed = math_random_float_range(7.5f, 10.0f);
    drift[0] = -(rand_speed * 0.020000001f) * half;
    part_spawn_object_relative_particle(object, mark1, drift, &g_tail_trail_particle_a, 1);
    rand_speed = math_random_float_range(7.5f, 10.0f);
    drift[0] = -(rand_speed * 0.020000001f) * half;
    part_spawn_object_relative_particle(object, mark2, drift, &g_tail_trail_particle_b, 1);
    rand_speed = math_random_float_range(7.5f, 10.0f);
    drift[0] = -(rand_speed * 0.020000001f) * half;
    part_spawn_object_relative_particle(object, mark3, drift, &g_tail_trail_particle_c, 1);
}
