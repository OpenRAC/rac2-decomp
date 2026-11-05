#include "common.h"

extern void func_0011CF78(int);
extern int func_0011D450(void *, int, int);
extern int func_0011D810(void *);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, void *);
typedef struct {
    int base, size, cd[10], cursor, count, extra;
} RpcBufferState;
extern RpcBufferState D_001A7240 __attribute__((sda));
extern int D_00215050[][4];

/* Bind asynchronously, obtain the remote buffer descriptor and clear the slots. */
void func_002EEBC8(void) {
    int reply[4];
    int i;
    func_0011CF78(0);
    for (;;) {
        if (func_0011D450(D_001A7240.cd, 0x11, 1) < 0) {
            for (;;) {
            }
        }
        while (func_0011D810(D_001A7240.cd) != 0) {
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
    func_0011D620(D_001A7240.cd, 2, 0, 0, 0, reply, 16, 0, 0);
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
