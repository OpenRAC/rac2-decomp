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

/* Queues a sound command with its data and an optional reply callback. Waits if the queue is full. */
void func_00132DF0(int command, int size, unsigned char *data, int callback, long callbackData)
{
    int paddedSize;
    int waitCount;
    int heldFlag;
    int i;
    int bufIdx;
    unsigned char *dest;

    heldFlag = 0;
    if (D_001A74C4 == 0 && D_001A7480 == 0 && size == 0 && callback == 0) {
        PrepareSoundReplyBuffer(D_001A7080, 1);
        while (IsRpcHandleValid(D_001A7040) != 0) {
            if (D_001A74F8 == 0)
                Printf(D_001A7578);
            snd_Pump();
            FlushCache(0);
        }
        CallRpcServer(D_001A7040, command, 1, 0, 0, D_001A7080, 0xC, 0, 0);
        return;
    }
    paddedSize = size + 4;
    waitCount = 0;
    if (paddedSize % 4 != 0)
        paddedSize += 4 - paddedSize % 4;
    while (*D_001A74A0[D_001A74C0] == 0x100 || D_001A74A8[D_001A74C0] < paddedSize) {
        if (D_001A74C4 != 0) {
            D_001A74C4 = 0;
            heldFlag = 1;
        }
        snd_Pump();
        if (waitCount == 1 && D_001A74F8 == 0)
            Printf(D_0013BFF8, D_001A74C0, *D_001A74A0[D_001A74C0]);
        waitCount++;
    }
    if (waitCount != 0 && D_001A74F8 == 0)
        Printf(D_001A78D0, waitCount);
    if (heldFlag != 0)
        D_001A74C4 = 1;
    dest = (unsigned char *)D_001A74A0[D_001A74C0] - (D_001A74A8[D_001A74C0] - 0x1000);
    *(short *)dest = command;
    dest += 2;
    *(short *)dest = size;
    dest += 2;
    for (i = 0; i < size; i++)
        dest[i] = data[i];
    D_001A74A8[D_001A74C0] -= paddedSize;
    bufIdx = D_001A74C0;
    D_001A74B0[bufIdx][*D_001A74A0[bufIdx]].fn = callback;
    D_001A74B0[bufIdx][*D_001A74A0[bufIdx]].data = callbackData;
    CommitQueuedSoundCommand();
}
