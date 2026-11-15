#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float,float);
extern char *func_0035CBA0(char *,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00350388(char *);
extern void func_L00_00326110(char *,float,int);
extern void func_L01_0031A278(char *,float,float,float,void *);
extern void func_002A0F48(char *);
extern float func_002A96A0(char *,char *);
extern void func_002AB800(char *,void *);
extern void func_002AB8C0(char *,void *);
extern int func_002B3868(char *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int func_003A0948(int,int,char *);
extern float func_00283B98(float,float);
extern int func_002A8C28(char *,void *,float,float,float,int,int,int,int);
extern void func_002B0A68(char *,int,void *,int,float,float,float,float);
extern void func_L06_00464F40(char *);
extern int D_0018C0B4 __attribute__((nosda));
extern float D_L06_001B1D70 __attribute__((sda));
extern float D_L06_001B1D70_4[] MACRO_ADDR;
extern struct { char pad[0x160]; float f160; int pad164, n168, n16c; char pad170[16]; float f180; int pad184,n188; } D_L06_001B9700 __attribute__((nosda));
/* The two height tests read their own values: with -frac2-gcse-unsplit-edges gcse leaves both
   loads in place, and reorg skips the second ground load on the first test's failure edge. */
/* Updates a Notak breakable machine: it takes damage until its health runs out, tips over with smoke and sparks, then falls and crashes. */
void func_L06_004649F0(char *moby) {
 float pos[4],vel[4];
 char *vars=*(char **)(moby+0x68);
 float damage,frac;
 int i;
 switch(*(unsigned char *)(moby+0x20)) {
 case 0:
 *(short *)(vars+0x24)=6; *(float *)(vars+0x20)=6; *(int *)(vars+0x80)=0;
 *(Quad *)vel=0; vel[0]=0.06666667f; vel[2]=RandomFloatRange(6,9)*0.0166666675f;
 *(Quad *)pos=*(Quad *)vel;
 func_002A0F48(moby);
 matrix_mul_vec3(vars+0x70,pos,moby+0xC0);
 SetMobyState(moby,1,-1); break;
 case 1:
 damage=UpdateAimTargetStrength(moby,func_0035CBA0(moby,0x230000,0));
 if(damage>0) {
 ((unsigned char *)vars)[0x57]=255; ((unsigned char *)vars)[0x58]=128; ((unsigned char *)vars)[0x59]=128;
 StartColorFade(moby,vars+0x50);
 *(float *)(vars+0x20)-=damage;
 }
 if(*(float *)(vars+0x20)<0) SetMobyState(moby,2,-1);
 UpdateColorFade(moby,vars+0x50); ((unsigned char *)moby)[0xA8]=255; break;
 case 2:
 if(SetFirstPendingFlag(moby)) {
 SpawnExplosion(moby+0x10,1,25,20,20,20,45,1,1,20,1,1,0,0);
 func_003A0948(1,0,moby);
 }
 UpdateColorFade(moby,vars+0x50);
 *(float *)(vars+0x68)+=0.000290888245f;
 *(float *)(moby+0xF4)=FastAddRotations(*(float *)(moby+0xF4),*(float *)(vars+0x68));
 if(*(float *)(moby+0xF4)>0.628318548f && D_0018C0B4!=140) {
 *(int *)(moby+0x98)=0;
 for(i=0;i<6;i++) {
 frac=i*0.2f;
 ComputeMobyLocalPoint(moby,frac*1.5f+(-0.5f),0,frac*7+2,pos);
 SweepCollisionFromObject(moby,pos,0.8f,4,1,0x30009,0,1,0);
 }
 ComputeMobyLocalPoint(moby,D_L06_001B1D70,D_L06_001B1D70_4[1],D_L06_001B1D70_4[2],pos);
 SweepCollisionFromObject(moby,pos,2.5f,4,1,0x4030000,0,1,0);
 }
 if(*(float *)(moby+0xF4)>1.2566371f) SetMobyState(moby,3,-1);
 break;
 case 3:
 if(SetFirstPendingFlag(moby)) {
 *(Quad *)pos=0; pos[2]=0.06666667f;
 SpawnDebrisForMaskedParts(moby,0x6FF,pos,255,3,6,3,7);
 func_003A0948(0,0,moby);
 SpawnScaledBolts(moby,0,9);
 gCameraState_L06.f180=0.1f;
 gCameraState_L06.n188=90;
 gCameraState_L06.f160=0.2f;
 gCameraState_L06.n168=60;
 gCameraState_L06.n16c=0;
 *(unsigned short *)(moby+0x7C)=0x8100;
 matrix_mul_vec3(vel,&D_L06_001B1D70,moby+0xC0);
 FastVecAdd(moby+0x10,moby+0x10,vel);
 }
 SweepCollisionFromObject(moby,moby+0x10,2.5f,4,1,0x4030000,0,1,0);
 FastVecAdd(moby+0x10,moby+0x10,vars+0x70);
 *(float *)(vars+0x78)-=0.003f;
 if (!*(int *)(vars+0x80) && *(float *)(moby+0x18) < *(float *)(vars+0x6C)) {
     SpawnCrashDebrisBurst(moby);
     *(int *)(vars+0x80)=1;
 } else if (*(float *)(moby+0x18) < *(float *)(vars+0x6C)-4.0f)
     func_00350388(moby);
 break;
 }
}
