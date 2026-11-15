#include "common.h"

/* Returns the top bits of a 64-bit value without consuming them. */
int mpeg_peek_top_bits64(void *valuePtr, int bitCount) {
    return (int)(*(unsigned long *)valuePtr >> (0x40 - bitCount));
}
