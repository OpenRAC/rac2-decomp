#include "common.h"
typedef struct { float vertex[4][4]; int color[4]; float uv[8]; u64 primitive, texture, mode, flags; } BillboardPacket;
extern float D_L00_001AF288 __attribute__((sda)), D_L00_001AF28C __attribute__((sda));
extern int D_L00_001AF290 __attribute__((sda)), D_L00_001AF294 __attribute__((sda)), D_L00_001AF298 __attribute__((sda));
extern float D_L00_001AF2A0[4][4] __attribute__((sda));
extern float D_L00_001B27DC MACRO_ADDR;
extern char D_L00_001B8DC0[];
extern float D_0018A0E0[4];
extern void func_00282D30(void *, void *, float), func_00282CC0(void *, void *, void *);
extern u64 func_0027C878(s32);
extern s32 func_002A77E0(s32);
extern float func_00283CE0(s32);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *), func_00280B90(void *, void *, int);
/* Builds a camera-facing quad around a point on the actor's local axis. */
void func_L00_00396078(char *actor) {
    BillboardPacket packet;
    float basis[4][4], transformed[4], axisOffset[4], difference[4];
    int color, i;
    float alpha;
    float *source;
    float *vertex;
    FastVecScale(axisOffset, actor + 0xD0, D_L00_001AF28C);
    FastVecAdd(basis[3], axisOffset, actor + 0x10);
    packet.texture = GetEffectTextureDescriptor(D_L00_001AF298);
    packet.flags = 0x8000000048ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 0;
    packet.uv[0] = 0; packet.uv[1] = 0; packet.uv[2] = 0; packet.uv[3] = 1;
    packet.uv[4] = 1; packet.uv[5] = 0; packet.uv[6] = 1; packet.uv[7] = 1;
    if (RandomIntBelow(4) == 0) color = D_L00_001AF294;
    else color = D_L00_001AF290;
    alpha = IntToFloat(color >> 24);
    color = (color & 0xFFFFFF) | (FloatToInt(alpha * D_L00_001B27DC) << 24);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    FastVecSub(difference, gCameraPosition_L00, basis[3]);
    vec_scale_to_length(basis[0], difference, 1.0f);
    FastVecCross(basis[1], basis[0], D_0018A0E0);
    vec_scale_to_length(basis[1], basis[1], -1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    FastVecScale(difference, basis[0], 0.2f);
    FastVecAdd(basis[3], basis[3], difference);
    source = D_L00_001AF2A0[0];
    vertex = packet.vertex[0];
    for (i = 3; i >= 0; i--) {
        FastVecScale(transformed, source, D_L00_001AF288);
        source += 4;
        transform_vector(vertex, transformed, basis);
        vertex += 4;
    }
    draw_world_quad(&packet, 0, 0);
}
