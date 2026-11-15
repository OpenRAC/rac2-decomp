/* func_00274A88 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int TI128_00274A88 __attribute__((mode(TI)));

extern float func_00282DF0(void *);
extern float func_00283198(float);
extern void func_002ACE78(float *, float *, float);
extern void func_002837D0(void *, void *, void *);

/* Limits how far a movement vector can push, clamping its length to small angle-based limits. */
void func_00274A88(void *unused, float *output, const TI128_00274A88 *input)
{
    TI128_00274A88 vector;
    float halfLength;
    float lowLimit;
    float highLimit;

    vector = *input;
    halfLength = FastVecLength(&vector) * 0.5f;
    lowLimit = FastSinOrCosB(0.013089971616864204f);
    highLimit = FastSinOrCosB(0.02617994323372841f);
    if (lowLimit < halfLength)
        halfLength = lowLimit;
    SetDirectionWithComplement((float *)&vector, (float *)&vector, halfLength);
    multiply_quaternions(output, output, &vector);
    if (highLimit < FastVecLength(output))
        SetDirectionWithComplement(output, output, highLimit);
}
