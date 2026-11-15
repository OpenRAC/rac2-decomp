#include "include_asm.h"
#include "names.h"

extern int coll_update_controller(char *a, char *b, char *c);

int func_PAL_L11_00342558(char *a0)
{
    return coll_update_controller(a0, a0 + 0x10, a0 + 0xC0);
}

