#include "common.h"

typedef unsigned int NotakTI __attribute__((mode(TI)));
typedef float NotakVec[4] __attribute__((aligned(16)));
typedef struct {
    NotakVec pos[4];
    u32 color[4];
    float uv[8];
    u64 primitive, texture, mode, flags;
} NotakPacket;

extern u64 func_0027C878(int);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, int, int);
extern NotakVec D_L06_001B9840;
extern char D_L06_001B1930 __attribute__((sda));

/* Draws a small glowing sprite that always faces the camera at the object's position. */
void func_L06_00459620(char *obj) {
    NotakPacket packet;
    NotakVec matrix[4], corner, up, dir;
    u32 color;
    int i;
    qcopy(matrix[3], obj + 0x10);
    matrix[3][3] = 1.0f;
    color = 0x307F4040;
    packet.texture = GetEffectTextureDescriptor(8);
    packet.flags = 0x8000000048ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 0;
    packet.uv[0] = 0; packet.uv[1] = 0; packet.uv[2] = 0; packet.uv[3] = 1;
    packet.uv[4] = 1; packet.uv[5] = 0; packet.uv[6] = 1; packet.uv[7] = 1;
    if (!RandomIntBelow(4)) color = 0x7F7F4040;
    color = (color & 0xFFFFFF) | ((u32)FloatToInt(IntToFloat(color >> 24)) << 24);
    *(NotakTI *)up = 0; up[2] = 1; up[3] = 1;
    packet.color[3] = color; packet.color[2] = color; packet.color[1] = color; packet.color[0] = color;
    FastVecSub(dir, D_L06_001B9840, matrix[3]);
    vec_scale_to_length(matrix[0], dir, 1);
    FastVecCross(matrix[1], matrix[0], up);
    vec_scale_to_length(matrix[1], matrix[1], 1);
    FastVecCross(matrix[2], matrix[1], matrix[0]);
    FastVecScale(dir, matrix[0], 0.2f);
    FastVecAdd(matrix[3], matrix[3], dir);
    for (i = 0; i < 4; i++) {
        FastVecScale(corner, &D_L06_001B1930 + i * 16, 0.2f);
        transform_vector(packet.pos[i], corner, matrix);
    }
    draw_world_quad(&packet, 0, 0);
}
