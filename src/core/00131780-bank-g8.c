#include "common.h"

extern int g_snd_cd_read_active __attribute__((sda));
extern int g_snd_bank_load_status __attribute__((sda));
extern int g_snd_quiet_flag __attribute__((sda));
extern int g_snd_cd_read_callback __attribute__((sda));
extern int g_bank_rpc_arg_bank MACRO_ADDR;
extern unsigned int g_bank_rpc_result MACRO_ADDR;
/* The CD read callback (D_001A74D0) and its argument (D_001A74D8) form one SndCommand
   record (00132028-g8.c): a word callback, 4 bytes of padding and a doubleword
   argument, as the return callback and its argument at 0x001A74E0/E8 do. This
   doubleword view of the record stores the argument as its second element, an sda
   symbol+offset access, which docs/build/compiler-notes.md ("reorg: which global loads may
   fill a slot") shows never fills a delay slot: the store stays where retail has it. */
extern long D_001A74D0_1[] __attribute__((sda));
extern int g_bank_rpc_client MACRO_ADDR;
extern char g_str_snd_busy_message[];
extern void printf(const void *, ...);
extern int snd_Pump(void);
extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(const void *);
extern int sceSifCallRpc(const void *, int, int, int *, int, unsigned int *, int, int, int);
extern int g_bank_rpc_arg_offset MACRO_ADDR;
extern char g_str_snd_bank_read_start[], g_str_snd_bank_read_busy[];
extern int snd_CheckLoadInProgress(int);
/* Starts reading a sound bank from disc and remembers the function to call when it is done. */
void snd_start_bank_read(int bank, int offset, int callback, long callback_data) {
    g_snd_bank_load_status = 0;
    if (g_snd_cd_read_active != 0) {
        if (g_snd_quiet_flag != 0) return;
        printf(g_str_snd_bank_read_start);
        return;
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        if (g_snd_quiet_flag != 0) return;
        printf(g_str_snd_bank_read_busy);
        return;
    }
    g_bank_rpc_arg_bank = bank;
    g_bank_rpc_arg_offset = offset;
    g_bank_rpc_result = -1u;
    g_snd_cd_read_callback = callback;
    D_001A74D0_1[1] = callback_data;
    while (sif_rpc_is_handle_valid(&g_bank_rpc_client)) {
        if (g_snd_quiet_flag == 0) printf(g_str_snd_busy_message);
        snd_Pump();
        FlushCache(0);
    }
    g_snd_cd_read_active = 1;
    sceSifCallRpc(&g_bank_rpc_client, 3, 1, &g_bank_rpc_arg_bank, 8, &g_bank_rpc_result, 4, 0, 0);
}
