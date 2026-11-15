/* func_002ACDE8: the three quaternions are one frame array; the copy is qcopy(), whose
 * destination pointer is also the call argument, while the w clear goes through the
 * array as a frame slot, as retail does. */
#include "common.h"

typedef __attribute__((mode(TI))) int QI_002ACDE8;

extern void func_00282D30(void *, void *, float);
extern void func_002837D0(void *, void *, void *);

void func_002ACDE8(void *a0, void *a1, void *a2)
{
    QI_002ACDE8 m[3];

    FastVecScale(&m[0], a2, -1.0f);
    *(float *)((char *)&m[0] + 0xC) = *(float *)((char *)a2 + 0xC);
    qcopy(&m[1], a1);
    ((int *)m)[7] = 0;
    multiply_quaternions(&m[2], a2, &m[1]);
    multiply_quaternions(a0, &m[2], &m[0]);
}
