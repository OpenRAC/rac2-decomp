#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void func_0033F030(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F308(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0033F030(value + 0x3BB08);
}

extern int func_PAL_00340A50(char *, int);

/* func_PAL_L00_0030F338, the PAL copy of func_L00_0030D4E8: the same C, where the object offset
 * 0x3B7C0 becomes 0x3BB08. */
int func_PAL_L00_0030F338(int a0)
{
    int v = D_L00_001A904C_2;

    if (v != 0) {
        return func_PAL_00340A50((char *)v + 0x3BB08, a0);
    }
    return 0;
}

extern void func_00345358(int);

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void func_PAL_L00_0030F378(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_00345358(value + 0x3A0B0);
}

