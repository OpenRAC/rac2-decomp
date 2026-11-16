#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void copy_matrix_rotation(void *moby, void *a1);
extern void euler_rotation_basis(void *moby, void *a1);
extern s32  PulseColor(u32 moby, u32 a1, f32 a2);
extern s32  FastTweenColor(s32 moby, s32 a1, f32 a2);
extern void FillQuadPacket(void *moby, s32 a1, s32 a2, void *a3, void *a4, s32 a5);
extern void gfx_transform_and_draw_entries(void *moby, s32 a1, void *a2, s32 a3, void *a4);

extern u32 g_tube_pulse_colors[] __attribute__((sda));
extern u8   g_tube_quad_packet_flag __attribute__((sda));
extern f32  g_tube_quad_data[];

/* Builds the actor's effect object: the track the level keeps, the two vectors
   the aim is folded into, and the level's own tables. */
void tube_start_draw_effect(char *moby)
{
    u8 packet[0x1A0];
    s32 vars;
    s32 color;
    f32 fade;

    vars = *(s32 *)(moby + 0x68);
    copy_matrix_rotation(packet + 0x150, moby + 0xC0);
    qcopy(packet + 0x180, moby + 0x10);
    *(TI128 *)(packet + 0x190) = 0;
    *(f32 *)(packet + 0x18C) = 1.0f;
    *(f32 *)(packet + 0x198) = 0.19634954f;
    euler_rotation_basis(packet + 0x120, packet + 0x190);
    color = PulseColor(g_tube_pulse_colors[0], g_tube_pulse_colors[1], *(f32 *)(vars + 0x30));
    fade = *(f32 *)(vars + 0x18);
    if (fade < 1.0f)
        color = FastTweenColor(color & 0xFFFFFF, color, fade);
    FillQuadPacket(packet, 5, color, &g_tube_quad_packet_flag, g_tube_quad_data, 1);
    FillQuadPacket(packet + 0x90, 5, color, &g_tube_quad_packet_flag, g_tube_quad_data + 0x10, 1);
    gfx_transform_and_draw_entries(packet, 2, packet + 0x120, 0x20, packet + 0x150);
}
