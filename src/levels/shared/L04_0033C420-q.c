#include "include_asm.h"
#include "common.h"

extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);
typedef struct { int pad[6]; int f18; int f1C; } L04Flags;
extern L04Flags ref_L04_0033C420_00;

int func_L04_0033C420(void *a0, void *a1, int a2, float f12, float f13)
{
    float v1[4];
    float v2[4];
    int r;

    qcopy(v1, a0);
    v1[2] += f12;
    qcopy(v2, a0);
    v2[2] -= f13;
    if (v2[2] < 0.0f)
        v2[2] = 0.0f;
    r = CollLine(v1, v2, 0x22, a1, 0);
    if (ref_L04_0033C420_00.f1C <= -1)
        r = 0;
    if (a2 != 0 && ref_L04_0033C420_00.f18 != 0)
        r = 0;
    return r;
}
