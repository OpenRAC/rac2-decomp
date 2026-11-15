#include "common.h"

/* Returns the top arg1 bits of the 64-bit word at arg0. */
int func_0012E8C8(void *arg0, int arg1) {
    return (int)(*(unsigned long *)arg0 >> (0x40 - arg1));
}
