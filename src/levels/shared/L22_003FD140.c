#include "include_asm.h"
#include "common.h"

extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_00325600(void *, void *, int);

/* Turns the object's frame (a three-row rotation) by a small fixed angle about z, then places it from the
   state's +0x10 block. */
/* Per-frame update for moby class 3644: slowly turns the object and places it on its path. */
void func_L22_003FD140(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float angles[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));

    qzero(angles);
    angles[2] = 0.018907737f;
    euler_rotation_basis(matrix, angles);
    multiply_matrix3x3(object + 0xC0, object + 0xC0, matrix);
    ComputeViewDirection(object + 0x10, state + 0x10, 0);
    NegateAndForwardVector(object + 0xC0, state + 0x10, 0);
}
