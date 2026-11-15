#include "common.h"
typedef float Vec[4] __attribute__((aligned(16)));
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct { Vec v[4]; u32 color[4]; float uv[4][2]; u64 regs[4]; } __attribute__((aligned(16))) Packet;
extern int D_L03_001B0C1C __attribute__((sda));
extern float D_L03_001B0C20 __attribute__((sda)),D_L03_001B0C24 __attribute__((sda));
extern float D_L03_001B0C28[] SDATA(D_L03_001B0C28);
extern float D_L03_001B0C2C[] __attribute__((sda));
extern void func_00281DE8(void *,int,int,int);
extern void func_00283658(void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *),func_00282DF0(void *),func_00283248(float,float);
extern int func_00283CF0(float);
extern float func_00283198(float),func_00283180(float),func_002A7878(float,float);
extern void func_00282F20(void *,void *,float),func_00283958(void *,void *);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00283098(void *,void *,void *);
extern void func_00280B90(void *,void *,int);
extern u32 func_00283D38(u32,u32,float);
extern void func_00282D08(void *,void *,void *,float);
/* Draws a curved glowing strip between two points on the puzzle ball, fading from one colour to another. */
void func_L03_003E4148(u8 *moby,u32 startColor,u32 endColor,void *startPoint,void *endPoint,float phase,int innerColor)
{
 Packet packet,innerPacket; Vec matrix[4],axis,step,quat,rotation[3];
 float distance,angle,dt,shrink; int count,i,j,segment;
 InitQuadPacketState(&packet,D_L03_001B0C1C,0,128);
 copy_matrix_rotation(matrix,moby+0xc0);qcopy(matrix[3],moby+0x10);
 FastVecCross(axis,startPoint,endPoint);count=1;distance=FastVecDot(startPoint,endPoint);
 angle=FastVecLength(axis);distance=FastMatrixHelperA(distance,angle);
 {int n=FloatToInt(distance*11.45915412902832f);int z=0;if(n>z)count=n;}
 distance/=count;distance*=0.5f;
 vec_scale_to_length(quat,axis,FastSinOrCosB(distance));quat[3]=FastSinOrCosA(distance);
 quaternion_to_rotation_basis(quat,rotation);vec_scale_to_length(step,axis,D_L03_001B0C20);
 for(i=0;i<4;i++){
  packet.color[i]=startColor;packet.uv[i][0]=D_L03_001B0C28[i*2]+phase;packet.uv[i][1]=D_L03_001B0C2C[i*2];
  vec_scale_to_length(packet.v[i],startPoint,D_L03_001B0C24);
  if(i&1)FastVecAdd(packet.v[i],packet.v[i],step);else FastVecSub(packet.v[i],packet.v[i],step);
  packet.v[i][3]=1.0f;
 }
 matrix_mul_vec3(packet.v[2],packet.v[2],rotation);matrix_mul_vec3(packet.v[3],packet.v[3],rotation);
 phase=0;dt=1.0f/count;
 if(innerColor){innerPacket=packet;{int k;for(k=3;k>=0;k--)innerPacket.color[k]=innerColor;}}
 for(segment=0;segment<count;segment++){
  packet.color[0]=packet.color[1]=FastTweenColor(startColor,endColor,phase);phase+=dt;
  packet.color[2]=packet.color[3]=FastTweenColor(startColor,endColor,phase);
  draw_world_quad(&packet,matrix,0);
  if(innerColor){shrink=RandomFloatRange(0.3f,0.9f);lerp_vector(innerPacket.v[2],packet.v[2],packet.v[3],shrink);lerp_vector(innerPacket.v[3],packet.v[2],packet.v[3],shrink-0.2f);draw_world_quad(&innerPacket,matrix,0);{int k;for(k=0;k<2;k++)qcopy(innerPacket.v[k],innerPacket.v[k+2]);}}
  {Vec *v=packet.v;for(j=3;j>=0;j--){matrix_mul_vec3(*v,*v,rotation);v++;}}
 }
}
