#include "include_asm.h"



#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int FloatToInt(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void FastVecSub(void *, void *, void *);
extern int FastDecTimer(void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern void euler_rotation_basis(void *, void *);
extern void func_PAL_L00_00322198(void *, void *, float, float, int);
extern char *func_PAL_L00_003FB330(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern int coll_test_point(void *, int, float, void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void mat_from_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern float D_L04_001BFB00[];
extern void func_PAL_L04_0040B8B8(void *);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_L04_0040BC70(unsigned char *m)
{
    float oldpoint[4];
    float rot[12];
    float point[4];
    float delta[4];
    float probe[4];
    float matrix[13];
    float bounce[4];
    float axis[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float speed, dot;
    float radius;
    *(unsigned short *)(p + 0x32) += 1;
    switch (m[0x20]) {
    case 1:
        if (FastDecTimer(p + 0x30)) {
            m[0x20] = (*(int *)(p + 0x34) & 1) ? 3 : 2;
            *(short *)(p + 0x30) = FloatToInt(8.666667f);
            return;
        }
        if (*(int *)(p + 0x34) & 4) gfx_add_draw_callback_third(func_PAL_L04_0040B8B8, m);
        break;
    case 2:
        matrix_mul_vec3(oldpoint, p + 0x20, m + 0xc0);
        FastVecAdd(oldpoint, oldpoint, m + 0x10);
        if (*(int *)(p + 0x34) & 2) func_PAL_L00_00322198(m, oldpoint, 0.3f, 10.0f, -1);
        else func_PAL_L00_003FB330(m + 0x10, 0.5f, 0.0f, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0);
        goto destroy;
    case 3:
        if (FastDecTimer(p + 0x30)) {
        case 0:
        destroy:
            moby_mark_spawned(m);
            return;
        }
        m[0x23] = FloatToInt((float)*(short *)(p + 0x30) * 14.76923f);
        break;
    }
    euler_rotation_basis(rot, p + 0x10);
    matrix_mul_vec3(oldpoint, p + 0x20, m + 0xc0);
    multiply_matrix3x3(m + 0xc0, rot, m + 0xc0);
    matrix_mul_vec3(point, p + 0x20, m + 0xc0);
    FastVecSub(delta, point, oldpoint);
    FastVecSub(m + 0x10, m + 0x10, delta);
    FastVecAdd(m + 0x10, m + 0x10, p);
    *(float *)(p + 8) -= *(float *)(p + 0x38);
    radius = *(float *)(p + 0x2c);
    matrix_mul_vec3(probe, p + 0x20, m + 0xc0);
    FastVecAdd(probe, probe, m + 0x10);
    if (coll_test_point(probe, 0, radius, m)) {
        vec_scale_to_length(D_L04_001BFB00, D_L04_001BFB00, 1.0f);
        speed = FastVecLength(p);
        dot = FastVecDot(p, D_L04_001BFB00);
        if (dot < 0.0f) {
            vec_fast_normalize(p, p, D_L04_001BFB00);
            vec_scale_to_length(bounce, D_L04_001BFB00, dot * 0.5f);
            FastVecAdd(p, p, bounce);
            vec_scale_to_length(p, p, speed);
            FastVecCross(axis, D_L04_001BFB00, p);
            vec_scale_to_length(axis, axis, 1.0f);
            math_build_axis_angle_quat(axis, axis, FastVecLength(p + 0x10));
            mat_from_rotation(axis, matrix);
            mat_get_euler_angles(matrix, p + 0x10);
            if (*(short *)(p + 0x32) >= 13) *(short *)(p + 0x30) = 0;
        }
    }
}

