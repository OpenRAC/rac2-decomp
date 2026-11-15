#include "names.h"
/* func_L23_003C16D8 (644 bytes): transforms the mode-dependent vectors through three-row
 * rotation matrices. Its own unit for -G8 (the $gp stamp) and -frac2-zero-ti-por (the por
 * zero of the second branch's vector).
 * The last spot was the extra saved register: retail recomputes the stack addresses after
 * each quadword clear (sp+0x40 and the second branch's sp+0x10 matrix), which is what
 * RAC1's clobber-free qzero gives: a bare volatile asm flushes cse's table. qzero_nc is
 * that helper; with it the matrix address is not kept in a callee-saved register across
 * func_0031B1A8. func_002AAA00 is float (out, f12, f13, f14, f15, in, int).
 */
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
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void FastVecScale(void *, void *, float);
extern void mat_align_to_dir(void *, void *, void *);
extern int FastDecTimer(short *);
extern void FastVecSub(void *, void *, void *);

/* Turns the helper object to face the right way each frame, twisting it by a timed amount. */
void child_update_orientation(char *moby) {
    TI128 base_vec[1], matrix[3], twist_vec[1], scratch_vec[1], matrix2[3], push_vec[1];
    float unused_out0, unused_out1;
    char *vars = *(char **)(moby + 0x68);
    float angle;
    float rate_a;
    float rate_b;
    float rate_c;

    if (*(unsigned char *)(moby + 0x95) == 2 || *(short *)(vars + 0x2A6) != 0)
        moby_transform_joint_to_world(moby, 1, *(char **)(vars + 0x2A0) + 0x10);
    else
        moby_copy_joint_transform_to_object(moby, *(char **)(vars + 0x2A0), 1, 0);
    if (*(unsigned char *)(moby + 0x95) == 2) {
        if (*(short *)(vars + 0x2A6) == 0)
            *(int *)(vars + 0x2AC) = 0;
        FastVecSub(base_vec, g_hero_position, *(char **)(vars + 0x2A0) + 0x10);
        angle = vec_get_heading_angle(*(char **)(vars + 0x2A0), base_vec, 0);
        rate_b = *(float *)(vars + 0x68) + *(float *)(vars + 0x68);
        rate_a = *(float *)(vars + 0x64);
        rate_c = *(float *)(vars + 0x6C);
        unused_out0 = 0;
        math_approach_target_with_direction_mode(&unused_out0, angle, rate_a, rate_b, rate_c, vars + 0x2AC, 0);
        qzero_nc(twist_vec);
        ((float *)twist_vec)[2] = *(float *)(vars + 0x2AC);
        euler_rotation_basis(matrix, twist_vec);
        multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, matrix);
        func_002A05A8(*(char **)(vars + 0x2A0));
        *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(vars + 0x2A0));
        FastVecScale(scratch_vec, vars + 0x280, -1.0f);
        mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, scratch_vec, 0);
        *(short *)(vars + 0x2A6) = D_L23_001AFA64;
        return;
    }
    {
        short timer = *(short *)(vars + 0x2A6);

        if (timer != 0) {
            if (timer == D_L23_001AFA64)
                *(int *)(vars + 0x2AC) = 0;
            *base_vec = 0;
            ((float *)base_vec)[0] = 1.0f;
            ((float *)base_vec)[3] = 1.0f;
            moby_transform_joint_point(moby, 1, matrix);
            qzero_nc(twist_vec);
            matrix_mul_vec3(base_vec, base_vec, matrix);
            angle = vec_get_heading_angle(*(char **)(vars + 0x2A0), base_vec, 0);
            rate_a = *(float *)(vars + 0x64) + *(float *)(vars + 0x64);
            rate_c = *(float *)(vars + 0x6C);
            rate_b = *(float *)(vars + 0x68) * 4.0f;
            unused_out1 = 0;
            math_approach_target_with_direction_mode(&unused_out1, angle, rate_a, rate_b, rate_c, vars + 0x2AC, 0);
            qzero_nc(scratch_vec);
            ((float *)scratch_vec)[2] = *(float *)(vars + 0x2AC);
            euler_rotation_basis(matrix2, scratch_vec);
            multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, matrix2);
            func_002A05A8(*(char **)(vars + 0x2A0));
            *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(vars + 0x2A0));
            FastVecScale(push_vec, vars + 0x280, -1.0f);
            mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, push_vec, 0);
            FastDecTimer((short *)(vars + 0x2A6));
        }
    }
}
