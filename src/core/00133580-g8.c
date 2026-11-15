#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern unsigned int D_001A7100 NOT_SDA;
extern char D_001A713F NOT_SDA;
extern void func_0011B500(void *, void *);
extern int func_00124B88(int);
extern int func_00132028(void);

/* snd_CheckLoadInProgress: poll the shared loader status, pumping when asked
 * to wait. The fallback preserves the caller's sceCdSync mode argument. */
int func_00133580(int waitMode) {
    char *statusEnd;
    int notReady;

    if (D_001A748C == 0)
        return WaitSCommandDone(waitMode);

    statusEnd = &D_001A713F;
    ProcessKernelRequestD(&D_001A7100, statusEnd);
    notReady = D_001A7100 < 1;
    D_001A7498 = notReady;
    if (notReady == 1)
        return 0;
    if (waitMode == 1)
        return 1;
    while (D_001A7498 == 0) {
        snd_Pump();
        ProcessKernelRequestD(&D_001A7100, statusEnd);
        notReady = D_001A7100 < 1;
        D_001A7498 = notReady;
    }
    return 0;
}

