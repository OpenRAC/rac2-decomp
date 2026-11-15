#include "include_asm.h"
#include "names.h"

/* func_US2_003377B0, the v2.00 relative of func_003369A8: the same C, with the fields 0x48-0x54 added. */

extern void object_alloc_float4_arrays(void *);
extern unsigned char D_00263B50[];

void func_US2_003377B0(char *self)
{
    object_alloc_float4_arrays(self);
    *(char **)(self + 0x34) = (char *)D_00263B50;
    *(long long *)(self + 0x38) = 1;
    *(int *)(self + 0x40) = 0;
    **(float **)(self + 4) = 1.0f;
    (*(float **)(self + 4))[1] = 1.0f;
    *(int *)(self + 0x44) = 1;
    *(int *)(self + 0x48) = 0;
    *(int *)(self + 0x4C) = 0x200;
    *(float *)(self + 0x50) = 0.7f;
    *(int *)(self + 0x54) = 1;
}
