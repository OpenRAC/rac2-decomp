#include "names.h"
extern void func_002FC3C0(int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int func_001265B0(void *, void *);
extern int func_001244B8(int, int);
extern int func_0011AEA0(int);

typedef struct {
    short value;
    short pad;
} UploadSlot;

typedef struct {
    char pad0000[0xE00];
    unsigned char blocks[8][0x400];
    UploadSlot slots[8];
    int count;
} UploadQueue;

/* Sends every waiting texture block to the graphics chip and empties the queue. */
void func_0034EB20(UploadQueue *queue)
{
    unsigned char buffer[0x60];
    int i;

    WaitForDmaStatusBits(1);
    for (i = 0; i < queue->count; i++) {
        func_00126288(buffer, queue->slots[i].value, 1, 0, 0, 0, 0x10, 0x10);
        FlushCache(0);
        ExecGsLoadImage(buffer, queue->blocks[i]);
        WaitGsPathsIdle(0, 0);
    }
    queue->count = 0;
}
