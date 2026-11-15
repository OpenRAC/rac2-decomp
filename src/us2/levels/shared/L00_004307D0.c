#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_texts_enabled(unsigned char *owner, int value);

/* Forward owner+8 and the supplied signed word to the measured two-argument setter. */
void func_US2_L00_004307D0(unsigned char *owner, int value)
{
    prompt_bar_set_texts_enabled(owner + 8, value);
}

