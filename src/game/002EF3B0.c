#include "names.h"
/* Advances the stage cursor by 0x10, mirrors the clock, builds the view matrix and restarts the two render packets. */
extern void FlushCache(int);
extern void gfx_append_vif_unpack_data(unsigned int, void *, unsigned int);
extern int g_vram_frame_base __attribute__((sda));
extern int g_vram_cursor __attribute__((sda));
extern unsigned char *g_dma_packet_cursor __attribute__((sda));
extern unsigned char *g_render_frame_cursor __attribute__((sda));
extern char g_camera_eye_state[];
extern int g_gfx_register_block_b[];
extern void set_identity_matrix(float *);
extern void FastVecScale(void *, void *, float);
extern void multiply_matrix(char *, char *, char *);
extern void func_002EF480(void);
extern void gfx_build_render_list_markers(void);
extern void gfx_write_register_with_sync(void *, unsigned int, unsigned int);

void gfx_begin_render_frame(void)
{
    float viewMatrix[16];
    unsigned char *cursor = g_dma_packet_cursor;

    g_render_frame_cursor = cursor;
    cursor += 0x10;
    g_dma_packet_cursor = cursor;
    g_vram_cursor = g_vram_frame_base;
    set_identity_matrix(viewMatrix);
    FastVecScale(viewMatrix + 12, g_camera_eye_state, -1024.0f);
    viewMatrix[15] = 1.0f;
    multiply_matrix((char *)viewMatrix, g_camera_eye_state - 0x100, (char *)viewMatrix);
    gfx_append_vif_unpack_data(5, viewMatrix, 4);
    gfx_append_vif_unpack_data(0x14D, viewMatrix, 4);
    FlushCache(0);
    func_002EF480();
    gfx_build_render_list_markers();
    gfx_write_register_with_sync(g_gfx_register_block_b, 0x3000, 0x40);
}
