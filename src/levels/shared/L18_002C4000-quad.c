#include "include_asm.h"
#include "common.h"

/* func_002820D0 (src/game/0027F128-quad.c) with an explicit facing direction: the same quad
   packet, basis and UV handling, so this unit uses the same -frac2-qcopy profile. */
typedef int VectorBits __attribute__((mode(TI)));
typedef union { VectorBits bits; float f[4]; } LensVector;
typedef struct { float u, v; } TexCoord;
typedef struct {
    LensVector vertex[4];
    u32 colors[4];
    TexCoord uv[4];
    s64 primitive, texture, mode, flags;
} QuadPacket;

extern float D_0018A0E0[4];
extern float D_L18_001AA250[4][4];
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00281DE8(QuadPacket *, s32, s32, s32);
extern void func_00280B90(void *, s32, s32);
extern void func_0027C768(s32, float *, float *);

/* Draws a quad facing DIRECTION at POSITION, then redraws it textured, with the caller's four
   UV pairs or, without them, the projected corners pushed apart by SPREAD; UVs clamp to [0, 1]. */
void func_L18_00307C60(LensVector *position, LensVector *direction, s32 opacity, float **customUV,
                       float size, float spread, float distance)
{
    QuadPacket packet;
    LensVector basis[4], offset;
    s32 i;

    basis[3].bits = position->bits;
    basis[0].bits = direction->bits;
    func_00282DD8(&basis[1], &basis[0], D_0018A0E0);
    func_00282F20(&basis[1], &basis[1], 1.0f);
    func_00282DD8(&basis[2], &basis[1], &basis[0]);
    func_00282D30(&offset, &basis[0], distance);
    func_00282CC0(&basis[3], &basis[3], &offset);
    for (i = 3; i >= 0; i--) {
        int index = 3 - i;
        func_00282D30(&packet.vertex[index], D_L18_001AA250[index], size);
        func_002830C0(&packet.vertex[index], &packet.vertex[index], basis);
    }
    func_00281DE8(&packet, 60, 5, 128);
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] =
        ((u32)opacity << 24) | 0x808080;
    packet.uv[0].u = 0.0f;
    packet.uv[0].v = 0.0f;
    packet.uv[1].u = 0.0f;
    packet.uv[1].v = 1.0f;
    packet.uv[2].u = 1.0f;
    packet.uv[2].v = 0.0f;
    packet.uv[3].u = 1.0f;
    packet.uv[3].v = 1.0f;
    func_00280B90(&packet, 0, 0);
    func_00281DE8(&packet, -1, 6, 128);
    func_00282D30(&offset, &basis[0], distance + 0.01f);
    if (customUV) {
        for (i = 3; i >= 0; i--) {
            int index = 3 - i;
            packet.uv[index].u = customUV[index][0];
            packet.uv[index].v = customUV[index][1];
            if (packet.uv[index].u > 1.0f)
                packet.uv[index].u = 1.0f;
            else if (packet.uv[index].u < 0.0f)
                packet.uv[index].u = 0.0f;
            if (packet.uv[index].v > 1.0f)
                packet.uv[index].v = 1.0f;
            else if (packet.uv[index].v < 0.0f)
                packet.uv[index].v = 0.0f;
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_0027C768((s32)&packet.vertex[i], &packet.uv[i].u, &packet.uv[i].v);
            if (i >> 1)
                packet.uv[i].u -= spread;
            else
                packet.uv[i].u += spread;
            {
                /* Assigning through the value leaves one store after the join, its address
                   copied before the branch, as retail has it (see func_002820D0). */
                float value = packet.uv[i].v;
                packet.uv[i].v = value = (i & 1) ? value + spread : value - spread;
            }
            if (packet.uv[i].u > 1.0f)
                packet.uv[i].u = 1.0f;
            else if (packet.uv[i].u < 0.0f)
                packet.uv[i].u = 0.0f;
            if (packet.uv[i].v > 1.0f)
                packet.uv[i].v = 1.0f;
            else if (packet.uv[i].v < 0.0f)
                packet.uv[i].v = 0.0f;
        }
    }
    func_00280B90(&packet, 0, 0);
}
