#include "include_asm.h"
#include "names.h"

extern int coll_update_controller(char *a, char *b, char *c);

int moby_call_helper_with_blocks_pal(char *a0)
{
    return coll_update_controller(a0, a0 + 0x10, a0 + 0xC0);
}

