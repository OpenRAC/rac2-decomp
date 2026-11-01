#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_00339968);

INCLUDE_ASM("asm/pal/game", func_PAL_00339B88);

INCLUDE_ASM("asm/pal/game", func_PAL_00339BF8);

extern void func_00115AC0(void *, int, int);
extern void func_PAL_00339BF8(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_PAL_00339DC8(int object, int value, int count)
{
    int limit = (count == -1) ? 300 : count;
    int inner = object + 8156;

    func_00115AC0((void *)(object + 8324), value, 255);
    func_PAL_00339BF8((void *)inner, 2, limit, 255.0f, 80.0f);
}


INCLUDE_ASM("asm/pal/game", func_PAL_00339E30);

INCLUDE_ASM("asm/pal/game", func_PAL_00339E38);

INCLUDE_ASM("asm/pal/game", func_PAL_0033A248);

INCLUDE_ASM("asm/pal/game", func_PAL_0033A4A0);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_PAL_0033A528(int object, int value, int count)
{
    int limit = (count == -1) ? 150 : count;
    int inner = object + 7564;

    func_00115AC0((void *)(object + 7732), value, 254);
    func_PAL_00339BF8((void *)inner, 2, limit, 255.0f, 123.0f);
}

