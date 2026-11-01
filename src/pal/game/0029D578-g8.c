#include "include_asm.h"
extern char *D_001A8CFC;
extern int func_PAL_00341C18(void *, int);

int func_PAL_0029D578(int value) {
    if (D_001A8CFC != 0)
        return func_PAL_00341C18(D_001A8CFC + 0x3A570, value);
    return 0;
}
