#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_L23_001AFA64 __attribute__((sda));
extern char g_hero_position[];
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
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

extern float D_L23_001B36A4 MACRO_ADDR;
extern int D_L23_001AFA54 __attribute__((sda));
extern TI128 D_L23_001C0AA0[];
extern char D_00189ED0[];
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void func_L22_002F3B38(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);

#define F(i, k) (((float *)&loc[i])[k])

/* func_PAL_L23_003C4CE8, the PAL copy of func_L23_003C1420: the same C, with the follow timer scaled to 50 Hz. */
int func_PAL_L23_003C4CE8(char *obj) {
    TI128 loc[8];
    char *state = *(char **)(obj + 0x68);
    int r;
    TI128 *pg;
    TI128 *pl;
    TI128 *ps;
    TI128 *pd;

    loc[1] = 0;
    F(1, 2) = *(float *)(state + 0x54) + *(float *)(state + 0x50);
    loc[2] = 0;
    F(2, 0) = 4.0f;
    loc[0] = loc[1];
    r = math_random_int_below(8);
    F(2, 1) = (float)r * 0.4285714626f + -1.5f;
    F(2, 2) = *(float *)(state + 0x54) + *(float *)(state + 0x50);
    loc[1] = loc[2];
    FastVecScale(&loc[0], obj + 0xE0, F(0, 2));
    FastVecAdd(&loc[0], &loc[0], obj + 0x10);
    matrix_mul_vec3(&loc[1], &loc[1], obj + 0xC0);
    FastVecAdd(&loc[1], &loc[1], obj + 0x10);
    if (CollLine(&loc[0], &loc[1], 0x12, 0, 0) != 0) {
    pg = &D_L23_001C0AA0[2];
    pl = &loc[2];
    qcopy(pl, pg);
    loc[5] = 0;
    F(5, 0) = 0.0009765625f;
    F(5, 1) = 0.0009765625f;
    F(5, 2) = 0.0009765625f;
    func_L22_002F3B38(pl, pl, &loc[5]);
    pg -= 2;
    vec_scale_to_length(pl, pl, 1.0f);
    FastVecSub(&loc[3], &loc[0], pg);
    { float d = FastVecDot(&loc[3], pl);
    FastVecScale(&loc[4], pl, d); }
    FastVecSub(&loc[6], &loc[3], &loc[4]);
    vec_scale_to_length(&loc[6], &loc[6], -30.0f);
    ps = (TI128 *)(state + 0x2D0);
    FastVecAdd(ps, obj + 0x10, &loc[6]);
    pd = &loc[7];
    FastVecSub(pd, ps, D_00189ED0);
    vec_scale_to_length(pd, pd, D_L23_001B36A4);
    FastVecAdd(pd, pd, D_00189ED0);
    qcopy(ps, pd);
    r = D_L23_001AFA54;
    *(short *)(state + 0x26C) = 1;
    *(unsigned short *)(state + 0x26E) = ((s32)(D_L23_001AFA54 + math_random_int_range(-r / 2, r / 2)) * 5 + 2) / 6;
    vec_scale_to_length(pl, pl, 10.0f);
    FastVecAdd(pl, pl, pg);
    return 1;
    }
    return 0;
}

void func_PAL_L23_003C4FC0(char *obj) {
    TI128 v0[1], v1[3], t[1], u[1], r3[3], r4[1];
    float fz0, fz1;
    char *state = *(char **)(obj + 0x68);
    float r;
    float a1;
    float b1;
    float c1;

    if (*(unsigned char *)(obj + 0x95) == 2 || *(short *)(state + 0x2A6) != 0)
        moby_transform_joint_to_world(obj, 1, *(char **)(state + 0x2A0) + 0x10);
    else
        moby_copy_joint_transform_to_object(obj, *(char **)(state + 0x2A0), 1, 0);
    if (*(unsigned char *)(obj + 0x95) == 2) {
        if (*(short *)(state + 0x2A6) == 0)
            *(int *)(state + 0x2AC) = 0;
        FastVecSub(v0, g_hero_position, *(char **)(state + 0x2A0) + 0x10);
        r = vec_get_heading_angle(*(char **)(state + 0x2A0), v0, 0);
        b1 = *(float *)(state + 0x68) + *(float *)(state + 0x68);
        a1 = *(float *)(state + 0x64);
        c1 = *(float *)(state + 0x6C);
        fz0 = 0;
        math_approach_target_with_direction_mode(&fz0, r, a1, b1, c1, state + 0x2AC, 0);
        qzero_nc(t);
        ((float *)t)[2] = *(float *)(state + 0x2AC);
        euler_rotation_basis(v1, t);
        multiply_matrix3x3(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, v1);
        func_PAL_002A0F68(*(char **)(state + 0x2A0));
        *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(state + 0x2A0));
        FastVecScale(u, state + 0x280, -1.0f);
        mat_align_to_dir(*(char **)(state + 0x2A0) + 0xC0, u, 0);
        *(short *)(state + 0x2A6) = ((s32)(D_L23_001AFA64) * 5 + 2) / 6;
        return;
    }
    {
        short v = *(short *)(state + 0x2A6);

        if (v != 0) {
            if (v == ((s32)(D_L23_001AFA64) * 5 + 2) / 6)
                *(int *)(state + 0x2AC) = 0;
            *v0 = 0;
            ((float *)v0)[0] = 1.0f;
            ((float *)v0)[3] = 1.0f;
            moby_transform_joint_point(obj, 1, v1);
            qzero_nc(t);
            matrix_mul_vec3(v0, v0, v1);
            r = vec_get_heading_angle(*(char **)(state + 0x2A0), v0, 0);
            a1 = *(float *)(state + 0x64) + *(float *)(state + 0x64);
            c1 = *(float *)(state + 0x6C);
            b1 = *(float *)(state + 0x68) * 4.0f;
            fz1 = 0;
            math_approach_target_with_direction_mode(&fz1, r, a1, b1, c1, state + 0x2AC, 0);
            qzero_nc(u);
            ((float *)u)[2] = *(float *)(state + 0x2AC);
            euler_rotation_basis(r3, u);
            multiply_matrix3x3(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, r3);
            func_PAL_002A0F68(*(char **)(state + 0x2A0));
            *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(state + 0x2A0));
            FastVecScale(r4, state + 0x280, -1.0f);
            mat_align_to_dir(*(char **)(state + 0x2A0) + 0xC0, r4, 0);
            FastDecTimer((short *)(state + 0x2A6));
        }
    }
}
