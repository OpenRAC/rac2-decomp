#include "common.h"
/* func_US2_0027D7D0, the v2.00 copy of func_0027D160: the same C, with an early return when
   D_001B163C is 0 and func_0027C878 becoming func_US2_0027CED8. */
/* Adapted from RAC1 draw_light_quads (src/game/draw.c). */
typedef float FVec4[4] __attribute__((aligned(16)));
typedef struct { FVec4 v; } FRow;
typedef struct { FRow pos; FRow dir; } LightRec;
extern float g_quad_uv_rows __attribute__((sda));
extern LightRec g_light_records[];
extern int g_ground_shadow_count;
extern unsigned long tex_get_effect_descriptor_us2(int);
extern void vec_scale_to_length(void *, void *, float);
extern void draw_world_quad(void *, int, int);
/* Draws the ground shadow quads: each light record projects a flat quad onto the ground along its direction (USA v2.00: returns early when there are none). */
void gfx_draw_light_quads_us2(void) {
    FRow quad[4];
    int colors[4];
    float uv[4][2];
    unsigned long pkt[4];
    FRow dir;
    int i;
    int j;

    if (g_ground_shadow_count == 0) {
        return;
    }
    pkt[1] = tex_get_effect_descriptor_us2(0);
    pkt[2] = 0xFF9000000260;
    pkt[0] = 5;
    pkt[3] = 0x8000000044;
    for (j = 0; j < 4; j++) {
        uv[j][0] = ((FRow *)&g_quad_uv_rows)[j].v[2];
        uv[j][1] = ((FRow *)&g_quad_uv_rows)[j].v[3];
        colors[j] = 0x40808080;
    }
    for (i = 0; i < g_ground_shadow_count; i++) {
        float scale;
        int k;

        qcopy(&dir, &g_light_records[i].dir);
        vec_scale_to_length(&dir, &dir, 1.0f);
        scale = g_light_records[i].pos.v[3];
        for (k = 0; k < 4; k++) {
            float cx = ((FRow *)&g_quad_uv_rows)[k].v[0];
            float vx = dir.v[0];
            float cy = ((FRow *)&g_quad_uv_rows)[k].v[1];
            float dot = cx * vx + cy * dir.v[1];

            qcopy(&quad[k], &g_light_records[i].pos);
            quad[k].v[0] += (cx - vx * dot) * scale;
            quad[k].v[1] += (cy - dir.v[1] * dot) * scale;
            quad[k].v[2] -= dir.v[2] * dot * scale;
        }
        draw_world_quad(quad, 0, 0);
    }
}
