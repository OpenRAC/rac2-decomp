#include "include_asm.h"
#include "names.h"

extern struct {
    char pad[0x1C0];
    float one;
    float reciprocal;
    int mode;
} D_001F2840;

/* Stores 1.0 and the inverse of the given value in the pause state block and clears its mode. */
void func_002C9C60(float value)
{
    float inverse = 1.0f / value;
    gPauseMenuState.one = 1.0f;
    gPauseMenuState.reciprocal = inverse;
    gPauseMenuState.mode = 0;
}
