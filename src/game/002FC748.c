#include "include_asm.h"
#include "names.h"

extern char *D_001B22A8 __attribute__((sda));
extern char D_001AC950[];

/* Queues a block of preset graphics data (table 1) for the vector unit. */
void func_002FC748(void)
{
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 0) = 0x30000003;
    *(char **)(*(char * volatile *)&gDmaPacketCursor + 4) = D_001AC950;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 8) = 0;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 12) = 0x50000003;
    gDmaPacketCursor = *(char * volatile *)&gDmaPacketCursor + 16;
}
