#include "include_asm.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern void func_L00_00443E18(int);

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_PAL_L00_0030F000(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_L00_00443E18(value + 0x36F28);
}

extern void func_0034E4F8(int);

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_PAL_L00_0030F030(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_0034E4F8(value + 0x36F28);
}

extern void func_PAL_0034B088(int);

/* func_PAL_L00_0030F060, the PAL copy of func_L00_0030D210: the same C, where the offset becomes 0x39160 and the handler func_PAL_0034B088. */
void func_PAL_L00_0030F060(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        func_PAL_0034B088(value + 0x39160);
}

extern int func_PAL_0034ABB0(int, int);

/* func_PAL_L00_0030F090, the PAL copy of func_L00_0030D240: the same C, where the offset becomes 0x39160 and the handler func_PAL_0034ABB0. */
int func_PAL_L00_0030F090(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_PAL_0034ABB0(value + 0x39160, argument);
    return 0;
}
