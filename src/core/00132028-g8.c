#include "names.h"
/* func_00132028, 488 bytes, boot: 989snd's snd_Pump (RAC1's snd_FlushSoundCommands).
   Once the pending RPC completes it runs the return callback or the callbacks
   queued with the other command buffer; it finishes a CD read (cache flush, then
   the read callback with the reply word); sends the next batch when idle; and
   polls a stop request. Returns whether an RPC or a CD read is still in flight.

   The default split-address profile keeps retail's separate `addiu $a0,$gp,...`
   for the count table: -mno-split-addresses makes (plus reg symbol) a legal address
   and folds it into the indexed load. D_001A7080[1] is the first return word of the
   reply buffer: read as an element it stays out of the delay slot, which retail fills
   from the branch's target; a scalar at that address is moved into the slot. */
#include "common.h"

typedef void (*SndCallback)(int, long);
typedef struct {
    SndCallback fn;
    int pad4;
    long arg;
} SndCommand;

extern int g_snd_rpc_reply_ptr __attribute__((sda));                 /* current buffer */
extern void (*g_snd_stop_callback)(int) __attribute__((sda));        /* stop callback */
extern int g_snd_stop_requested __attribute__((sda));                 /* stop requested */
extern int g_snd_load_ready __attribute__((sda));
extern int g_snd_return_pending __attribute__((sda));                 /* return pending */
extern int *g_snd_command_buffers[2] __attribute__((sda));             /* counts */
extern SndCommand *g_snd_callback_tables[2] __attribute__((sda));      /* commands */
extern int *g_snd_reply_buffers[2] __attribute__((sda));             /* replies */
extern int g_snd_active_buffer_index __attribute__((sda));                 /* batch index */
extern int g_snd_dma_busy __attribute__((sda));
extern int g_snd_cd_read_active __attribute__((sda));                 /* CD read pending */
extern SndCallback g_snd_cd_read_callback __attribute__((sda));         /* CD read callback */
extern SndCallback g_snd_return_callback __attribute__((sda));         /* return callback */
extern long g_snd_return_callback_arg __attribute__((sda));                /* its argument */
/* The CD read callback's argument. No second context is known to write it: this pump
   runs in its callers' thread (func_00132498's commit, d71286afe). The volatile is
   kept only because the unit needs it: without it, or as an incomplete sda array
   (D_001A74D8[0]), func_00132028 is 16 bytes short and matches 0 of 1 in USA v1.01,
   PAL and v2.00 (the accesses become $gp-relative and retail's beql into this block
   is lost). Measured 8 November 2026 with both set-side volatile rules, the EE tree's
   and GCC 2.95's. */
extern volatile long g_snd_cd_read_callback_arg MACRO_ADDR;
extern unsigned int g_bank_rpc_result MACRO_ADDR;
extern int g_sound_rpc_reply[] MACRO_ADDR;                         /* reply buffer */

extern int snd_poll_rpc_done(void);
extern void FlushCache(int);
extern void snd_submit_dma_buffer(void);
extern int snd_CheckLoadInProgress(int);

/* Runs the sound system once per call: finishes the pending sound requests, runs their callbacks, sends the next batch and handles disc reads. Returns nonzero while work is still going on. */
int snd_Pump(void)
{
    int i;
    int idx;
    SndCallback fn;
    long arg;

    if (g_snd_rpc_reply_ptr != 0 && snd_poll_rpc_done() != 0) {
        if (g_snd_return_pending != 0) {
            if (g_snd_return_callback != 0)
                g_snd_return_callback(g_sound_rpc_reply[1], g_snd_return_callback_arg);
            g_snd_return_callback = 0;
            g_snd_return_pending = 0;
        } else {
            idx = g_snd_active_buffer_index != 1;
            for (i = 0; i < *g_snd_command_buffers[idx]; i++) {
                if (g_snd_callback_tables[idx][i].fn != 0)
                    g_snd_callback_tables[idx][i].fn(g_snd_reply_buffers[idx][i + 1], g_snd_callback_tables[idx][i].arg);
            }
        }
    }
    if (g_snd_cd_read_active != 0) {
        FlushCache(0);
        if (g_bank_rpc_result != -1u) {
            if (g_snd_cd_read_callback != 0) {
                arg = g_snd_cd_read_callback_arg;
                fn = g_snd_cd_read_callback;
                g_snd_cd_read_callback = 0;
                g_snd_cd_read_callback_arg = 0;
                fn(g_bank_rpc_result, arg);
            }
            g_bank_rpc_result = 0;
            g_snd_cd_read_active = 0;
        }
    }
    if (g_snd_rpc_reply_ptr == 0) {
        if (*g_snd_command_buffers[g_snd_active_buffer_index] != 0 && g_snd_dma_busy == 0)
            snd_submit_dma_buffer();
    }
    if (g_snd_stop_requested != 0) {
        snd_CheckLoadInProgress(1);
        if (g_snd_load_ready != 0) {
            g_snd_stop_requested = 0;
            g_snd_load_ready = 0;
            if (g_snd_stop_callback != 0)
                g_snd_stop_callback(1);
        }
    }
    return g_snd_rpc_reply_ptr != 0 || g_snd_cd_read_active != 0;
}

