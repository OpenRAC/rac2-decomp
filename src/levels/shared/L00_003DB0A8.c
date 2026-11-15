#include "names.h"
extern float IntToFloat(int value);
extern int FloatToInt(float value);
/* Rounds a number up to the next multiple of 16. */
int mem_round_up_16(int value)
{
    int alignment = 16;
    if (value % alignment != 0)
        {
        float quotient = IntToFloat(value);
        quotient = quotient / (float)alignment;
        value = (FloatToInt(quotient) + 1) * alignment;
    }
    return value;
}
