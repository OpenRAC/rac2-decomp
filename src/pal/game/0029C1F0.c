#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_0034E4B8(void *);

void func_PAL_0029C1F0(void) {
    if (D_001A8CFC[0] != 0)
        func_0034E4B8(D_001A8CFC[0] + 0x36F28);
}

extern int D_L00_001A904C_6 __attribute__((sda));
extern void func_003380B0(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void func_PAL_0029C220(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        func_003380B0((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

INCLUDE_ASM("asm/pal/game", func_PAL_0029C7F0);

INCLUDE_ASM("asm/pal/game", func_PAL_0029C820);

INCLUDE_ASM("asm/pal/game", func_PAL_0029C8A0);
