#include "ps2_hw.h"
#include "names.h"

/* libgraph StoreImage execution, transcribed from the public RAC1 reconstruction
 * src/core/gs/store_image.c (sceGsExecStoreImage, GPL-3.0), matched there with the
 * same SDK compiler. As in RAC1, the diagnostic's result is unused and declared void
 * (precedent: src/core/00124C98.c), and the IMR put returns int and the saved IMR is
 * an int: the 64-bit views give other registers or a longer body.
 * The byte tail uses a real 16-byte FIFO buffer, shared with the drain loop.
 */
extern void printf_to_deci2_console(const char *, ...);

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
extern unsigned long GsGetIMR(void);
extern int GsPutIMR(unsigned long);

/* Runs an image read-back from graphics memory into main memory and waits for each step. */
int sceGsExecStoreImage(SiStoreImage *packet, u128_si *dest)
{
    unsigned int pollCount = 0;
    int nfull = 0, nrem = 0, nbyte = 0, nrest = 0;
    int w, h, psm, bytes, i, totalQuads;
    int oldImr;
    int paddedH;
    union { u128_si q; unsigned char c[16]; } buf;

    w = packet->trxreg.RRW;
    h = packet->trxreg.RRH;
    psm = packet->bitbltbuf.SPSM;
    paddedH = 0;
    switch (psm) {
    case 0x00:
    case 0x30:
        bytes = w * h * 4;
        nbyte = bytes & 0xF;
        nfull = (bytes >> 4) & ~7u;
        nrem = (bytes >> 4) & 7;
        if (!nbyte) {
            paddedH = h;
            nrest = 0;
        } else {
            paddedH = (h + 3) & ~3;
            totalQuads = w * paddedH;
            nrest = (totalQuads >> 2) - nfull - nrem - 1;
        }
        break;
    case 0x01:
    case 0x31:
        bytes = w * h * 3;
        nbyte = bytes & 0xF;
        nfull = (bytes >> 4) & ~7u;
        nrem = (bytes >> 4) & 7;
        if (!nbyte) {
            paddedH = h;
            nrest = 0;
        } else {
            paddedH = (h + 15) & ~15;
            totalQuads = w * paddedH;
            totalQuads = ((totalQuads * 3) >> 4) - nfull;
            nrest = totalQuads - nrem - 1;
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
            paddedH = h;
            nrest = 0;
        } else {
            paddedH = (h + 7) & ~7u;
            totalQuads = w * paddedH;
            nrest = (totalQuads >> 3) - nfull - nrem - 1;
        }
        break;
    case 0x13:
    case 0x1B:
        bytes = w * h;
        nbyte = bytes & 0xF;
        nrem = (bytes >> 4) & 7;
        nfull = (bytes >> 4) & ~7u;
        if (!nbyte) {
            paddedH = h;
            nrest = 0;
        } else {
            paddedH = (h + 7) & ~7u;
            totalQuads = w * paddedH;
            nrest = (totalQuads >> 4) - nfull - nrem - 1;
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
            paddedH = h;
            nrest = 0;
        } else {
            paddedH = (h + 7) & ~7u;
            totalQuads = w * paddedH;
            nrest = (totalQuads >> 5) - nfull - nrem - 1;
        }
        break;
    }

    if (nbyte) {
        *(long *)((unsigned int)&packet->trxreg | 0x20000000) = (long)(int)packet->trxreg.RRW | ((long)paddedH << 32);
    }

    while (D1_CHCR & 0x100) {
        if (pollCount++ > 0x1000000) {
            printf_to_deci2_console(D_0013B520);
            return -1;
        }
    }

    oldImr = GsPutIMR(GsGetIMR() | 0x200);
    GS_CSR = 2;
    D1_QWC = 7;
    if (((unsigned int)packet & 0x70000000) == 0x70000000) {
        D1_MADR = ((unsigned int)packet & 0x0FFFFFFF) | 0x80000000;
    } else {
        D1_MADR = (unsigned int)packet & 0x0FFFFFFF;
    }
    D1_CHCR = 0x101;
    while (D1_CHCR & 0x100) {
        if (pollCount++ > 0x1000000) {
            printf_to_deci2_console(D_0013B520);
            return -1;
        }
    }

    while (!(GS_CSR & 2)) {
        if (pollCount++ > 0x1000000) {
            printf_to_deci2_console(D_0013B558);
            VIF1_FIFO = D_00137E10;
            return -1;
        }
    }

    VIF1_STAT = 0x800000;
    GS_BUSDIR = 1;

    if (nfull) {
        D1_QWC = nfull;
        if (((unsigned int)dest & 0x70000000) == 0x70000000) {
            D1_MADR = ((unsigned int)dest & 0x0FFFFFFF) | 0x80000000;
        } else {
            D1_MADR = (unsigned int)dest & 0x0FFFFFFF;
        }
        D1_CHCR = 0x100;
        while (D1_CHCR & 0x100) {
            if (pollCount++ > 0x1000000) {
                printf_to_deci2_console(D_0013B588);
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
            if (pollCount++ > 0x1000000) {
                printf_to_deci2_console(D_0013B5C8);
                GS_CSR = 0x100;
                GS_BUSDIR = 0;
                GIF_CTRL = 1;
                VIF1_FBRST = 1;
                return -1;
            }
        }
        dest[nfull + i] = VIF1_FIFO;
    }

    if (nbyte) {
        while (!(VIF1_STAT & 0x1F000000)) {
            if (pollCount++ > 0x1000000) {
                printf_to_deci2_console(D_0013B5C8);
                GS_CSR = 0x100;
                GS_BUSDIR = 0;
                GIF_CTRL = 1;
                VIF1_FBRST = 1;
                return -1;
            }
        }
        buf.q = VIF1_FIFO;
        for (i = 0; i < nbyte; i++) {
            ((unsigned char *)&dest[nfull + nrem])[i] = buf.c[i];
        }
        for (i = 0; i < nrest; i++) {
            while (!(VIF1_STAT & 0x1F000000)) {
                if (pollCount++ > 0x1000000) {
                    printf_to_deci2_console(D_0013B5C8);
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
    GsPutIMR(oldImr);
    {
        u128_si zeroQuad = D_00137E10;
        GS_CSR = 2;
        VIF1_FIFO = zeroQuad;
    }
    return 0;
}
