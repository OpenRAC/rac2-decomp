#include "common.h"

/* snd_StreamSafeCdRead (rac1-decomp src/core/989snd.c). This unit needs
   -mno-split-addresses for the absolute `lui $at; sw` stores and for the return-zero
   constant in the beq's delay slot.

   D_001A7100 and D_001A7110 are the count and error fields of RAC1's CdSafeState
   (sound_read_work), which declares them volatile with these types at offsets 0 and
   0x10; func_00133580 polls the count. Two volatile stores depend on each other, which
   raises the first store's scheduling priority above the two address loads, so it goes
   first; the second then ranks behind the remaining load, having fewer dependents.
   Without volatile all four tie on priority and the loads, with more dependents, go
   first. */
extern int g_snd_cmd_result __attribute__((sda));
extern int g_snd_stop_requested __attribute__((sda));
extern int g_snd_load_ready __attribute__((sda));
extern volatile unsigned int g_cd_read_count NOT_SDA;
extern volatile int g_cd_read_error NOT_SDA;
extern char g_cd_status_end NOT_SDA;

extern void kernel_process_request_b(void *, void *);
extern int sceCdRead(int, int, void *, unsigned char *);
extern int snd_CheckLoadInProgress(int);
extern void snd_queue_command(int, int, void *, int, long);

/* Starts a disc read through the sound server, or reads directly when it is not in use. Returns 0 if a read is already running. */
int CdStartRead(int lba, int sectors, void *buf, unsigned char *mode) {
    int payload[4];

    if (g_snd_cmd_result == 0) {
        return sceCdRead(lba, sectors, buf, mode);
    }
    if (snd_CheckLoadInProgress(1) == 1) {
        return 0;
    }
    g_cd_read_count = 1;
    g_cd_read_error = 0;
    kernel_process_request_b((void *)&g_cd_read_count, &g_cd_status_end);
    payload[0] = lba;
    payload[1] = sectors;
    payload[2] = (int)buf;
    g_snd_stop_requested = 1;
    g_snd_load_ready = 0;
    snd_queue_command(0x38, 0xC, payload, 0, 0);
    return 1;
}
