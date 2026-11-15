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

extern void func_001322B8(void *, int);
extern int func_0011D810(void *);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, int);
extern void func_00115D48(char *, ...);
extern void func_0011AEA0(int);
extern int func_00132028(void);
extern void func_001330D0(void);

/* Queues a sound command (id, payload, callback and data) in the active command buffer,
   sending it at once when the system is idle and it has no payload. */
void func_00132DF0(int cmd, int size, unsigned char *data, int cb, long cb_data)
{
    int need;
    int tries;
    int held;
    int i;
    int slot;
    unsigned char *p;

    held = 0;
    if (D_001A74C4 == 0 && D_001A7480 == 0 && size == 0 && cb == 0) {
        func_001322B8(D_001A7080, 1);
        while (func_0011D810(D_001A7040) != 0) {
            if (D_001A74F8 == 0)
                func_00115D48(D_001A7578);
            snd_Pump();
            func_0011AEA0(0);
        }
        func_0011D620(D_001A7040, cmd, 1, 0, 0, D_001A7080, 0xC, 0, 0);
        return;
    }
    need = size + 4;
    tries = 0;
    if (need % 4 != 0)
        need += 4 - need % 4;
    while (*D_001A74A0[D_001A74C0] == 0x100 || D_001A74A8[D_001A74C0] < need) {
        if (D_001A74C4 != 0) {
            D_001A74C4 = 0;
            held = 1;
        }
        snd_Pump();
        if (tries == 1 && D_001A74F8 == 0)
            func_00115D48(D_0013BFF8, D_001A74C0, *D_001A74A0[D_001A74C0]);
        tries++;
    }
    if (tries != 0 && D_001A74F8 == 0)
        func_00115D48(D_001A78D0, tries);
    if (held != 0)
        D_001A74C4 = 1;
    p = (unsigned char *)D_001A74A0[D_001A74C0] - (D_001A74A8[D_001A74C0] - 0x1000);
    *(short *)p = cmd;
    p += 2;
    *(short *)p = size;
    p += 2;
    for (i = 0; i < size; i++)
        p[i] = data[i];
    D_001A74A8[D_001A74C0] -= need;
    slot = D_001A74C0;
    D_001A74B0[slot][*D_001A74A0[slot]].fn = cb;
    D_001A74B0[slot][*D_001A74A0[slot]].data = cb_data;
    func_001330D0();
}
