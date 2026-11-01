#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_0045D908);

#include "common.h"
extern void *func_0029EFD0(int id);
extern float func_00283248(float x, float y);
extern float func_00282E20(char *a);
extern int D_L06_001B3760[];
extern int D_L06_001B3778[];

/* The func_L09_003A06B0 spawn for the level-06 slots: marks slot `index` busy, records it
   in the child's state and clears its handle. */
char *func_PAL_L06_0045DF30(char *object, char *a1, char *a2, int index, float f12)
{
    char *s1 = func_0029EFD0(0xFE5);
    char *s0;
    float d;

    if (s1 != 0) {
        *(u8 *)(s1 + 0x30) = 0xFF;
        *(u16 *)(s1 + 0x32) = 0xFF;
        *(u8 *)(s1 + 0x31) = 1;
        *(u8 *)(s1 + 0x20) = 0;
        *(u64 *)(s1 + 0x38) = *(u64 *)(object + 0x38);
        qcopy(s1 + 0x10, a2);
        D_L06_001B3760[index] = 1;
        s0 = *(char **)(s1 + 0x68);
        qcopy(s0, a1);
        *(u32 *)(s0 + 0x38) = 0xC8;
        *(char **)(s0 + 0x3C) = object;
        *(float *)(s0 + 0x40) = f12;
        *(int *)(s0 + 0x48) = index;
        *(int *)(s0 + 0x4C) = -1;
        *(float *)(s1 + 0xF8) = func_00283248(*(float *)a1, *(float *)(a1 + 4));
        d = func_00282E20(a1);
        *(float *)(s1 + 0xF4) = -func_00283248(d, *(float *)(a1 + 8));
        D_L06_001B3778[index] = -1;
    }
    return s1;
}

