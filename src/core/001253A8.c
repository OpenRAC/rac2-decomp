#include "common.h"
#include "structs.h"

extern int r1_D_001313EC;

extern int r1_func_0011B4C8();

extern void r1_func_00118C90(int);

extern char r1_D_00132E08[];

extern int r1_func_00121040(int);

extern int r1_D_001325C0;

extern volatile int r1_D_00131414;

extern void r1_func_0011A6C8();

extern int r1_D_001313D0;

extern char r1_D_001530F0[];

extern char r1_D_00153110[];

typedef struct {
    char b[8];
} CdClock;

extern void *r1_func_00121D08();

typedef struct {
    short sceGsInterMode;
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
    volatile int (*sceGsVSCfunc)(int);
    int sceGsVSCid;
} sceGsGParam;

extern void *r1_func_00121D08(void);

          /* sceGsGetGParam */
extern int r1_func_00118DE0();

                /* GsPutIMR */
extern int r1_func_00118AA0();

                /* RemoveIntcHandler */
extern int r1_func_00119328();

extern void r1_func_00118A50(int, int, int);

extern int r1_D_001313E8;
extern int r1_D_001313F0;
extern int r1_func_0011B4C8();
extern int r1_func_00120D28(int);
extern void r1_func_00118C90(int);
extern char r1_D_00132590[];
extern void r1_func_0011A6C8();
extern int r1_D_001313D0;
extern int r1_func_00120E98(void);
extern int r1_func_0011B4C8(void *, int, int, void *, int, void *, int, void *, void *);
extern int r1_D_001313F4 NOT_SDA;
extern char r1_D_001314C0[];
extern char r1_D_001324C0[];
extern int r1_D_00132580 NOT_SDA;
extern char r1_D_001530C8[];
extern char r1_D_001530E0[];
extern volatile int r1_D_00131414;
extern void r1_func_0011AD70(void *, int);
extern void r1_func_00120A88();


/* rac1-decomp src/core/00121750.c: func_001253A8 */
/* Starts reading sectors from the disc into a memory buffer. */
int sceCdRead(int lba, int sectors, void *buf, unsigned char *mode) {
    char *req = r1_D_001314C0;
    int byteCount;
    int rpcResult;

    if ((r1_D_001313F4 & 1) == 0) {
        if (r1_func_00120E98() == 6) {
            return 0;
        }
    }
    if (r1_func_00120D28(4) == 0) {
        return 0;
    }

    *(int *)(req + 0x0) = lba;
    *(int *)(req + 0x4) = sectors;
    *(void **)(req + 0x8) = buf;
    req[0xC] = mode[0];
    req[0xD] = mode[1];
    req[0xE] = mode[2];
    *(void **)(req + 0x10) = r1_D_001324C0;
    *(void **)(req + 0x14) = &r1_D_00132580;

    switch (mode[2]) {
    case 1:
        byteCount = sectors * 0x918;
        break;
    case 2:
        byteCount = sectors * 0x924;
        break;
    case 0:
    default:
        byteCount = sectors << 11;
        break;
    }

    r1_D_00132580 = 0;
    if ((*(volatile int *)&r1_D_001313F4 & 2) == 0) {
        r1_func_0011AD70(buf, byteCount);
    }
    r1_func_0011AD70(r1_D_001324C0, 0x90);
    r1_func_0011AD70(req, 0x18);
    r1_func_0011AD70(&r1_D_00132580, 4);
    if (r1_D_001313D0 > 0) {
        r1_func_0011A6C8(r1_D_001530C8);
    }

    r1_D_00131414 = 1;
    *(volatile int *)&r1_D_001313F0 = 1;
    rpcResult = r1_func_0011B4C8(r1_D_00132590, 1, 1, req, 0x18, 0, 0,
                      (void *)r1_func_00120A88, r1_D_001324C0);
    if (rpcResult < 0) {
        r1_D_00131414 = 0;
        *(volatile int *)&r1_D_001313F0 = 0;
        r1_func_00118C90(*(volatile int *)&r1_D_001313E8);
        return 0;
    }
    if (r1_D_001313D0 > 0) {
        r1_func_0011A6C8(r1_D_001530E0);
    }
    return 1;
}

/* rac1-decomp src/core/00121750.c: func_00121930 */
/* sceCdGetError, r1_func_00120E98's sibling: S-command 3, RPC 4, and -1
   rather than 0 as the failure result.

   The RPC failure is handled first (SignalSema, return -1), then the
   success path. That is the layout retail has, and it keeps 2.9-ee from
   cross-jumping the two `return -1` tails into one (SIZE 144/152 with
   the success path first, which 2.95.3 needed). */
/* Asks the CD drive for its last error code. */
int sceCdGetError(void) {
    int result;

    if (r1_func_00121040(3) == 0) {
        return -1;
    }
    if (r1_func_0011B4C8(r1_D_00132E08, 4, 0, 0, 0, &r1_D_001325C0, 4, 0, 0) < 0) {
        r1_func_00118C90(r1_D_001313EC);
        return -1;
    }
    result = *(int *)((unsigned int)&r1_D_001325C0 | 0x20000000);
    r1_func_00118C90(r1_D_001313EC);
    return result;
}

/* rac1-decomp src/core/00121750.c: func_001219C8 */
/* sceCdBreak, sibling of func_00125588: S-command 0x1E, RPC 0x16 on
   r1_D_00132E08 under the r1_D_001313EC semaphore, with the r1_D_00131414 busy flag
   set around it; returns the reply word read uncached. The volatile flag
   and semaphore reads stay out of the delay slots, where reorg never puts
   a volatile access (this module sees its globals as volatile, as
   cdvd000.o does).

   As in func_00125588, the RPC failure path comes first: with the success
   path first 2.9-ee merges the two `return 0` tails (SIZE 176/184). */
/* Stops the CD command that is running and returns the drive reply. */
int sceCdBreak(void) {
    int result;

    if (r1_func_00121040(0x1E) == 0) {
        return 0;
    }
    r1_D_00131414 = 8;
    if (r1_func_0011B4C8(r1_D_00132E08, 0x16, 0, 0, 0, &r1_D_001325C0, 4, 0, 0) < 0) {
        r1_func_00118C90(*(volatile int *)&r1_D_001313EC);
        r1_D_00131414 = 0;
        return 0;
    }
    r1_D_00131414 = 0;
    result = *(int *)((unsigned int)&r1_D_001325C0 | 0x20000000);
    r1_func_00118C90(*(volatile int *)&r1_D_001313EC);
    return result;
}

/* rac1-decomp src/core/00121750.c: func_00121A80 */
/* sceCdReadClock: S-command 0xF, RPC 1 with a 0x10-byte reply; the
   8-byte clock after the status word is copied out uncached. Failure
   path first, as in func_00125588. */
/* Reads the clock from the CD drive into a small structure. */
int sceCdReadClock(CdClock *clockOut) {
    int status;

    if (r1_func_00121040(0xF) == 0) {
        return 0;
    }
    if (r1_D_001313D0 > 0) {
        r1_func_0011A6C8(r1_D_001530F0);
    }
    if (r1_func_0011B4C8(r1_D_00132E08, 1, 0, 0, 0, &r1_D_001325C0, 0x10, 0, 0) < 0) {
        r1_func_00118C90(r1_D_001313EC);
        return 0;
    }
    *clockOut = *(CdClock *)(((unsigned int)&r1_D_001325C0 + 4) | 0x20000000);
    if (r1_D_001313D0 > 0) {
        r1_func_0011A6C8(r1_D_00153110);
    }
    status = *(int *)((unsigned int)&r1_D_001325C0 | 0x20000000);
    r1_func_00118C90(r1_D_001313EC);
    return status;
}

/* rac1-decomp src/core/00121750.c: func_00121B78 */
  /* SetGsCrt */

/* sceGsResetGraph. Adapted from Lombyte (GPL-3.0) for PAL. */
/* Resets the graphics chip and stores the screen mode settings. */
void sceGsResetGraph(short mode, short inter, short out, short ff) {
    sceGsGParam *gParam;

    switch (mode) {
    case 0:
        gParam = (sceGsGParam *)r1_func_00121D08();
        GS_CSR = 0x200;
        gParam->sceGsInterMode = inter;
        gParam->sceGsOutMode = out;
        gParam->sceGsVersion = (short)((GS_CSR >> 16) & 0xFF);
        r1_func_00118DE0(0xFF00);
        gParam->sceGsFFMode = (ff != 0);
        if (gParam->sceGsVSCfunc != 0) {
            r1_func_00119328(2);
            r1_func_00118AA0(2, gParam->sceGsVSCid);
            gParam->sceGsVSCfunc = 0;
            gParam->sceGsVSCid = 0;
        }
        r1_func_00118A50(inter & 1, out & 0xFF, ff & 1);
        break;
    case 1:
        GS_CSR = 0x100;
        break;
    case 5:
        gParam = (sceGsGParam *)r1_func_00121D08();
        gParam->sceGsFFMode = (ff != 0);
        gParam->sceGsInterMode = inter;
        gParam->sceGsOutMode = out;
        gParam->sceGsVersion = (short)((GS_CSR >> 16) & 0xFF);
        r1_func_00118A50(inter & 1, out & 0xFF, ff & 1);
        break;
    }
}
