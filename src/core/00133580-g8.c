#include "common.h"

extern int g_snd_cmd_result __attribute__((sda));
extern int g_snd_load_ready __attribute__((sda));
extern unsigned int g_cd_read_count NOT_SDA;
extern char g_cd_status_end NOT_SDA;
extern void kernel_process_request_d(void *, void *);
extern int sceCdSyncS(int);
extern int snd_Pump(void);

/* snd_CheckLoadInProgress: poll the shared loader status, pumping when asked
 * to wait. The fallback preserves the caller's sceCdSync mode argument. */
int snd_CheckLoadInProgress(int wait_mode) {
    char *status_end;
    int not_ready;

    if (g_snd_cmd_result == 0)
        return sceCdSyncS(wait_mode);

    status_end = &g_cd_status_end;
    kernel_process_request_d(&g_cd_read_count, status_end);
    not_ready = g_cd_read_count < 1;
    g_snd_load_ready = not_ready;
    if (not_ready == 1)
        return 0;
    if (wait_mode == 1)
        return 1;
    while (g_snd_load_ready == 0) {
        snd_Pump();
        kernel_process_request_d(&g_cd_read_count, status_end);
        not_ready = g_cd_read_count < 1;
        g_snd_load_ready = not_ready;
    }
    return 0;
}

