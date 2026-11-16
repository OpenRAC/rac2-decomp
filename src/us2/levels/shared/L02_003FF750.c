#include "include_asm.h"
#include "common.h"

/* func_US2_L02_003FF750, v2.00's own: no v1.01 twin. Tests the language index. */
extern unsigned char g_language MACRO_ADDR;

int language_at_least_two_us2(void) {
    return g_language >= 2;
}
