#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));

extern int snd_Pump(void);
extern int snd_SendCommandSync(int, int, void *);
extern int snd_CheckLoadInProgress(int);

/* Sends sound command 0x2A with four values once, and remembers the answer so it is not sent twice. */
int snd_send_cmd2a_once(int p0, int p1, int p2, int p3) {
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
