#include "include_asm.h"

/* func_US2_L08_003326F0, the USA v2.00 copy of func_002AEB60: the same C, where the 0x4C field becomes 0.5f. */
extern float func_0029F530(void *);
extern float func_002AEAE0(int, float);

int func_US2_L08_003326F0(char *object, float threshold)
{
    float current = func_002AEAE0(4, func_0029F530(object));
    float difference = current - threshold;
    float step = func_002AEAE0(4, *(float *)(object + 0x48) * 0.5f);
    if (threshold <= current)
        return difference < step;
    return 0;
}
