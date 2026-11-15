#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

extern void func_0011AC60(int value);

extern void func_00350808_1(int value);

extern void func_00350798(int value);

extern void func_0011AC40(int value);

/* snapshots five hardware registers into a structure, spins while one register's nibble stays set, snapshots five more and returns 1 */
/* Saves the video decoder and DMA channel registers into the buffer, waiting for the decoder to finish first. */
int func_00350DC8(int *buf)
{
    WaitSema(buf[16]);
    buf[17] = 0;
    func_00350808_1(5);
    buf[7] = ((int)D4_MADR);
    buf[8] = ((int)D4_TADR);
    buf[9] = ((int)D4_QWC);
    buf[10] = ((int)D4_CHCR);
    if (((int)IPU_CTRL) & 0xF0)
        while (((int)IPU_CTRL) & 0xF0)
            ;
    StartDmaChannel3(0);
    buf[11] = ((int)D3_MADR);
    buf[12] = ((int)D3_QWC);
    buf[13] = ((int)D3_CHCR);
    buf[14] = ((int)IPU_BP);
    buf[15] = ((int)IPU_CTRL);
    SignalSema(buf[16]);
    return 1;
}

extern int func_00350750(void *, int);

struct ipu_fifo {
    unsigned base;
    unsigned link;
    int units;
    int head;
    int count;
    int pad14;
    int pad18;
    unsigned madr;
    unsigned tadr;
    unsigned qwc;
    unsigned chcr;
    unsigned d3_madr;
    unsigned d3_qwc;
    unsigned d3_chcr;
    unsigned ipu_bp;
    unsigned ipu_ctrl;
    int intr;
    int saved;
};

/* restores the saved IPU and DMA channel 3/4 registers (the inverse of func_00350DC8) after rewinding
   the channel 4 address past the bytes the IPU still holds, wrapping inside the ring buffer; each of the
   two ring-index tests is written with its % twice because retail keeps one divide but a zero check
   per use */
/* Puts back the saved video decoder and DMA state after a pause. */
int func_00350ED8(struct ipu_fifo *p)
{
    unsigned bp = p->ipu_bp;
    unsigned ifc = (bp >> 8) & 0xF;
    unsigned fp = (bp >> 16) & 3;
    unsigned fifo = fp + ifc;
    unsigned bp_pos = bp & 0x7F;
    unsigned madr = p->madr - fifo * 16;
    unsigned qwc = p->qwc + fifo;
    unsigned chcr = p->chcr | 0x100;
    unsigned tadr;

    tadr = p->tadr;
    WaitSema(p->intr);
    if (madr < p->base) {
        int units = p->units;
        int size = units << 11;
        int tag;

        qwc = (p->base - madr) >> 4;
        tadr = p->link & 0x0FFFFFFF;
        madr += size;
        tag = (p->madr != p->base && p->madr != p->base + size) ? 3 : 0;
        chcr = ((p->chcr & 0x0FFFFFFF) | (tag << 28)) | 0x100;
        if ((units - p->head) % units < 0 || (units - p->head) % units >= p->count) {
            p->head = units - 1;
            p->count++;
        }
    } else {
        int r1 = ViBufAddressToSlot(p, p->madr);
        int r2 = ViBufAddressToSlot(p, madr);

        if (r1 != r2) {
            int units = p->units;
            unsigned base = p->base;
            unsigned a;
            unsigned b;
            int tag;

            qwc = (base + (r1 << 11) - madr) >> 4;
            a = base + (p->madr - base) % (units << 11);
            b = base + (((p->head + p->count) % units) << 11);
            tadr = ((r1 << 4) + p->link) & 0x0FFFFFFF;
            tag = (a != b) ? 3 : 0;
            chcr = ((p->chcr & 0x0FFFFFFF) | (tag << 28)) | 0x100;
            if ((r2 + units - p->head) % units < 0 || (r2 + units - p->head) % units >= p->count) {
                p->head = r2;
                p->count++;
            }
        }
    }
    if (p->d3_madr != 0) {
        if (p->d3_qwc != 0) {
            D3_MADR = p->d3_madr;
            D3_QWC = p->d3_qwc;
            StartDmaChannel3(p->d3_chcr | 0x100);
        }
    }
    if (p->count != 0) {
        if (((int)IPU_CTRL) < 0)
            while (((int)IPU_CTRL) < 0)
                ;
        IPU_CMD = bp_pos;
        if (((int)IPU_CTRL) < 0)
            while (((int)IPU_CTRL) < 0)
                ;
    }
    D4_MADR = madr;
    D4_TADR = tadr;
    D4_QWC = qwc;
    if (p->count != 0)
        func_00350808_1(chcr);
    IPU_CTRL = p->ipu_ctrl;
    p->saved = 1;
    SignalSema(p->intr);
    return 1;
}

extern void func_0011AC30(int value);
/* Stops DMA channel 4, clears its addresses and releases the buffer's semaphore. */
int func_00351210(int *buf)
{
    func_00350808_1(5);
    D4_QWC = 0;
    D4_MADR = 0;
    D4_TADR = 0;
    DeleteSema(buf[16]);
    return 1;
}
