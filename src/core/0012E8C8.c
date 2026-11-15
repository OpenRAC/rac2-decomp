#include "common.h"

/* Returns the top bits of a 64-bit value without consuming them. */
int func_0012E8C8(void *valuePtr, int bitCount) {
    return (int)(*(unsigned long *)valuePtr >> (0x40 - bitCount));
}
