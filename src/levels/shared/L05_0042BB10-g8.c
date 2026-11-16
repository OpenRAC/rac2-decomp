#include "common.h"

typedef unsigned int DrawQuad __attribute__((mode(TI)));
typedef union { DrawQuad q; float v[4]; } DrawVector;
typedef struct {
    DrawVector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
    DrawVector extra;
} DrawPacket;
typedef struct { DrawVector row[3], position; } DrawFrame;

extern float g_ground_quad_offset_scale __attribute__((sda));
extern float g_ground_quad_vertex_scale __attribute__((sda));
extern int g_ground_quad_texture __attribute__((sda));
extern DrawVector g_ground_quad_vertices[4];
extern char g_origin_vec[];
extern void VU1_addGSregister(int, unsigned long);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

/* Draws a flat tiled textured quad facing the camera at the object's position. */
void gfx_draw_tiled_ground_quad(char *object)
{
    DrawVector position, offset;
    DrawPacket packet;
    DrawFrame frame;
    int i;

    VU1_addGSregister(0x47, 0x53001UL);
    {
        float x = *(float *)(object + 0x10), y = *(float *)(object + 0x14), z = *(float *)(object + 0x18);
        position.v[2] = z;
        position.v[0] = x;
        position.v[1] = y;
    }
    position.v[3] = 1.0f;
    FastVecScale(&offset, object + 0xC0, g_ground_quad_offset_scale);
    FastVecAdd(&position, &position, &offset);
    gfx_init_quad_packet_state(&packet, g_ground_quad_texture, 2, 0x80);
    packet.extra.q = 0;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[1][1] = 5.0f;
    packet.uv[2][0] = 5.0f;
    packet.uv[3][0] = 5.0f;
    packet.uv[3][1] = 5.0f;
    packet.uv[0][0] = 0;
    packet.uv[0][1] = 0;
    packet.uv[1][0] = 0;
    packet.uv[2][1] = 0;
    packet.extra.v[2] = 1.0f;
    packet.extra.v[3] = 1.0f;
    qcopy(&frame.position, &position);
    FastVecSub(&frame.row[0], g_origin_vec, &frame.position);
    vec_scale_to_length(&frame.row[0], &frame.row[0], 1.0f);
    FastVecCross(&frame.row[1], &frame.row[0], &packet.extra);
    vec_scale_to_length(&frame.row[1], &frame.row[1], 1.0f);
    FastVecCross(&frame.row[2], &frame.row[1], &frame.row[0]);
    for (i = 0; i < 4; i++) {
        FastVecScale(&packet.vertex[i], &g_ground_quad_vertices[i], g_ground_quad_vertex_scale);
        transform_vector(&packet.vertex[i], &packet.vertex[i], &frame);
    }
    draw_world_quad(&packet, 0, 0);
}
