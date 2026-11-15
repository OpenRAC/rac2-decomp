/* Its own unit: the branch to the hazard nop at the end needs -frac2-hazard-labels. */
#include "common.h"
typedef union { struct { float x,y,z,w; } v; unsigned int quad __attribute__((mode(TI))); } V1078;
typedef struct { unsigned char b[8]; } P1078;
extern const P1078 D_L11_001B2930, D_L11_001B2938;
extern const V1078 D_L11_001B2940[2];
extern void func_L11_004701A0(char *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern void func_00282D30(void *, void *, float);
extern int func_L00_0033E220(void *, void *, int, float, int, int, float, int, int, int);
extern float func_002A7878(float,float);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002A7750(void *,int,int);
extern void func_L00_002E6EF8(void (*)(char *),void *);
extern void func_L00_00324F18(void *,void *,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern float func_00283248(float,float);
extern float func_00282E80(void *,void *);
extern float func_00283BE0(float,float);
extern float func_002A78D8(float,float);
extern float func_00282E48(void *,void *);
extern int func_002A9640(void *,int,int);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_L00_002EC248(void *,void *,float,void *,float,int,int,float,float,float);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002B9180(int);
extern char *func_L00_00326620(void *,int,int);
extern int func_00282948(void *);
extern void func_00283098(void *,void *,void *);
extern int func_002A7820(int,int);
extern void func_00282F20(void *,void *,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_002A7A00(void *,float,float);
/* Updates an orb with sparks circling it (moby classes 4330 and 4492): when it is hit it bursts with a sound and the sparks drift away and fade. */
void func_L11_0046F8F0(char *moby) {
 P1078 tableA = D_L11_001B2930, tableB = D_L11_001B2938;
 V1078 bounds[2], small, offset;
 V1078 temp, center, v, axis;
 char *vars=*(char **)(moby+0x68);
 int sound=0x10eb;
 float height=18;
 int none=-1;
 bounds[0].quad=D_L11_001B2940[0].quad; bounds[1].quad=D_L11_001B2940[1].quad;
 small.quad=0;small.v.z=0.1166666746f;
 if(H(moby,0xaa)==0x118c /* moby class 4492 */) {height=21;sound=0x118d;}
 offset.quad=0;offset.v.z=height;
 switch(B(moby,0x20)) {
 case 0: {
 int i;
 float a,b,c;
 F(vars,0x18)=1;
 if(I(vars,0x10)>8) I(vars,0x10)=8;
 FastVecScale(&offset,&offset,F(moby,0x2c));
 I(vars,4)=SpawnObjectFollowingEffect(&offset,moby,0x1fffffff,315000.0f,-1,0,0.0f,-1,0,-1);
 I(vars,8)=SpawnObjectFollowingEffect(&offset,moby,0x3f106060,315000.0f,-1,1,0.0f,-1,0,-1);
 for(i=0;i<I(vars,0x10);i++) {
 V1078 *point=(V1078 *)(vars+0x20+i*16);
 a=RandomFloatRange(0.75f,1.25f); b=RandomAngle(); c=RandomAngle();
 BuildSphericalOffset(point,a,b,c); FastVecAdd(point,moby+0x10,point);
 }
 SetMobyState(moby,1,-1); break;
 }
 case 1: {
 int i;
 float a,b,c,r;
 AddDrawCallbackToList3(DrawOrbitingSparks,moby);
 LocalOffsetToWorld(moby,&center,0,0,height);
 for(i=0;i<I(vars,0x10);i++) {
 V1078 *point=(V1078 *)(vars+0x20+i*16);
 FastVecSub(&temp,moby+0x10,point);
 a=FastMatrixHelperA(point->v.x-center.v.x,point->v.y-center.v.y);
 r=vec_distance_xy(&center,point);
 b=FastMatrixHelperA(r,point->v.z-center.v.z);
 a=fast_subtract_rotations(a,0.0523598827f);
 c=RandomSignedFloatRange(1,3);
 b=fast_subtract_rotations(b,c*0.0174532942f);
 if(b>1.1f)b=1.1f; if(b< -1.1f)b= -1.1f;
 r=fast_vec_dist(&center,point);
 r+=RandomSignedFloatRange(0.0166666675f,0.0166666675f);
 if(r>1.05f)r=1.05f;if(r<0.75f)r=0.75f;
 BuildSphericalOffset(point,r,a,b); FastVecAdd(point,&center,point);
 }
 if(FindOwnedEffectSlot(moby,0x04010000,0) && !I(vars,0)) {
 SetMobyState(moby,2,-1);
 } B(moby,0xa8)=255; break;
 }
 case 2:
 ExplodeObjectIntoPieces(moby,bounds,&tableB,&tableA,65535,0,-1,0,65535,255,0);
 SpawnSparkBurst_L00(moby,&offset,0.1f,&small,0.15f,80,3,1,20,1);
 temp.quad=0;
 LocalOffsetToWorld(moby,&offset,0,0,18);
 SpawnExplosionEffects(moby,&temp,&offset,0,0,10,3,5,0,1,9,0.5f,-1,0,0,0,none,0,0x810001);
 KillParticle(I(vars,4));KillParticle(I(vars,8));SpawnChildMoby_L00(moby,sound,0);
 *(unsigned short *)(moby+0x34)|=1;I(moby,0x98)=0;B(moby,0x31)=0;
 I(vars,0xc)=120; I(vars,0x14)=600;SetMobyState(moby,3,-1);break;
 case 3: {
 int i,n;
 float a;
 if(FastFloatHelperD(vars+0xc) || I(vars,0xc)>=91) {
 temp.quad=0;temp.v.x=0.033333335f;temp.v.z=0.033333335f;
 matrix_mul_vec3(&temp,&temp,moby+0xc0);
 a=19; if(H(moby,0xaa)==0x10ea /* moby class 4330 */) a=17; offset.v.z=a;
 SpawnSparkBurst_L00(moby,&offset,0,&temp,0.033333335f,RandomIntRange(3,6),0,0.5f,15,1);
 temp.v.x=-0.033333335f;temp.v.z=0.04000000283122063f;
 matrix_mul_vec3(&temp,&temp,moby+0xc0);
 SpawnSparkBurst_L00(moby,&offset,0,&temp,0.033333335f,RandomIntRange(3,6),1,0.5f,15,1);
 I(vars,0xc)=RandomIntRange(45,90);
 }
 LocalOffsetToWorld(moby,&v,0,0,18);
 if(!FastFloatHelperD(vars+0x14)) {
 AddDrawCallbackToList3(DrawOrbitingSparks,moby);
 for(i=0;i<I(vars,0x10);i++) {
 V1078 *point=(V1078 *)(vars+0x20+i*16);
 FastVecSub(&temp,point,moby+0x10);temp.v.z=0;
 vec_scale_to_length(&temp,&temp,1);
 axis.quad=0;axis.v.z=1;
 ApplyAxisRotationToQuaternion(&center,&temp,&axis,(float)I(vars,0x14)*-0.002617994323372841f);
 RandomDirectionVector(&temp,1,1);
 a=RandomFloatRange(-0.25f,0.75f); center.v.z+=a;
 FastVecAdd(&center,&temp,&center);
 a=RandomFloatRange(0.0166666675f,0.0166666675f);
 vec_scale_to_length(&center,&center,a+a);FastVecAdd(point,&center,point);
 }
 }
 if(I(vars,0x14)<60) F(vars,0x18)=(float)I(vars,0x14)*0.0166666675f;
 break;
 }
 }
}
