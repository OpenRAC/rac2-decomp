#include "common.h"

extern void func_0029FC20(void *, int, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00281EB8(void *, float, float, float, int, int, int);
extern void func_002A7988(void *, float, float);
extern float func_002A7940(void);
extern int D_L19_001B1C00 __attribute__((sda));
extern int D_L19_001B1BFC __attribute__((sda));
extern float D_L19_001B1C04 __attribute__((sda));

/* Draws the glowing sprites at the tip of the beam and makes the glow grow a little each call. */
void func_L19_00417CA0(char *moby)
{
 char *vars=*(char **)(moby+0x68);
 char mat[0x40] __attribute__((aligned(16)));
 float pos[4] __attribute__((aligned(16)));
 float offset[4] __attribute__((aligned(16)));
 float random[4] __attribute__((aligned(16)));
 float point[4] __attribute__((aligned(16)));
 TransformMobyJointPoint(moby,0,mat);
 qcopy(pos,mat+0x30);
 vec_scale_to_length(offset,mat,0.25f);
 FastVecAdd(pos,pos,offset);
 pos[2]+=1.0f;
 DrawBillboardQuad_00281EB8(pos,D_L19_001B1C04 * *(float *)(vars+0x22C),0.08f,0.0f,D_L19_001B1C00,D_L19_001B1BFC,1);
 DrawBillboardQuad_00281EB8(pos,D_L19_001B1C04 * *(float *)(vars+0x22C)*1.2f,0.08f,0.0f,D_L19_001B1C00,0xFF804020,1);
 *(float *)(vars+0x22C)+=0.12f;
 SpawnRandomDirectionEffect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 DrawBillboardQuad_00281EB8(pos,*(float *)(vars+0x228)*2.0f,0.08f,RandomAngle(),0x31,0x60804020,1);
 DrawBillboardQuad_00281EB8(pos,*(float *)(vars+0x228)*1.5f,0.08f,RandomAngle(),0x31,0x80808080,1);
 SpawnRandomDirectionEffect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 DrawBillboardQuad_00281EB8(point,*(float *)(vars+0x228)*2.0f,0.08f,RandomAngle(),0x31,0x60804020,1);
 DrawBillboardQuad_00281EB8(point,*(float *)(vars+0x228)*1.5f,0.08f,RandomAngle(),0x31,0x80808080,1);
 SpawnRandomDirectionEffect(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 DrawBillboardQuad_00281EB8(point,*(float *)(vars+0x228)*2.0f,0.08f,RandomAngle(),0x31,0x60804020,1);
 DrawBillboardQuad_00281EB8(point,*(float *)(vars+0x228)*1.5f,0.08f,RandomAngle(),0x31,0x80808080,1);
}
