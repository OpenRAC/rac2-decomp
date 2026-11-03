/* Complete StoreImage executor reconstruction, 3 November 2026; not linked.
 * Profile: sdk -O2 -G2 -ffunction-sections -Wa,--r5900-swap-branch-slots,
 * in its own source unit. US/US2/PAL: 1676/1676 bytes, 0/1 each; the checker
 * first reports +0x3CC. The 0x90 frame, full 112-byte packet view and real
 * 16-byte FIFO/tail buffer agree with the decoded body.
 * Default SDK assembler profile gives 1680 bytes: it leaves the final
 * volatile 64-bit BUSDIR store before JAL and adds a nop. The already
 * qualified swap-slot profile restores that slot; no tool change is needed.
 * Remaining error paths allocate reset-packet and MMIO temporaries in
 * different registers and order the cleanup addresses differently. The
 * diagnostic is actually int-returning/variadic, and both IMR APIs and
 * saved IMR state are 64-bit. Do not copy the donor's narrower/void views.
 * Bare diagnostic calls, explicit(void) discards and a named reset quad
 * produce identical listings. A shared real transfer-error cleanup keeps
 * 1676 bytes but moves the first failure earlier to +0x22C. Nine observations
 * include one compile-only probe and eight placement-check calls, with
 * the final retained source rechecked in all three releases.
 * Reopen with independent error-temporary/cleanup lifetime evidence that
 * preserves the true interfaces and ordered MMIO operations. No linked or
 * native-runtime qualification is claimed; production marker is restored.
 */
#include "common.h"

/* libgraph StoreImage execution, adapted from the public RAC1 reconstruction
 * src/core/00122AD8.c (GPL-3.0), revision bbb526cb. The public PS2DEV kernel
 * API and the full-register return/restore sequence establish 64-bit IMR state.
 * The byte tail uses a real 16-byte FIFO buffer, shared with the drain loop.
 */
extern int func_0011C820(const char *, ...);

typedef int u128_si __attribute__((mode(TI)));
typedef struct {
    unsigned long SBP:14; unsigned long p14:2; unsigned long SBW:6; unsigned long p22:2;
    unsigned long SPSM:6; unsigned long p30:2; unsigned long DBP:14; unsigned long p46:2;
    unsigned long DBW:6; unsigned long p54:2; unsigned long DPSM:6; unsigned long p62:2;
} SiBitbltbuf;
typedef struct {
    unsigned long RRW:12; unsigned long p12:20; unsigned long RRH:12; unsigned long p44:20;
} SiTrxreg;
typedef struct {
    unsigned int vifcode[4];
    unsigned long giftag[2];
    SiBitbltbuf bitbltbuf; long bitbltbufaddr;
    unsigned long trxpos; long trxposaddr;
    SiTrxreg trxreg; long trxregaddr;
    unsigned long finish; long finishaddr;
    unsigned long trxdir; long trxdiraddr;
} SiStoreImage __attribute__((aligned(16)));

extern char D_0013B520[];
extern char D_0013B558[];
extern char D_0013B588[];
extern char D_0013B5C8[];
extern u128_si D_00137E10;
extern unsigned long func_0011AF40(void);
extern unsigned long func_0011AF60(unsigned long);

int func_0012672C(SiStoreImage *sp, u128_si *dstaddr)
{
    unsigned int cnt = 0;
    int nfull = 0, nrem = 0, nbyte = 0, nrest = 0;
    int w, h, psm, bytes, i, n;
    unsigned long old;
    int h2;
    union { u128_si q; unsigned char c[16]; } buf;

    w = sp->trxreg.RRW;
    h = sp->trxreg.RRH;
    psm = sp->bitbltbuf.SPSM;
    h2 = 0;
    switch (psm) {
    case 0x00:
    case 0x30:
        bytes = w * h * 4;
        nbyte = bytes & 0xF;
        nfull = (bytes >> 4) & ~7u;
        nrem = (bytes >> 4) & 7;
        if (!nbyte) {
            h2 = h;
            nrest = 0;
        } else {
            h2 = (h + 3) & ~3;
            n = w * h2;
            nrest = (n >> 2) - nfull - nrem - 1;
        }
        break;
    case 0x01:
    case 0x31:
        bytes = w * h * 3;
        nbyte = bytes & 0xF;
        nfull = (bytes >> 4) & ~7u;
        nrem = (bytes >> 4) & 7;
        if (!nbyte) {
            h2 = h;
            nrest = 0;
        } else {
            h2 = (h + 15) & ~15;
            n = w * h2;
            n = ((n * 3) >> 4) - nfull;
            nrest = n - nrem - 1;
        }
        break;
    case 0x02:
    case 0x0A:
    case 0x32:
    case 0x3A:
        bytes = w * h * 2;
        nbyte = bytes & 0xF;
        nrem = (bytes >> 4) & 7;
        nfull = (bytes >> 4) & ~7u;
        if (!nbyte) {
            h2 = h;
            nrest = 0;
        } else {
            h2 = (h + 7) & ~7u;
            n = w * h2;
            nrest = (n >> 3) - nfull - nrem - 1;
        }
        break;
    case 0x13:
    case 0x1B:
        bytes = w * h;
        nbyte = bytes & 0xF;
        nrem = (bytes >> 4) & 7;
        nfull = (bytes >> 4) & ~7u;
        if (!nbyte) {
            h2 = h;
            nrest = 0;
        } else {
            h2 = (h + 7) & ~7u;
            n = w * h2;
            nrest = (n >> 4) - nfull - nrem - 1;
        }
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        bytes = (w * h) >> 1;
        nbyte = bytes & 0xF;
        nrem = (bytes >> 4) & 7;
        nfull = (bytes >> 4) & ~7u;
        if (!nbyte) {
            h2 = h;
            nrest = 0;
        } else {
            h2 = (h + 7) & ~7u;
            n = w * h2;
            nrest = (n >> 5) - nfull - nrem - 1;
        }
        break;
    }

    if (nbyte) {
        *(long *)((unsigned int)&sp->trxreg | 0x20000000) = (long)(int)sp->trxreg.RRW | ((long)h2 << 32);
    }

    while (*(volatile int *)0x10009000 & 0x100) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B520);
            return -1;
        }
    }

    old = func_0011AF60(func_0011AF40() | 0x200);
    *(volatile long *)0x12001000 = 2;
    *(volatile int *)0x10009020 = 7;
    if (((unsigned int)sp & 0x70000000) == 0x70000000) {
        *(volatile int *)0x10009010 = ((unsigned int)sp & 0x0FFFFFFF) | 0x80000000;
    } else {
        *(volatile int *)0x10009010 = (unsigned int)sp & 0x0FFFFFFF;
    }
    *(volatile int *)0x10009000 = 0x101;
    while (*(volatile int *)0x10009000 & 0x100) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B520);
            return -1;
        }
    }

    while (!(*(volatile long *)0x12001000 & 2)) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B558);
            *(volatile u128_si *)0x10005000 = D_00137E10;
            return -1;
        }
    }

    *(volatile int *)0x10003C00 = 0x800000;
    *(volatile long *)0x12001040 = 1;

    if (nfull) {
        *(volatile int *)0x10009020 = nfull;
        if (((unsigned int)dstaddr & 0x70000000) == 0x70000000) {
            *(volatile int *)0x10009010 = ((unsigned int)dstaddr & 0x0FFFFFFF) | 0x80000000;
        } else {
            *(volatile int *)0x10009010 = (unsigned int)dstaddr & 0x0FFFFFFF;
        }
        *(volatile int *)0x10009000 = 0x100;
        while (*(volatile int *)0x10009000 & 0x100) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B588);
                *(volatile long *)0x12001000 = 0x100;
                *(volatile long *)0x12001040 = 0;
                *(volatile int *)0x10003000 = 1;
                *(volatile int *)0x10003C10 = 1;
                return -1;
            }
        }
    }

    for (i = 0; i < nrem; i++) {
        while (!(*(volatile int *)0x10003C00 & 0x1F000000)) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B5C8);
                *(volatile long *)0x12001000 = 0x100;
                *(volatile long *)0x12001040 = 0;
                *(volatile int *)0x10003000 = 1;
                *(volatile int *)0x10003C10 = 1;
                return -1;
            }
        }
        dstaddr[nfull + i] = *(volatile u128_si *)0x10005000;
    }

    if (nbyte) {
        while (!(*(volatile int *)0x10003C00 & 0x1F000000)) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B5C8);
                *(volatile long *)0x12001000 = 0x100;
                *(volatile long *)0x12001040 = 0;
                *(volatile int *)0x10003000 = 1;
                *(volatile int *)0x10003C10 = 1;
                return -1;
            }
        }
        buf.q = *(volatile u128_si *)0x10005000;
        for (i = 0; i < nbyte; i++) {
            ((unsigned char *)&dstaddr[nfull + nrem])[i] = buf.c[i];
        }
        for (i = 0; i < nrest; i++) {
            while (!(*(volatile int *)0x10003C00 & 0x1F000000)) {
                if (cnt++ > 0x1000000) {
                    func_0011C820(D_0013B5C8);
                    *(volatile long *)0x12001000 = 0x100;
                    *(volatile long *)0x12001040 = 0;
                    *(volatile int *)0x10003000 = 1;
                    *(volatile int *)0x10003C10 = 1;
                    return -1;
                }
            }
            buf.q = *(volatile u128_si *)0x10005000;
        }
    }

    *(volatile int *)0x10003C00 = 0;
    *(volatile long *)0x12001040 = 0;
    func_0011AF60(old);
    {
        u128_si t = D_00137E10;
        *(volatile long *)0x12001000 = 2;
        *(volatile u128_si *)0x10005000 = t;
    }
    return 0;
}
