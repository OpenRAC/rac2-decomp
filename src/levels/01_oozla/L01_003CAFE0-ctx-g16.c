#include "names.h"
/* func_L01_003CAFE0 needs -G16 small data, quadword copies and -g line labels
 * (the nop pairs before both div.s); -frac2-hazard-labels keeps the second
 * division guard's label on its padding.  The frame entries are block-local,
 * so local allocation ties them to their index chains. */
#include "common.h"


typedef unsigned int Quad __attribute__((mode(TI)));
extern unsigned char g_render_scales[];
typedef struct { u8 prefix[8]; u16 first, second; u32 other; } FrameEntry;
extern FrameEntry g_water_frame_entries[];
extern unsigned char g_water_packet_header[], g_water_packet_template[], g_water_background_data[];
extern unsigned char g_water_background_template[];
extern unsigned char g_water_bg_gif_tag_data_b[] SDATA(D_L01_001B0270);
extern unsigned char g_water_bg_gif_tag_data_a[] SDATA(D_L01_001B0240);
/* The camera position follows its view matrix by 0x100, as in RAC1 CameraSystem. */
typedef struct { float matrix[16]; u8 unknown40[0xc0]; float pos[4]; } CameraView;
extern CameraView g_camera_views[];
extern unsigned char *g_water_texture_data;
extern unsigned char *g_water_packet_headers[] __attribute__((sda));
extern int g_water_mode_table[] __attribute__((sda));
extern int g_oozla_intro_stage, g_water_draw_mode;
extern float g_water_context_a, g_water_context_b, g_water_context_c;
extern float g_water_context_d __attribute__((sda));
extern float g_water_bg_context_float_a __attribute__((sda)), g_water_bg_context_float_b __attribute__((sda));
extern float g_water_bg_context_float_c __attribute__((sda)), g_water_bg_context_float_d __attribute__((sda));
extern int g_water_bg_color_red __attribute__((sda)), g_water_bg_color_green __attribute__((sda)), g_water_bg_color_blue __attribute__((sda));
extern int g_water_bg_packet_value __attribute__((sda)), g_water_bg_interval_a __attribute__((sda)), g_water_bg_frame_base_a __attribute__((sda));
extern int g_water_bg_frame_count_a __attribute__((sda)), g_water_bg_interval_b __attribute__((sda)), g_water_bg_frame_base_b __attribute__((sda));
extern int g_water_bg_frame_count_b __attribute__((sda));
extern unsigned char *g_water_bg_packet_ptr __attribute__((sda)), *g_water_bg_palette_ptr __attribute__((sda));
extern Quad g_water_bg_header_a __attribute__((sda)), g_water_bg_header_b __attribute__((sda));
extern unsigned char g_water_bg_packet_data[] SDATA(D_L01_001B0300);
extern int g_vram_cursor;
extern unsigned short g_water_vu_data_size[];
extern unsigned char g_water_vu_program[];
extern void UpdateViewContext(void), gfx_build_view_matrices(void);
extern void mem_copy_aligned(void *, void *, int), mem_fast_helper_c(void *, void *, int);
extern void VU1_addDataRef(unsigned int, unsigned int);
extern void set_identity_matrix(float *);
extern void FastVecScale(float *, float *, float);
extern void multiply_matrix(float *, float *, float *);
extern void oozla_run_asm_routine(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *, int, float);
#define CONTEXT_FLOAT(offset) (*(float *)(context + (offset)))
#define CONTEXT_INT(offset) (*(int *)(context + (offset)))
#define PACKET_LONG(ptr,offset) (*(u64 *)((ptr) + (offset)))
/* Builds the draw commands for the animated background water: it blends between two animation frames and adds the camera matrix. */
void gfx_draw_animated_water_background(void)
{
    float matrix[16] __attribute__((aligned(16)));
    unsigned char *packet;
    u8 *context = g_render_scales;
    int mode = g_water_mode_table[0];
    g_water_context_a = CONTEXT_FLOAT(0x218);
    g_water_context_b = CONTEXT_FLOAT(0x21c);
    g_water_context_c = CONTEXT_FLOAT(0x228);
    g_water_context_d = CONTEXT_FLOAT(0x22c);
    if (mode != 1) {
        CONTEXT_FLOAT(0x218) = g_water_bg_context_float_a;
        CONTEXT_FLOAT(0x21c) = g_water_bg_context_float_b;
        CONTEXT_FLOAT(0x228) = g_water_bg_context_float_c;
        CONTEXT_FLOAT(0x22c) = g_water_bg_context_float_d;
    }
    UpdateViewContext();
    gfx_build_view_matrices();
    {
        u8 *header = g_water_packet_headers[0];
        qcopy(header, &g_water_bg_header_a);
        packet = header + 0x10;
    }
    g_water_packet_headers[0] = packet;
    mem_copy_aligned(packet, g_water_packet_header, 0xa0);
    g_water_packet_headers[0] += 0xa0;
    PACKET_LONG(packet,0x20) = ((u64)g_water_bg_packet_value << 32) | 100;
    PACKET_LONG(packet,0x30) = (u64)((g_vram_cursor >> 8) | 0x18100000) | 0x580000000UL;
    PACKET_LONG(packet,0x40) = (s32)((u32)g_water_bg_color_red | ((u32)g_water_bg_color_green << 8) | ((u32)g_water_bg_color_blue << 16));
    if (g_water_mode_table[0] == 1)
        PACKET_LONG(packet,0x40) = (s32)((u32)CONTEXT_INT(0x230) | ((u32)CONTEXT_INT(0x234) << 8) | ((u32)CONTEXT_INT(0x238) << 16));
    PACKET_LONG(packet,0x50) = ((u64)((long)g_vram_cursor >> 8) << 32) | 0x1000000000000UL;
    PACKET_LONG(packet,0x90) = 0x5360a;
    if (g_water_bg_packet_value < 97) PACKET_LONG(packet,0x90) = 0x5370b;
    {
        FrameEntry *entry0, *entry1;
        int frame;
        float fraction;
        int ticks = g_oozla_intro_stage;
        int interval = g_water_bg_interval_a;
        fraction = (float)ticks / (float)interval;
        frame = ticks / interval;
        fraction -= (float)frame;
        entry0 = g_water_frame_entries + (g_water_bg_frame_base_a + frame % g_water_bg_frame_count_a);
        entry1 = g_water_frame_entries + (g_water_bg_frame_base_a + (frame + 1) % g_water_bg_frame_count_a);
        {
            /* Each entry's second index is read before its first. */
            u16 idx1 = entry0->second;
            u16 idx0 = entry0->first;
            u16 idx3 = entry1->second;
            u16 idx2 = entry1->first;
            u8 *src0 = g_water_texture_data + idx0 * 16;
            u8 *src1 = g_water_texture_data + idx1 * 16;
            u8 *src2 = g_water_texture_data + idx2 * 16;
            u8 *src3 = g_water_texture_data + idx3 * 16;
            PACKET_LONG(g_water_bg_packet_ptr,0) = 0x800000000000400UL;
            PACKET_LONG(g_water_bg_packet_ptr,8) = 0;
            oozla_run_asm_routine(g_water_bg_packet_ptr + 0x10, src0, src1, src2, src3, 4096, fraction);
        }
    }
    {
        FrameEntry *entry0, *entry1;
        int frame;
        float fraction;
        int ticks = g_oozla_intro_stage;
        int interval = g_water_bg_interval_b;
        g_vram_cursor += 0x4000;
        fraction = (float)ticks / (float)interval;
        frame = ticks / interval;
        fraction -= (float)frame;
        entry0 = g_water_frame_entries + (g_water_bg_frame_base_b + frame % g_water_bg_frame_count_b);
        entry1 = g_water_frame_entries + (g_water_bg_frame_base_b + (frame + 1) % g_water_bg_frame_count_b);
        {
            /* Each entry's second index is read before its first. */
            u16 idx1 = entry0->second;
            u16 idx0 = entry0->first;
            u16 idx3 = entry1->second;
            u16 idx2 = entry1->first;
            u8 *src0 = g_water_texture_data + idx0 * 16;
            u8 *src1 = g_water_texture_data + idx1 * 16;
            u8 *src2 = g_water_texture_data + idx2 * 16;
            u8 *src3 = g_water_texture_data + idx3 * 16;
            PACKET_LONG(g_water_bg_packet_ptr,0) = 0x800000000000400UL;
            PACKET_LONG(g_water_bg_packet_ptr,8) = 0;
            oozla_run_asm_routine(g_water_bg_palette_ptr, src0, src1, src2, src3, 4096, fraction);
        }
    }
    {
        u8 *header = g_water_packet_headers[0];
        qcopy(header, &g_water_bg_header_b);
        *(unsigned char **)(header + 4) = g_water_bg_packet_ptr;
    }
    g_water_packet_headers[0] += 0x10;
    mem_fast_helper_c(g_water_packet_headers[0], g_water_bg_packet_data, 0x30);
    g_water_packet_headers[0] += 0x30;
    if (g_water_draw_mode != 6) {
        VU1_addDataRef((unsigned int)g_water_vu_program, g_water_vu_data_size[0]);
        g_water_draw_mode = 6;
    }
    packet = g_water_packet_headers[0];
    {
        unsigned char *tmpl = g_water_packet_template;
        *(unsigned char **)(tmpl + 4) = g_water_background_data;
        mem_fast_helper_c(packet, tmpl, 0x50);
    }
    g_water_packet_headers[0] += 0x50;
    *(unsigned char **)(packet + 0x24) = g_water_packet_headers[0];
    *(unsigned char **)(packet + 0x34) = g_water_packet_headers[0];
    *(unsigned char **)(packet + 0x44) = g_water_packet_headers[0] + 0x60;
    mem_fast_helper_c(g_water_packet_headers[0], context, 0x60);
    g_water_packet_headers[0] += 0x60;
    set_identity_matrix(matrix);
    FastVecScale(matrix + 12, g_camera_views[0].pos, -1024.0f);
    matrix[15] = 1.0f;
    multiply_matrix(matrix, g_camera_views[0].matrix, matrix);
    mem_fast_helper_c(g_water_packet_headers[0], g_water_background_template, 0x20);
    *(unsigned char **)(g_water_packet_headers[0] + 4) = g_water_packet_headers[0] + 0x20;
    mem_fast_helper_c(g_water_packet_headers[0] + 0x20, matrix, 0x40);
    g_water_packet_headers[0] += 0x60;
    mem_copy_aligned(g_water_packet_headers[0], g_water_bg_gif_tag_data_b, 0x20);
    g_water_packet_headers[0] += 0x20;
    mem_copy_aligned(g_water_packet_headers[0], g_water_bg_gif_tag_data_a, 0x20);
    g_water_packet_headers[0] += 0x20;
}
