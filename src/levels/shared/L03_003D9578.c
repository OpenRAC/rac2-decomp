#include "common.h"
extern void func_00282CC0(void *,void *,void *),func_00282D30(void *,void *,float),func_002A8C00(void *,u8 *,int,void *,float),func_002A7750(u8 *,u8,int),func_L00_003E3258(void *,int,int),func_002A7A00(float *,float,float),func_0029F338(u8 *);
extern int func_002761F8(void *,void *,int,int,void *),func_00282978(void *),func_002A77E0(int);
extern float func_002A7878(float,float);
extern void func_002C65A0(void *,void *,int,int,int,int,int,float,float,float,int);
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern u8 D_L03_001BFDE0[];
/* Moves a fired shot, leaves sparkles behind it, and removes it when it hits something or runs out of time. */
void func_L03_003D9578(u8 *moby) {
 float next[4],matrix[12],pos[4],step[4],particle[4];
 u8 *vars=*(u8 **)(moby+0x68);int i,color;float size;
 switch(moby[0x20]) {
 case 0:
 FastVecAdd(next,moby+0x10,vars);
 if(*(short *)(vars+0x12)<12)(*(short *)(vars+0x12))++;
 make_hit_descriptor(matrix,moby,0x10001,D_L03_001A8F20,(float)*(int *)(vars+0x18));
 if(CollLine(moby+0x10,next,0,*(int *)(vars+0x14),matrix)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;SetMobyState(moby,1,-1);
 SpawnSparkBurstAtPosition(D_L03_001BFDE0,10,1);goto finishmove;
 }
 if(FastDecTimer(vars+0x10)){
 *(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;SetMobyState(moby,1,-1);goto finishmove;
 }
 qcopy(pos,moby+0x10);FastVecScale(step,vars,0.2f);
 for(i=4;i>=0;i--){
 size=RandomFloatRange(0.1f,0.3f);color=RandomIntBelow(255);
 RandomDirectionVector(particle,0.0f,0.1f);FastVecAdd(particle,particle,pos);
 SpawnGravityFadeParticle(particle,D_L03_001A8F20,15,0x808080,color,32,0,size*210000.0f,size*42000.0f,0.0f,0);
 FastVecAdd(pos,pos,step);
 }
 finishmove:
 qcopy(moby+0x10,next);break;
 case 1:
 if(--*(short *)(vars+0x12)==-1)MarkMobySpawned(moby);break;
 }
}
