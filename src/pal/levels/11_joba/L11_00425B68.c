#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_00425B68);

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_00429B30);

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_0042A858);

typedef unsigned short u16;
extern void func_PAL_002AC3C0(char *object, char *p);
extern void func_00282978(char *p);
extern void func_002AEC48(char *object, char *p, int kind, float f12, float f13);
extern void func_PAL_002B14F8(char *object, char *p, int kind, int a3, float f12);

/* re-arms the object's two guard nodes and restarts its measurement window */
void func_PAL_L11_0042AB20(char *object)
{
    char *p = *(char **)(object + 0x68);

    func_PAL_002AC3C0(object, p + 0x50);
    func_00282978(p + 0x260);
    func_00282978(p + 0x26);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    func_002AEC48(object, p + 0x2A0, 4, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(object, p + 0x2A0, 4, 1, 3.5f);
}

