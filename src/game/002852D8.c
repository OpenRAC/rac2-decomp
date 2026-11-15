#include "include_asm.h"
#include "names.h"

extern char *D_001B22A8 __attribute__((sda));
extern char D_001A6600[];
extern char D_001A6860[];

/* Queues a draw list that runs the first set of screen strip packets. */
void func_002852D8(void)
{
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 0) = 0x30000026;
    *(char **)(*(char * volatile *)&gDmaPacketCursor + 4) = D_001A6600;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 8) = 0;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 12) = 0x50000026;
    gDmaPacketCursor = *(char * volatile *)&gDmaPacketCursor + 16;
}


/* Queues a draw list that runs the second set of screen strip packets. */
void func_00285338(void)
{
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 0) = 0x30000029;
    *(char **)(*(char * volatile *)&gDmaPacketCursor + 4) = D_001A6860;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 8) = 0;
    *(int *)(*(char * volatile *)&gDmaPacketCursor + 12) = 0x50000029;
    gDmaPacketCursor = *(char * volatile *)&gDmaPacketCursor + 16;
}
