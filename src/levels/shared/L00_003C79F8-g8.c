/* Ring renderer, following draw_beam_ring_and_rail_effects in
 * OpenRAC/rac1-decomp's walloper_and_beam_effects.c (GPL-3.0).
 * The two texture scrolls cover the same visible ring segments.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } SurfaceVector;
typedef struct { SurfaceVector vertex[4]; int color[4]; float uv[8]; u64 primitive, texture, mode, flags; } SurfacePacket;
extern float g_ribbon_core_scroll_u __attribute__((sda)), g_ribbon_core_scroll_speed __attribute__((sda));
extern int g_ribbon_l00_draw_param_a __attribute__((sda)), g_ribbon_l00_draw_param_b __attribute__((sda));
extern float g_ribbon_width_scale __attribute__((sda)), g_ribbon_draw_param_c __attribute__((sda)), g_ribbon_draw_param_d __attribute__((sda));
extern int g_ribbon_l00_color_a __attribute__((sda)), g_ribbon_l00_color_b __attribute__((sda)), g_ribbon_edge_color __attribute__((sda)), g_ribbon_texture_id __attribute__((sda));
extern float g_ribbon_scroll_u_offset __attribute__((sda)), g_ribbon_scroll_v_offset __attribute__((sda)), g_ribbon_scroll_u __attribute__((sda)), g_ribbon_scroll_u_speed __attribute__((sda));
extern float g_ribbon_scroll_v __attribute__((sda)), g_ribbon_scroll_w __attribute__((sda)), g_ribbon_scroll_vw_speed __attribute__((sda));
extern SurfaceVector g_lightning_ribbon_inner_points[], g_lightning_ribbon_outer_points[], g_lightning_ribbon_surface_a[][20], g_lightning_ribbon_surface_b[][20];
extern char g_camera_l00_position[];
extern void DrawScrollingRibbonColored(void *, int, int, float, float, float, int, int);
extern void DrawLightningArcSparks2(void *), DrawBeamOriginCameraFacingQuads(void *);
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *), FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void draw_world_quad(void *, void *, int);
/* Draws the beam effect: two glowing ribbons, the lightning sparks, the beam origin quads and a ring of scrolling surface quads around the beam. */
void DrawBeamRingAndRailEffects(void *object)
{
    SurfacePacket packet;
    SurfaceVector edge, side, normal, eye;
    int row, i;
    float tex_u, tex_v, tex_w;
    g_ribbon_core_scroll_u -= g_ribbon_core_scroll_speed;
    if (g_ribbon_core_scroll_u <= -8.0f) g_ribbon_core_scroll_u += 8.0f;
    DrawScrollingRibbonColored(g_lightning_ribbon_inner_points, g_ribbon_l00_draw_param_a, g_ribbon_l00_draw_param_b, g_ribbon_width_scale, g_ribbon_draw_param_c, g_ribbon_draw_param_d, 12, g_ribbon_l00_color_a);
    DrawScrollingRibbonColored(g_lightning_ribbon_outer_points, g_ribbon_l00_draw_param_a, g_ribbon_l00_draw_param_b, g_ribbon_width_scale, g_ribbon_draw_param_c, g_ribbon_draw_param_d, 12, g_ribbon_l00_color_b);
    DrawLightningArcSparks2(object);
    DrawBeamOriginCameraFacingQuads(object);
    {
        int color = g_ribbon_edge_color;
        packet.texture = GetEffectTextureDescriptor(g_ribbon_texture_id);
        tex_u = g_ribbon_scroll_u;
        packet.mode = 0xFF9000000260ULL;
        packet.flags = 0x8000000048ULL;
        packet.primitive = 0;
        packet.color[3] = color; packet.color[2] = color; packet.color[1] = color; packet.color[0] = color;
    }
    g_ribbon_scroll_u -= g_ribbon_scroll_u_speed;
    if (g_ribbon_scroll_u <= -8.0f) g_ribbon_scroll_u += 8.0f;
    g_ribbon_scroll_v -= g_ribbon_scroll_vw_speed;
    if (g_ribbon_scroll_v <= -7.0f) g_ribbon_scroll_v += 7.0f;
    g_ribbon_scroll_w += g_ribbon_scroll_vw_speed;
    if (g_ribbon_scroll_w >= 5.0f) g_ribbon_scroll_w -= 5.0f;
    {
        SurfaceVector *point2;
        for (row = 2; row < 12;) {
            int nextRow = row + 1;
            tex_v = g_ribbon_scroll_v; tex_w = g_ribbon_scroll_w;
            for (i = 0; i < 20; i++) {
                qcopy_nc(&packet.vertex[0], &g_lightning_ribbon_surface_a[row][i]);
                qcopy_nc(&packet.vertex[1], &g_lightning_ribbon_surface_a[row][(i + 1) % 20]);
                qcopy_nc(point2 = &packet.vertex[2], &g_lightning_ribbon_surface_b[row][i]);
                qcopy_nc(&packet.vertex[3], &g_lightning_ribbon_surface_b[row][(i + 1) % 20]);
                FastVecSub(&edge, &packet.vertex[0], &packet.vertex[1]);
                FastVecSub(&side, point2, &packet.vertex[1]);
                FastVecCross(&normal, &side, &edge);
                FastVecSub(&eye, &packet.vertex[1], g_camera_l00_position);
                if (FastVecDot(&normal, &eye) >= 0) {
                    tex_v += g_ribbon_scroll_v_offset; tex_w += g_ribbon_scroll_v_offset;
                } else {
                    if (row == 11) { packet.color[1] = g_ribbon_edge_color & 0xFFFFFF; packet.color[0] = g_ribbon_edge_color & 0xFFFFFF; }
                    packet.uv[5] = tex_v;
                    packet.uv[1] = tex_v;
                    packet.uv[3] = tex_v + g_ribbon_scroll_v_offset;
                    packet.uv[4] = tex_u - g_ribbon_scroll_u_offset;
                    packet.uv[0] = tex_u;
                    packet.uv[2] = tex_u;
                    packet.uv[7] = tex_v + g_ribbon_scroll_v_offset;
                    packet.uv[6] = tex_u - g_ribbon_scroll_u_offset;
                    tex_v = tex_v + g_ribbon_scroll_v_offset;
                    draw_world_quad(&packet, 0, 0);
                    packet.uv[0] = tex_u;
                    packet.uv[1] = tex_w;
                    packet.uv[2] = tex_u;
                    packet.uv[3] = tex_w + g_ribbon_scroll_v_offset;
                    packet.uv[5] = tex_w;
                    packet.uv[4] = tex_u - g_ribbon_scroll_u_offset;
                    packet.uv[6] = tex_u - g_ribbon_scroll_u_offset;
                    packet.uv[7] = tex_w + g_ribbon_scroll_v_offset;
                    tex_w = tex_w + g_ribbon_scroll_v_offset;
                    draw_world_quad(&packet, 0, 0);
                }
            }
            row = nextRow;
            tex_u += g_ribbon_scroll_u_offset;
        }
    }
}
