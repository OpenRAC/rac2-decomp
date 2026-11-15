#include "names.h"
extern void func_L00_00310D30(unsigned char *, unsigned char *);

/* Sets up an animation state from a source animation and optionally advances it right away. */
void func_L00_00311080(unsigned char *source, unsigned char *state, int valueA, int valueB, int frameCount, int advanceNow)
{
    state[0x22] = source[0x43];
    state[0x20] = source[0x41];
    state[0x23] = valueA;
    state[0x21] = valueB;
    *(int *)(state + 0x24) = 0;
    *(float *)(state + 0x28) = 1.0f;
    *(float *)(state + 0x2C) = 1.0f / (float)frameCount;
    if (advanceNow != 0)
        AdvanceAndDecodeAnimationFrames(source, state);
}
