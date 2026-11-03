#include "common.h"

/* libgraph StoreImage packet construction, adapted from the public RAC1
 * reconstruction src/core/00122818.c (GPL-3.0), revision bbb526cb.
 * The packet is 112 bytes; each incoming dimension/position is a signed short.
 */
typedef unsigned long u_long_sd;
typedef int u128_sd __attribute__((mode(TI)));
typedef struct {
    unsigned long NLOOP:15; unsigned long EOP:1; unsigned long pad16:30; unsigned long PRE:1;
    unsigned long PRIM:11; unsigned long FLG:2; unsigned long NREG:4;
    unsigned long REGS0:4; unsigned long REGS1:4; unsigned long REGS2:4; unsigned long REGS3:4;
    unsigned long REGS4:4; unsigned long REGS5:4; unsigned long REGS6:4; unsigned long REGS7:4;
    unsigned long REGS8:4; unsigned long REGS9:4; unsigned long REGS10:4; unsigned long REGS11:4;
    unsigned long REGS12:4; unsigned long REGS13:4; unsigned long REGS14:4; unsigned long REGS15:4;
} SdGifTag __attribute__((aligned(16)));
typedef struct {
    unsigned long SBP:14; unsigned long pad14:2; unsigned long SBW:6; unsigned long pad22:2;
    unsigned long SPSM:6; unsigned long pad30:2; unsigned long DBP:14; unsigned long pad46:2;
    unsigned long DBW:6; unsigned long pad54:2; unsigned long DPSM:6; unsigned long pad62:2;
} SdBitbltbuf;
typedef struct {
    unsigned long SSAX:11; unsigned long pad11:5; unsigned long SSAY:11; unsigned long pad27:5;
    unsigned long DSAX:11; unsigned long pad43:5; unsigned long DSAY:11; unsigned long DIR:2;
    unsigned long pad61:3;
} SdTrxpos;
typedef struct {
    unsigned long RRW:12; unsigned long pad12:20; unsigned long RRH:12; unsigned long pad44:20;
} SdTrxreg;
typedef struct { unsigned long pad00; } SdFinish;
typedef struct { unsigned long XDR:2; unsigned long pad02:62; } SdTrxdir;
typedef struct {
    unsigned int vifcode[4];
    SdGifTag giftag;
    SdBitbltbuf bitbltbuf; long bitbltbufaddr;
    SdTrxpos trxpos; long trxposaddr;
    SdTrxreg trxreg; long trxregaddr;
    SdFinish finish; long finishaddr;
    SdTrxdir trxdir; long trxdiraddr;
} SdStoreImage __attribute__((aligned(16)));

int func_0012646C(SdStoreImage *sp, short sbp, short sbw, short spsm, short x, short y, short w, short h)
{
    sp->vifcode[0] = 0;
    *(unsigned long *)&sp->finish = 0;
    sp->vifcode[1] = 0x06008000;
    sp->vifcode[2] = 0x13000000;
    sp->vifcode[3] = 0x50000006;
    *(u128_sd *)&sp->giftag = (u128_sd)0;
    sp->giftag.NLOOP = 5;
    sp->giftag.EOP = 1;
    sp->giftag.NREG = 1;
    sp->giftag.REGS0 = 0xE;
    *(unsigned long *)&sp->bitbltbuf = (unsigned long)sbp | ((unsigned long)sbw << 16) | ((unsigned long)spsm << 24);
    sp->bitbltbufaddr = 0x50;
    *(unsigned long *)&sp->trxpos = (unsigned long)x | ((unsigned long)y << 16);
    sp->trxposaddr = 0x51;
    *(unsigned long *)&sp->trxreg = (unsigned long)w | ((unsigned long)h << 32);
    sp->trxregaddr = 0x52;
    sp->finishaddr = 0x61;
    *(unsigned long *)&sp->trxdir = 1;
    sp->trxdiraddr = 0x53;
    CpuSync();
    return 7;
}
