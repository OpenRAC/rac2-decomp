#include "names.h"
/* func_L20_0039F560: draws the object's effect. It builds a basis from the object's
 * position, transforms the 290-vertex mesh into D_L20_0023D8D0 and submits it in three
 * overlapping strips, then draws 32 quads whose corners come from D_L20_0029FD60. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { Vector vertex[4]; unsigned int color[4]; float uv[8]; unsigned long long reserved,texture,state,flags; } QuadPacket;
extern int g_electric_ball_texture __attribute__((sda));
extern float g_electric_ball_basis_scale __attribute__((sda));
extern float g_electric_ball_narrow_size __attribute__((sda));
extern float g_electric_ball_wide_ratio __attribute__((sda));
extern int g_electric_ball_alpha __attribute__((sda));
extern Vector g_camera_l20_position;
extern float g_electric_orb_transformed_verts[][3];
extern Vector g_electric_orb_mesh_vertices[];
extern float g_electric_orb_glint_uvs[][2];
extern Vector g_electric_orb_strip_directions[];
extern short g_electric_orb_quad_faces[32][4];
extern unsigned long long GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(unsigned int,unsigned long long);
extern void vec_copy_helper_a(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern int FloatToInt(float);
extern void font_queue_vu_state(void);
extern void transform_vector(void *,void *,void *);
extern void part_draw_glint_effect(int,void *,void *,void *,int);
extern void draw_world_quad(QuadPacket *,void *,int);

/* Draws the glowing ball of the electric orb and the small flares around it. */
void electric_orb_draw_ball(u8 *object)
{
    QuadPacket packet;
    Vector basis[4], up, relative, transformed;
    unsigned int colors[290];
    u8 *state=*(u8 **)(object+0x68);
    short *face;
    float wide,narrow;
    unsigned int rgba;
    int i,j;
    packet.texture=GetEffectTextureDescriptor(g_electric_ball_texture);
    packet.state=0xff9000000260ULL;
    packet.flags=0x8000000044ULL;
    packet.reserved=0;
    VU1_addGSregister(0x47,0x53001);
    vec_copy_helper_a(&up);
    basis[3].q=*(Quadword *)(object+0x10);
    basis[3].f[3]=1.0f;
    FastVecSub(&relative,&g_camera_l20_position,&basis[3]);
    vec_scale_to_length(&basis[0],&relative,1.0f);
    FastVecCross(&basis[1],&basis[0],&up);
    vec_scale_to_length(&basis[1],&basis[1],1.0f);
    FastVecCross(&basis[2],&basis[1],&basis[0]);
    FastVecScale(&basis[0],&basis[0],g_electric_ball_basis_scale);
    FastVecScale(&basis[1],&basis[1],g_electric_ball_basis_scale);
    FastVecScale(&basis[2],&basis[2],g_electric_ball_basis_scale);
    rgba=FloatToInt((float)g_electric_ball_alpha * *(float *)(state+0x14));
    packet.color[0]=packet.color[1]=packet.color[2]=packet.color[3]=(rgba&0xffffff)|*(u32 *)(state+4);
    VU1_addGSregister(6,GetEffectTextureDescriptor(g_electric_ball_texture));
    VU1_addGSregister(0x42,0x8000000044ULL);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xff9000000260ULL);
    VU1_addGSregister(0x4a,0);
    font_queue_vu_state();
    for (j=0;j<290;j++) {
        transform_vector(&transformed,&g_electric_orb_mesh_vertices[j],basis);
        g_electric_orb_transformed_verts[j][0]=transformed.f[0];
        g_electric_orb_transformed_verts[j][1]=transformed.f[1];
        g_electric_orb_transformed_verts[j][2]=transformed.f[2];
        colors[j]=packet.color[0];
    }
    part_draw_glint_effect(148,g_electric_orb_transformed_verts,colors,g_electric_orb_glint_uvs,1);
    part_draw_glint_effect(109,g_electric_orb_transformed_verts[146],colors+146,g_electric_orb_glint_uvs[146],1);
    part_draw_glint_effect(36,g_electric_orb_transformed_verts[254],colors+254,g_electric_orb_glint_uvs[254],1);
    packet.texture=GetEffectTextureDescriptor(11);
    packet.flags=0x8000000048ULL;
    rgba=FloatToInt(*(float *)(state+0x14)*64.0f);
    packet.color[0]=packet.color[1]=(rgba<<24)|*(u32 *)(state+4);
    packet.color[3]=0;packet.color[2]=0;
    wide=g_electric_ball_narrow_size*g_electric_ball_wide_ratio;
    narrow=g_electric_ball_narrow_size;
    for (i=0;i<32;i++) {
        face=g_electric_orb_quad_faces[i];
        for (j=0;j<4;j++,face++) {
            int index=*face;
            if (j>=2) FastVecScale(&packet.vertex[j],&g_electric_orb_strip_directions[index],wide);
            else FastVecScale(&packet.vertex[j],&g_electric_orb_strip_directions[index],narrow);
        }
        packet.uv[0]=0.5f;
        packet.uv[1]=0.5f;
        packet.uv[2]=0.5f;
        packet.uv[3]=0.5f;
        packet.uv[4]=0.5f;
        packet.uv[5]=1.0f;
        packet.uv[6]=0.5f;
        packet.uv[7]=1.0f;
        draw_world_quad(&packet,basis,0);
    }
}
