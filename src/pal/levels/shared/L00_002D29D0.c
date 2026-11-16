#include "include_asm.h"
#include "names.h"

extern int g_hero_anim_mode;

/* Publishes the argument into the resident word, with 0xFFFFFFFF becoming 5. */
void func_PAL_L00_002D29D0(int value)
{
    if (value == -1)
        value = 4;
    g_hero_anim_mode = value;
}


