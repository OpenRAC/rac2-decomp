#include "names.h"
/* func_00274A88 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int TI128_00274A88 __attribute__((mode(TI)));

extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_b(float);
extern void vec_set_direction_with_complement(float *, float *, float);
extern void multiply_quaternions(void *, void *, void *);

/* Limits how far a movement vector can push, clamping its length to small angle-based limits. */
void coll_clamp_movement_vector(void *unused, float *output, const TI128_00274A88 *input)
{
    TI128_00274A88 vector;
    float halfLength;
    float lowLimit;
    float highLimit;

    vector = *input;
    halfLength = FastVecLength(&vector) * 0.5f;
    lowLimit = math_fast_sin_or_cos_b(0.013089971616864204f);
    highLimit = math_fast_sin_or_cos_b(0.02617994323372841f);
    if (lowLimit < halfLength)
        halfLength = lowLimit;
    vec_set_direction_with_complement((float *)&vector, (float *)&vector, halfLength);
    multiply_quaternions(output, output, &vector);
    if (highLimit < FastVecLength(output))
        vec_set_direction_with_complement(output, output, highLimit);
}
