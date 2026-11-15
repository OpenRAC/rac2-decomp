#include "common.h"

typedef unsigned long long U64;
typedef int TI128 __attribute__((mode(TI)));
struct Vertex { float x, y, z, w; };
struct Packet { struct Vertex vertices[4]; int colors[4]; float uv[8]; U64 tag, texture, mode, state; };
/* The effect's tuning block: a member at its start is read as an absolute macro load. */
struct Tuning {
    float rates[2];
    float speed[2];
    int alpha[2];
    int colors[2];
    float sizes[2];
    float spin[2];
    int texture;
    int blend[2];
    int pad;
    float uvs[8];
    float pad2[2];
    struct Vertex vertices[4];
    int fade[3];
};
extern struct Tuning D_L02_001AFFB8[] __attribute__((sda));
extern float D_L02_001BA518[];
extern float D_L02_001B006C __attribute__((sda)), D_L02_001B0070 __attribute__((sda));
extern int D_L02_001B0060 __attribute__((sda));
extern struct Vertex D_L02_001B0020[] SDATA(D_L02_001B0020);
extern float D_L02_001AFFF8[] SDATA(D_L02_001AFFF8);
extern float D_L02_001AFFFC[] __attribute__((sda));
extern int D_L02_001AFFE8 __attribute__((sda)), D_L02_001AFFEC __attribute__((sda)), D_L02_001AFFF0 __attribute__((sda));
extern void func_00283410(void *, void *), func_00282D30(void *, void *, float), func_00280B90(void *, void *, int);
extern int func_00283D38(int, int, float);
extern U64 func_0027C878(int);

/* Draws the effect's quad twice, scaled by the two timers and faded through three colours. */
void func_L02_003CA280(char *obj)
{
    struct Packet packet;
    float matrix[16] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    char *data;
    float a, b, c;
    int color, i;
    float *us, *vs;
    *(TI128 *)temp = 0;
    temp[2] = D_L02_001BA518[0];
    data = *(char **)(obj + 0x68);
    *(TI128 *)angles = *(TI128 *)temp;
    euler_to_matrix(matrix, angles);
    a = *(float *)(data + 8);
    b = (1.0f - a) * D_L02_001B006C + 1.0f;
    c = D_L02_001B0070 * *(float *)(data + 12);
    a += c;
    b += c;
    FastVecScale(matrix, matrix, a);
    FastVecScale(matrix + 4, matrix + 4, a);
    FastVecScale(matrix + 8, matrix + 8, b);
    qcopy(matrix + 12, obj + 0x10);
    matrix[14] -= D_L02_001B0070 * *(float *)(data + 12) * 0.5f;
    matrix[15] = 1.0f;
    if (*(float *)(data + 8) < 1.0f)
        color = FastTweenColor(D_L02_001B0060, D_L02_001AFFB8[0].fade[1], *(float *)(data + 8));
    else
        color = FastTweenColor(D_L02_001AFFB8[0].fade[1], D_L02_001AFFB8[0].fade[2], *(float *)(data + 12));
    us = packet.uv;
    vs = packet.uv + 1;
    for (i = 0; i < 4; i++) {
        packet.colors[i] = color;
        us[i * 2] = D_L02_001AFFF8[i * 2];
        vs[i * 2] = D_L02_001AFFFC[i * 2];
        qcopy(&packet.vertices[i], &D_L02_001B0020[i]);
    }
    packet.texture = GetEffectTextureDescriptor(D_L02_001AFFE8);
    packet.mode = 0xFF9000000260ULL;
    packet.tag = 5;
    packet.state = ((U64)D_L02_001AFFEC << 2) | ((U64)D_L02_001AFFF0 << 6) | 0x8000000000ULL;
    draw_world_quad(&packet, matrix, 1);
    draw_world_quad(&packet, matrix, 1);
}
