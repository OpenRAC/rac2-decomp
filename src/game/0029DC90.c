#include "names.h"
/* A unit of its own: at the default -G0 an sda base with an offset is one assembler operand, the
   retail's absolute lui + load through the destination register, never in a delay slot, while the
   first byte stays split. Without the offset the load moves into a delay slot as one $gp load. */

extern unsigned char D_001395C1[];
extern unsigned char D_001A7B00[] __attribute__((sda));

/* Returns 1 only if three separate status bytes are all non-zero. */
int menu_are_all_status_bytes_set(void)
{
    if (D_001395C1[0] == 0)
        goto no;
    if (D_001A7B00[5] == 0)
        goto no;
    if (D_001A7B00[12] != 0)
        return 1;
no:
    return 0;
}
