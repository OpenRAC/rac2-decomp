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
    TI128 baseVec[1], matrix[3], twistVec[1], scratchVec[1], matrix2[3], pushVec[1];
    float unusedOut0, unusedOut1;
    char *vars = *(char **)(moby + 0x68);
    float angle;
    float rateA;
    float rateB;
    float rateC;

    if (*(unsigned char *)(moby + 0x95) == 2 || *(short *)(vars + 0x2A6) != 0)
        moby_transform_joint_to_world(moby, 1, *(char **)(vars + 0x2A0) + 0x10);
    else
        moby_copy_joint_transform_to_object(moby, *(char **)(vars + 0x2A0), 1, 0);
    if (*(unsigned char *)(moby + 0x95) == 2) {
        if (*(short *)(vars + 0x2A6) == 0)
            *(int *)(vars + 0x2AC) = 0;
        FastVecSub(baseVec, g_hero_position, *(char **)(vars + 0x2A0) + 0x10);
        angle = vec_get_heading_angle(*(char **)(vars + 0x2A0), baseVec, 0);
        rateB = *(float *)(vars + 0x68) + *(float *)(vars + 0x68);
        rateA = *(float *)(vars + 0x64);
        rateC = *(float *)(vars + 0x6C);
        unusedOut0 = 0;
        math_approach_target_with_direction_mode(&unusedOut0, angle, rateA, rateB, rateC, vars + 0x2AC, 0);
        qzero_nc(twistVec);
        ((float *)twistVec)[2] = *(float *)(vars + 0x2AC);
        euler_rotation_basis(matrix, twistVec);
        multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, matrix);
        func_002A05A8(*(char **)(vars + 0x2A0));
        *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(vars + 0x2A0));
        FastVecScale(scratchVec, vars + 0x280, -1.0f);
        mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, scratchVec, 0);
        *(short *)(vars + 0x2A6) = D_L23_001AFA64;
        return;
    }
    {
        short timer = *(short *)(vars + 0x2A6);

        if (timer != 0) {
            if (timer == D_L23_001AFA64)
                *(int *)(vars + 0x2AC) = 0;
            *baseVec = 0;
            ((float *)baseVec)[0] = 1.0f;
            ((float *)baseVec)[3] = 1.0f;
            moby_transform_joint_point(moby, 1, matrix);
            qzero_nc(twistVec);
            matrix_mul_vec3(baseVec, baseVec, matrix);
            angle = vec_get_heading_angle(*(char **)(vars + 0x2A0), baseVec, 0);
            rateA = *(float *)(vars + 0x64) + *(float *)(vars + 0x64);
            rateC = *(float *)(vars + 0x6C);
            rateB = *(float *)(vars + 0x68) * 4.0f;
            unusedOut1 = 0;
            math_approach_target_with_direction_mode(&unusedOut1, angle, rateA, rateB, rateC, vars + 0x2AC, 0);
            qzero_nc(scratchVec);
            ((float *)scratchVec)[2] = *(float *)(vars + 0x2AC);
            euler_rotation_basis(matrix2, scratchVec);
            multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, matrix2);
            func_002A05A8(*(char **)(vars + 0x2A0));
            *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(vars + 0x2A0));
            FastVecScale(pushVec, vars + 0x280, -1.0f);
            mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, pushVec, 0);
            FastDecTimer((short *)(vars + 0x2A6));
        }
    }
}
