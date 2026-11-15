#include "include_asm.h"
#include "names.h"

extern void anim_start_blended(void *, int, int, int);

void func_PAL_L04_003E9100(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);

    if (*(char **)(s0 + 0x2AC) != 0) {
        anim_start_blended(*(char **)(s0 + 0x2AC), 9, 0, 2);
        *(int *)(*(char **)(*(char **)(s0 + 0x2AC) + 0x68) + 0x27C) = 0;
        *(char **)(s0 + 0x2AC) = 0;
    }
}

