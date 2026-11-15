#include "include_asm.h"

#include "common.h"
extern void part_kill(char *);
extern s32 math_fast_float_d(void *);
extern void vec_transform_or_copy(char *, char *);

void func_PAL_L22_00337244(u8 *a0)
{
    u8 *s0 = a0;
    u8 *s1 = a0 + 0x20;

    if (math_fast_float_d((char *)s1) != 0) {
        part_kill((char *)s0);
        return;
    }
    {
        u8 *p = s0 + 0x10;

        vec_transform_or_copy((char *)p, (char *)p);
    }
    *(f32 *)(s0 + 0xC) = *(f32 *)(s0 + 0xC) + *(f32 *)(s1 + 4);
    if (*(s32 *)(s1) < 5) {
        *(unsigned int *)(s0 + 4) = (*(unsigned int *)(s0 + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(s1) * 127 / 5) << 24);
    }
}


