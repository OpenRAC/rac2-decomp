#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));

extern int func_00132028(void);
extern int func_00132C48(int, int, void *);
extern void func_00133580(int);

/* Sends sound command 0x2A with four values once, and remembers the answer so it is not sent twice. */
int func_00133250(int p0, int p1, int p2, int p3) {
    int payload[4];

    if (D_001A748C == 1) {
        return 0;
    }
    if (D_001A74C8 != 0) {
        while (snd_Pump() != 0) {
        }
    }
    snd_CheckLoadInProgress(0);
    payload[0] = p0;
    payload[1] = p1;
    payload[2] = p2;
    payload[3] = p3;
    D_001A748C = snd_SendCommandSync(0x2A, 0x10, payload);
}
