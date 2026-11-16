#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 WaitSema(s32);

extern void SignalSema(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 WaitSema(s32 a0);

extern void SignalSema(s32 a0);

typedef struct ViBuf {
    int base;               /* 0x0 */
    unsigned char *tags;    /* 0x4 */
    int count;              /* 0x8 */
    int fC;                 /* 0xC */
    int f10;                /* 0x10 */
    int f14;                /* 0x14 */
    int f18;
    char pad1C[0x24];
    int sema;               /* 0x40 */
    int f44;                /* 0x44 */
} ViBuf;

extern void mpeg_set_debug_value(char *);
extern char g_str_mpeg_buf_add_dma[];
extern void mpeg_start_dma4(unsigned int);
extern int mpeg_vibuf_addr_to_slot(ViBuf *, unsigned int);
extern void scTag2(unsigned long *, unsigned long, unsigned long, unsigned long);

/* Adds a number of bytes to the amount of data waiting in the video buffer. */
void mpeg_vibuf_add_pending_bytes(u8 *buf, s32 byteCount) {
    WaitSema(*(s32 *)(buf+0x40));
    *(s32 *)(buf+0x14) += (s32)byteCount;
    *(long *)(buf+0x48) = (long)byteCount + *(long *)(buf+0x48);
    SignalSema(*(s32 *)(buf+0x40));
}
/* Refills the video buffer's DMA tags after the decoder has used up some data, then restarts the transfer. */
int viBufAddDMA(ViBuf *vb) {
    int linkPrev = 0;
    unsigned int chcr;
    int idx;
    int usedSlots;
    int newCount;
    int i;
    int readSlot;
    int writeSlot;

    WaitSema(vb->sema);
    if (vb->f44 == 0) {
        mpeg_set_debug_value(g_str_mpeg_buf_add_dma);
        return 0;
    }
    mpeg_start_dma4(5);
    chcr = D4_CHCR;
    readSlot = mpeg_vibuf_addr_to_slot(vb, D4_MADR);
    usedSlots = (readSlot + vb->count - vb->fC) % vb->count;
    vb->fC = (vb->fC + usedSlots) % vb->count;
    vb->f10 -= usedSlots;
    writeSlot = (vb->fC + vb->f10) % vb->count;

    newCount = vb->f14 / 0x800;
    vb->f14 -= newCount << 11;
    if (newCount > 0) {
        int last = vb->count - 1;
        int prev = (vb->fC + vb->f10 + last) % vb->count;
        scTag2((unsigned long *)(vb->tags + prev * 16), vb->base + (prev << 11), 3, 0x80);
        linkPrev = 1;
    }
    idx = writeSlot;
    for (i = 0; i < newCount; i++) {
        int tagBits = 0;
        if (i != newCount - 1) {
            tagBits = 3;
        }
        scTag2((unsigned long *)(vb->tags + idx * 16), vb->base + (idx << 11), tagBits, 0x80);
        idx = (idx + 1) % vb->count;
    }
    vb->f10 += newCount;
    if (vb->f10 != 0) {
        if (linkPrev) {
            chcr = (chcr & 0x0FFFFFFF) | 0x30000000;
        }
        mpeg_start_dma4(chcr | 0x100);
    }
    SignalSema(vb->sema);
    return 1;
}
