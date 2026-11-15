#include "names.h"
extern void gfx_wait_for_dma_status_bits(int);
extern int func_00126288(void *, short, short, short, short, short, short, short);
extern int sceGsExecLoadImage(void *, void *);
extern int gfx_wait_paths_idle(int, int);
extern void FlushCache(int);

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
void tex_upload_queued_blocks(UploadQueue *queue)
{
    unsigned char buffer[0x60];
    int i;

    gfx_wait_for_dma_status_bits(1);
    for (i = 0; i < queue->count; i++) {
        func_00126288(buffer, queue->slots[i].value, 1, 0, 0, 0, 0x10, 0x10);
        FlushCache(0);
        sceGsExecLoadImage(buffer, queue->blocks[i]);
        gfx_wait_paths_idle(0, 0);
    }
    queue->count = 0;
}
