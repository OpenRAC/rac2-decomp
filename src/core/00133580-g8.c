#include "common.h"

extern int D_001A748C __attribute__((sda));
extern int D_001A7498 __attribute__((sda));
extern unsigned int D_001A7100 NOT_SDA;
extern char D_001A713F NOT_SDA;
extern void kernel_process_request_d(void *, void *);
extern int sceCdSyncS(int);
extern int snd_Pump(void);

/* snd_CheckLoadInProgress: poll the shared loader status, pumping when asked
 * to wait. The fallback preserves the caller's sceCdSync mode argument. */
int snd_CheckLoadInProgress(int waitMode) {
    char *statusEnd;
    int notReady;

    if (D_001A748C == 0)
        return sceCdSyncS(waitMode);

    statusEnd = &D_001A713F;
    kernel_process_request_d(&D_001A7100, statusEnd);
    notReady = D_001A7100 < 1;
    D_001A7498 = notReady;
    if (notReady == 1)
        return 0;
    if (waitMode == 1)
        return 1;
    while (D_001A7498 == 0) {
        snd_Pump();
        kernel_process_request_d(&D_001A7100, statusEnd);
        notReady = D_001A7100 < 1;
        D_001A7498 = notReady;
    }
    return 0;
}

