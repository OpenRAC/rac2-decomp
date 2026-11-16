#include "names.h"
/* A unit of its own: at the default -G0 an sda base with an offset is one assembler operand, the
   retail's absolute lui + load through the destination register, never in a delay slot, while the
   first byte stays split. Without the offset the load moves into a delay slot as one $gp load. */

extern unsigned char g_menu_status_bytes[];
extern unsigned char g_inventory_have_flags[] __attribute__((sda));

/* Returns 1 only if three separate status bytes are all non-zero. */
int menu_are_all_status_bytes_set(void)
{
    if (g_menu_status_bytes[0] == 0)
        goto no;
    if (g_inventory_have_flags[5] == 0)
        goto no;
    if (g_inventory_have_flags[12] != 0)
        return 1;
no:
    return 0;
}
