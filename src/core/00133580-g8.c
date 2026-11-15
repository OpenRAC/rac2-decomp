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
int snd_CheckLoadInProgress(int wait_mode) {
    char *status_end;
    int not_ready;

    if (D_001A748C == 0)
        return sceCdSyncS(wait_mode);

    status_end = &D_001A713F;
    kernel_process_request_d(&D_001A7100, status_end);
    not_ready = D_001A7100 < 1;
    D_001A7498 = not_ready;
    if (not_ready == 1)
        return 0;
    if (wait_mode == 1)
        return 1;
    while (D_001A7498 == 0) {
        snd_Pump();
        kernel_process_request_d(&D_001A7100, status_end);
        not_ready = D_001A7100 < 1;
        D_001A7498 = not_ready;
    }
    return 0;
}

