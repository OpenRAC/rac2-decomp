#include "common.h"

extern void moby_transform_joint_point(void *, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_draw_billboard_quad(void *, float, float, float, int, int, int);
extern void part_spawn_random_direction_effect(void *, float, float);
extern float math_random_angle(void);
extern int D_L19_001B1C00 __attribute__((sda));
extern int D_L19_001B1BFC __attribute__((sda));
extern float D_L19_001B1C04 __attribute__((sda));

/* Draws the glowing sprites at the tip of the beam and makes the glow grow a little each call. */
void part_emit_beam_muzzle_glow(char *moby)
{
 char *vars=*(char **)(moby+0x68);
 char mat[0x40] __attribute__((aligned(16)));
 float pos[4] __attribute__((aligned(16)));
 float offset[4] __attribute__((aligned(16)));
 float random[4] __attribute__((aligned(16)));
 float point[4] __attribute__((aligned(16)));
 moby_transform_joint_point(moby,0,mat);
 qcopy(pos,mat+0x30);
 vec_scale_to_length(offset,mat,0.25f);
 FastVecAdd(pos,pos,offset);
 pos[2]+=1.0f;
 gfx_draw_billboard_quad(pos,D_L19_001B1C04 * *(float *)(vars+0x22C),0.08f,0.0f,D_L19_001B1C00,D_L19_001B1BFC,1);
 gfx_draw_billboard_quad(pos,D_L19_001B1C04 * *(float *)(vars+0x22C)*1.2f,0.08f,0.0f,D_L19_001B1C00,0xFF804020,1);
 *(float *)(vars+0x22C)+=0.12f;
 part_spawn_random_direction_effect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 gfx_draw_billboard_quad(pos,*(float *)(vars+0x228)*2.0f,0.08f,math_random_angle(),0x31,0x60804020,1);
 gfx_draw_billboard_quad(pos,*(float *)(vars+0x228)*1.5f,0.08f,math_random_angle(),0x31,0x80808080,1);
 part_spawn_random_direction_effect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 gfx_draw_billboard_quad(point,*(float *)(vars+0x228)*2.0f,0.08f,math_random_angle(),0x31,0x60804020,1);
 gfx_draw_billboard_quad(point,*(float *)(vars+0x228)*1.5f,0.08f,math_random_angle(),0x31,0x80808080,1);
 part_spawn_random_direction_effect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 gfx_draw_billboard_quad(point,*(float *)(vars+0x228)*2.0f,0.08f,math_random_angle(),0x31,0x60804020,1);
 gfx_draw_billboard_quad(point,*(float *)(vars+0x228)*1.5f,0.08f,math_random_angle(),0x31,0x80808080,1);
}
