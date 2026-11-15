#include "include_asm.h"

#include "common.h"

extern unsigned char *g_dma_packet_cursor __attribute__((sda));
extern unsigned char D_PAL_001AC950[];

/* func_PAL_0026E780, PAL's own function, built like func_002FC518: appends a packet header for
   three quadwords to the buffer at D_001B22A8, the quadword at D_PAL_001AC950, and four doublewords.
   D_PAL_001AC950 is PAL's own name: v1.01's D_001AC950 is another object, which func_002FC748
   reads from elsewhere in PAL.
   -G0 as func_002FC468: D_001B22A8 is loaded absolutely, and the store in the return's delay
   slot takes the assembler's $gp form. */
void func_PAL_0026E780(void)
{
    unsigned char *p;

    *(unsigned int *)(g_dma_packet_cursor + 0) = 0x10000003u;
    *(unsigned int *)(g_dma_packet_cursor + 4) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 8) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 12) = 0x50000003u;
    g_dma_packet_cursor += 16;
    p = g_dma_packet_cursor;
    qcopy(p, D_PAL_001AC950);
    p += 16;
    g_dma_packet_cursor = p;
    *(unsigned long long *)(p + 0) = 0x101;
    *(unsigned long long *)(p + 8) = 0x80000000u;
    *(unsigned long long *)(p + 16) = 0x8FE86FF8u;
    *(unsigned long long *)(p + 24) = 0x8FE88FF8u;
    g_dma_packet_cursor += 32;
}

typedef struct { char prefix[20]; int *data; } SplashState;
extern char D_001BAEC0[];
extern int D_001A72DC[] __attribute__((sda));
extern void func_PAL_0029DE68(int, void *);
extern int FlushCache(int);
extern void gfx_reset_packet_buffer(void);
extern void tex_upload_blocks_return_setup(void *, int, int, int);
extern void gfx_write_clear_color_packets(void);
extern void gfx_set_clear_color_packet(int, int, int, int);
extern void PutDrawBufferSmall(void);
extern void gfx_queue_second_strip_packet(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int gfx_wait_paths_idle(int, int);
extern int sceGsSyncV(int);
extern void gfx_install_dma_handlers(void);
extern void SetBackgroundColor(int, int, int);
extern void gfx_append_draw_list_header(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_remove_dma_handlers(void);

/* func_PAL_0026E838, the PAL copy of func_0026EA00: the same C with three more calls before the
   image draw (func_00284E18, func_00284EA8, func_00284F40) and func_PAL_0026E780() before the
   second func_0011AEA0(0). Draws the loaded splash image over 65 frames, fading its alpha from
   128 to 0. */
void func_PAL_0026E838(int arg)
{
    int *data;
    int count;

    func_PAL_0029DE68(arg, ((SplashState *)D_001BAEC0)->data);
    FlushCache(0);
    for (count = 0x80; count >= 0; count -= 2) {
        gfx_reset_packet_buffer();
        SetBackgroundColor(0, 0, 0);
        gfx_append_draw_list_header();
        gfx_append_draw_list_buffer_tag(0);
        data = ((SplashState *)D_001BAEC0)->data;
        tex_upload_blocks_return_setup(data + 4, D_001A72DC[0], data[0], data[1]);
        gfx_write_clear_color_packets();
        gfx_set_clear_color_packet(0, 0, 0, count);
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        func_PAL_0026E780();
        FlushCache(0);
        SubmitBufferedDmaChain();
        gfx_wait_for_dma_status_bits(1);
        gfx_wait_paths_idle(0, 0);
        sceGsSyncV(0);
    }
}

/* func_PAL_0026E928, the PAL copy of func_0026EAC8: the same C with one more call,
   func_PAL_0026E780(), before the second func_0011AEA0(0). */

void func_PAL_0026E928(int arg)
{
    char *state = D_001BAEC0;
    int *data;
    func_PAL_0029DE68(arg, *(void **)(state + 20));
    FlushCache(0);
    gfx_reset_packet_buffer();
    gfx_install_dma_handlers();
    SetBackgroundColor(0, 0, 0);
    gfx_append_draw_list_header();
    gfx_append_draw_list_buffer_tag(0);
    data = *(int **)(state + 20);
    tex_upload_blocks_return_setup(data + 4, D_001A72DC[0], data[0], data[1]);
    gfx_write_clear_color_packets();
    PutDrawBufferSmall();
    gfx_queue_second_strip_packet();
    func_PAL_0026E780();
    FlushCache(0);
    SubmitBufferedDmaChain();
    gfx_wait_for_dma_status_bits(1);
    gfx_wait_paths_idle(0, 0);
    sceGsSyncV(0);
    gfx_remove_dma_handlers();
}
