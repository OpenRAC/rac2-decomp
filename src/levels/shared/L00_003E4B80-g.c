#include "include_asm.h"
#include "names.h"

extern float func_00283CE0(int);
extern int func_00283CF0(float);

/* Adjust a non-aligned count through the integer/float conversion helpers. */
/* Rounds a size up to the next multiple of 16. */
int func_L00_003E4B80(int n)
{
    int alignment;
    int blocks;
    int result;
    float sizeFloat;
    float alignmentFloat;

    alignment = 16;
    result = n;
    if (n % alignment != 0) {
        sizeFloat = IntToFloat(n);
        alignmentFloat = (float)alignment;
        blocks = FloatToInt(sizeFloat / alignmentFloat);
        result = (blocks + 1) * alignment;
    }
    return result;
}
