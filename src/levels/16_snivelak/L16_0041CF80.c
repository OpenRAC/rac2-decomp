#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; unsigned long long header[4]; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide,direction,end,scratch; } BeamWorkspace;
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern unsigned long long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern char D_L16_001B9B00[];
extern float D_L16_001B1EA8[] __attribute__((sda));
extern float D_L16_001B1EAC[] __attribute__((sda));

/* Draws the object's 25-unit beam along its heading: a wide tinted quad, then a narrow white core. */
void func_L16_0041CF80(char *object)
{
    BeamWorkspace local;
    int i, j;
    ((float *)&local.direction)[0]=func_00283180(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.direction)[1]=func_00283198(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.direction)[2]=0.0f;
    FastVecAdd(&local.end,object+0x10,&local.direction);
    FastVecSub(&local.firstSide,object+0x10,D_L16_001B9B00);
    FastVecSub(&local.secondSide,&local.end,D_L16_001B9B00);
    FastVecCross(&local.firstSide,&local.firstSide,&local.direction);
    vec_scale_to_length(&local.firstSide,&local.firstSide,0.15f);
    FastVecCross(&local.secondSide,&local.secondSide,&local.direction);
    vec_scale_to_length(&local.secondSide,&local.secondSide,0.15f);
    local.packet.header[1]=GetEffectTextureDescriptor(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    local.packet.colors[0] = local.packet.colors[1] = local.packet.colors[2] = local.packet.colors[3] = 0x80243278u;
    for (i = 0; i < 4; i++) {
        local.packet.uv[i][0] = D_L16_001B1EA8[i * 2];
        local.packet.uv[i][1] = D_L16_001B1EAC[i * 2];
    }
    FastVecSub(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[0]=local.scratch;
    FastVecAdd(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[1]=local.scratch;
    FastVecSub(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[2]=local.scratch;
    FastVecAdd(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[3]=local.scratch;
    draw_world_quad(&local.packet,0,0);
    FastVecSub(&local.firstSide,object+0x10,D_L16_001B9B00);
    FastVecSub(&local.secondSide,&local.end,D_L16_001B9B00);
    FastVecCross(&local.firstSide,&local.firstSide,&local.direction);
    vec_scale_to_length(&local.firstSide,&local.firstSide,0.05f);
    FastVecCross(&local.secondSide,&local.secondSide,&local.direction);
    vec_scale_to_length(&local.secondSide,&local.secondSide,0.05f);
    local.packet.header[1]=GetEffectTextureDescriptor(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    local.packet.colors[0] = local.packet.colors[1] = local.packet.colors[2] = local.packet.colors[3] = 0x80808080u;
    for (j = 0; j < 4; j++) {
        local.packet.uv[j][0] = D_L16_001B1EA8[j * 2];
        local.packet.uv[j][1] = D_L16_001B1EAC[j * 2];
    }
    FastVecSub(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[0]=local.scratch;
    FastVecAdd(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[1]=local.scratch;
    FastVecSub(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[2]=local.scratch;
    FastVecAdd(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[3]=local.scratch;
    draw_world_quad(&local.packet,0,0);
}
