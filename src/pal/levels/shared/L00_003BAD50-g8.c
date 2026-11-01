#include "include_asm.h"

#include "common.h"
extern float D_L00_001AFA40 __attribute__((sda));

void func_PAL_L00_003BAD50(float x, float y, float unused_step, float *p, float *q)
{
    float s = -(D_L00_001AFA40 * 0.00040000002f) / (x * x + y * y);

    *p = *p + x * s;
    *q = *q + y * s;
}
