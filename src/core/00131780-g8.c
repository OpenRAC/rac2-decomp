#include "common.h"

extern int r1_D_0015EDC4 __attribute__((sda));
extern void snd_Pump(void);

/* Clears a sound flag and runs the sound update. */
void snd_clear_flag_and_update(void) {
    r1_D_0015EDC4 = 0;
    snd_Pump();
}

extern int D_001A74F8 __attribute__((sda));
extern char D_001A7578[];
extern void printf(const void *, ...);
extern void FlushCache(int);
extern int sif_rpc_is_handle_valid(const void *);
extern int sceSifCallRpc(const void *, int, int, int *, int, int *, int, int, int);
extern int *D_001A74A0[2] __attribute__((sda));
extern int D_001A74A8[2] __attribute__((sda));
extern int *D_001A74B8[2] __attribute__((sda));
extern int D_001A74C0 __attribute__((sda));
extern int D_001A7040;
extern void snd_prepare_reply_buffer(void *, int, void *);
/* Sends the filled sound data buffer by DMA and switches to the other buffer. */
void snd_submit_dma_buffer(void) {
    snd_prepare_reply_buffer(D_001A74B8[D_001A74C0], *D_001A74A0[D_001A74C0], D_001A74A0[D_001A74C0]);
    while (sif_rpc_is_handle_valid(&D_001A7040)) {
        if (D_001A74F8 == 0)
            printf(D_001A7578);
        FlushCache(0);
    }
    sceSifCallRpc(&D_001A7040, 0x4D, 1, D_001A74A0[D_001A74C0], 0x1000-D_001A74A8[D_001A74C0], D_001A74B8[D_001A74C0], (*D_001A74A0[D_001A74C0] << 2)+8, 0, 0);
    {
        int next = (D_001A74C0 ^ 1) != 0;
        D_001A74C0 = next;
        *D_001A74A0[next] = 0;
        D_001A74A8[next] = 0xFFC;
    }
}

extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74D0 __attribute__((sda));
extern int D_001A71C0 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
extern long D_001A74D8 MACRO_ADDR;
extern int D_001A7140 MACRO_ADDR;
extern char D_001A76F8[];
/* Starts a disc read for the sound system and remembers the function to call when it is done. */
void snd_start_cd_read(int a, int c, long d) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) return;
        printf(D_001A76F8);
        return;
    }
    do {
        D_001A71C0 = a;
        D_001A74D0 = c;
        D_001A7180 = -1u;
        D_001A74D8 = d;
    } while (0);
    while (sif_rpc_is_handle_valid(&D_001A7140)) {
        if (D_001A74F8 == 0) printf(D_001A7578);
        snd_Pump();
        FlushCache(0);
    }
    D_001A74C8 = 1;
    sceSifCallRpc(&D_001A7140, 0x57, 1, &D_001A71C0, 4, (int *)&D_001A7180, 4, 0, 0);
}
