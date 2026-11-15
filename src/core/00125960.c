#include "include_asm.h"
#include "names.h"

extern unsigned char D_00137E00;

/* Returns the address of a fixed data block. */
void *gfx_get_data_block_address(void)
{
    return &D_00137E00;
}

