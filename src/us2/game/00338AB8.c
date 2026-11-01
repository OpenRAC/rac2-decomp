#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_00338AB8);

INCLUDE_ASM("asm/us2/game", func_US2_00338CD8);

INCLUDE_ASM("asm/us2/game", func_US2_00338D48);

extern void func_00115AC0(void *, int, int);
extern void func_US2_00338D48(void *, int, int, float, float);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 360, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_US2_00338F18(int object, int value, int count)
{
    int limit = (count == -1) ? 360 : count;
    int inner = object + 8156;

    func_00115AC0((void *)(object + 8324), value, 255);
    func_US2_00338D48((void *)inner, 2, limit, 255.0f, 80.0f);
}


INCLUDE_ASM("asm/us2/game", func_US2_00338F80);

INCLUDE_ASM("asm/us2/game", func_US2_00338F88);

INCLUDE_ASM("asm/us2/game", func_US2_00339398);

INCLUDE_ASM("asm/us2/game", func_US2_003395F0);

/* clamps a caller-supplied terminator value (-1 meaning unset) to 180, then runs two callees on two sub-objects of one handle, the second with a float pair */
void func_US2_00339678(int object, int value, int count)
{
    int limit = (count == -1) ? 180 : count;
    int inner = object + 7564;

    func_00115AC0((void *)(object + 7732), value, 254);
    func_US2_00338D48((void *)inner, 2, limit, 255.0f, 123.0f);
}

