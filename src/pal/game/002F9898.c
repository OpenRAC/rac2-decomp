#include "include_asm.h"
#include "common.h"



INCLUDE_ASM("asm/pal/game", func_PAL_002FA330);

INCLUDE_ASM("asm/pal/game", func_PAL_002FA720);

/* func_PAL_002FAB40, the PAL copy of func_002F9BC0: the same C, with the thousands separator
   chosen by the language byte D_PAL_001A7C3C ('.' for 3, 4 and 5, ' ' for 2, ',' elsewhere). */
extern int func_00115DA8_1(char *, char *, ...);
extern unsigned char D_PAL_001A7C3C MACRO_ADDR;
extern char D_PAL_001AD470[];
extern char D_PAL_001AD480[];
extern char D_L00_001AD6B0[];
extern char D_PAL_001AD4A0[];
extern char D_PAL_001AD4A8[];
extern char D_L00_001AD6C0[];
extern char D_L00_001AD6C8[];

void func_PAL_002FAB40(char *dst, int value)
{
    if (value > 999999) {
        if (D_PAL_001A7C3C == 3 || D_PAL_001A7C3C == 5 || D_PAL_001A7C3C == 4)
            func_00115DA8_1(dst, D_PAL_001AD470, value / 1000000, (value / 1000) % 1000, value % 1000);
        else if (D_PAL_001A7C3C == 2)
            func_00115DA8_1(dst, D_PAL_001AD480, value / 1000000, (value / 1000) % 1000, value % 1000);
        else
            func_00115DA8_1(dst, D_L00_001AD6B0, value / 1000000, (value / 1000) % 1000, value % 1000);
    } else if (value >= 1000) {
        if (D_PAL_001A7C3C == 3 || D_PAL_001A7C3C == 5 || D_PAL_001A7C3C == 4)
            func_00115DA8_1(dst, D_PAL_001AD4A0, value / 1000, value % 1000);
        else if (D_PAL_001A7C3C == 2)
            func_00115DA8_1(dst, D_PAL_001AD4A8, value / 1000, value % 1000);
        else
            func_00115DA8_1(dst, D_L00_001AD6C0, value / 1000, value % 1000);
    } else
        func_00115DA8_1(dst, D_L00_001AD6C8, value);
}
