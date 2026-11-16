#include "include_asm.h"
#include "names.h"

extern int coll_update_controller(char *a, char *b, char *c);

/* Passes the object and two data blocks inside it (at +0x10 and +0xC0) to the collision controller update. */
int moby_call_helper_with_blocks_pal(char *moby)
{
    return coll_update_controller(moby, moby + 0x10, moby + 0xC0);
}

