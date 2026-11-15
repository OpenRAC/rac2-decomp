#include "common.h"

extern char *g_movie_player_state[] __attribute__((sda));
extern int g_widescreen_flag __attribute__((sda));
extern int D_001B23C8[] __attribute__((sda));
/* The observed packet-builder interface includes its mode argument. */
extern void BuildFrameDmaChain(void *, int);
extern int sceDmaGetChan(int);
extern int gfx_wait_paths_idle(int, int);
/* The catalogue retains the legacy name; its measured entry is 00127220. */
extern void func_00127218(int *, int) __asm__("func_00127220");
extern int mpeg_get_ring_buffer_position(volatile int *);
/* Movie-frame state: written by the movie decoder's interrupt-time callback while this runs. */
extern volatile int D_001AE7D0[] __attribute__((sda));
extern volatile int D_001AE7D4[] __attribute__((sda));
extern volatile int D_001AE7D8[] __attribute__((sda));
extern volatile int D_001AE7DC[] __attribute__((sda));
extern volatile int D_001AE7E0[] __attribute__((sda));

/* Submit a ready movie frame on the active GS field, then restore EE interrupts.
 * The 0xD9168 and 0x1C81C0 values are offsets inside decoder allocations. */
int func_PAL_003521A8(void) {
    int *h = (int *)sceDmaGetChan(2);
    int *buf;

    D_001AE7DC[0] = g_widescreen_flag ? D_001AE7DC[0] ^ 1 : (int)((GS_CSR >> 13) & 1);
    if (D_001AE7D0[0] != 0) {
        D_001AE7D4[0] = D_001AE7D4[0] + 1;
        D_001AE7E0[0] = gfx_wait_paths_idle(1, 0);
        if (D_001AE7E0[0] == 0) {
            buf = (int *)mpeg_get_ring_buffer_position((volatile int *)(g_movie_player_state[0] + 0xD9168));
            if (buf == 0) {
                CpuSync();
                CpuEnableInt();
                return 0;
            }
            if (D_001AE7DC[0] == 0 && buf[0] == 2) {
                int off;
                gfx_wait_paths_idle(0, 0);
                off = (buf[1] << 14) + 0x1C81C0;
                BuildFrameDmaChain((void *)(D_001B23C8[0] + off), 0);
                dma_reset_channel_state(h, (int)buf + 0x40);
                buf[0] = 1;
            } else if (D_001AE7DC[0] == 1) {
                int st = buf[0];
                if (st == 1) {
                    int off;
                    gfx_wait_paths_idle(0, 0);
                    off = (buf[1] << 14) + 0x1C81C0;
                    BuildFrameDmaChain((void *)(D_001B23C8[0] + off), 0);
                    dma_reset_channel_state(h, (int)buf + 0x13880);
                    buf[0] = 0;
                    D_001AE7D8[0] = st;
                }
            }
        }
    }
    CpuSync();
    CpuEnableInt();
    return 0;
}