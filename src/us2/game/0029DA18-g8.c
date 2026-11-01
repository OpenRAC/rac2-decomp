#include "include_asm.h"
extern char *D_001A8CFC;
extern int func_US2_00340AA8(void *, int);

int func_US2_0029DA18(int value) {
    if (D_001A8CFC != 0)
        return func_US2_00340AA8(D_001A8CFC + 0x3A4C0, value);
    return 0;
}
