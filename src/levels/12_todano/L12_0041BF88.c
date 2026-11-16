#include "common.h"

typedef int BF88Quad __attribute__((mode(TI)));
typedef union { BF88Quad q; float f[4]; } __attribute__((aligned(16))) BF88Vector;
typedef struct {
    BF88Vector point[4];
    u32 color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} __attribute__((aligned(16))) BF88Packet;
extern u8 *g_path_waypoint_table;
extern float g_beam_panel_uv_u_table[8] SDATA(D_L12_001B1D20);
extern float g_beam_panel_uv_v_table[];
extern float g_beam_panel_corner_z SDATA(D_L12_001B1D40);
extern float g_beam_panel_thickness SDATA(D_L12_001B1D44);
extern float g_beam_panel_half_width SDATA(D_L12_001B1D80);
extern float g_beam_panel_point_z SDATA(D_L12_001B1D84);
extern s32 g_beam_panel_texture_id SDATA(D_L12_001B1D14);
extern s32 g_beam_panel_gs_state_a SDATA(D_L12_001B1D18);
extern s32 g_beam_panel_gs_state_b SDATA(D_L12_001B1D1C);
extern s32 g_beam_panel_color SDATA(D_L12_001B1D4C);
extern s32 g_beam_panel_color_a SDATA(D_L12_001B1D50);
extern s32 g_beam_panel_color_b SDATA(D_L12_001B1D54);
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern u64 GetEffectTextureDescriptor(int);
extern u32 FastTweenColor(u32, u32, float);

/* Draws the beam volume as a stack of glowing panels with side walls. */
void gfx_draw_beam_volume_panels(u8 *self)
{
    BF88Packet packet;
    BF88Vector matrix[4], rotation[4], angle, offset;
    u8 *vars = *(u8 **)(self + 0x68);
    float width, height, thickness;
    float halfWidth;
    float h, y, phase, nextPhase, step, halfHeight;
    int i, j, k, n;

    angle.q = 0;
    angle.f[1] = 1.5707964897155762f;
    height = *(float *)(vars + 0x44);
    width = *(float *)(vars + 0x40);
    euler_to_matrix(rotation, &angle);
    ({
        BF88Vector corner;
        corner.q = 0;
        thickness = width * 0.5f;
        corner.f[1] = thickness;
        corner.f[2] = g_beam_panel_corner_z;
        corner.f[3] = 1.0f;
        offset.q = corner.q;
    });
    euler_to_matrix(matrix, g_path_waypoint_table + *(int *)vars * 128 + 0x70);
    qcopy(&matrix[3], g_path_waypoint_table + *(int *)vars * 128 + 0x30);
    matrix[3].f[2] -= height * 0.5f + 0.5f;
    matrix[3].f[3] = 1.0f;
    {
        u32 color = g_beam_panel_color;
        for (n = 0; n < 4; n++) {
            packet.color[n] = color;
            packet.uv[n][0] = g_beam_panel_uv_u_table[n * 2];
            packet.uv[n][1] = g_beam_panel_uv_v_table[n * 2];
            qcopy(&packet.point[n], &offset);
            if (n < 2) packet.point[n].f[1] = -packet.point[n].f[1];
            if (n & 1) packet.point[n].f[2] = -packet.point[n].f[2];
            packet.point[n].f[2] += 0.25f;
        }
    }
    packet.texture = GetEffectTextureDescriptor(g_beam_panel_texture_id);
    packet.setup = 0xFF9000000260ULL;
    packet.state = ((u64)g_beam_panel_gs_state_a << 2) | ((u64)g_beam_panel_gs_state_b << 6) | 0x8000000000ULL;
    packet.reserved = 0;
    for (h = 0.0f; h <= height - 0.1f; h += 0.5f) {
        for (j = 0; j < 4; j++) {
            if (j >= 2) {
                if (h <= 2.5f) packet.point[j].f[1] = *(float *)(vars + 0x34);
                else if (h <= 4.5f) packet.point[j].f[1] = *(float *)(vars + 0x38);
                else packet.point[j].f[1] = width;
            }
            packet.point[j].f[2] += 0.5f;
        }
        ({
            BF88Packet rotated;
            rotated = packet;
            for (i = 0; i < 4; i++)
                transform_vector(&rotated.point[i], &packet.point[i], matrix);
            draw_world_quad(&rotated, 0, 1);
        });
    }
    for (k = 0; k < 4; k++) {
        thickness = g_beam_panel_thickness;
        packet.point[k].f[2] -= height;
        if (packet.point[k].f[2] <= 0.0f) thickness = -thickness;
        packet.point[k].f[2] = thickness;
    }
    y = *(float *)(vars + 0x34);
    phase = *(float *)(vars + 4);
    step = 0.5f / width;
    halfWidth = width * 0.5f;
    halfHeight = height * 0.5f;
    for (; y > -halfWidth; y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 0; i < 2; i++) packet.point[i].f[2] = -halfHeight; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 3; i >= 0; i--) packet.point[i].f[0] = g_beam_panel_half_width; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = g_beam_panel_half_width; }
            draw_world_quad(&rotated, matrix, 1);
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = -g_beam_panel_half_width; }
            draw_world_quad(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            draw_world_quad(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            draw_world_quad(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = FastTweenColor(g_beam_panel_color_a, g_beam_panel_color_b, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
    for (y = *(float *)(vars + 0x38); y > *(float *)(vars + 0x34); y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 1; i >= 0; i--) packet.point[i].f[2] = g_beam_panel_point_z; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 3; i >= 0; i--) packet.point[i].f[0] = g_beam_panel_half_width; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = g_beam_panel_half_width; }
            draw_world_quad(&rotated, matrix, 1);
            rotated = packet;
            draw_world_quad(&rotated, matrix, 1);
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = -g_beam_panel_half_width; }
            draw_world_quad(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            draw_world_quad(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            draw_world_quad(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = FastTweenColor(g_beam_panel_color_a, g_beam_panel_color_b, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
}
