#include "common.h"

extern void sceSifInitRpc(int);
extern int sceSifBindRpc(void *, int, int);
extern int sif_rpc_is_handle_valid(void *);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);
typedef struct {
    int base, size, cd[10], cursor, count, extra;
} RpcBufferState;
extern RpcBufferState D_001A7240 __attribute__((sda));
extern int D_00215050[][4];

/* Bind asynchronously, obtain the remote buffer descriptor and clear the slots. */
/* Connects to the remote IO server, waits until it is ready, reads its buffer size, and clears the table of 64 buffer slots. */
void iop_init_remote_buffer_server(void) {
    int reply[4];
    int i;
    sceSifInitRpc(0);
    for (;;) {
        if (sceSifBindRpc(D_001A7240.cd, 0x11, 1) < 0) {
            for (;;) {
            }
        }
        while (sif_rpc_is_handle_valid(D_001A7240.cd) != 0) {
        }
        if (D_001A7240.cd[9] != 0) {
            goto bound;
        }
        /* Retail waits this many iterations before retrying an unbound server. */
        i = 0xFFFF;
        while (i--) {
        }
    }
bound:
    sceSifCallRpc(D_001A7240.cd, 2, 0, 0, 0, reply, 16, 0, 0);
    D_001A7240.base = reply[0];
    D_001A7240.size = reply[1];
    D_001A7240.cursor = reply[0];
    D_001A7240.extra = reply[2];
    D_001A7240.count = 0;
    for (i = 0; i < 64; i++) {
        D_00215050[i][0] = 0;
        D_00215050[i][1] = 0;
    }
}
