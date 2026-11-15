#include "common.h"

extern void func_00283388(void *m);
extern float func_00283248(float, float);
extern void func_00283410(void *m, void *angles);
extern void func_002830C0(void *dst, void *src, void *m);
extern void func_00283430(void *m, void *angles);
extern void func_00283788(void *dst, void *a, void *b);
extern void func_00283698(void *dst, void *src);
extern void func_00283678(void *dst, void *src);

/* Builds a rotation matrix that points along a direction and then turns by a roll angle. */
void func_L11_00332EE0(void *out, float *dir, float roll)
{
    float combined[16];
    float yawMatrix[16];
    float pitchMatrix[16];
    float rollMatrix[16];
    float angles[4];
    float direction[4] __attribute__((aligned(16)));

    qcopy(direction, dir);
    set_identity_matrix(combined);
    angles[2] = -FastMatrixHelperA(direction[0], direction[1]);
    angles[0] = 0;
    angles[1] = 0;
    euler_to_matrix(yawMatrix, angles);
    transform_vector(direction, direction, yawMatrix);
    angles[1] = -FastMatrixHelperA(direction[2], direction[0]);
    angles[0] = 0;
    angles[2] = 0;
    FastMatrixHelperB(pitchMatrix, angles);
    transform_vector(direction, direction, pitchMatrix);
    angles[2] = roll;
    angles[0] = 0;
    angles[1] = 0;
    FastMatrixHelperB(rollMatrix, angles);
    multiply_matrix(combined, yawMatrix, combined);
    multiply_matrix(combined, pitchMatrix, combined);
    multiply_matrix(combined, rollMatrix, combined);
    matrix_from_basis_rows(pitchMatrix, pitchMatrix);
    multiply_matrix(combined, pitchMatrix, combined);
    matrix_from_basis_rows(yawMatrix, yawMatrix);
    multiply_matrix(combined, yawMatrix, combined);
    qcopy(direction, dir);
    transform_vector(direction, direction, combined);
    copy_matrix3x4(out, combined);
}
