#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int g_space_ship_tilt_value __attribute__((sda));
extern char g_hero_position[];
extern void moby_transform_joint_point(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float vec_get_heading_angle(void *, void *, int);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void FastVecScale(void *, void *, float);
extern void mat_align_to_dir(void *, void *, void *);
extern int FastDecTimer(short *);
extern void FastVecSub(void *, void *, void *);

void func_PAL_L22_003A7FF0(char *obj) {
    TI128 v0[1], v1[3], t[1], u[1], r3[3], r4[1];
    float fz0, fz1;
    char *state = *(char **)(obj + 0x68);
    float r;
    float a1;
    float b1;
    float c1;

    if ((unsigned)(*(unsigned char *)(*(char **)(state + 0x440) + 0x43) - 1) < 3) {
        if (*(short *)(state + 0x460) == 0)
            *(int *)(state + 0x458) = 0;
        FastVecSub(v0, g_hero_position, *(char **)(state + 0x440) + 0x10);
        r = vec_get_heading_angle(*(char **)(state + 0x440), v0, 0);
        b1 = *(float *)(state + 0x128) + *(float *)(state + 0x128);
        a1 = *(float *)(state + 0x124);
        c1 = *(float *)(state + 0x12C);
        fz0 = 0;
        math_approach_target_with_direction_mode(&fz0, r, a1, b1, c1, state + 0x458, 0);
        qzero_nc(t);
        ((float *)t)[2] = *(float *)(state + 0x458);
        euler_rotation_basis(v1, t);
        multiply_matrix3x3(*(char **)(state + 0x440) + 0xC0, *(char **)(state + 0x440) + 0xC0, v1);
        func_PAL_002A0F68(*(char **)(state + 0x440));
        *(unsigned short *)(*(char **)(state + 0x440) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(state + 0x440));
        FastVecScale(u, state + 0x200, -1.0f);
        mat_align_to_dir(*(char **)(state + 0x440) + 0xC0, u, 0);
        *(short *)(state + 0x460) = ((s32)(g_space_ship_tilt_value) * 5 + 2) / 6;
        return;
    }
    {
        short v = *(short *)(state + 0x460);

        if (v != 0) {
            if (v == ((s32)(g_space_ship_tilt_value) * 5 + 2) / 6)
                *(int *)(state + 0x458) = 0;
            *v0 = 0;
            ((float *)v0)[0] = 1.0f;
            ((float *)v0)[3] = 1.0f;
            moby_transform_joint_point(obj, 1, v1);
            qzero_nc(t);
            matrix_mul_vec3(v0, v0, v1);
            r = vec_get_heading_angle(*(char **)(state + 0x440), v0, 0);
            a1 = *(float *)(state + 0x124) + *(float *)(state + 0x124);
            c1 = *(float *)(state + 0x12C);
            b1 = *(float *)(state + 0x128) * 4.0f;
            fz1 = 0;
            math_approach_target_with_direction_mode(&fz1, r, a1, b1, c1, state + 0x458, 0);
            qzero_nc(u);
            ((float *)u)[2] = *(float *)(state + 0x458);
            euler_rotation_basis(r3, u);
            multiply_matrix3x3(*(char **)(state + 0x440) + 0xC0, *(char **)(state + 0x440) + 0xC0, r3);
            func_PAL_002A0F68(*(char **)(state + 0x440));
            *(unsigned short *)(*(char **)(state + 0x440) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(state + 0x440));
            FastVecScale(r4, state + 0x200, -1.0f);
            mat_align_to_dir(*(char **)(state + 0x440) + 0xC0, r4, 0);
            FastDecTimer((short *)(state + 0x460));
        }
    }
}
