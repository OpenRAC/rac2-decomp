#include "common.h"
typedef unsigned int Q12 __attribute__((mode(TI)));
typedef struct { float x, y; } UV12;
extern int g_water_wave_texture_id __attribute__((sda));
extern int g_water_wave_color_a __attribute__((sda)), g_water_wave_color_b __attribute__((sda));
typedef short Face12[4][3];
extern short g_water_wave_vertex_indices[12] __attribute__((sda));
extern Face12 g_water_wave_face_uvs[] __attribute__((sda));
extern Q12 g_water_wave_matrix[4] __attribute__((sda));
extern UV12 g_water_wave_uv_x[4] __attribute__((sda));
extern UV12 g_water_wave_uv_y[] __attribute__((sda));
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void draw_world_quad(void *, int, int);

/* Draws the two water-wave strips using the wave offsets kept by the wave moby. */
void gfx_draw_water_wave_strips(char *obj) {
    struct {
        Q12 vertices[4];
        int colors[4];
        UV12 uv[4];
        char pad[0x20];
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    int i, j;
    /* Keep the first pass's table bases live across packet initialization. */
    Q12 *vertices = g_water_wave_matrix;
    UV12 *texX = g_water_wave_uv_x;
    UV12 *texY = g_water_wave_uv_y;
    gfx_init_quad_packet_state(&frame, g_water_wave_texture_id, 2, 128);
    frame.colors[0] = frame.colors[1] = frame.colors[2] = frame.colors[3] = g_water_wave_color_a;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = g_water_wave_vertex_indices[i * 12 + j * 3];
            int uv = g_water_wave_face_uvs[i][j][0];
            qcopy(&frame.vertices[j], &vertices[vertex]);
            frame.uv[j].x = texX[uv].x + *(float *)(ctx + 0x10);
            frame.uv[j].y = texY[uv].x;
        }
        draw_world_quad(&frame, 0, 0);
    }
    gfx_init_quad_packet_state(&frame, g_water_wave_texture_id + 1, 0, 128);
    frame.colors[0] = frame.colors[1] = frame.colors[2] = frame.colors[3] = g_water_wave_color_b;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = g_water_wave_vertex_indices[i * 12 + j * 3];
            int uv = g_water_wave_face_uvs[i][j][0];
            qcopy(&frame.vertices[j], &g_water_wave_matrix[vertex]);
            frame.uv[j].x = g_water_wave_uv_x[uv].x + *(float *)(ctx + 0x10);
            frame.uv[j].y = g_water_wave_uv_y[uv].x;
        }
        draw_world_quad(&frame, 0, 0);
    }
}
