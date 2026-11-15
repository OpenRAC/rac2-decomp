#include "include_asm.h"
#include "names.h"

/* func_US2_002AF9C8, the USA v2.00 copy of func_002AEB60: the same C, where the 0x4C field becomes 0.5f. */
extern float moby_get_anim_value(void *);
extern float math_round_to_decimal_places(int, float);

int func_US2_002AF9C8(char *object, float threshold)
{
    float current = math_round_to_decimal_places(4, moby_get_anim_value(object));
    float difference = current - threshold;
    float step = math_round_to_decimal_places(4, *(float *)(object + 0x48) * 0.5f);
    if (threshold <= current)
        return difference < step;
    return 0;
}
