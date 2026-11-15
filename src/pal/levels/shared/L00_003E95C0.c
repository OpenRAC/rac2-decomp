#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern int func_001163B0(void);
extern char g_camera_l00_position[];
extern void FastVecSub(char *, char *, char *);
extern float math_random_float_range(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern char g_camera_l00_position[];
extern void FastVecSub(char *dst, char *src, char *arg);
extern float math_random_float_range(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void ref_L00_003E5340_00(float *, float *, int, int, int);
#include "common.h"

/* Emits ten particles at POSITION: one thrown towards D_L00_001B8DC0 with a random spread, then
   nine at random upward angles turned by the object's matrix, about a third of them (rand() % 3
   == 0) in mode 1. */
void func_PAL_L00_003E95C0(char *object, float *position)
{
    Vector delta, velocity, random;
    float distance;
    int divisor = 3;
    int i = 8;
    int mode;

    FastVecSub((char *)delta, g_camera_l00_position, (char *)position);
    distance = FastVecLength(delta);
    *(VectorBits *)random = 0;
    random[0] = math_random_float_range(-1.0f, 1.0f);
    random[1] = math_random_float_range(-1.0f, 1.0f);
    random[2] = math_random_float_range(-1.0f, 1.0f);
    delta[2] += distance * 0.5f;
    *(VectorBits *)velocity = *(VectorBits *)random;
    vec_scale_to_length(velocity, velocity, distance * 0.004f);
    vec_scale_to_length(delta, delta, (distance + distance) * 0.020000001f);
    FastVecAdd(velocity, velocity, delta);
    vec_fast_divide_helper(velocity, velocity, 0.20000002f);
    ref_L00_003E5340_00(position, velocity, math_random_int_range(50, 75), 0, 0);
    for (; i >= 0; i--) {
        float pitch, yaw, speed;

        mode = 0;
        pitch = math_random_float_range(0.2617994248867035f, 1.3089970350265503f);
        yaw = math_random_angle();
        speed = math_random_float_range(8.0f, 12.0f);
        vec_build_spherical_offset(random, speed * 0.020000001f, yaw, pitch);
        random[2] += 0.060000002f;
        if (func_001163B0() % divisor == 0)
            mode = 1;
        matrix_mul_vec3(random, random, object + 0xC0);
        ref_L00_003E5340_00(position, random, math_random_int_range(50, 75), mode, 0);
    }
}

