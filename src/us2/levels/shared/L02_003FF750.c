#include "include_asm.h"
#include "common.h"

/* func_US2_L02_003FF750, v2.00's own: no v1.01 twin. Tests the language index. */
extern unsigned char D_001A7BB4 MACRO_ADDR;

int func_US2_L02_003FF750(void) {
    return D_001A7BB4 >= 2;
}
