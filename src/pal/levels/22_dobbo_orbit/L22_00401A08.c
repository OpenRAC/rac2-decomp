#include "include_asm.h"

#include "common.h"
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_negate_and_forward(void *, void *, int);

/* Turns the object's frame (a three-row rotation) by a small fixed angle about z, then places it from the
   state's +0x10 block. */
void func_PAL_L22_00401A08(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float angles[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));

    qzero(angles);
    angles[2] = 0.022689285f;
    euler_rotation_basis(matrix, angles);
    multiply_matrix3x3(object + 0xC0, object + 0xC0, matrix);
    cam_compute_view_direction(object + 0x10, state + 0x10, 0);
    vec_negate_and_forward(object + 0xC0, state + 0x10, 0);
}

