#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003A7720);

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003C5A84);

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003C70B8);

extern int func_419B10(void *, void *, int, void *, void *, void *, float, float);
extern void func_32D0F0(void *, int, float);
float func_L03_003C5AB8(unsigned char *);

int func_PAL_L03_003C81C8(unsigned char *a0, int a1, int a2) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float f = 0.0f;
    float out;
    int r;

    if (a2 != 0)
        f = func_L03_003C5AB8(a0);
    r = func_419B10(*(void **)(s0 + 0x220), a0 + 0x10, a1, &out, s0 + 0x368, s0 + 0x36C, f,
                    *(float *)(s0 + 0x110));
    func_32D0F0(a0, a1, out);
    return r;
}




