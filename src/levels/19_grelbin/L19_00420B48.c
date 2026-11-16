#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; unsigned long long header[4]; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide,direction,end,scratch; } BeamWorkspace;
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern unsigned long long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,void *,int);
extern char g_hero_origin_vec[];
extern float g_beam_l19_uv_u_table[] __attribute__((sda));
extern float g_beam_l19_uv_v_table[] __attribute__((sda));

/* Draws the object's 25-unit beam along its heading: a wide tinted quad, then a narrow white core. */
void gfx_draw_beam_along_heading(char *moby)
{
    BeamWorkspace beam;
    int i, j;
    vec_scale_to_length(&beam.direction,moby+0xe0,*(float *)(*(char **)(moby+0x68)+0xc));
    FastVecAdd(&beam.end,moby+0x10,&beam.direction);
    FastVecSub(&beam.firstSide,moby+0x10,g_hero_origin_vec);
    FastVecSub(&beam.secondSide,&beam.end,g_hero_origin_vec);
    FastVecCross(&beam.firstSide,&beam.firstSide,&beam.direction);
    vec_scale_to_length(&beam.firstSide,&beam.firstSide,0.15f);
    FastVecCross(&beam.secondSide,&beam.secondSide,&beam.direction);
    vec_scale_to_length(&beam.secondSide,&beam.secondSide,0.15f);
    beam.packet.header[1]=GetEffectTextureDescriptor(14);
    beam.packet.header[2]=0xff9000000260ULL;
    beam.packet.header[3]=0x8000000048ULL;
    beam.packet.header[0]=0;
    beam.packet.colors[0] = beam.packet.colors[1] = beam.packet.colors[2] = beam.packet.colors[3] = 0x80243278u;
    for (i = 0; i < 4; i++) {
        beam.packet.uv[i][0] = g_beam_l19_uv_u_table[i * 2];
        beam.packet.uv[i][1] = g_beam_l19_uv_v_table[i * 2];
    }
    FastVecSub(&beam.scratch,moby+0x10,&beam.firstSide);
    beam.packet.vertices[0]=beam.scratch;
    FastVecAdd(&beam.scratch,moby+0x10,&beam.firstSide);
    beam.packet.vertices[1]=beam.scratch;
    FastVecSub(&beam.scratch,&beam.end,&beam.secondSide);
    beam.packet.vertices[2]=beam.scratch;
    FastVecAdd(&beam.scratch,&beam.end,&beam.secondSide);
    beam.packet.vertices[3]=beam.scratch;
    draw_world_quad(&beam.packet,0,0);
    FastVecSub(&beam.firstSide,moby+0x10,g_hero_origin_vec);
    FastVecSub(&beam.secondSide,&beam.end,g_hero_origin_vec);
    FastVecCross(&beam.firstSide,&beam.firstSide,&beam.direction);
    vec_scale_to_length(&beam.firstSide,&beam.firstSide,0.05f);
    FastVecCross(&beam.secondSide,&beam.secondSide,&beam.direction);
    vec_scale_to_length(&beam.secondSide,&beam.secondSide,0.05f);
    beam.packet.header[1]=GetEffectTextureDescriptor(14);
    beam.packet.header[2]=0xff9000000260ULL;
    beam.packet.header[3]=0x8000000048ULL;
    beam.packet.header[0]=0;
    beam.packet.colors[0] = beam.packet.colors[1] = beam.packet.colors[2] = beam.packet.colors[3] = 0x80808080u;
    for (j = 0; j < 4; j++) {
        beam.packet.uv[j][0] = g_beam_l19_uv_u_table[j * 2];
        beam.packet.uv[j][1] = g_beam_l19_uv_v_table[j * 2];
    }
    FastVecSub(&beam.scratch,moby+0x10,&beam.firstSide);
    beam.packet.vertices[0]=beam.scratch;
    FastVecAdd(&beam.scratch,moby+0x10,&beam.firstSide);
    beam.packet.vertices[1]=beam.scratch;
    FastVecSub(&beam.scratch,&beam.end,&beam.secondSide);
    beam.packet.vertices[2]=beam.scratch;
    FastVecAdd(&beam.scratch,&beam.end,&beam.secondSide);
    beam.packet.vertices[3]=beam.scratch;
    draw_world_quad(&beam.packet,0,0);
}
