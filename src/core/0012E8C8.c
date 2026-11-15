#include "common.h"

/* Returns the top bits of a 64-bit value without consuming them. */
int mpeg_peek_top_bits64(void *value_ptr, int bit_count) {
    return (int)(*(unsigned long *)value_ptr >> (0x40 - bit_count));
}
