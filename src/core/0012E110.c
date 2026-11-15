#include "common.h"
#include "structs.h"

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern void r1_func_00128560();

extern void r1_func_0012BC78();

extern long r1_func_0012AAC8();

extern long r1_func_0012AAC8(void *, int);

/* rac1-decomp src/core/0012A2F0.c: func_0012A2F0 */
/* _doCSC (libmpeg). Stack-size probe #2: a 32-byte local (two 16-byte
   compiler stack slots) instead of one, since a single int/4-int array
   both land in one slot here (frame still 0x10 short of retail's 0x70,
   see c1-c4). */
/* Sends data to the video chip with DMA for color conversion, then waits until it is done. */
void mpeg_send_data_to_ipu(void *decoder, unsigned int address, int blockCount) {
    char *dec = (char *)decoder;
    int intrState;
    int event[8];

    while (((int)IPU_CTRL) < 0) {
    }
    intrState = r1_func_0011D960();
    D3_MADR = address & 0x0FFFFFFF;
    D3_QWC = (unsigned int)blockCount << 6;
    D3_CHCR = 0x100;
    if (intrState != 0) {
        r1_func_0011D9A8();
    }
    r1_func_00128560(decoder, blockCount | 0x70000000);
    event[0] = 4;
    r1_func_0012BC78(*(int *)(dec + 0x858), event);
    while (((D3_CHCR >> 8) & 1) != 0) {
    }
    while (((int)IPU_CTRL) < 0) {
    }
}

ASM_FUNC("asm/core", func_0012E238);

extern void r1_func_001193F8(int);
extern void r1_func_00118AD0(int, int);
extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern void r1_func_0012C468_a(void *, void *) __asm__("r1_func_0012C468");
extern void r1_func_0012BC78();
extern int r1_func_00118AC0_2A558(int, void *, int, void *) __asm__("r1_func_00118AC0");
extern void r1_func_00119460_2A558(int) __asm__("r1_func_00119460");
extern void r1_func_0012A418_2A558(void) __asm__("r1_func_0012A418");
extern char r1_D_00153AB0[];
typedef struct {
    volatile int done; /* 0x00: chunks finished (callback counts) */
    int err;           /* 0x04 */
    int size;          /* 0x08 */
    int next;          /* 0x0C */
    int total;         /* 0x10 */
} CscRec_2A558;

/* rac1-decomp src/core/0012A2F0.c: func_0012E378 */
/* libmpeg chunked DMA copy: arm the channel-3 callback with a progress record, start the transfer, wait for all chunks. */
/* Sends a large block to the video chip in chunks using DMA and waits for every chunk to finish. */
void mpeg_send_data_to_ipu_chunked(void *decoder, unsigned int address, int byteCount) {
    char *dec = (char *)decoder;
    int event[8];
    CscRec_2A558 progress;
    CscRec_2A558 *progressPtr;
    int handlerId;
    int intrState;

    progress.total = byteCount / 0x3FF + 1;
    progress.size = byteCount;
    progress.next = (address + 0xFFC00) & 0x0FFFFFFF;
    progress.err = 0;
    progress.done = 0;
    progressPtr = &progress;
    while (((int)IPU_CTRL) < 0) {
    }
    handlerId = r1_func_00118AC0_2A558(3, (void *)r1_func_0012A418_2A558, 0, progressPtr);
    D_STAT = 8;
    r1_func_00119460_2A558(3);
    intrState = r1_func_0011D960();
    {
        volatile unsigned int *madr = &D3_MADR;
        volatile unsigned int *qwc = &D3_QWC;
        volatile unsigned int *chcr = &D3_CHCR;
        *madr = address & 0x0FFFFFFF;
        *qwc = 0xFFC0;
        *chcr = 0x100;
    }
    if (intrState != 0) {
        r1_func_0011D9A8();
    }
    IPU_CMD = 0x700003FF;
    event[0] = 4;
    r1_func_0012BC78(*(void **)(dec + 0x858), event);
    while (progress.done < progress.total) {
    }
    if (progress.err != 0) {
        r1_func_0012C468_a(dec, r1_D_00153AB0);
    }
    while (((int)IPU_CTRL) < 0) {
    }
    r1_func_001193F8(3);
    r1_func_00118AD0(3, handlerId);
}

ASM_FUNC("asm/core", func_0012E538);


/* rac1-decomp src/core/0012A2F0.c: func_0012AA70 */
/* _sysbitInit: points the bit stream at arg0 at the arg3-byte ring buffer
   at arg2, reading from arg1, and resets it. The store order is
   load-bearing (LEVERS.md lever 3): arg1's +0x8 store has to come before
   its +0xC store, after the other fields in retail's order. */
/* Sets up a bit stream reader on a ring buffer and resets it. */
void mpeg_init_bit_stream(void *stream, int startAddr, int bufferStart, int bufferSize) {
    char *bs = (char *)stream;
    *(int *)(bs + 0x28) = bufferSize;
    *(int *)(bs + 0x8) = startAddr;
    *(long *)(bs + 0x0) = 0;
    *(int *)(bs + 0x10) = 0;
    *(long *)(bs + 0x18) = 0;
    *(int *)(bs + 0x20) = bufferStart;
    *(int *)(bs + 0x24) = bufferStart + bufferSize;
    *(int *)(bs + 0xC) = startAddr;
    r1_func_0012AAC8(stream, 0);
}

extern void r1_func_001193F8(int);
extern void r1_func_00118AD0(int, int);
extern int r1_func_0011D960(void);
extern void r1_func_0011D9A8(void);
extern void r1_func_00128560();
extern void r1_func_0012BC78();
extern void *r1_func_0012BC78_result(void *, int *) __asm__("r1_func_0012BC78");
extern void *r1_func_00118AC0(int, void *, int, void *);
extern void r1_func_00119460(int);
extern void r1_func_0012A558(void *, unsigned int, int);
extern void r1_func_0012A718();

/* rac1-decomp src/core/0012A2F0.c: func_0012E608 */
/* Copies a decoded picture to the video chip with DMA, then converts its colors. */
void mpeg_store_reference_image(void *decoder, int *picture) {
    char *dec = (char *)decoder;
    int event[8];
    int transfer[4];
    int blockCount, isSmall, intrState, picAddr;
    unsigned int mask;
    void *handlerId;

    event[0] = 2;
    blockCount = picture[3] * picture[4];
    r1_func_0012BC78_result(*(void **)(dec + 0x858), event);
    if ((IPU_CTRL & 0x4000) != 0) {
        IPU_CTRL = 0x40000000;
    }
    isSmall = blockCount < 0x400;
    while (((int)IPU_CTRL) < 0) {
    }
    r1_func_00128560(decoder, 0);
    picAddr = picture[0];
    while (((int)IPU_CTRL) < 0) {
    }
    mask = 0x0FFFFFFF;
    transfer[1] = picAddr & mask;
    transfer[0] = blockCount * 0x18;
    if ((unsigned int)transfer[0] > 0xFFFF) {
        handlerId = r1_func_00118AC0(4, (void *)r1_func_0012A718, 0, &transfer[0]);
        D_STAT = 0x10;
        r1_func_00119460(4);
        intrState = r1_func_0011D960();
        D4_MADR = transfer[1];
        D4_QWC = 0xFFFF;
        D4_CHCR = 0x101;
        if (intrState != 0) {
            r1_func_0011D9A8();
        }
        transfer[1] = (transfer[1] + 0xFFFF0) & mask;
        transfer[0] = transfer[0] - 0xFFFF;
        if (isSmall) {
            r1_func_0012A2F0(decoder, *(int *)(dec + 0xD8), blockCount);
        } else {
            r1_func_0012A558(decoder, *(int *)(dec + 0xD8), blockCount);
        }
        r1_func_001193F8(4);
        r1_func_00118AD0(4, (int)handlerId);
    } else {
        intrState = r1_func_0011D960();
        D4_MADR = picture[0] & mask;
        D4_QWC = transfer[0];
        D4_CHCR = 0x101;
        if (intrState != 0) {
            r1_func_0011D9A8();
        }
        transfer[0] = 0;
        if (isSmall) {
            r1_func_0012A2F0(decoder, *(int *)(dec + 0xD8), blockCount);
        } else {
            r1_func_0012A558(decoder, *(int *)(dec + 0xD8), blockCount);
        }
    }
    event[0] = 3;
    r1_func_0012BC78_result(*(void **)(dec + 0x858), event);
}
