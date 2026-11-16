#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[20]; int *data; } SplashState;
extern SplashState g_loader_memory;
extern int g_vram_display_address[] __attribute__((sda));
extern int fast_decompress(int, void *);
extern void FlushCache(int);
extern void gfx_reset_packet_buffer(void);
extern long long tex_upload_blocks_return_setup(void *, int, int, int);
extern void gfx_write_clear_color_packets(void);
extern void gfx_set_clear_color_packet(int, int, int, int);
extern void PutDrawBufferSmall(void);
extern void gfx_queue_second_strip_packet(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int gfx_wait_paths_idle(int, int);
extern int sceGsSyncV(int);

/* Draw the loaded splash image over 65 frames, fading its alpha from 128 to 0. */
void ShowSplashImage(int arg)
{
    int *data;
    int count;

    fast_decompress(arg, g_loader_memory.data);
    FlushCache(0);
    for (count = 0x80; count >= 0; count -= 2) {
        gfx_reset_packet_buffer();
        data = g_loader_memory.data;
        tex_upload_blocks_return_setup(data + 4, g_vram_display_address[0], data[0], data[1]);
        gfx_write_clear_color_packets();
        gfx_set_clear_color_packet(0, 0, 0, count);
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        FlushCache(0);
        SubmitBufferedDmaChain();
        gfx_wait_for_dma_status_bits(1);
        gfx_wait_paths_idle(0, 0);
        sceGsSyncV(0);
    }
}
