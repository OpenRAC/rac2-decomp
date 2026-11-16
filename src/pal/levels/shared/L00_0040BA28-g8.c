#include "common.h"

/* func_PAL_L00_0040BA28, the PAL copy of func_L00_00406FB0: the same C, where each scroll speed
 * is scaled by 1.2f for 50 Hz. */

extern float g_sheepinator_beam_uv_x_step __attribute__((sda)), g_sheepinator_beam_uv_y_step __attribute__((sda));
extern float g_sheepinator_beam_scroll_x __attribute__((sda)), g_sheepinator_beam_scroll_x_rate __attribute__((sda));
extern float g_sheepinator_beam_scroll_y __attribute__((sda)), g_sheepinator_beam_scroll_z __attribute__((sda));
extern float g_sheepinator_beam_scroll_rate __attribute__((sda));
extern int g_beam_ribbon_param_a __attribute__((sda)), g_beam_ribbon_param_b __attribute__((sda));
extern float g_beam_ribbon_width_scale __attribute__((sda)), g_beam_ribbon_halo_scale __attribute__((sda)), g_beam_ribbon_scroll_speed __attribute__((sda));
extern int g_beam_ribbon_halo_color_idle __attribute__((sda)), g_beam_ribbon_halo_color_active __attribute__((sda));
extern float g_beam_ribbon_uv_offset __attribute__((sda)), g_beam_ribbon_uv_rate __attribute__((sda));
extern int g_beam_packet_color_idle __attribute__((sda)), g_beam_packet_color_active __attribute__((sda)), g_beam_packet_texture_id __attribute__((sda));
extern char g_sheepinator_ribbon_inner_points[], g_sheepinator_ribbon_outer_points[];
extern float g_sheepinator_ribbon_surface_a[][20][4], g_sheepinator_ribbon_surface_b[][20][4];

typedef struct {
    int word;
    unsigned char state;
    char pad[219];
} StripState;

extern char g_weapon_active_index[], g_camera_l00_position[];
extern StripState g_weapon_l00_table[];

extern void DrawScrollingRibbonWithHalo(void *, int, int, int, float, float, float, int);
extern void DrawLightningArcSparks(void *), DrawTwoPassCameraQuad(void *);
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void draw_world_quad(void *, int, int);

typedef struct {
    float x, y, z, w;
} BeamVertex __attribute__((aligned(16)));

typedef struct {
    BeamVertex q[4];
    unsigned int colors[4];
    struct {
        float x0, y0, x1, y1, x2, y2, x3, y3;
    } uv;
    u64 tags[4];
} BeamPacket;

/* Scrolls the textures, draws the two halo ribbons and two child effects, then draws rows
 * 2 to 11 of a 20-column ring mesh, culling faces turned from the camera; each face is drawn
 * twice with its own scrolling V. Same mesh loop as RAC1's suck_beam_draw_mesh. */
void func_PAL_L00_0040BA28(char *arg)
{
    BeamPacket packet;
    float e[4], f[4], g[4], h[4];
    float x, y, z;
    int color, i, j;

    g_beam_ribbon_uv_offset -= g_beam_ribbon_uv_rate * 1.2f;
    if (g_beam_ribbon_uv_offset <= -8.0f) g_beam_ribbon_uv_offset += 8.0f;
    DrawScrollingRibbonWithHalo(g_sheepinator_ribbon_inner_points, g_beam_ribbon_param_a, g_beam_ribbon_param_b, 12, g_beam_ribbon_width_scale, g_beam_ribbon_halo_scale, g_beam_ribbon_scroll_speed, g_beam_ribbon_halo_color_idle);
    DrawScrollingRibbonWithHalo(g_sheepinator_ribbon_outer_points, g_beam_ribbon_param_a, g_beam_ribbon_param_b, 12, g_beam_ribbon_width_scale, g_beam_ribbon_halo_scale, g_beam_ribbon_scroll_speed, g_beam_ribbon_halo_color_active);
    DrawLightningArcSparks(arg);
    DrawTwoPassCameraQuad(arg);
    color = g_weapon_l00_table[(unsigned char)g_weapon_active_index[0]].state ? g_beam_packet_color_active : g_beam_packet_color_idle;
    packet.tags[1] = GetEffectTextureDescriptor(g_beam_packet_texture_id);
    packet.tags[2] = 0xff9000000260ULL;
    packet.tags[3] = 0x8000000048ULL;
    packet.tags[0] = 0;
    x = g_sheepinator_beam_scroll_x;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    g_sheepinator_beam_scroll_x -= g_sheepinator_beam_scroll_x_rate * 1.2f;
    if (g_sheepinator_beam_scroll_x <= -8.0f) g_sheepinator_beam_scroll_x += 8.0f;
    g_sheepinator_beam_scroll_y -= g_sheepinator_beam_scroll_rate * 1.2f;
    if (g_sheepinator_beam_scroll_y <= -7.0f) g_sheepinator_beam_scroll_y += 7.0f;
    g_sheepinator_beam_scroll_z += g_sheepinator_beam_scroll_rate * 1.2f;
    if (g_sheepinator_beam_scroll_z >= 5.0f) g_sheepinator_beam_scroll_z -= 5.0f;
    for (i = 2; i < 12; i++) {
        y = g_sheepinator_beam_scroll_y;
        z = g_sheepinator_beam_scroll_z;
        for (j = 0; j < 20; j++) {
            qcopy(&packet.q[0], g_sheepinator_ribbon_surface_a[i][j]);
            qcopy(&packet.q[1], g_sheepinator_ribbon_surface_a[i][(j + 1) % 20]);
            qcopy(&packet.q[2], g_sheepinator_ribbon_surface_b[i][j]);
            qcopy(&packet.q[3], g_sheepinator_ribbon_surface_b[i][(j + 1) % 20]);
            FastVecSub(e, &packet.q[0], &packet.q[1]);
            FastVecSub(f, &packet.q[2], &packet.q[1]);
            FastVecCross(g, f, e);
            FastVecSub(h, &packet.q[1], g_camera_l00_position);
            if (FastVecDot(g, h) >= 0.0f) {
                y += g_sheepinator_beam_uv_y_step;
                z += g_sheepinator_beam_uv_y_step;
                continue;
            }
            if (i == 11) {
                packet.colors[0] = packet.colors[1] = g_beam_packet_color_idle & 0xffffff;
            }
            packet.uv.x1 = packet.uv.x0 = x;
            packet.uv.y0 = packet.uv.y2 = y;
            packet.uv.y1 = y + g_sheepinator_beam_uv_y_step;
            packet.uv.x2 = x - g_sheepinator_beam_uv_x_step;
            packet.uv.x3 = x - g_sheepinator_beam_uv_x_step;
            packet.uv.y3 = y + g_sheepinator_beam_uv_y_step;
            y += g_sheepinator_beam_uv_y_step;
            draw_world_quad(&packet.q[0], 0, 0);
            packet.uv.x1 = packet.uv.x0 = x;
            packet.uv.y0 = packet.uv.y2 = z;
            packet.uv.y1 = z + g_sheepinator_beam_uv_y_step;
            packet.uv.x2 = x - g_sheepinator_beam_uv_x_step;
            packet.uv.x3 = x - g_sheepinator_beam_uv_x_step;
            packet.uv.y3 = z + g_sheepinator_beam_uv_y_step;
            z += g_sheepinator_beam_uv_y_step;
            draw_world_quad(&packet.q[0], 0, 0);
        }
        x += g_sheepinator_beam_uv_x_step;
    }
}
