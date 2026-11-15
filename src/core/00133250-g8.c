#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));

extern int func_00132028(void);
extern int func_00132C48(int, int, void *);
extern void func_00133580(int);

/* Sends sound command 0x2A with four ints (after finishing pending work) and stores the result
   in D_001A748C; does nothing if D_001A748C is 1. */
int func_00133250(int arg0, int arg1, int arg2, int arg3) {
    int args[4];

    if (D_001A748C == 1) {
        return 0;
    }
    if (D_001A74C8 != 0) {
        while (snd_Pump() != 0) {
        }
    }
    snd_CheckLoadInProgress(0);
    args[0] = arg0;
    args[1] = arg1;
    args[2] = arg2;
    args[3] = arg3;
    D_001A748C = snd_SendCommandSync(0x2A, 0x10, args);
}
