#include "common.h"

/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/water_pool_and_sand_mouse.c:
 * build_water_render_setup_packet. */

typedef float Vec4[4];
struct DmaTag {
    u32 tag, addr, vif0, vif1;
};
union PacketCursor {
    struct DmaTag *tag;
    u8 *bytes;
};
extern union PacketCursor g_water_dma_packet_ptr MACRO_ADDR;
extern void set_scale_matrix(void *, float);
extern void FastVecScale(void *, void *, float);
extern void VU1_addDataRef(void *, int);
extern void multiply_matrix(void *, void *, void *);
extern void gfx_append_fixed_dma_block_tags(void);
extern char g_tether_zero_vec[];
extern int g_level_l04_mode_word MACRO_ADDR;
extern unsigned short g_font_vu_state_size NOT_SDA;
extern char g_font_vu_program[];
extern char g_water_camera[];
extern char g_water_camera_tag_data[];
extern unsigned g_water_alpha_index __attribute__((sda));
extern unsigned g_water_texture_id __attribute__((sda));
extern unsigned g_water_second_texture_id __attribute__((sda));
extern unsigned g_water_l04_second_alpha __attribute__((sda));

typedef struct WaterCamera {
    u8 pad000[0x190];
    Vec4 v190;                 /* 0x190 */
    Vec4 v1A0;                 /* 0x1A0 */
    u8 pad1B0[0x60];
    f32 f210;                  /* 0x210 */
    u8 pad214[0x14];
    f32 f228;                  /* 0x228 */
    f32 f22C;                  /* 0x22C */
} WaterCamera;

/* Builds the VU1 setup packet used to render the water. */
void BuildWaterRenderSetupPacket(void)
{
    f32 scaled_translation_matrix[4][4];
    struct DmaTag *base;
    u8 *packet_write_cursor;
    WaterCamera *camera;

    set_scale_matrix(scaled_translation_matrix, 1024.0f);
    FastVecScale(scaled_translation_matrix[3], g_tether_zero_vec, -1024.0f);
    scaled_translation_matrix[3][3] = 1.0f;
    if (g_level_l04_mode_word != 8) {
        VU1_addDataRef(g_font_vu_program, g_font_vu_state_size);
        g_level_l04_mode_word = 8;
    }
    g_water_dma_packet_ptr.tag->tag = 0x10000000;
    g_water_dma_packet_ptr.tag->addr = 0;
    g_water_dma_packet_ptr.tag->vif0 = 0x11000000;
    g_water_dma_packet_ptr.tag->vif1 = 0x1000404;
    base = g_water_dma_packet_ptr.tag;
    base[1].tag = 0;
    base[1].addr = 0;
    base[1].vif0 = 0;
    base[1].vif1 = 0x6C0C43A4;
    multiply_matrix(base + 2, g_tether_zero_vec - 0x100, scaled_translation_matrix);
    multiply_matrix(base + 6, g_tether_zero_vec - 0x80, scaled_translation_matrix);
    base[10].tag = 0x8000;
    base[10].addr = 0x303EC000;
    base[10].vif0 = 0x412;
    camera = (WaterCamera *)g_water_camera;
    *(f32 *)&base[10].vif1 = camera->f210;
    packet_write_cursor = (u8 *)(base + 11);
    qcopy(packet_write_cursor, &camera->v190);
    packet_write_cursor = (u8 *)(base + 12);
    qcopy(packet_write_cursor, &camera->v1A0);
    *(f32 *)&base[13].tag = camera->f22C;
    *(f32 *)&base[13].addr = camera->f228;
    base[13].vif0 = 0;
    base[13].vif1 = 0;
    base[14].addr = 0x20001D2;
    base[14].vif0 = 0x15000000;
    base[14].tag = 0x3000000;
    base[14].vif1 = 0;
    packet_write_cursor = (u8 *)(base + 15);
    g_water_dma_packet_ptr.tag->tag |= ((packet_write_cursor - (u8 *)g_water_dma_packet_ptr.tag) >> 4) - 1;
    g_water_dma_packet_ptr.bytes = packet_write_cursor;
    gfx_append_fixed_dma_block_tags();
    g_water_dma_packet_ptr.tag->tag = 0x30000007;
    g_water_dma_packet_ptr.tag->addr = (u32)g_water_camera_tag_data;
    g_water_dma_packet_ptr.tag->vif0 = 0;
    g_water_dma_packet_ptr.tag->vif1 = 0x50000007;
    g_water_texture_id = 0xFFFFFFFFu;
    g_water_second_texture_id = 0xFFFFFFFFu;
    g_water_l04_second_alpha = 0xFFFFFFFFu;
    g_water_alpha_index = 0xFFFFFFFFu;
    g_water_dma_packet_ptr.tag++;
}
