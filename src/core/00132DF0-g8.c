#include "common.h"

/* func_00132DF0, 736 bytes: 989snd's snd_SendIOPCommandNoWait (rac1's func_0012E820
   twin). A bare command goes out at once through the command RPC when nothing is
   queued or pending; otherwise it waits for room in the current batch, appends the
   command and its data, and records the callback for its reply. -G8 by the file
   name: the batch tables are sized sda arrays ($gp addresses); the RPC client and
   its reply buffer are sda incomplete arrays, rebuilt at each use as retail does. */

extern int D_001A74C4 __attribute__((sda));
extern int D_001A7480 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int *D_001A74A0[2] __attribute__((sda));
extern int D_001A74A8[2] __attribute__((sda));

typedef struct {
    int fn;
    int pad;
    long data;
} SndRingEntry;

extern SndRingEntry *D_001A74B0[2] __attribute__((sda));
extern int D_001A7040[] __attribute__((sda));
extern int D_001A7080[] __attribute__((sda));
extern char D_001A7578[];
extern char D_001A78D0[];
extern char D_0013BFF8[];

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
    if (D_001A74C4 == 0 && D_001A7480 == 0 && size == 0 && callback == 0) {
        snd_prepare_reply_buffer(D_001A7080, 1);
        while (sif_rpc_is_handle_valid(D_001A7040) != 0) {
            if (D_001A74F8 == 0)
                printf(D_001A7578);
            snd_Pump();
            FlushCache(0);
        }
        sceSifCallRpc(D_001A7040, command, 1, 0, 0, D_001A7080, 0xC, 0, 0);
        return;
    }
    padded_size = size + 4;
    wait_count = 0;
    if (padded_size % 4 != 0)
        padded_size += 4 - padded_size % 4;
    while (*D_001A74A0[D_001A74C0] == 0x100 || D_001A74A8[D_001A74C0] < padded_size) {
        if (D_001A74C4 != 0) {
            D_001A74C4 = 0;
            held_flag = 1;
        }
        snd_Pump();
        if (wait_count == 1 && D_001A74F8 == 0)
            printf(D_0013BFF8, D_001A74C0, *D_001A74A0[D_001A74C0]);
        wait_count++;
    }
    if (wait_count != 0 && D_001A74F8 == 0)
        printf(D_001A78D0, wait_count);
    if (held_flag != 0)
        D_001A74C4 = 1;
    dest = (unsigned char *)D_001A74A0[D_001A74C0] - (D_001A74A8[D_001A74C0] - 0x1000);
    *(short *)dest = command;
    dest += 2;
    *(short *)dest = size;
    dest += 2;
    for (i = 0; i < size; i++)
        dest[i] = data[i];
    D_001A74A8[D_001A74C0] -= padded_size;
    buf_idx = D_001A74C0;
    D_001A74B0[buf_idx][*D_001A74A0[buf_idx]].fn = callback;
    D_001A74B0[buf_idx][*D_001A74A0[buf_idx]].data = callback_data;
    snd_commit_queued_command();
}
