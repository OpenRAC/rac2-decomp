#include "common.h"

extern char *g_movie_player_state[] __attribute__((sda));
extern int g_widescreen_flag __attribute__((sda));
extern int g_movie_buffer_base[] __attribute__((sda));
/* The observed packet-builder interface includes its mode argument. */
extern void BuildFrameDmaChain(void *, int);
extern int sceDmaGetChan(int);
extern int gfx_wait_paths_idle(int, int);
/* The catalogue retains the legacy name; its measured entry is 00127220. */
extern void func_00127218(int *, int) __asm__("func_00127220");
extern int mpeg_get_ring_buffer_position(volatile int *);
/* Movie-frame state: written by the movie decoder's interrupt-time callback while this runs. */
extern volatile int g_mpeg_field_wait_flag[] __attribute__((sda));
extern volatile int g_mpeg_vblank_count[] __attribute__((sda));
extern volatile int g_mpeg_video_frame_state[] __attribute__((sda));
extern volatile int g_gs_field_parity[] __attribute__((sda));
extern volatile int g_paths_idle_result[] __attribute__((sda));

/* Submit a ready movie frame on the active GS field, then restore EE interrupts.
 * The 0xD9168 and 0x1C81C0 values are offsets inside decoder allocations. */
int vblankHandler_pal(void) {
    int *h = (int *)sceDmaGetChan(2);
    int *buf;

    g_gs_field_parity[0] = g_widescreen_flag ? g_gs_field_parity[0] ^ 1 : (int)((GS_CSR >> 13) & 1);
    if (g_mpeg_field_wait_flag[0] != 0) {
        g_mpeg_vblank_count[0] = g_mpeg_vblank_count[0] + 1;
        g_paths_idle_result[0] = gfx_wait_paths_idle(1, 0);
        if (g_paths_idle_result[0] == 0) {
            buf = (int *)mpeg_get_ring_buffer_position((volatile int *)(g_movie_player_state[0] + 0xD9168));
            if (buf == 0) {
                CpuSync();
                CpuEnableInt();
                return 0;
            }
            if (g_gs_field_parity[0] == 0 && buf[0] == 2) {
                int off;
                gfx_wait_paths_idle(0, 0);
                off = (buf[1] << 14) + 0x1C81C0;
                BuildFrameDmaChain((void *)(g_movie_buffer_base[0] + off), 0);
                dma_reset_channel_state(h, (int)buf + 0x40);
                buf[0] = 1;
            } else if (g_gs_field_parity[0] == 1) {
                int st = buf[0];
                if (st == 1) {
                    int off;
                    gfx_wait_paths_idle(0, 0);
                    off = (buf[1] << 14) + 0x1C81C0;
                    BuildFrameDmaChain((void *)(g_movie_buffer_base[0] + off), 0);
                    dma_reset_channel_state(h, (int)buf + 0x13880);
                    buf[0] = 0;
                    g_mpeg_video_frame_state[0] = st;
                }
            }
        }
    }
    CpuSync();
    CpuEnableInt();
    return 0;
}