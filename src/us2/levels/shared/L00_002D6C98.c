#include "include_asm.h"

extern int D_0018C0B4;

int func_US2_L00_002D6C98(void) {
    int value = D_0018C0B4;
    int result = 0;

    if (value <= 100) {
        result = value >= 98;
    }
    return result;
}
