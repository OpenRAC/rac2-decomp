#include "common.h"

typedef struct {
    int count, flags;
    float depth, radius;
    float xyz[4];
    float params[4];
} RenderDFBB0;

/* Header offsets use the shared byte packet cursor. */
extern unsigned char *g_dma_packet_cursor MACRO_ADDR;
extern char D_001390B0[];
extern void *D_001B2080;
extern int D_001A72DC[] __attribute__((sda));
extern void gfx_shadow_buffer_init_strips_draw(void);
extern void gfx_shadow_build_projection_basis(float *, float);
extern RenderDFBB0 *gfx_shadow_process_record(RenderDFBB0 *);
extern void shadow_set_volume_bounds(float *, float *);
extern void shadow_draw_outline_batch(int, void *, int);
extern void gfx_shadow_submit_packet(int, int, int);
extern void VU1_addGSregister(int, long);
extern void gfx_shadow_buffer_color_fill_draw(long);

/* Draws all shadows in the list: for each group it sets up the direction, builds each shadow and draws it, then resets the drawing state. */
void gfx_shadow_list_draw(RenderDFBB0 *data) {
    RenderDFBB0 *next = data;
    RenderDFBB0 *current;
    int i;
    float a[4], b[4];
    gfx_shadow_buffer_init_strips_draw();
    current = next;
    *(int *)g_dma_packet_cursor = 0x30000007;
    *(int *)(g_dma_packet_cursor + 4) = (int)D_001390B0;
    *(int *)(g_dma_packet_cursor + 8) = 0x13000000;
    *(int *)(g_dma_packet_cursor + 12) = 0x50000007;
    g_dma_packet_cursor = g_dma_packet_cursor + 16;
    while (current->count) {
        next = next + 1;
        gfx_shadow_build_projection_basis(current->params, 1000.0f);
        b[0] = a[0] = current->xyz[0];
        b[1] = a[1] = current->xyz[1];
        b[2] = a[2] = current->xyz[2];
        a[3] = -current->depth - current->radius;
        {
            float depth = current->depth;
            b[3] = current->radius - depth;
        }
        for (i = 0; i < current->count; i++) {
            next = gfx_shadow_process_record(next);
            shadow_set_volume_bounds(a, b);
            shadow_draw_outline_batch(0x70000000, D_001B2080, current->flags);
            gfx_shadow_submit_packet(2, 1, 2);
            gfx_shadow_submit_packet(1, 0, 2);
        }
        current = next;
    }
    VU1_addGSregister(0x4C, (D_001A72DC[0] >> 13) | 0x80000);
    VU1_addGSregister(0x42, 0x2000000064L);
    gfx_shadow_buffer_color_fill_draw(0);
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x42, 0x8000000044L);
}
