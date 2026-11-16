#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern void endako_boss_remove_target(u8 *, int);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern Vector g_endako_marker_quad_verts[4] __attribute__((sda));
extern float g_endako_marker_quad_uvs[8] __attribute__((sda));
extern float g_endako_marker_quad_uv_v[] MACRO_ADDR;
extern int g_endako_marker_colors[2] __attribute__((sda));
extern float g_endako_marker_scale __attribute__((sda));
extern u8 g_camera_pose_buffer[];

/* Removes inactive targets and draws a textured quad at each remaining target. */
void endako_boss_draw_target_markers_pal(u8 *self) {
    struct { Vector a, b, c, pos; } frame;
    /* The initializer writes four 64-bit state words at +0x70..+0x88. */
    struct { Vector v[4]; int color[4]; float uv[4][2]; long state[4]; } packet;
    u8 *st = *(u8 **)(self + 0x68);
    int i, j, k;
    float scale;

    for (i = 0; i < *(int *)(st + 0x3BC); i++) {
        u8 *obj = *(u8 **)(st + 0x340 + i * 4);
        if (!obj || *(s16 *)(obj + 0xAA) != 0xA72 || obj[0x20] == 0xFE || obj[0x20] == 0xFD)
            endako_boss_remove_target(self, i);
    }
    if (*(int *)(st + 0x3BC) == 0)
        return;
    gfx_init_quad_packet_state(&packet, 5, 1, 0x80);
    for (j = 0; j < 4; j++) {
        qcopy(&packet.v[j], &g_endako_marker_quad_verts[j]);
        packet.color[j] = g_endako_marker_colors[j >> 1];
        packet.uv[j][0] = g_endako_marker_quad_uvs[j * 2];
        packet.uv[j][1] = g_endako_marker_quad_uv_v[j * 2];
    }
    scale = g_endako_marker_scale * 0.020000001f;
    for (k = 0; k < *(int *)(st + 0x3BC); k++) {
        u8 *obj = *(u8 **)(st + 0x340 + k * 4);
        u8 *data = *(u8 **)(obj + 0x68);
        qcopy(&frame.pos, obj + 0x10);
        frame.pos.f[3] = 1.0f;
        FastVecSub(&frame.a, g_camera_pose_buffer, &frame.pos);
        vec_scale_to_length(&frame.b, data, (float)*(s16 *)(data + 0x12) * scale);
        FastVecCross(&frame.c, &frame.b, &frame.a);
        vec_scale_to_length(&frame.c, &frame.c, 1.0f);
        FastVecCross(&frame.a, &frame.b, &frame.c);
        draw_world_quad(&packet, &frame.a, 0);
    }
}
