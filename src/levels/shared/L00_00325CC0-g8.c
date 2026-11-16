#include "common.h"

typedef struct { float x, y, z, w; } BillboardBatchVec __attribute__((aligned(16)));
typedef int BillboardBatchQuad __attribute__((mode(TI)));
typedef union { BillboardBatchVec v; BillboardBatchQuad word; } BillboardBatchUp;
typedef struct {
    BillboardBatchVec vertex[4];
    int color[4];
    float uv[8];
    unsigned long long tag[4];
} BillboardBatchPacket;

extern unsigned long long GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern BillboardBatchVec g_billboard_corner_table[4] __attribute__((sda));
extern BillboardBatchVec g_camera_l00_position NOT_SDA;

/* Draws offset camera-facing quads, reusing the packet while its color is unchanged. */
void DrawOffsetBillboardBatch(int count, BillboardBatchVec *positions, int *colors,
                     float size, float offset)
{
    BillboardBatchPacket packet;
    BillboardBatchUp up;
    BillboardBatchVec matrix[4];
    BillboardBatchVec shift;
    int i, j, color;
    BillboardBatchVec *dst, *src;

    up.word = 0;
    up.v.z = 1.0f;
    up.v.w = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(11);
    color = colors[0];
    packet.tag[3] = 0x8000000048ULL;
    packet.tag[2] = 0xff9000000260ULL;
    packet.tag[0] = 5;
    packet.uv[0] = 0; packet.uv[1] = 0;
    packet.uv[2] = 0; packet.uv[3] = 1;
    packet.uv[4] = 1; packet.uv[5] = 0;
    packet.uv[6] = 1; packet.uv[7] = 1;
    packet.color[3] = color;
    packet.color[2] = color;
    packet.color[1] = color;
    packet.color[0] = color;
    for (i = 0; i < count; ++i) {
        qcopy(&matrix[3], &positions[i]);
        FastVecSub(&matrix[0], &g_camera_l00_position, &matrix[3]);
        vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
        FastVecCross(&matrix[1], &matrix[0], &up);
        vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
        FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
        FastVecScale(&shift, &matrix[0], offset);
        FastVecAdd(&matrix[3], &matrix[3], &shift);
        if (colors[i] != color) {
            packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = colors[i];
            color = colors[i];
        }
        dst = packet.vertex;
        src = g_billboard_corner_table;
        for (j = 3; j >= 0; --j) {
            FastVecScale(dst, src, size);
            ++src;
            transform_vector(dst, dst, matrix);
            ++dst;
        }
        draw_world_quad(&packet, 0, 0);
    }
}
