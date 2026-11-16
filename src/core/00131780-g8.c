#include "common.h"

extern int r1_D_0015EDC4 __attribute__((sda));
extern int snd_Pump(void);

/* Clears a sound flag and runs the sound update. */
void snd_clear_flag_and_update(void) {
    r1_D_0015EDC4 = 0;
    snd_Pump();
}

extern int g_snd_quiet_flag __attribute__((sda));
extern char g_str_snd_busy_message[];
extern void printf(const void *, ...);
extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(const void *);
extern int sceSifCallRpc(const void *, int, int, int *, int, int *, int, int, int);
extern int *g_snd_command_buffers[2] __attribute__((sda));
extern int g_snd_command_space_left[2] __attribute__((sda));
extern int *g_snd_reply_buffers[2] __attribute__((sda));
extern int g_snd_active_buffer_index __attribute__((sda));
extern int g_sound_rpc_client;
extern void snd_prepare_reply_buffer(void *, int, void *);
/* Sends the filled sound data buffer by DMA and switches to the other buffer. */
void snd_submit_dma_buffer(void) {
    snd_prepare_reply_buffer(g_snd_reply_buffers[g_snd_active_buffer_index], *g_snd_command_buffers[g_snd_active_buffer_index], g_snd_command_buffers[g_snd_active_buffer_index]);
    while (sif_rpc_is_handle_valid(&g_sound_rpc_client)) {
        if (g_snd_quiet_flag == 0)
            printf(g_str_snd_busy_message);
        FlushCache(0);
    }
    sceSifCallRpc(&g_sound_rpc_client, 0x4D, 1, g_snd_command_buffers[g_snd_active_buffer_index], 0x1000-g_snd_command_space_left[g_snd_active_buffer_index], g_snd_reply_buffers[g_snd_active_buffer_index], (*g_snd_command_buffers[g_snd_active_buffer_index] << 2)+8, 0, 0);
    {
        int next = (g_snd_active_buffer_index ^ 1) != 0;
        g_snd_active_buffer_index = next;
        *g_snd_command_buffers[next] = 0;
        g_snd_command_space_left[next] = 0xFFC;
    }
}

extern int g_snd_cd_read_active __attribute__((sda));
extern int g_snd_bank_load_status __attribute__((sda));
extern int g_snd_cd_read_callback __attribute__((sda));
extern int g_bank_rpc_arg_bank MACRO_ADDR;
extern unsigned int g_bank_rpc_result MACRO_ADDR;
extern long g_snd_cd_read_callback_arg MACRO_ADDR;
extern int g_bank_rpc_client MACRO_ADDR;
extern char g_str_snd_cd_read_busy[];
/* Starts a disc read for the sound system and remembers the function to call when it is done. */
void snd_start_cd_read(int a, int c, long d) {
    g_snd_bank_load_status = 0;
    if (g_snd_cd_read_active != 0) {
        if (g_snd_quiet_flag != 0) return;
        printf(g_str_snd_cd_read_busy);
        return;
    }
    do {
        g_bank_rpc_arg_bank = a;
        g_snd_cd_read_callback = c;
        g_bank_rpc_result = -1u;
        g_snd_cd_read_callback_arg = d;
    } while (0);
    while (sif_rpc_is_handle_valid(&g_bank_rpc_client)) {
        if (g_snd_quiet_flag == 0) printf(g_str_snd_busy_message);
        snd_Pump();
        FlushCache(0);
    }
    g_snd_cd_read_active = 1;
    sceSifCallRpc(&g_bank_rpc_client, 0x57, 1, &g_bank_rpc_arg_bank, 4, (int *)&g_bank_rpc_result, 4, 0, 0);
}
