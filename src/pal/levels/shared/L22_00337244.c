#include "include_asm.h"

#include "common.h"
extern void func_002B9180(char *);
extern s32 func_00282948(void *);
extern void func_00300190(char *, char *);

void func_PAL_L22_00337244(u8 *a0)
{
    u8 *s0 = a0;
    u8 *s1 = a0 + 0x20;

    if (func_00282948((char *)s1) != 0) {
        func_002B9180((char *)s0);
        return;
    }
    {
        u8 *p = s0 + 0x10;

        func_00300190((char *)p, (char *)p);
    }
    *(f32 *)(s0 + 0xC) = *(f32 *)(s0 + 0xC) + *(f32 *)(s1 + 4);
    if (*(s32 *)(s1) < 5) {
        *(unsigned int *)(s0 + 4) = (*(unsigned int *)(s0 + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(s1) * 127 / 5) << 24);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L22_0033BBB0);
