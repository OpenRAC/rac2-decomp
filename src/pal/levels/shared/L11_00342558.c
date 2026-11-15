#include "include_asm.h"
#include "names.h"

extern void coll_update_controller(char *a, char *b, char *c);

void func_PAL_L11_00342558(char *a0)
{
    coll_update_controller(a0, a0 + 0x10, a0 + 0xC0);
}

