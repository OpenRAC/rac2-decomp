#include "include_asm.h"
#include "names.h"
#include "double_parts.h"

typedef int s32;

typedef unsigned int u32;

/* Construct a double through the original runtime packing routine. */
typedef DoubleParts DoubleParts44;

extern double fp_pack_double(DoubleParts44 *);

/* Builds a double from a kind, sign, exponent and fraction. */
double fp_build_double_from_parts(s32 kind, u32 sign, s32 exponent, unsigned long long fraction)
{
    DoubleParts44 parts;
    parts.kind = kind;
    parts.sign = sign;
    parts.exponent = exponent;
    parts.fraction.ll = fraction;
    return fp_pack_double(&parts);
}

extern void fp_unpack_double(double *, DoubleParts44 *);
extern float fp_build_float_from_parts(s32, u32, s32, u32);

/* Converts a double to a float using software math. */
float __truncdfsf2(double value) {
    DoubleParts44 parts;
    int fraction;
    fp_unpack_double(&value, &parts);
    fraction = (int)(parts.fraction.ll >> 30);
    if ((parts.fraction.ll & 0x3FFFFFFF) != 0)
        fraction |= 1;
    return fp_build_float_from_parts(parts.kind, parts.sign, parts.exponent, fraction);
}

