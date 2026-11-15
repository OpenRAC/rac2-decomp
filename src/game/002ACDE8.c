/* func_002ACDE8: the three quaternions are one frame array; the copy is qcopy(), whose
 * destination pointer is also the call argument, while the w clear goes through the
 * array as a frame slot, as retail does. */
#include "common.h"

typedef __attribute__((mode(TI))) int QI_002ACDE8;

extern void func_00282D30(void *, void *, float);
extern void func_002837D0(void *, void *, void *);

/* Rotates a vector by a quaternion and stores the result. */
void func_002ACDE8(void *result, void *vector, void *quat)
{
    QI_002ACDE8 quats[3];

    FastVecScale(&quats[0], quat, -1.0f);
    *(float *)((char *)&quats[0] + 0xC) = *(float *)((char *)quat + 0xC);
    qcopy(&quats[1], vector);
    ((int *)quats)[7] = 0;
    multiply_quaternions(&quats[2], quat, &quats[1]);
    multiply_quaternions(result, &quats[2], &quats[0]);
}
