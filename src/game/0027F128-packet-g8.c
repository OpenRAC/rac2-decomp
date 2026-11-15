#include "common.h"

/* -G8 sibling of src/game/0027F128.c.
 * Adapted from RAC1 draw.c, font_queue_vu_state (GPL-3.0). Build the VU1 setup packet; the DMA
 * tag's qword count is patched in at the end. The casted cursor stores are what make each one
 * reload the cursor, and the packet stores stay ordered ahead of its final read. */
extern void set_scale_matrix(float *, float);
extern void FastVecScale(void *, void *, float);
extern int D_001B169C;
extern unsigned short D_0010ED20 __attribute__((section(".data")));
extern char D_0010ED30[], g_camera_eye_state[], D_001B9040[];
extern int *g_dma_packet_cursor;
extern float D_001A86F0 __attribute__((sda));
extern void VU1_addDataRef(void *, int);
extern void multiply_matrix(void *, void *, void *);
extern void gfx_append_fixed_dma_block_tags(void);

/* Builds the setup packet that gets the graphics chip ready to draw text. */
void font_queue_vu_state(void) {
    float m[16];
    char *cam;
    char *g;
    char *base;
    int *p;

    set_scale_matrix(m, 1024.0f);
    cam = g_camera_eye_state;
    FastVecScale(&m[12], cam, -1024.0f);
    m[15] = 1.0f;
    if (D_001B169C != 8) {
        VU1_addDataRef(D_0010ED30, D_0010ED20);
        D_001B169C = 8;
    }
    *(int *)((char *)g_dma_packet_cursor + 0) = 0x10000000;
    *(int *)((char *)g_dma_packet_cursor + 4) = 0;
    *(int *)((char *)g_dma_packet_cursor + 8) = 0x11000000;
    *(int *)((char *)g_dma_packet_cursor + 12) = 0x01000404;
    base = (char *)g_dma_packet_cursor;
    *(int *)(base + 0x10) = 0;
    *(int *)(base + 0x14) = 0;
    *(int *)(base + 0x18) = 0;
    *(int *)(base + 0x1C) = 0x6C0C43A4;
    p = (int *)(base + 0x20);
    multiply_matrix(p, cam - 0x100, m);
    *(float *)(p + 14) += D_001A86F0;
    p = (int *)(base + 0x60);
    multiply_matrix(p, cam - 0x80, m);
    *(float *)(p + 14) += D_001A86F0;
    g = D_001B9040;
    *(int *)(base + 0xA0) = 0x8000;
    *(int *)(base + 0xA4) = 0x303EC000;
    *(int *)(base + 0xA8) = 0x412;
    *(float *)(base + 0xAC) = *(float *)(g + 0x210);
    p = (int *)(base + 0xB0);
    qcopy(p, g + 0x190);
    p = (int *)(base + 0xC0);
    qcopy(p, g + 0x1A0);
    *(float *)(base + 0xD0) = *(float *)(g + 0x22C);
    *(float *)(base + 0xD4) = *(float *)(g + 0x228);
    *(int *)(base + 0xD8) = 0;
    *(int *)(base + 0xDC) = 0;
    *(int *)(base + 0xE0) = 0x03000000;
    *(int *)(base + 0xE4) = 0x020001D2;
    *(int *)(base + 0xE8) = 0x15000000;
    *(int *)(base + 0xEC) = 0;
    p = (int *)(base + 0xF0);
    g_dma_packet_cursor[0] |= ((char *)p - (char *)g_dma_packet_cursor >> 4) - 1;
    g_dma_packet_cursor = p;
    gfx_append_fixed_dma_block_tags();
}
