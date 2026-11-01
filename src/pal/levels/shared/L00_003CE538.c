#include "include_asm.h"

extern void func_L00_003CA688(char *);

void func_PAL_L00_003CE538(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 1)
        func_L00_003CA688(object);
}

