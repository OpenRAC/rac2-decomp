#include "include_asm.h"
#include "names.h"

extern unsigned char g_gfx_data_block;

/* Returns the address of a fixed data block. */
void *gfx_get_data_block_address(void)
{
    return &g_gfx_data_block;
}

