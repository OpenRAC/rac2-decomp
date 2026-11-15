#include "names.h"
extern float func_00283CE0(int value);
extern int func_00283CF0(float value);
/* Rounds a number up to the next multiple of 16. */
int func_L00_003DB0A8(int value)
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
