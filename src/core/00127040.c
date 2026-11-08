#include "common.h"
#include "structs.h"

extern int func_00127040(void *);

typedef struct {
    unsigned char sts;
    unsigned char std;
    unsigned char mfd;
    unsigned char rcyc;
    unsigned short express;
    unsigned short notify;
    unsigned short sqwc;
    unsigned short tqwc;
    void *rbadr;
    unsigned int rbmsk;
} sceDmaEnv;

extern unsigned char r1_D_00153520[];

extern unsigned char r1_D_00153530[];

extern unsigned char r1_D_00153540[];

extern sceDmaEnv r1_D_00159AD8;

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern int func_001272A8(void *);

extern void r1_func_00118C90(int);

extern int r1_D_00132EAC;

extern char r1_D_00159B00[];

extern char r1_D_0015B0C0[];

extern int r1_func_0011B4C8();

extern int r1_func_00118CC0(int);

extern char r1_D_00159BB0[];

extern void *r1_func_00116B00(void *, const void *, int);

extern int r1_D_00132EA8;

extern int func_00127508(int, int, int, int);

/* rac1-decomp src/core/00123168.c: func_001233E8 */
/* sceDmaPutEnv. Adapted from Lombyte (GPL-3.0) for PAL. */
int func_00127040(void *arg0) {
    sceDmaEnv *env = arg0;
    unsigned int ctrl;
    unsigned int pcr;
    unsigned int sqwc;
    unsigned int rbor;
    unsigned int rbsr;

    ctrl = *(volatile unsigned int *)0x1000E000;
    pcr = *(volatile unsigned int *)0x1000E020;
    sqwc = *(volatile unsigned int *)0x1000E030;
    rbor = *(volatile unsigned int *)0x1000E050;
    rbsr = *(volatile unsigned int *)0x1000E040;
    if (env->sts >= 10) {
        return -1;
    }
    if (env->std >= 10) {
        return -2;
    }
    if (env->mfd >= 10) {
        return -3;
    }
    if (env->rcyc >= 7) {
        return -4;
    }
    ctrl = (ctrl & ~0x30) | (r1_D_00153520[env->sts] << 4);
    ctrl = (ctrl & ~0xC0) | (r1_D_00153530[env->std] << 6);
    ctrl = (ctrl & ~0xC) | (r1_D_00153540[env->mfd] << 2);
    if (env->rcyc != 0) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300) | ((env->rcyc - 1) << 8);
    } else {
        ctrl &= ~2;
    }
    pcr = (env->express << 16) | env->notify;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (unsigned int)env->rbadr;
    rbsr = env->rbmsk;
    *(volatile unsigned int *)0x1000E000 = ctrl;
    *(volatile unsigned int *)0x1000E020 = pcr;
    *(volatile unsigned int *)0x1000E030 = sqwc;
    *(volatile unsigned int *)0x1000E050 = rbor;
    *(volatile unsigned int *)0x1000E040 = rbsr;
    r1_D_00159AD8 = *env;
    return 0;
}

extern int func_00126ED8(int);

extern void func_00126E60(void *);

void func_00127218(int *p, int arg1) {
    int r = func_00126ED8(arg1);

    func_00126E60(p);
    if ((unsigned int)p[12] != 0xFFFFFFFFU) {
        p[12] = r;
    }
    p[8] = 0;
    p[0] = (p[0] & ~0xC) | 0x105;
}


/* rac1-decomp src/core/00123168.c: func_00123650 */
/*
 * sceDmaPause: DI (r1_func_0011D960), force D_ENABLEW.CPND (0x10000) if
 * D_ENABLER has it clear, read D_CTRL (a volatile read for its side
 * effect only), clear the channel's CHCR.STR (bit 8), restore
 * D_ENABLEW, EI (r1_func_0011D9A8) if DI said interrupts were on, and
 * return the old CHCR.
 *
 * Exact under 2.9-ee. The mask has to be an unsigned constant
 * (`old & 0xFFFFFEFF`; `~0x100` is one addiu, SIZE 148), and the channel
 * word goes through a `volatile unsigned int *`, which keeps its load
 * after the D_CTRL read and gives retail's $4-$7 allocation. Under
 * 2.95.3 the same C differs in the prologue order only (8/152).
 */
int func_001272A8(void *arg0) {
    volatile unsigned int *d = arg0;
    int en;
    unsigned int prev, old;
    en = r1_func_0011D960();
    prev = *(volatile unsigned int *)0x1000F520;
    if ((prev & 0x10000) == 0)
        *(volatile unsigned int *)0x1000F590 = prev | 0x10000;
    *(volatile unsigned int *)0x1000E000;
    old = *d;
    *d = old & 0xFFFFFEFF;
    *(volatile unsigned int *)0x1000F590 = prev;
    if (en != 0) r1_func_0011D9A8();
    return old;
}

typedef struct {
    char pad[0x24];
    void *serve;
} SifRpcClientData;

extern int r1_func_00118C70(void *);
extern int r1_func_00123F30(int, int *, int *);
extern int r1_func_00118CB0(int);
extern int r1_func_0011AE20(int);
extern int r1_func_0011B2F8(void *, int, int);
extern void r1_func_0011A6C8(char *);
extern char r1_D_00159B80[];
extern char r1_D_00153550[];
extern char r1_D_00153568[];
extern char r1_D_00153590[];

/* rac1-decomp src/core/001236F0.c: func_001236F0 */
/* sceMcInit (libmc): one-shot init. Creates the module semaphore if not yet
   valid, resets any pending command (sceMcSync), takes the semaphore, brings up
   the SIF RPC layer and loops binding the IOP memory-card RPC server (0x80000400)
   until the client data's serve pointer is set, busy-waiting between binds; a
   bind failure prints and hangs forever. Once bound, issues RPC 0xFE (a
   handshake/version query) and validates the two version words in the reply,
   printing and clearing serve on any failure. */
int func_00127340(void) {
    int buf[8];
    int *rbuf;
    int i;
    int r;

    if (r1_D_00132EAC < 0) {
        buf[5] = 0;
        buf[2] = 1;
        buf[1] = 1;
        r1_D_00132EAC = r1_func_00118C70(buf);
    }
    r1_func_00123F30(0, 0, 0);
    r1_func_00118CB0(r1_D_00132EAC);
    r1_func_0011AE20(0);
    for (;;) {
        if (r1_func_0011B2F8(r1_D_00159B00, 0x80000400, 0) < 0) {
            r1_func_0011A6C8(r1_D_00153550);
            for (;;) ;
        }
        if (((SifRpcClientData *)r1_D_00159B00)->serve != 0) break;
        for (i = 0x100000; i != 0; i--) ;
    }
    r = r1_func_0011B4C8(r1_D_00159B00, 0xFE, 0, r1_D_00159B80, 0x30, r1_D_0015B0C0, 0xC, 0, 0);
    r1_func_00118C90(r1_D_00132EAC);
    if (r < 0) {
        ((SifRpcClientData *)r1_D_00159B00)->serve = 0;
        return r - 100;
    }
    rbuf = (int *)r1_D_0015B0C0;
    if (rbuf[1] < 0x20A) {
        r1_func_0011A6C8(r1_D_00153568);
        ((SifRpcClientData *)r1_D_00159B00)->serve = 0;
        return -0x78;
    }
    if (rbuf[2] < 0x20E) {
        r1_func_0011A6C8(r1_D_00153590);
        ((SifRpcClientData *)r1_D_00159B00)->serve = 0;
        return -0x79;
    }
    return *(int *)r1_D_0015B0C0;
}


/* rac1-decomp src/core/001236F0.c: func_001238B0 */
/* sceMcOpen(port, slot, fname, mode) (libmc): same RPC-wrapper shape as
   sceMcDelete (func_00128068) but with the flags/mode argument stored to
   the descriptor's +0x8 word instead of a hardcoded 0, and RPC command 2. */
int func_00127508(int port, int slot, int fname_, int mode) {
    char *cd = r1_D_00159B00;
    char *fname = (char *)fname_;
    char *fp;
    int r;

    if (*(int *)(cd + 0x24) == 0) {
        return -100;
    }
    if (r1_func_00118CC0(r1_D_00132EAC) < 0) {
        return -200;
    }
    if (fname == 0 || *fname == 0) {
        r1_func_00118C90(r1_D_00132EAC);
        return -210;
    }
    r1_func_00116B00(r1_D_00159BB0 + 0x14, fname, 0x3FF);
    fp = r1_D_00159BB0;
    *(int *)(fp + 0x0) = port;
    fp[0x413] = 0;
    *(int *)(fp + 0x8) = mode;
    *(int *)(fp + 0x4) = slot;
    r = r1_func_0011B4C8(cd, 2, 1, fp, 0x414, r1_D_0015B0C0, 4, 0, 0);
    if (r == 0) {
        r1_D_00132EA8 = 2;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return r;
}
