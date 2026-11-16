#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; unsigned long long header[4]; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide,direction,end,scratch; } BeamWorkspace;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern unsigned long long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,void *,int);
extern char g_scene_origin_transform[];
extern float g_quad_uv_x_table[] __attribute__((sda));
extern float g_quad_uv_y_table[] __attribute__((sda));

/* Draws the object's 25-unit beam along its heading: a wide tinted quad, then a narrow white core. */
void DrawBeamQuads(char *object)
{
    BeamWorkspace local;
    int i, j;
    ((float *)&local.direction)[0]=math_fast_sin_or_cos_a(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.direction)[1]=math_fast_sin_or_cos_b(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.direction)[2]=0.0f;
    FastVecAdd(&local.end,object+0x10,&local.direction);
    FastVecSub(&local.firstSide,object+0x10,g_scene_origin_transform);
    FastVecSub(&local.secondSide,&local.end,g_scene_origin_transform);
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
        local.packet.uv[i][0] = g_quad_uv_x_table[i * 2];
        local.packet.uv[i][1] = g_quad_uv_y_table[i * 2];
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
    FastVecSub(&local.firstSide,object+0x10,g_scene_origin_transform);
    FastVecSub(&local.secondSide,&local.end,g_scene_origin_transform);
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
        local.packet.uv[j][0] = g_quad_uv_x_table[j * 2];
        local.packet.uv[j][1] = g_quad_uv_y_table[j * 2];
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
