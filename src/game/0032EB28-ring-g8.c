#include "include_asm.h"
#include "names.h"

typedef unsigned int RenderQuad __attribute__((mode(TI)));
typedef union { RenderQuad word; float v[4]; } RenderVector;
typedef struct { float x, y, z, w; } RenderVec __attribute__((aligned(16)));

/* The 144-byte quad packet func_00280B90 draws: four vertices, their colours,
   their UVs and four GS words. */
typedef struct {
    RenderVec vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long long tag[4];
} RenderPacket;

extern long long func_0027C878(int);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282DD8(void *, const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern void func_002830C0(void *, const void *, const void *);
extern void func_0027C768(void *, float *, float *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A7798(float);
extern float func_00283B98(float, float);
extern void func_00280B90(void *, void *, int);
extern RenderVec D_001B5340;
extern int D_001B0A4C __attribute__((sda));
extern int D_001B0A50 __attribute__((sda));
extern int D_001B0A54 __attribute__((sda));
extern int D_001B0A58 __attribute__((sda));
extern int D_001B0A5C __attribute__((sda));
extern int D_001B0A60 __attribute__((sda));
extern unsigned int D_001B0A64 __attribute__((sda));
extern float D_001B0954 __attribute__((sda));
/* 48 quads of a flat ring of 98 vertices: per corner a vertex index and an
   index into the angle table, which holds an angle and its step. */
extern short D_0026C020[][4][2];
extern RenderVec D_0026BA20[];
extern float D_002373F0[][2];

/* Draws the object's ring facing the camera (D_001B5340), scaled by its
   state's size, with each corner's UV taken from its screen position and
   pushed along a rotating angle; the push weakens as the size nears
   D_001B0954. Then advances every angle. */
void func_00330EC0(char *object)
{
    RenderPacket packet;
    RenderVec matrix[4];
    RenderVector up;
    char *state;
    int face, corner, index, vtx;
    long long flags;
    float *u, *v, *uv;
    float delta, scale, c, s;

    state = *(char **)(object + 0x68);
    up.word = 0;
    up.v[2] = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(D_001B0A60);
    packet.tag[2] = 0xFF9000000260LL;
    flags = (long long)D_001B0A4C;
    flags |= (long long)D_001B0A50 << 2;
    flags |= (long long)D_001B0A54 << 4;
    flags |= (long long)D_001B0A58 << 6;
    flags |= (long long)D_001B0A5C << 32;
    packet.tag[3] = flags;
    packet.tag[0] = 0;
    FastVecSub(&matrix[0], &gCameraState_001B5340, object + 0x10);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &up);
    vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    matrix[3].x = *(float *)(object + 0x10);
    matrix[3].y = *(float *)(object + 0x14);
    matrix[3].z = *(float *)(object + 0x18);
    matrix[3].w = 1.0f;
    packet.color[3] = D_001B0A64;
    packet.color[2] = D_001B0A64;
    packet.color[1] = D_001B0A64;
    packet.color[0] = D_001B0A64;
    uv = &packet.uv[0][0];
    for (face = 0; face < 48; face++) {
        v = &packet.uv[0][1];
        u = uv;
        for (corner = 0; corner < 4; corner++) {
            vtx = D_0026C020[face][corner][0];
            index = D_0026C020[face][corner][1];
            FastVecScale(&packet.vertex[corner], &D_0026BA20[vtx], *(float *)(state + 0x64) * 2.0f);
            transform_vector(&packet.vertex[corner], &packet.vertex[corner], matrix);
            ProjectWorldToScreen(&packet.vertex[corner], &packet.uv[corner][0], &packet.uv[corner][1]);
            c = FastSinOrCosA(gRingAngleTable[index][0]);
            delta = c * EaseOutQuad((1.0f - *(float *)(state + 0x64) / D_001B0954) * 0.0125f);
            *u += delta;
            s = FastSinOrCosB(gRingAngleTable[index][0]);
            scale = EaseOutQuad((1.0f - *(float *)(state + 0x64) / D_001B0954) * 0.0125f);
            delta = -s;
            delta *= scale;
            *v += delta;
            if (*u > 1.0f) *u = 1.0f;
            else if (*u < 0.0f) *u = 0.0f;
            if (*v > 1.0f) *v = 1.0f;
            else if (*v < 0.0f) *v = 0.0f;
            v += 2;
            u += 2;
        }
        draw_world_quad(&packet, 0, 0);
    }
    for (face = 0; face < 98; face++)
        gRingAngleTable[face][0] = FastAddRotations(gRingAngleTable[face][0], gRingAngleTable[face][1]);
}
