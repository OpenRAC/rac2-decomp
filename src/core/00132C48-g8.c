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
extern int snd_Pump(void);
extern void FlushCache(int);
extern void snd_prepare_reply_buffer(void *, int);
extern int sif_rpc_is_handle_valid(void *);
extern void printf(char *, ...);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, int, int);
extern int snd_poll_rpc_done(void);
extern void snd_submit_dma_buffer(void);
/* Sends a sound command to the sound server and waits for the answer. Returns the reply value. */
int snd_SendCommandSync(int command, int size, void *arg_data) {
    unsigned char *bytes = arg_data;
    int i;
    int result;
    for (i = 0; i < size; i++) D_001A70C0[i] = bytes[i];
    goto check;
    do {
        snd_Pump();
        FlushCache(0);
check:;
    } while (D_001A7480 != 0);
    snd_prepare_reply_buffer(D_001A7080, 1);
    while (sif_rpc_is_handle_valid(D_001A7040) != 0) {
        if (D_001A74F8 == 0) printf(D_001A7578);
        snd_Pump();
        FlushCache(0);
    }
    if (size != 0)
        sceSifCallRpc(D_001A7040, command, 1, D_001A70C0, size, D_001A7080, 12, 0, 0);
    else
        sceSifCallRpc(D_001A7040, command, 1, 0, 0, D_001A7080, 12, 0, 0);
    while (snd_poll_rpc_done() == 0) {}
    result = D_001A7080[1];
    if (*D_001A74A0[D_001A74C0] != 0 && D_001A74C4 == 0) snd_submit_dma_buffer();
    return result;
}
