#include "include_asm.h"
#include "common.h"

extern float func_L08_00425328(void *position, float first, float second, float floor);
extern int func_00278E78(void);
extern float D_00189EA8;

void func_L08_00425398(char *a0)
{
    float aim[4] __attribute__((aligned(16)));
    char *q = *(char **)(a0 + 0x68);

    qcopy(aim, a0 + 0x10);
    aim[2] = aim[2] + 20.0f;
    *(float *)(q + 0x1C4) = func_L08_00425328(aim, *(float *)(q + 0x178) + 10.0f, *(float *)(q + 0x178) - 3.0f, *(float *)(q + 0x90));
    if (GetCollHitMaterial() == 0)
        *(float *)(q + 0x1C4) = *(float *)(q + 0x1C4) + 2.0f;
    {
        float v = *(float *)(q + 0x1C4) + 6.5f;
        *(float *)(q + 0x1C8) = v > D_00189EA8 ? v : D_00189EA8;
    }
}
