#include "include_asm.h"

extern void *D_00133E74;

extern void *D_0013A308;

void *func_00115200(void)
{
    return D_00133E74;
}

void **func_00115210(void)
{
    return &D_0013A308;
}


ASM_FUNC("asm/core", func_00115250);

ASM_FUNC("asm/core", func_00115340);

ASM_FUNC("asm/core", func_001153D4);

ASM_FUNC("asm/core", func_00115484);

ASM_FUNC("asm/core", func_00115544);

ASM_FUNC("asm/core", func_00115690);

ASM_FUNC("asm/core", func_001157AC);

/* Newlib's original r5900/strncmp.S, Cygnus Solutions (1999), from the
 * public SSXModding/ps2-ee-toolchain snapshot b595ded. Its complete MMI
 * body assembles byte-identically in all three releases; it is not C. */
ASM_FUNC("asm/core", func_001158F4);

ASM_FUNC("asm/core", func_00115AC0);


INCLUDE_ASM("asm/core", func_00115E28);


extern int D_001341E0;

extern int D_001341E4;

extern int D_00134DB8;

extern int func_0011AB10(void);

extern void func_0011AC60(int arg0);

int func_00116300(void) {
    int id = func_0011AB10();

    if (D_001341E0 != id) {
        func_0011AC60(D_00134DB8);
        D_001341E0 = id;
        return ++D_001341E4;
    }
    return ++D_001341E4;
}

void func_001163A0(unsigned int value)
{
    *(unsigned int *)((unsigned char *)D_00133E74 + 0x58) = value;
}
