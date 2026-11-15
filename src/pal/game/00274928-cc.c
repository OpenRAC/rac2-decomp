#include "names.h"
/* func_PAL_00274928, the PAL copy of func_00274A88: the same C. */
/* func_PAL_00274928 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */

typedef int TI128_00274A88 __attribute__((mode(TI)));

extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_b(float);
extern void vec_set_direction_with_complement(float *, float *, float);
extern void multiply_quaternions(void *, void *, void *);

void func_PAL_00274928(void *unused, float *output, const TI128_00274A88 *input)
{
    TI128_00274A88 vector;
    float halfLength;
    float lowLimit;
    float highLimit;

    vector = *input;
    halfLength = FastVecLength(&vector) * 0.5f;
    lowLimit = math_fast_sin_or_cos_b(0.015707966f);
    highLimit = math_fast_sin_or_cos_b(0.031415932f);
    if (lowLimit < halfLength)
        halfLength = lowLimit;
    vec_set_direction_with_complement((float *)&vector, (float *)&vector, halfLength);
    multiply_quaternions(output, output, &vector);
    if (highLimit < FastVecLength(output))
        vec_set_direction_with_complement(output, output, highLimit);
}
