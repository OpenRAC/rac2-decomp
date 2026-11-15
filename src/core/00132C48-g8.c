/* snd_SendCommandSync; adapted from rac1-decomp src/core/989snd.c
 * snd_SendIOPCommandAndWait (GPL-3.0). RPC buffers use absolute macro
 * addresses; the default split profile keeps the diagnostic base in s1. */
#include "common.h"
extern unsigned char D_001A70C0[] MACRO_ADDR;
extern int D_001A7080[] MACRO_ADDR;
extern char D_001A7040[] MACRO_ADDR;
extern char D_001A7578[];
extern int D_001A7480 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int D_001A74C4 __attribute__((sda));
extern int *D_001A74A0[2] __attribute__((sda));
extern int func_00132028(void);
extern void func_0011AEA0(int);
extern void func_001322B8(void *, int);
extern int func_0011D810(void *);
extern void func_00115D48(char *, ...);
extern int func_0011D620(void *, int, int, void *, int, void *, int, int, int);
extern int func_00132220(void);
extern void func_00133108(void);
/* Sends a sound command to the sound server and waits for the answer. Returns the reply value. */
int func_00132C48(int command, int size, void *argData) {
    unsigned char *bytes = argData;
    int i;
    int result;
    for (i = 0; i < size; i++) D_001A70C0[i] = bytes[i];
    goto check;
    do {
        snd_Pump();
        FlushCache(0);
check:;
    } while (D_001A7480 != 0);
    PrepareSoundReplyBuffer(D_001A7080, 1);
    while (IsRpcHandleValid(D_001A7040) != 0) {
        if (D_001A74F8 == 0) Printf(D_001A7578);
        snd_Pump();
        FlushCache(0);
    }
    if (size != 0)
        CallRpcServer(D_001A7040, command, 1, D_001A70C0, size, D_001A7080, 12, 0, 0);
    else
        CallRpcServer(D_001A7040, command, 1, 0, 0, D_001A7080, 12, 0, 0);
    while (PollSoundRpcDone() == 0) {}
    result = D_001A7080[1];
    if (*D_001A74A0[D_001A74C0] != 0 && D_001A74C4 == 0) SubmitSoundDmaBuffer();
    return result;
}
