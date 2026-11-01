#include "include_asm.h"

typedef signed int s32;
typedef unsigned long long u64;
extern s32 func_L23_00419CA0(s32 arg0);
extern s32 func_L23_00419070(u64, s32);
extern float func_00282C48(float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern s32 D_L23_001B3744 __attribute__((sda));
extern s32 D_L23_001B3738[3] __attribute__((sda));
extern s32 D_L23_00259050[3][60];
extern s32 D_L23_001B3744 __attribute__((sda));
extern s32 D_L23_001B3738[3] __attribute__((sda));
extern s32 D_L23_001B1FA0[4];
extern s32 D_L23_00259050[3][60];

/* Springs the second measure toward its target, doubles the word at +0x74, and latches the
 * measure once it is within a tenth of the target. */
void func_PAL_L23_004206A8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(s32 *)(state + 0x5D8) != 0)
        return;
    func_002AA548((float *)(state + 0x588), (float *)(state + 0x58C), *(float *)(state + 0x5D4),
                  0.024f, 0.024f, 0.49000004f);
    *(float *)(state + 0x74) *= 2.0f;
    if (func_00282C48(*(float *)(state + 0x588) - *(float *)(state + 0x5D4)) < 0.1f) {
        *(s32 *)(state + 0x5D8) = 1;
        *(s32 *)(state + 0x58C) = 0;
    }
}

