#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002CE9BC);

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_PAL_003435D0(void *, int);
extern void func_PAL_003435C0(char *, char *, char *, char *);
extern void func_PAL_00343690(char *, int);
extern char D_002615F8[];
extern char D_00261698[];
extern char D_00261750[];
extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));

int func_PAL_002CEA20(void)
{
    if (D_001A8CFC[0] != 0) {
        func_PAL_003435D0(D_001A8CFC[0] + 0x3C210, 1);
        func_PAL_003435C0(D_001A8CFC[0] + 0x3C210, D_002615F8, D_00261698, D_00261750);
        func_PAL_00343690(D_001A8CFC[0] + 0x3C210, 0);
    }
    return 0;
}

