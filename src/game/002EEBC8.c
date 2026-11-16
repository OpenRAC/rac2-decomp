#include "common.h"

extern void sceSifInitRpc(int);
extern int sceSifBindRpc(void *, int, int);
extern int sif_rpc_is_handle_valid(void *);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
typedef struct {
    int base, size, cd[10], cursor, count, extra;
} RpcBufferState;
extern RpcBufferState g_buffer_slot_queue __attribute__((sda));
extern int g_gfx_buffer_slot_table[][4];

/* Bind asynchronously, obtain the remote buffer descriptor and clear the slots. */
/* Connects to the remote IO server, waits until it is ready, reads its buffer size, and clears the table of 64 buffer slots. */
void iop_init_remote_buffer_server(void) {
    int reply[4];
    int i;
    sceSifInitRpc(0);
    for (;;) {
        if (sceSifBindRpc(g_buffer_slot_queue.cd, 0x11, 1) < 0) {
            for (;;) {
            }
        }
        while (sif_rpc_is_handle_valid(g_buffer_slot_queue.cd) != 0) {
        }
        if (g_buffer_slot_queue.cd[9] != 0) {
            goto bound;
        }
        /* Retail waits this many iterations before retrying an unbound server. */
        i = 0xFFFF;
        while (i--) {
        }
    }
bound:
    sceSifCallRpc(g_buffer_slot_queue.cd, 2, 0, 0, 0, reply, 16, 0, 0);
    g_buffer_slot_queue.base = reply[0];
    g_buffer_slot_queue.size = reply[1];
    g_buffer_slot_queue.cursor = reply[0];
    g_buffer_slot_queue.extra = reply[2];
    g_buffer_slot_queue.count = 0;
    for (i = 0; i < 64; i++) {
        g_gfx_buffer_slot_table[i][0] = 0;
        g_gfx_buffer_slot_table[i][1] = 0;
    }
}
