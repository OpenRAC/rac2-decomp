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
/* Applies a DMA settings block to the DMA controller registers, and returns a negative number if any value is out of range. */
int func_00127040(void *envPtr) {
    sceDmaEnv *env = envPtr;
    unsigned int ctrl;
    unsigned int pcr;
    unsigned int sqwc;
    unsigned int rbor;
    unsigned int rbsr;

    ctrl = D_CTRL;
    pcr = D_PCR;
    sqwc = D_SQWC;
    rbor = D_RBOR;
    rbsr = D_RBSR;
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
    D_CTRL = ctrl;
    D_PCR = pcr;
    D_SQWC = sqwc;
    D_RBOR = rbor;
    D_RBSR = rbsr;
    r1_D_00159AD8 = *env;
    return 0;
}

extern int func_00126ED8(int);

extern void func_00126E60(void *);

/* Resets a DMA channel record and stores a converted value in it. */
void func_00127218(int *channel, int input) {
    int converted = ConvertScratchpadDmaAddress(input);

    WaitDmaChannelDone(channel);
    if ((unsigned int)channel[12] != 0xFFFFFFFFU) {
        channel[12] = converted;
    }
    channel[8] = 0;
    channel[0] = (channel[0] & ~0xC) | 0x105;
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
/* Pauses a DMA channel with interrupts off and returns its old control value. */
int func_001272A8(void *channelAddr) {
    volatile unsigned int *chcr = channelAddr;
    int intWasOn;
    unsigned int savedEnable, oldChcr;
    intWasOn = r1_func_0011D960();
    savedEnable = D_ENABLER;
    if ((savedEnable & 0x10000) == 0)
        D_ENABLEW = savedEnable | 0x10000;
    D_CTRL;
    oldChcr = *chcr;
    *chcr = oldChcr & 0xFFFFFEFF;
    D_ENABLEW = savedEnable;
    if (intWasOn != 0) r1_func_0011D9A8();
    return oldChcr;
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
/* Starts up the memory card library: finds the memory card server and checks its version. */
int func_00127340(void) {
    int semaParam[8];
    int *reply;
    int i;
    int result;

    if (r1_D_00132EAC < 0) {
        semaParam[5] = 0;
        semaParam[2] = 1;
        semaParam[1] = 1;
        r1_D_00132EAC = r1_func_00118C70(semaParam);
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
    result = r1_func_0011B4C8(r1_D_00159B00, 0xFE, 0, r1_D_00159B80, 0x30, r1_D_0015B0C0, 0xC, 0, 0);
    r1_func_00118C90(r1_D_00132EAC);
    if (result < 0) {
        ((SifRpcClientData *)r1_D_00159B00)->serve = 0;
        return result - 100;
    }
    reply = (int *)r1_D_0015B0C0;
    if (reply[1] < 0x20A) {
        r1_func_0011A6C8(r1_D_00153568);
        ((SifRpcClientData *)r1_D_00159B00)->serve = 0;
        return -0x78;
    }
    if (reply[2] < 0x20E) {
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
/* Opens a file on a memory card and returns a request handle, or a negative error. */
int func_00127508(int port, int slot, int fnameAddr, int mode) {
    char *client = r1_D_00159B00;
    char *fname = (char *)fnameAddr;
    char *request;
    int result;

    if (*(int *)(client + 0x24) == 0) {
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
    request = r1_D_00159BB0;
    *(int *)(request + 0x0) = port;
    request[0x413] = 0;
    *(int *)(request + 0x8) = mode;
    *(int *)(request + 0x4) = slot;
    result = r1_func_0011B4C8(client, 2, 1, request, 0x414, r1_D_0015B0C0, 4, 0, 0);
    if (result == 0) {
        r1_D_00132EA8 = 2;
    } else {
        r1_func_00118C90(r1_D_00132EAC);
    }
    return result;
}
