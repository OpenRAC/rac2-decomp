#include "ps2_hw.h"

/* libgraph StoreImage execution, transcribed from the public RAC1 reconstruction
 * src/core/gs/store_image.c (sceGsExecStoreImage, GPL-3.0), matched there with the
 * same SDK compiler. As in RAC1, the diagnostic's result is unused and declared void
 * (precedent: src/core/00124C98.c), and the IMR put returns int and the saved IMR is
 * an int: the 64-bit views give other registers or a longer body.
 * The byte tail uses a real 16-byte FIFO buffer, shared with the drain loop.
 */
extern void func_0011C820(const char *, ...);

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
extern int func_0011AF60(unsigned long);

int func_0012672C(SiStoreImage *sp, u128_si *dstaddr)
{
    unsigned int cnt = 0;
    int nfull = 0, nrem = 0, nbyte = 0, nrest = 0;
    int w, h, psm, bytes, i, n;
    int old;
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

    while (D1_CHCR & 0x100) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B520);
            return -1;
        }
    }

    old = func_0011AF60(func_0011AF40() | 0x200);
    GS_CSR = 2;
    D1_QWC = 7;
    if (((unsigned int)sp & 0x70000000) == 0x70000000) {
        D1_MADR = ((unsigned int)sp & 0x0FFFFFFF) | 0x80000000;
    } else {
        D1_MADR = (unsigned int)sp & 0x0FFFFFFF;
    }
    D1_CHCR = 0x101;
    while (D1_CHCR & 0x100) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B520);
            return -1;
        }
    }

    while (!(GS_CSR & 2)) {
        if (cnt++ > 0x1000000) {
            func_0011C820(D_0013B558);
            VIF1_FIFO = D_00137E10;
            return -1;
        }
    }

    VIF1_STAT = 0x800000;
    GS_BUSDIR = 1;

    if (nfull) {
        D1_QWC = nfull;
        if (((unsigned int)dstaddr & 0x70000000) == 0x70000000) {
            D1_MADR = ((unsigned int)dstaddr & 0x0FFFFFFF) | 0x80000000;
        } else {
            D1_MADR = (unsigned int)dstaddr & 0x0FFFFFFF;
        }
        D1_CHCR = 0x100;
        while (D1_CHCR & 0x100) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B588);
                GS_CSR = 0x100;
                GS_BUSDIR = 0;
                GIF_CTRL = 1;
                VIF1_FBRST = 1;
                return -1;
            }
        }
    }

    for (i = 0; i < nrem; i++) {
        while (!(VIF1_STAT & 0x1F000000)) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B5C8);
                GS_CSR = 0x100;
                GS_BUSDIR = 0;
                GIF_CTRL = 1;
                VIF1_FBRST = 1;
                return -1;
            }
        }
        dstaddr[nfull + i] = VIF1_FIFO;
    }

    if (nbyte) {
        while (!(VIF1_STAT & 0x1F000000)) {
            if (cnt++ > 0x1000000) {
                func_0011C820(D_0013B5C8);
                GS_CSR = 0x100;
                GS_BUSDIR = 0;
                GIF_CTRL = 1;
                VIF1_FBRST = 1;
                return -1;
            }
        }
        buf.q = VIF1_FIFO;
        for (i = 0; i < nbyte; i++) {
            ((unsigned char *)&dstaddr[nfull + nrem])[i] = buf.c[i];
        }
        for (i = 0; i < nrest; i++) {
            while (!(VIF1_STAT & 0x1F000000)) {
                if (cnt++ > 0x1000000) {
                    func_0011C820(D_0013B5C8);
                    GS_CSR = 0x100;
                    GS_BUSDIR = 0;
                    GIF_CTRL = 1;
                    VIF1_FBRST = 1;
                    return -1;
                }
            }
            buf.q = VIF1_FIFO;
        }
    }

    VIF1_STAT = 0;
    GS_BUSDIR = 0;
    func_0011AF60(old);
    {
        u128_si t = D_00137E10;
        GS_CSR = 2;
        VIF1_FIFO = t;
    }
    return 0;
}
