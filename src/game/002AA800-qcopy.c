#include "include_asm.h"
#include "common.h"

#ifndef RAC2_T_V4_002AD6F0
#define RAC2_T_V4_002AD6F0
typedef int V4_002AD6F0 __attribute__((mode(TI)));
#endif

typedef struct { char pad[64]; } Matrix64_002AD6F0;

extern void euler_to_matrix(char *dst, char *src);
extern void matrix_from_basis_rows(char *dst, char *src);
extern void multiply_matrix(char *a, char *b, char *c);
extern void mat_get_euler_angles(char *a, char *b);

extern void matrix_mul_vec3(char *a, char *b, char *c);
extern void FastVecAdd(char *dst, char *a, char *b);
extern void copy_matrix_rotation(char *dst, char *src);
extern void vec_clamp_length(char *vec, float x);
extern char *moby_get_private_value_2(char *a);
extern int moby_get_attachment_rotation_angles(char *unused, char *obj, char *arg2, char *arg3, char *arg4, char *arg5);
extern char *g_hero_moby;

/* Works out where a hit object should be pushed and spins it, using its collision shape. */
int coll_apply_push_to_object(char *a0, char *a1, char *a2, char *a3, char *a4, char *a5)
{
    char buf0[64];
    char buf2[64];
    char vec[16];
    char *p;

    p = moby_get_private_value_2(a1);
    if (p == 0)
        return 0;
    if (*(int *)(p + 60) & 0x40)
        euler_to_matrix(buf0, a1 + 240);
    else
        copy_matrix_rotation(buf0, a1 + 192);
    matrix_mul_vec3(a4, a2, buf0);
    FastVecAdd(a4, a4, a1 + 16);
    euler_to_matrix(buf2, a3);
    multiply_matrix(buf2, buf0, buf2);
    mat_get_euler_angles(buf2, a5);
    if (*(int *)(p + 60) & 4) {
        FastVecAdd(a4, a4, p + 16);
        moby_get_attachment_rotation_angles(a0, a1, a4, a5, a2, a3);
        return 1;
    }
    if (a0 == g_hero_moby)
        return 1;
    if ((unsigned char)a0[0x22] < (unsigned char)a1[0x22]) {
        qcopy(vec, p + 16);
        vec_clamp_length(vec, 1.0f);
        FastVecAdd(a4, a4, vec);
    }
    return 1;
}

/* Combines two transforms and stores the result on the object, then copies in new positions. */
void mat_combine_and_store(void *obj, void *a1, void *a2, void *a3)
{
    Matrix64_002AD6F0 m0, m1, m2, m3;
    V4_002AD6F0 *p;

    euler_to_matrix((char *)&m0, (char *)a2);
    matrix_from_basis_rows((char *)&m1, (char *)&m0);
    euler_to_matrix((char *)&m2, (char *)a3);
    multiply_matrix((char *)&m3, (char *)&m1, (char *)&m2);
    mat_get_euler_angles((char *)&m3, (char *)obj);
    if (*(int *)((char *)obj + 0x3C) & 2) {
        p = (V4_002AD6F0 *)((char *)obj + 0x20);
        *p = *(V4_002AD6F0 *)a2;
    }
    p = (V4_002AD6F0 *)((char *)obj + 0x10);
    *p = *(V4_002AD6F0 *)a1;
}

extern void FastVecCross(float *dst, float *a, float *b);
extern void vec_scale_to_length(float *dst, float *src, float scale);
extern float FastVecDot(float *a, float *b);
extern float FastVecLength(float *a);
extern float math_fast_angle_helper(float x);
extern float math_fast_sin_or_cos_b(float x);
extern float math_fast_sin_or_cos_a(float x);
extern void FastVecScale(float *dst, float *src, float scale);
extern void vec_rotate_by_quaternion(float *dst, float *a, float *b);

/* Builds a rotation that turns one direction toward another by a given fraction. */
void mat_build_rotation_toward_vector(float *dst, float *a, float *b, int normalized, float scale)
{
    float axis[4];
    float dot;
    float len;
    float angle;

    FastVecCross(axis, b, a);
    vec_scale_to_length(axis, axis, 1.0f);
    dot = FastVecDot(a, b);
    if (normalized == 0) {
        len = FastVecLength(a) * FastVecLength(b);
        if (len == 0.0f) {
            qcopy(dst, a);
            return;
        }
        dot /= len;
    }
    angle = (1.5707964f - math_fast_angle_helper(dot)) * (scale * 0.5f);
    FastVecScale(axis, axis, math_fast_sin_or_cos_b(angle));
    axis[3] = math_fast_sin_or_cos_a(angle);
    vec_rotate_by_quaternion(dst, a, axis);
}

