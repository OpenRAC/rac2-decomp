#include "include_asm.h"
#include "names.h"
#include "double_parts.h"

typedef int s32;

typedef unsigned int u32;

/* Construct a double through the original runtime packing routine. */
typedef DoubleParts DoubleParts44;

extern double func_00122630(DoubleParts44 *);

/* Builds a double from a kind, sign, exponent and fraction. */
double func_00123268(s32 kind, u32 sign, s32 exponent, unsigned long long fraction)
{
    DoubleParts44 parts;
    parts.kind = kind;
    parts.sign = sign;
    parts.exponent = exponent;
    parts.fraction.ll = fraction;
    return PackDouble(&parts);
}

extern void func_00122760(double *, DoubleParts44 *);
extern float func_001234C0(s32, u32, s32, u32);

/* Converts a double to a float using software math. */
float func_00123298(double value) {
    DoubleParts44 parts;
    int fraction;
    UnpackDouble(&value, &parts);
    fraction = (int)(parts.fraction.ll >> 30);
    if ((parts.fraction.ll & 0x3FFFFFFF) != 0)
        fraction |= 1;
    return BuildFloatFromParts(parts.kind, parts.sign, parts.exponent, fraction);
}

