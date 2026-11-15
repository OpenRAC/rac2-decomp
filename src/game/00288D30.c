#include "include_asm.h"
#include "names.h"

extern int ref_L00_002F4398_00 __attribute__((sda));

/* Returns 1 when a flag word is set. */
int flag_is_word_set(void)
{
    return ref_L00_002F4398_00 != 0;
}
