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
void func_L03_003E4148(u8 *m,u32 c0,u32 c1,void *a,void *b,float phase,int innerColor)
{
 Packet p,q; Vec matrix[4],axis,step,quat,rotation[3];
 float distance,angle,dt,r; int count,i,j,segment;
 func_00281DE8(&p,D_L03_001B0C1C,0,128);
 func_00283658(matrix,m+0xc0);qcopy(matrix[3],m+0x10);
 func_00282DD8(axis,a,b);count=1;distance=func_00282DB0(a,b);
 angle=func_00282DF0(axis);distance=func_00283248(distance,angle);
 {int n=func_00283CF0(distance*11.45915412902832f);int z=0;if(n>z)count=n;}
 distance/=count;distance*=0.5f;
 func_00282F20(quat,axis,func_00283198(distance));quat[3]=func_00283180(distance);
 func_00283958(quat,rotation);func_00282F20(step,axis,D_L03_001B0C20);
 for(i=0;i<4;i++){
  p.color[i]=c0;p.uv[i][0]=D_L03_001B0C28[i*2]+phase;p.uv[i][1]=D_L03_001B0C2C[i*2];
  func_00282F20(p.v[i],a,D_L03_001B0C24);
  if(i&1)func_00282CC0(p.v[i],p.v[i],step);else func_00282CF0(p.v[i],p.v[i],step);
  p.v[i][3]=1.0f;
 }
 func_00283098(p.v[2],p.v[2],rotation);func_00283098(p.v[3],p.v[3],rotation);
 phase=0;dt=1.0f/count;
 if(innerColor){q=p;{int k;for(k=3;k>=0;k--)q.color[k]=innerColor;}}
 for(segment=0;segment<count;segment++){
  p.color[0]=p.color[1]=func_00283D38(c0,c1,phase);phase+=dt;
  p.color[2]=p.color[3]=func_00283D38(c0,c1,phase);
  func_00280B90(&p,matrix,0);
  if(innerColor){r=func_002A7878(0.3f,0.9f);func_00282D08(q.v[2],p.v[2],p.v[3],r);func_00282D08(q.v[3],p.v[2],p.v[3],r-0.2f);func_00280B90(&q,matrix,0);{int k;for(k=0;k<2;k++)qcopy(q.v[k],q.v[k+2]);}}
  {Vec *v=p.v;for(j=3;j>=0;j--){func_00283098(*v,*v,rotation);v++;}}
 }
}
