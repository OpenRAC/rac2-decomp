#include "names.h"
/* snd_SendCommandSync; adapted from rac1-decomp src/core/989snd.c
 * snd_SendIOPCommandAndWait (GPL-3.0). RPC buffers use absolute macro
 * addresses; the default split profile keeps the diagnostic base in s1. */
#include "common.h"
extern unsigned char g_sound_rpc_send_buffer[] MACRO_ADDR;
extern int g_sound_rpc_reply[] MACRO_ADDR;
extern char g_sound_rpc_client[] MACRO_ADDR;
extern char g_str_snd_busy_message[];
extern int g_snd_rpc_reply_ptr __attribute__((sda));
extern int g_snd_quiet_flag __attribute__((sda));
extern int g_snd_active_buffer_index __attribute__((sda));
extern int g_snd_dma_busy __attribute__((sda));
extern int *g_snd_command_buffers[2] __attribute__((sda));
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
    for (i = 0; i < size; i++) g_sound_rpc_send_buffer[i] = bytes[i];
    goto check;
    do {
        snd_Pump();
        FlushCache(0);
check:;
    } while (g_snd_rpc_reply_ptr != 0);
    snd_prepare_reply_buffer(g_sound_rpc_reply, 1);
    while (sif_rpc_is_handle_valid(g_sound_rpc_client) != 0) {
        if (g_snd_quiet_flag == 0) printf(g_str_snd_busy_message);
        snd_Pump();
        FlushCache(0);
    }
    if (size != 0)
        sceSifCallRpc(g_sound_rpc_client, command, 1, g_sound_rpc_send_buffer, size, g_sound_rpc_reply, 12, 0, 0);
    else
        sceSifCallRpc(g_sound_rpc_client, command, 1, 0, 0, g_sound_rpc_reply, 12, 0, 0);
    while (snd_poll_rpc_done() == 0) {}
    result = g_sound_rpc_reply[1];
    if (*g_snd_command_buffers[g_snd_active_buffer_index] != 0 && g_snd_dma_busy == 0) snd_submit_dma_buffer();
    return result;
}
