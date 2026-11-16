#include "names.h"
/* func_00132220, 148 bytes, boot. 989snd's snd_ServiceRpcCompletion: it polls
   the command channel's RPC completion (chan 0x1A7040) and either clears the
   pending descriptor or prints an error.
   The $gp-relative globals are gp-0x7B70 (0x1A7480), -0x7B6C (0x1A7484) and
   -0x7AF8 (0x1A74F8); the unit is built with -G8 by the file name, plus
   -mno-split-addresses: retail keeps `lui $a0,%hi ; addiu $a0,$a0,%lo`
   adjacent with a `nop` in the jal delay slot, which only the single
   (unsplit) symbol operand gives. */
extern unsigned int *g_snd_rpc_reply_ptr __attribute__((sda));
extern unsigned int g_snd_reply_count __attribute__((sda));
extern unsigned int g_snd_quiet_flag __attribute__((sda));

extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(void *);
extern void printf(char *);

extern char g_str_snd_rpc_poll[];
extern char g_sound_rpc_client[] __attribute__((sda));

/* Checks whether the sound server has finished the last request. Returns 1 when it is done and 0 when it is still busy. */
int snd_poll_rpc_done(void) {
    unsigned int *p;

    FlushCache(0);
    if (g_snd_rpc_reply_ptr == 0)
        return 1;
    if (sif_rpc_is_handle_valid(g_sound_rpc_client) != 0)
        return 0;
    p = g_snd_rpc_reply_ptr;
    if (p[0] == 0xFFFFFFFFu && p[1 + g_snd_reply_count] == p[0]) {
        g_snd_rpc_reply_ptr = 0;
        return 1;
    }
    if (g_snd_quiet_flag == 0)
        printf(g_str_snd_rpc_poll);
    return 0;
}
