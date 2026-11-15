#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef int s32;
extern char g_sound_state[];
extern int PlayMobySound(int, int, char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);

void func_PAL_L02_00406558(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);
    char *e = g_sound_state + *(s32 *)(s0 + 0x16C) * 0x70;
    float f;

    if (*(char **)(e + 0x88) != a0 || *(u8 *)(e + 0x74) == 0)
        *(s32 *)(s0 + 0x16C) = PlayMobySound(1, 4, a0);
    *(TI128 *)(a0 + 0x10) = *(TI128 *)(s0 + 0x120);
    *(TI128 *)(a0 + 0xF0) = *(TI128 *)(s0 + 0x130);
    f = FastAddRotations(*(float *)(s0 + 0x148), 0.010471977f);
    *(float *)(s0 + 0x148) = f;
    *(float *)(a0 + 0xF0) += math_fast_sin_or_cos_b(f) * 0.05f;
    f = FastAddRotations(*(float *)(s0 + 0x144), 0.017453294f);
    *(float *)(s0 + 0x144) = f;
    *(float *)(a0 + 0xF4) += math_fast_sin_or_cos_b(f) * 0.05f;
    f = FastAddRotations(*(float *)(s0 + 0x140), 0.024434613f);
    *(float *)(s0 + 0x140) = f;
    *(float *)(a0 + 0x18) += math_fast_sin_or_cos_b(f) * 0.25f;
}
