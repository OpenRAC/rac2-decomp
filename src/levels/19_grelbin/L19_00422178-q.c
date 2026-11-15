#include "include_asm.h"
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

/* Picks a random spot around the object. The farthest distance depends on the object's size. The result is written to the second argument. */
void func_L19_00422178(u8 *moby, float *outPos)
{
    float distance = RandomFloatRange(0.0f, (*(float *)(moby + 0x2C) / *(float *)(*(u8 **)(moby + 0x24) + 0x24)) * 6.0f);
    float angle = RandomFloatRange(-3.14159274f, 3.14159274f);

    *(TI128 *)outPos = *(TI128 *)(moby + 0x10);
    outPos[0] = outPos[0] + distance * FastSinOrCosA(angle);
    outPos[1] = outPos[1] + distance * FastSinOrCosB(angle);
}
