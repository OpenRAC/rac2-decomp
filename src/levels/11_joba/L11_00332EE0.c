#include "common.h"

extern void set_identity_matrix(void *m);
extern float mat_fast_helper_a(float, float);
extern void euler_to_matrix(void *m, void *angles);
extern void transform_vector(void *dst, void *src, void *m);
extern void mat_fast_helper_b(void *m, void *angles);
extern void multiply_matrix(void *dst, void *a, void *b);
extern void matrix_from_basis_rows(void *dst, void *src);
extern void copy_matrix3x4(void *dst, void *src);

/* Builds a rotation matrix that points along a direction and then turns by a roll angle. */
void mat_build_direction_roll(void *out, float *dir, float roll)
{
    float combined[16];
    float yawMatrix[16];
    float pitchMatrix[16];
    float rollMatrix[16];
    float angles[4];
    float direction[4] __attribute__((aligned(16)));

    qcopy(direction, dir);
    set_identity_matrix(combined);
    angles[2] = -mat_fast_helper_a(direction[0], direction[1]);
    angles[0] = 0;
    angles[1] = 0;
    euler_to_matrix(yawMatrix, angles);
    transform_vector(direction, direction, yawMatrix);
    angles[1] = -mat_fast_helper_a(direction[2], direction[0]);
    angles[0] = 0;
    angles[2] = 0;
    mat_fast_helper_b(pitchMatrix, angles);
    transform_vector(direction, direction, pitchMatrix);
    angles[2] = roll;
    angles[0] = 0;
    angles[1] = 0;
    mat_fast_helper_b(rollMatrix, angles);
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
