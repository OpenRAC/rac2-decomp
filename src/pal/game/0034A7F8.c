#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;

void func_PAL_0034A7F8(u8 *a0, s32 a1, s32 a2) { a0 += a1 * 4; *(s32 *)(a0 + 0x488) = a2; }

extern int func_00288FB8_2(int a);
extern void func_L00_0042C360_1(char *a, int b);

/* stores the count in a field, then loops count times calling one helper on each successive 72-byte slot and passing the result to a second helper. */
void func_PAL_0034A808(char *a0, int a1, int *a2)
{
    int i;

    *(int *)(a0 + 1204) = a1;
    for (i = 0; i < a1; i++)
        func_L00_0042C360_1(a0 + 536 + i * 88, func_00288FB8_2(a2[i]));
}

INCLUDE_ASM("asm/pal/game", func_PAL_0034A870);



INCLUDE_ASM("asm/pal/game", func_PAL_0034B088);
