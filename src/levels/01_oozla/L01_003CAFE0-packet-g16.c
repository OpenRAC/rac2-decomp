#include "common.h"

/* Incomplete views keep absolute macro accesses; the measured 16-byte template
 * uses small data. The packet cursor is reread between packet-field stores. */
extern u8 * volatile g_water_packet_headers[] __attribute__((sda));
extern u8 *D_L01_001B2CC8_gp __asm__("D_L01_001B2CC8") MACRO_ADDR;
extern u8 g_wave_grid_packet_tail[16] __attribute__((sda));
extern float g_water_context_a[] __attribute__((sda));
extern float g_water_context_b[] __attribute__((sda));
extern float g_water_context_c[] __attribute__((sda));
extern float g_water_context_d[] __attribute__((sda));
extern u8 g_render_scales[];
extern void func_002DA4F8(void);
extern void func_002D96D0(void);
extern void func_00371A70(void);

/* Finishes the water wave drawing by writing the draw settings into the graphics packet. */
void gfx_finish_wave_grid_packet(void)
{
    u8 *state;
    u8 *cursor = g_water_packet_headers[0];
    qcopy(cursor, g_wave_grid_packet_tail);
    cursor += 16;
    g_water_packet_headers[0] = cursor;
    {
        float a = g_water_context_a[0], b = g_water_context_b[0];
        float c = g_water_context_c[0], d = g_water_context_d[0];
        state = g_render_scales;
        *(float *)(state + 0x218) = a;
        *(float *)(state + 0x21C) = b;
        *(float *)(state + 0x228) = c;
        *(float *)(state + 0x22C) = d;
    }
    func_002DA4F8();
    func_002D96D0();
    *(u32 *)(g_water_packet_headers[0] + 0) = 0x10000002;
    *(u32 *)(g_water_packet_headers[0] + 4) = 0;
    *(u32 *)(g_water_packet_headers[0] + 8) = 0x11000000;
    *(u32 *)(g_water_packet_headers[0] + 12) = 0x50000002;
    {
        u8 *base_packet = g_water_packet_headers[0];
        g_water_packet_headers[0] = base_packet + 16;
        {
            u8 *next_packet = base_packet + 16;
            *(u64 *)(base_packet + 16) = 0x1000000000008001ULL;
            *(u64 *)(next_packet + 8) = 14;
            *(u64 *)(next_packet + 16) = (u64)*(s32 *)(state + 0x230) |
                ((u64)*(s32 *)(state + 0x234) << 8) |
                ((u64)*(s32 *)(state + 0x238) << 16);
            *(u64 *)(next_packet + 24) = 0x3D;
            D_L01_001B2CC8_gp = base_packet + 48;
        }
    }
    func_00371A70();
}
