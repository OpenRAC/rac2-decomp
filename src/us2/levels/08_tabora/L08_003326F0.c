#include "include_asm.h"
#include "names.h"

/* func_US2_L08_003326F0, the USA v2.00 copy of func_002AEB60: the same C, where the 0x4C field becomes 0.5f. */
extern float moby_get_anim_value(void *);
extern float math_round_to_decimal_places(int, float);

/* Tells whether the animation value has reached the threshold but is still within half a step of it (USA v2.00). */
int math_is_value_within_half_step_us2(char *object, float threshold)
{
    float current = math_round_to_decimal_places(4, moby_get_anim_value(object));
    float difference = current - threshold;
    float step = math_round_to_decimal_places(4, *(float *)(object + 0x48) * 0.5f);
    if (threshold <= current)
        return difference < step;
    return 0;
}
