#include "include_asm.h"

extern char *D_001A8CFC;
extern int func_US2_00349728(void *, int);

int func_US2_0029CFA0(int value) {
    if (D_001A8CFC != 0)
        return func_US2_00349728(D_001A8CFC + 0x39160, value);
    return 0;
}

extern int func_US2_00347B88(void *, int);

int func_US2_0029D040(int value) {
    if (D_001A8CFC != 0)
        return func_US2_00347B88(D_001A8CFC + 0x39620, value);
    return 0;
}
