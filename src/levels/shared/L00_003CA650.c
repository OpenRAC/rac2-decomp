/* func_L00_003CA650 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

extern void func_L00_003CA688(char *);

/* Runs the effect update when the object is in state 1. */
void func_L00_003CA650(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 1)
        SpawnGlowEffectInFront(object);
}
