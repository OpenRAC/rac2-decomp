#include "common.h"

/* The single on-screen notice slot: D_001A8C64 is its owner (0 = free), D_001B1D48 the text id.
 * A global that is both read and written here is reached under two names (the `_1` alias for the
 * write), as retail keeps a separate absolute address for each access. D_001A8C60 is stored both
 * $gp-relative and absolutely, so its `_1` name is the $gp view. */
extern int D_001A8C64 MACRO_ADDR;
extern int D_001A8C64_1 MACRO_ADDR;
extern int D_001A8C60 MACRO_ADDR;
extern int D_001A8C60_1 __attribute__((sda));
extern int D_001B1D48 MACRO_ADDR;
extern int D_001B1D48_1 MACRO_ADDR;
extern int func_00288FB8(int);
extern void func_0029CCD8(int, int);

int func_002B0C28(int a0, int a1, int a2)
{
    int current = D_001A8C64;

    if (current == a0) {
        if (a1 != 0)
            func_0029CCD8(func_00288FB8(a1), a2);
        D_001B1D48 = a1;
        D_001A8C60_1 = 2;
        return 2;
    }
    if (current == 0) {
        if (a1 != 0)
            func_0029CCD8(func_00288FB8(a1), a2);
        D_001A8C64_1 = a0;
        D_001A8C60 = 2;
        D_001B1D48_1 = a1;
        return 1;
    }
    return 0;
}

int func_002B0CE0(int a0, int a1, int a2)
{
    int result = func_002B0C28(a0, a1, a2);

    if (result == 0) {
        if (a1 != 0) {
            func_0029CCD8(func_00288FB8(a1), a2);
            D_001A8C60 = a2;
            result = 3;
        } else {
            D_001A8C60_1 = a2;
            result = 3;
        }
        D_001A8C64_1 = a0;
        D_001B1D48_1 = a1;
    }
    return result;
}
