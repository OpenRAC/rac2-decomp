#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_0034E4B8(void *);

void func_US2_0029C648(void) {
    if (D_001A8CFC[0] != 0)
        func_0034E4B8(D_001A8CFC[0] + 0x36F28);
}

extern int D_L00_001A904C_6 __attribute__((sda));
extern void func_003380B0(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void func_US2_0029C678(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        func_003380B0((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

INCLUDE_ASM("asm/us2/game", func_US2_0029C700);



INCLUDE_ASM("asm/us2/game", func_US2_0029CA88);


INCLUDE_ASM("asm/us2/game", func_US2_0029CC48);

INCLUDE_ASM("asm/us2/game", func_US2_0029CCB8);

INCLUDE_ASM("asm/us2/game", func_US2_0029CD18);


extern void func_US2_0034F1C0(void *);

void func_US2_0029CF10(void) {
    if (D_001A8CFC[0] != 0)
        func_US2_0034F1C0(D_001A8CFC[0] + 0x36F28);
}


extern void func_US2_0034F240(void *);

void func_US2_0029CF40(void) {
    if (D_001A8CFC[0] != 0)
        func_US2_0034F240(D_001A8CFC[0] + 0x36F28);
}


extern void func_US2_00349C00(void *);

void func_US2_0029CF70(void) {
    if (D_001A8CFC[0] != 0)
        func_US2_00349C00(D_001A8CFC[0] + 0x39160);
}



extern void func_US2_00348628(void *);

void func_US2_0029CFE0(void) {
    if (D_001A8CFC[0] != 0)
        func_US2_00348628(D_001A8CFC[0] + 0x39620);
}


extern void func_US2_00347550(void *);

void func_US2_0029D010(void) {
    if (D_001A8CFC[0] != 0)
        func_US2_00347550(D_001A8CFC[0] + 0x39AF0);
}


