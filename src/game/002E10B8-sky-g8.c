#include "common.h"

/* The sky's two piece renderers, called by func_002E3940: func_002E3998 draws textured pieces,
   func_002E3BD8 Gouraud-shaded ones. Each visible piece is copied by toSPR DMA into one of two
   scratchpad buffers while the previous one is transformed and drawn from the other. They read
   $gp small data (the buffer pair and its toggle), so this file is built with -G8. */

typedef struct {
    u8 pad[0x20];
    int data;           /* main-memory address of the piece's data, uploaded by DMA */
    s16 vertex_count;
    s16 face_count;
    s16 vertices;       /* byte offsets into the uploaded copy */
    s16 face_data;      /* texture ST (textured) or vertex colours (Gouraud) */
    s16 faces;
    s16 size;           /* upload size in bytes, a whole number of quadwords */
} SkyPiece;

typedef struct {
    int count;
} Sky;

#define PIECE(sky, k) ((SkyPiece *)((char *)(sky) + ((k) << 5)))

#define SKY_VERTEX_RECORDS 0x70002000   /* scratchpad: the transformed vertex records */

extern unsigned char *g_dma_packet_cursor;           /* the DMA packet cursor */
extern char g_gfx_sky_gouraud_packet[];
extern char g_gfx_sky_textured_packet[];
extern int g_sky_spr_buffers[2] __attribute__((sda));  /* the two scratchpad buffers */
extern int g_sky_spr_buffer_index __attribute__((sda));     /* which buffer receives the next upload */
extern int g_vram_zbuffer_address;

extern void vec_transform_vectors_vu0_alt(void *, int, void *);
extern int gfx_process_render_entry_a(int, int, int);
extern void gfx_process_render_entry_b(int, int, int, int);
extern void gfx_process_render_entry_c(int, int, int, int);
extern void DmaToSpr(int, int, int);
extern void DmaToSprSync(void);
extern void VU1_addGSregister(int, long);

/* Draws the textured pieces of the sky, loading each piece into fast memory while the previous one is drawn. */
void gfx_sky_textured_pieces_draw(Sky *sky)
{
    int count = sky->count;
    u8 visible[count];
    int i;

    if (count == 0)
        return;
    vec_transform_vectors_vu0_alt((char *)sky + 0x10, count, visible);
    *(int *)(g_dma_packet_cursor + 0) = 0x30000007;
    *(int *)(g_dma_packet_cursor + 4) = (int)g_gfx_sky_textured_packet;
    *(int *)(g_dma_packet_cursor + 8) = 0;
    *(int *)(g_dma_packet_cursor + 0xC) = 0x50000007;
    g_dma_packet_cursor = g_dma_packet_cursor + 16;
    g_sky_spr_buffer_index = 1 - g_sky_spr_buffer_index;
    if (visible[0] == 1)
        DmaToSpr(PIECE(sky, 0)->data, PIECE(sky, 0)->size >> 4, g_sky_spr_buffers[g_sky_spr_buffer_index]);
    for (i = 0; i < sky->count; i++) {
        if (visible[i] == 1)
            DmaToSprSync();
        g_sky_spr_buffer_index = 1 - g_sky_spr_buffer_index;
        if (i + 1 < sky->count && visible[i + 1] == 1)
            DmaToSpr(PIECE(sky, i + 1)->data, PIECE(sky, i + 1)->size >> 4,
                          g_sky_spr_buffers[g_sky_spr_buffer_index]);
        if (visible[i] == 1) {
            int base = g_sky_spr_buffers[1 - g_sky_spr_buffer_index];
            int faces, st, vertices, face_list, st_list;

            faces = PIECE(sky, i)->faces;
            vertices = PIECE(sky, i)->vertices;
            st = PIECE(sky, i)->face_data;
            face_list = base + faces;
            st_list = base + st;
            if (gfx_process_render_entry_a(base + vertices, SKY_VERTEX_RECORDS, PIECE(sky, i)->vertex_count) == 0)
                gfx_process_render_entry_c(PIECE(sky, i)->face_count, face_list, st_list, SKY_VERTEX_RECORDS);
        }
    }
}

/* Draws the colour-shaded pieces of the sky, loading each piece into fast memory while the previous one is drawn. */
void gfx_sky_gouraud_pieces_draw(Sky *sky)
{
    int count = sky->count;
    u8 visible[count];
    int i;

    if (count == 0)
        return;
    vec_transform_vectors_vu0_alt((char *)sky + 0x10, count, visible);
    *(int *)(g_dma_packet_cursor + 0) = 0x30000007;
    *(int *)(g_dma_packet_cursor + 4) = (int)g_gfx_sky_gouraud_packet;
    *(int *)(g_dma_packet_cursor + 8) = 0;
    *(int *)(g_dma_packet_cursor + 0xC) = 0x50000007;
    g_dma_packet_cursor = g_dma_packet_cursor + 16;
    g_sky_spr_buffer_index = 1 - g_sky_spr_buffer_index;
    if (visible[0] == 1)
        DmaToSpr(PIECE(sky, 0)->data, PIECE(sky, 0)->size >> 4, g_sky_spr_buffers[g_sky_spr_buffer_index]);
    for (i = 0; i < sky->count; i++) {
        if (visible[i] == 1)
            DmaToSprSync();
        g_sky_spr_buffer_index = 1 - g_sky_spr_buffer_index;
        if (i + 1 < sky->count && visible[i + 1] == 1)
            DmaToSpr(PIECE(sky, i + 1)->data, PIECE(sky, i + 1)->size >> 4,
                          g_sky_spr_buffers[g_sky_spr_buffer_index]);
        if (visible[i] == 1) {
            int base = g_sky_spr_buffers[1 - g_sky_spr_buffer_index];
            int faces, colours, vertices, face_list, colour_list;

            faces = PIECE(sky, i)->faces;
            vertices = PIECE(sky, i)->vertices;
            colours = PIECE(sky, i)->face_data;
            face_list = base + faces;
            colour_list = base + colours;
            if (gfx_process_render_entry_a(base + vertices, SKY_VERTEX_RECORDS, PIECE(sky, i)->vertex_count) == 0)
                gfx_process_render_entry_b(PIECE(sky, i)->face_count, face_list, colour_list, SKY_VERTEX_RECORDS);
        }
    }
    VU1_addGSregister(0x47, 0x3180B);
    VU1_addGSregister(0x4E, (long)(g_vram_zbuffer_address >> 13) | 0x1000000 | 0x100000000L);
}
