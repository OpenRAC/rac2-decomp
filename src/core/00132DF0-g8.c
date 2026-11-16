#include "common.h"

/* func_00132DF0, 736 bytes: 989snd's snd_SendIOPCommandNoWait (rac1's func_0012E820
   twin). A bare command goes out at once through the command RPC when nothing is
   queued or pending; otherwise it waits for room in the current batch, appends the
   command and its data, and records the callback for its reply. -G8 by the file
   name: the batch tables are sized sda arrays ($gp addresses); the RPC client and
   its reply buffer are sda incomplete arrays, rebuilt at each use as retail does. */

extern int g_snd_dma_busy __attribute__((sda));
extern int g_snd_rpc_reply_ptr __attribute__((sda));
extern int g_snd_quiet_flag __attribute__((sda));
extern int g_snd_active_buffer_index __attribute__((sda));
extern int *g_snd_command_buffers[2] __attribute__((sda));
extern int g_snd_command_space_left[2] __attribute__((sda));

typedef struct {
    int fn;
    int pad;
    long data;
} SndRingEntry;

extern SndRingEntry *g_snd_callback_tables[2] __attribute__((sda));
extern int g_sound_rpc_client[] __attribute__((sda));
extern int g_sound_rpc_reply[] __attribute__((sda));
extern char g_str_snd_busy_message[];
extern char g_str_snd_queue_wait[];
extern char g_str_snd_queue_overflow[];

extern void snd_prepare_reply_buffer(void *, int);
extern int sif_rpc_is_handle_valid(void *);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, int);
extern void printf(char *, ...);
extern void FlushCache(int);
extern int snd_Pump(void);
extern void snd_commit_queued_command(void);

/* Queues a sound command with its data and an optional reply callback. Waits if the queue is full. */
void snd_queue_command(int command, int size, unsigned char *data, int callback, long callback_data)
{
    int padded_size;
    int wait_count;
    int held_flag;
    int i;
    int buf_idx;
    unsigned char *dest;

    held_flag = 0;
    if (g_snd_dma_busy == 0 && g_snd_rpc_reply_ptr == 0 && size == 0 && callback == 0) {
        snd_prepare_reply_buffer(g_sound_rpc_reply, 1);
        while (sif_rpc_is_handle_valid(g_sound_rpc_client) != 0) {
            if (g_snd_quiet_flag == 0)
                printf(g_str_snd_busy_message);
            snd_Pump();
            FlushCache(0);
        }
        sceSifCallRpc(g_sound_rpc_client, command, 1, 0, 0, g_sound_rpc_reply, 0xC, 0, 0);
        return;
    }
    padded_size = size + 4;
    wait_count = 0;
    if (padded_size % 4 != 0)
        padded_size += 4 - padded_size % 4;
    while (*g_snd_command_buffers[g_snd_active_buffer_index] == 0x100 || g_snd_command_space_left[g_snd_active_buffer_index] < padded_size) {
        if (g_snd_dma_busy != 0) {
            g_snd_dma_busy = 0;
            held_flag = 1;
        }
        snd_Pump();
        if (wait_count == 1 && g_snd_quiet_flag == 0)
            printf(g_str_snd_queue_overflow, g_snd_active_buffer_index, *g_snd_command_buffers[g_snd_active_buffer_index]);
        wait_count++;
    }
    if (wait_count != 0 && g_snd_quiet_flag == 0)
        printf(g_str_snd_queue_wait, wait_count);
    if (held_flag != 0)
        g_snd_dma_busy = 1;
    dest = (unsigned char *)g_snd_command_buffers[g_snd_active_buffer_index] - (g_snd_command_space_left[g_snd_active_buffer_index] - 0x1000);
    *(short *)dest = command;
    dest += 2;
    *(short *)dest = size;
    dest += 2;
    for (i = 0; i < size; i++)
        dest[i] = data[i];
    g_snd_command_space_left[g_snd_active_buffer_index] -= padded_size;
    buf_idx = g_snd_active_buffer_index;
    g_snd_callback_tables[buf_idx][*g_snd_command_buffers[buf_idx]].fn = callback;
    g_snd_callback_tables[buf_idx][*g_snd_command_buffers[buf_idx]].data = callback_data;
    snd_commit_queued_command();
}
