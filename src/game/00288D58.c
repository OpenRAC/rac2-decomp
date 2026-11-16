#include "include_asm.h"
#include "names.h"

/* Frozen Batch A A16-sda-byte-16; acknowledged claim 3b1980407c8765dd4baf122f505692e49c411cbff6089e896e8b3921ce208b41. */
typedef unsigned char BatchA_A16_u8;

extern BatchA_A16_u8 BatchA_A16_BatchA_D001A7A0A[] __attribute__((sda));

/* Returns 1 when a flag byte is set. */
int flag_is_byte_set(void) { return BatchA_A16_BatchA_D001A7A0A[0] != 0; }

extern int g_flag_word __attribute__((sda));

/* Clears a flag word. */
void flag_clear_word(void) {
    g_flag_word = 0;
}
