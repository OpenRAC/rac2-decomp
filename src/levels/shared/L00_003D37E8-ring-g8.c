#include "include_asm.h"
#include "names.h"

/* Level counterpart of func_00327D50; the vector clear takes one register,
   as in the matched boot unit. */

typedef unsigned int RenderQuad __attribute__((mode(TI)));
typedef union { RenderQuad word; float v[4]; } RenderVector;
typedef struct { float x, y, z, w; } RenderVec __attribute__((aligned(16)));

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
extern char D_L00_001B8DC0[];
extern int D_L00_001B04F4 __attribute__((sda));
extern int D_L00_001B04F8 __attribute__((sda));
extern int D_L00_001B04FC __attribute__((sda));
extern int D_L00_001B0500 __attribute__((sda));
extern int D_L00_001B0504 __attribute__((sda));
extern int D_L00_001B0508 __attribute__((sda));
extern unsigned int D_L00_001B050C __attribute__((sda));
extern float D_L00_001B0434 __attribute__((sda));
extern short D_L00_002967A0[][4][2];
extern RenderVec D_L00_002961A0[];
extern float D_L00_002474F0[][2];

/* Draws a wobbling 3D ball made of 48 textured faces around the object, facing the camera. The wobble shrinks as the object grows. */
void func_L00_003DF338(char *object)
{
    RenderPacket packet;
    RenderVec matrix[4];
    RenderVector up;
    char *vars;
    int face, corner, index, vtx;
    long long flags;
    float *texU, *texV, *uvStart;
    float delta, scale, cosValue, sinValue;

    vars = *(char **)(object + 0x68);
    up.word = 0;
    up.v[2] = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(D_L00_001B0508);
    packet.tag[2] = 0xFF9000000260LL;
    flags = (long long)D_L00_001B04F4;
    flags |= (long long)D_L00_001B04F8 << 2;
    flags |= (long long)D_L00_001B04FC << 4;
    flags |= (long long)D_L00_001B0500 << 6;
    flags |= (long long)D_L00_001B0504 << 32;
    packet.tag[3] = flags;
    packet.tag[0] = 0;
    FastVecSub(&matrix[0], gCameraPosition_L00, object + 0x10);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &up);
    vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    matrix[3].x = *(float *)(object + 0x10);
    matrix[3].y = *(float *)(object + 0x14);
    matrix[3].z = *(float *)(object + 0x18);
    matrix[3].w = 1.0f;
    packet.color[3] = D_L00_001B050C;
    packet.color[2] = D_L00_001B050C;
    packet.color[1] = D_L00_001B050C;
    packet.color[0] = D_L00_001B050C;
    uvStart = &packet.uv[0][0];
    for (face = 0; face < 48; face++) {
        texV = &packet.uv[0][1];
        texU = uvStart;
        for (corner = 0; corner < 4; corner++) {
            vtx = D_L00_002967A0[face][corner][0];
            index = D_L00_002967A0[face][corner][1];
            FastVecScale(&packet.vertex[corner], &D_L00_002961A0[vtx], *(float *)(vars + 0x24) * 2.0f);
            transform_vector(&packet.vertex[corner], &packet.vertex[corner], matrix);
            ProjectWorldToScreen(&packet.vertex[corner], &packet.uv[corner][0], &packet.uv[corner][1]);
            cosValue = FastSinOrCosA(D_L00_002474F0[index][0]);
            delta = cosValue * EaseOutQuad((1.0f - *(float *)(vars + 0x24) / D_L00_001B0434) * 0.0125f);
            *texU += delta;
            sinValue = FastSinOrCosB(D_L00_002474F0[index][0]);
            scale = EaseOutQuad((1.0f - *(float *)(vars + 0x24) / D_L00_001B0434) * 0.0125f);
            delta = -sinValue;
            delta *= scale;
            *texV += delta;
            if (*texU > 1.0f) *texU = 1.0f;
            else if (*texU < 0.0f) *texU = 0.0f;
            if (*texV > 1.0f) *texV = 1.0f;
            else if (*texV < 0.0f) *texV = 0.0f;
            texV += 2;
            texU += 2;
        }
        draw_world_quad(&packet, 0, 0);
    }
    for (face = 0; face < 98; face++)
        D_L00_002474F0[face][0] = FastAddRotations(D_L00_002474F0[face][0], D_L00_002474F0[face][1]);
}
