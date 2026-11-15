/* func_00274A88 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"

typedef int TI128_00274A88 __attribute__((mode(TI)));

extern float func_00282DF0(void *);
extern float func_00283198(float);
extern void func_002ACE78(float *, float *, float);
extern void func_002837D0(void *, void *, void *);

/* Clamps the length of an input vector between two limits and writes the resulting vector to output. */
void func_00274A88(void *unused, float *output, const TI128_00274A88 *input)
{
    TI128_00274A88 vector;
    float halfLength;
    float lowLimit;
    float highLimit;

    vector = *input;
    halfLength = func_00282DF0(&vector) * 0.5f;
    lowLimit = func_00283198(0.013089971616864204f);
    highLimit = func_00283198(0.02617994323372841f);
    if (lowLimit < halfLength)
        halfLength = lowLimit;
    func_002ACE78((float *)&vector, (float *)&vector, halfLength);
    func_002837D0(output, output, &vector);
    if (highLimit < func_00282DF0(output))
        func_002ACE78(output, output, highLimit);
}
