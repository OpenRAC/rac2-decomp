#include "common.h"

extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74D0 __attribute__((sda));
extern int D_001A71C0 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
/* The CD read callback (D_001A74D0) and its argument (D_001A74D8) form one SndCommand
   record (00132028-g8.c): a word callback, 4 bytes of padding and a doubleword
   argument, as the return callback and its argument at 0x001A74E0/E8 do. This
   doubleword view of the record stores the argument as its second element, an sda
   symbol+offset access, which docs/build/compiler-notes.md ("reorg: which global loads may
   fill a slot") shows never fills a delay slot: the store stays where retail has it. */
extern long D_001A74D0_1[] __attribute__((sda));
extern int D_001A7140 MACRO_ADDR;
extern char D_001A7578[];
extern void printf(const void *, ...);
extern int snd_Pump(void);
extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(const void *);
extern int sceSifCallRpc(const void *, int, int, int *, int, unsigned int *, int, int, int);
extern int D_001A71C4 MACRO_ADDR;
extern char D_001A7600[], D_001A7630[];
extern int snd_CheckLoadInProgress(int);
/* Starts reading a sound bank from disc and remembers the function to call when it is done. */
void snd_start_bank_read(int bank, int offset, int callback, long callback_data) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) return;
        printf(D_001A7600);
        return;
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        if (D_001A74F8 != 0) return;
        printf(D_001A7630);
        return;
    }
    D_001A71C0 = bank;
    D_001A71C4 = offset;
    D_001A7180 = -1u;
    D_001A74D0 = callback;
    D_001A74D0_1[1] = callback_data;
    while (sif_rpc_is_handle_valid(&D_001A7140)) {
        if (D_001A74F8 == 0) printf(D_001A7578);
        snd_Pump();
        FlushCache(0);
    }
    D_001A74C8 = 1;
    sceSifCallRpc(&D_001A7140, 3, 1, &D_001A71C0, 8, &D_001A7180, 4, 0, 0);
}
