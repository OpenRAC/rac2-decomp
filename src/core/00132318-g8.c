#include "names.h"
/* snd_BankLoadByLoc and snd_BankLoadFromIOP (989snd): synchronous bank loads over RPC.

   Both end by waiting for the RPC reply word, which RAC1 writes as a plain
   if/do-while. Here that spelling gets one NOP too many: retail's wait loop reads the
   word with two instructions and is padded by words, while this compiler's padding
   pass counts a macro load as one insn. So the loop reads through D_001A7180_abs, a
   split %hi/%lo pair that counts as two, and has to keep that %hi inside the loop:
   - the jump to `done` enters the loop from outside, so loop.c leaves it alone; it
     is still a real loop, whose label keeps retail's .p2align 3. Nothing is hoisted,
     so the sentinel is a local set in front of the loop;
   - -fno-gcse stops PRE hoisting the %hi instead.
   -fno-cse-follow-jumps keeps the separate read at `reread`, which reorg moves into
   the branch's delay slot, where retail reads the reply again through $gp. */
#include "common.h"

extern int g_snd_cd_read_active __attribute__((sda));
extern int g_snd_bank_load_status __attribute__((sda));
extern int g_snd_quiet_flag __attribute__((sda));
/* The RPC reply word: a macro load outside delay slots, $gp inside them. */
extern unsigned int g_bank_rpc_result MACRO_ADDR;
/* The same word for the final wait loops, read as a split %hi/%lo pair. */
extern unsigned int D_001A7180_abs __asm__("D_001A7180") NOT_SDA;
extern int g_bank_rpc_arg_bank MACRO_ADDR;
extern int g_bank_rpc_arg_offset MACRO_ADDR;
extern int g_bank_rpc_client MACRO_ADDR;
extern char g_str_snd_busy_message[];
extern char g_str_snd_bank_read_start[];
extern char g_str_snd_bank_read_busy[];
extern char g_str_snd_bank_load_by_loc[];
extern char g_str_snd_iop_load_start[];
extern char g_str_snd_iop_load_busy[];

extern void printf(const void *, ...);
extern int snd_CheckLoadInProgress(int);
extern int snd_Pump(void);
extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(const void *);
extern int sceSifCallRpc(const void *, int, int, int *, int, unsigned int *, int, int, int);

/* Loads a sound bank from a disc position and waits for the answer. */
unsigned int snd_BankLoadByLoc(int loc, int offset) {
    unsigned int reply;
    unsigned int busy;

    g_snd_bank_load_status = 0;
    if (g_snd_cd_read_active != 0) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_bank_read_start);
        return 0;
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_bank_read_busy);
        return 0;
    }
    g_bank_rpc_arg_bank = loc;
    g_bank_rpc_arg_offset = offset;
    g_bank_rpc_result = -1u;
    while (sif_rpc_is_handle_valid(&g_bank_rpc_client) != 0) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_busy_message);
        snd_Pump();
        FlushCache(0);
    }
    if (sceSifCallRpc(&g_bank_rpc_client, 3, 1, &g_bank_rpc_arg_bank, 8, &g_bank_rpc_result, 4, 0, 0) < 0) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_bank_load_by_loc);
        g_snd_bank_load_status = 0x106;
        return 0;
reread:
        reply = g_bank_rpc_result;
        goto done;
    }
    if (g_bank_rpc_result != -1u)
        goto reread;
    busy = -1u;
    for (;;) {
        FlushCache(0);
        reply = D_001A7180_abs;
        if (reply != busy) {
done:
            return reply;
        }
    }
}

/* Loads a sound bank by id and waits for the answer. */
unsigned int snd_BankLoadFromIOP(int bank_id) {
    unsigned int reply;
    unsigned int busy;

    g_snd_bank_load_status = 0;
    if (g_snd_cd_read_active != 0) {
        if (g_snd_quiet_flag != 0)
            return 0;
        printf(g_str_snd_iop_load_start);
        return 0;
    }
    g_bank_rpc_arg_bank = bank_id;
    g_bank_rpc_result = -1u;
    while (sif_rpc_is_handle_valid(&g_bank_rpc_client) != 0) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_busy_message);
        snd_Pump();
        FlushCache(0);
    }
    if (sceSifCallRpc(&g_bank_rpc_client, 0x59, 1, &g_bank_rpc_arg_bank, 4, &g_bank_rpc_result, 4, 0,
                      0) < 0) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_iop_load_busy);
        g_snd_bank_load_status = 0x106;
        return 0;
reread:
        reply = g_bank_rpc_result;
        goto done;
    }
    if (g_bank_rpc_result != -1u)
        goto reread;
    busy = -1u;
    for (;;) {
        FlushCache(0);
        reply = D_001A7180_abs;
        if (reply != busy) {
done:
            return reply;
        }
    }
}
