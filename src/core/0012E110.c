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
void func_0012E110(void *arg0, unsigned int arg1, int arg2) {
    char *p = (char *)arg0;
    int r;
    int event[8];

    while (((int)IPU_CTRL) < 0) {
    }
    r = r1_func_0011D960();
    D3_MADR = arg1 & 0x0FFFFFFF;
    D3_QWC = (unsigned int)arg2 << 6;
    D3_CHCR = 0x100;
    if (r != 0) {
        r1_func_0011D9A8();
    }
    r1_func_00128560(arg0, arg2 | 0x70000000);
    event[0] = 4;
    r1_func_0012BC78(*(int *)(p + 0x858), event);
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
void func_0012E378(void *arg0, unsigned int arg1, int arg2) {
    char *p = (char *)arg0;
    int event[8];
    CscRec_2A558 rec;
    CscRec_2A558 *rp;
    int h;
    int r;

    rec.total = arg2 / 0x3FF + 1;
    rec.size = arg2;
    rec.next = (arg1 + 0xFFC00) & 0x0FFFFFFF;
    rec.err = 0;
    rec.done = 0;
    rp = &rec;
    while (((int)IPU_CTRL) < 0) {
    }
    h = r1_func_00118AC0_2A558(3, (void *)r1_func_0012A418_2A558, 0, rp);
    D_STAT = 8;
    r1_func_00119460_2A558(3);
    r = r1_func_0011D960();
    {
        volatile unsigned int *madr = &D3_MADR;
        volatile unsigned int *qwc = &D3_QWC;
        volatile unsigned int *chcr = &D3_CHCR;
        *madr = arg1 & 0x0FFFFFFF;
        *qwc = 0xFFC0;
        *chcr = 0x100;
    }
    if (r != 0) {
        r1_func_0011D9A8();
    }
    IPU_CMD = 0x700003FF;
    event[0] = 4;
    r1_func_0012BC78(*(void **)(p + 0x858), event);
    while (rec.done < rec.total) {
    }
    if (rec.err != 0) {
        r1_func_0012C468_a(p, r1_D_00153AB0);
    }
    while (((int)IPU_CTRL) < 0) {
    }
    r1_func_001193F8(3);
    r1_func_00118AD0(3, h);
}

ASM_FUNC("asm/core", func_0012E538);


/* rac1-decomp src/core/0012A2F0.c: func_0012AA70 */
/* _sysbitInit: points the bit stream at arg0 at the arg3-byte ring buffer
   at arg2, reading from arg1, and resets it. The store order is
   load-bearing (LEVERS.md lever 3): arg1's +0x8 store has to come before
   its +0xC store, after the other fields in retail's order. */
void func_0012E890(void *arg0, int arg1, int arg2, int arg3) {
    char *p = (char *)arg0;
    *(int *)(p + 0x28) = arg3;
    *(int *)(p + 0x8) = arg1;
    *(long *)(p + 0x0) = 0;
    *(int *)(p + 0x10) = 0;
    *(long *)(p + 0x18) = 0;
    *(int *)(p + 0x20) = arg2;
    *(int *)(p + 0x24) = arg2 + arg3;
    *(int *)(p + 0xC) = arg1;
    r1_func_0012AAC8(arg0, 0);
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
void func_0012E608(void *arg0, int *arg1) {
    char *p = (char *)arg0;
    int ev[8];
    int loc[4];
    int n, small, r, addr;
    unsigned int mask;
    void *h;

    ev[0] = 2;
    n = arg1[3] * arg1[4];
    r1_func_0012BC78_result(*(void **)(p + 0x858), ev);
    if ((IPU_CTRL & 0x4000) != 0) {
        IPU_CTRL = 0x40000000;
    }
    small = n < 0x400;
    while (((int)IPU_CTRL) < 0) {
    }
    r1_func_00128560(arg0, 0);
    addr = arg1[0];
    while (((int)IPU_CTRL) < 0) {
    }
    mask = 0x0FFFFFFF;
    loc[1] = addr & mask;
    loc[0] = n * 0x18;
    if ((unsigned int)loc[0] > 0xFFFF) {
        h = r1_func_00118AC0(4, (void *)r1_func_0012A718, 0, &loc[0]);
        D_STAT = 0x10;
        r1_func_00119460(4);
        r = r1_func_0011D960();
        D4_MADR = loc[1];
        D4_QWC = 0xFFFF;
        D4_CHCR = 0x101;
        if (r != 0) {
            r1_func_0011D9A8();
        }
        loc[1] = (loc[1] + 0xFFFF0) & mask;
        loc[0] = loc[0] - 0xFFFF;
        if (small) {
            r1_func_0012A2F0(arg0, *(int *)(p + 0xD8), n);
        } else {
            r1_func_0012A558(arg0, *(int *)(p + 0xD8), n);
        }
        r1_func_001193F8(4);
        r1_func_00118AD0(4, (int)h);
    } else {
        r = r1_func_0011D960();
        D4_MADR = arg1[0] & mask;
        D4_QWC = loc[0];
        D4_CHCR = 0x101;
        if (r != 0) {
            r1_func_0011D9A8();
        }
        loc[0] = 0;
        if (small) {
            r1_func_0012A2F0(arg0, *(int *)(p + 0xD8), n);
        } else {
            r1_func_0012A558(arg0, *(int *)(p + 0xD8), n);
        }
    }
    ev[0] = 3;
    r1_func_0012BC78_result(*(void **)(p + 0x858), ev);
}
