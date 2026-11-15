#include "names.h"
/* func_PAL_002AF6C0, the PAL copy of func_002AEB60: the same C, where the field at 0x4C becomes 0.6f. */

extern float moby_get_anim_value(void *);
extern float math_round_to_decimal_places(int, float);

int func_PAL_002AF6C0(char *object, float threshold)
{
    float current = math_round_to_decimal_places(4, moby_get_anim_value(object));
    float difference = current - threshold;
    float step = math_round_to_decimal_places(4, *(float *)(object + 0x48) * 0.6f);
    if (threshold <= current)
        return difference < step;
    return 0;
}
