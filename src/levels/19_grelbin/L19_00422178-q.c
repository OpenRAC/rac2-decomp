#include "include_asm.h"
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Picks a random spot around the object. The farthest distance depends on the object's size. The result is written to the second argument. */
void moby_pick_random_point_around(u8 *moby, float *outPos)
{
    float distance = math_random_float_range(0.0f, (*(float *)(moby + 0x2C) / *(float *)(*(u8 **)(moby + 0x24) + 0x24)) * 6.0f);
    float angle = math_random_float_range(-3.14159274f, 3.14159274f);

    *(TI128 *)outPos = *(TI128 *)(moby + 0x10);
    outPos[0] = outPos[0] + distance * math_fast_sin_or_cos_a(angle);
    outPos[1] = outPos[1] + distance * math_fast_sin_or_cos_b(angle);
}
