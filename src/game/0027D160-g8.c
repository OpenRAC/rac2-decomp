#include "common.h"
/* Adapted from RAC1 draw_light_quads (src/game/draw.c). */
typedef float FVec4[4] __attribute__((aligned(16)));
typedef struct { FVec4 v; } FRow;
typedef struct { FRow pos; FRow dir; } LightRec;
extern float D_001A87A0 __attribute__((sda));
extern LightRec D_001BA640[];
extern int D_001B163C;
extern long long GetEffectTextureDescriptor(int);
extern void vec_scale_to_length(void *, void *, float);
extern void draw_world_quad(void *, int, int);
/* Draws the glowing light sprites that face the camera. */
void DrawLightQuads(void) {
    FRow m[4];
    int colors[4];
    float uv[4][2];
    unsigned long pkt[4];
    FRow dir;
    int i;
    int j;

    pkt[1] = GetEffectTextureDescriptor(0);
    pkt[2] = 0xFF9000000260;
    pkt[0] = 5;
    pkt[3] = 0x8000000044;
    for (j = 0; j < 4; j++) {
        uv[j][0] = ((FRow *)&D_001A87A0)[j].v[2];
        uv[j][1] = ((FRow *)&D_001A87A0)[j].v[3];
        colors[j] = 0x40808080;
    }
    for (i = 0; i < D_001B163C; i++) {
        float s;
        int k;

        qcopy(&dir, &D_001BA640[i].dir);
        vec_scale_to_length(&dir, &dir, 1.0f);
        s = D_001BA640[i].pos.v[3];
        for (k = 0; k < 4; k++) {
            float cx = ((FRow *)&D_001A87A0)[k].v[0];
            float vx = dir.v[0];
            float cy = ((FRow *)&D_001A87A0)[k].v[1];
            float d = cx * vx + cy * dir.v[1];

            qcopy(&m[k], &D_001BA640[i].pos);
            m[k].v[0] += (cx - vx * d) * s;
            m[k].v[1] += (cy - dir.v[1] * d) * s;
            m[k].v[2] -= dir.v[2] * d * s;
        }
        draw_world_quad(m, 0, 0);
    }
}
