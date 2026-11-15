/* func_L07_0040EC08: the five path riders' update (Siberius). A unit of its own for -G8 and
 * -frac2-frame-pointer-liveness (config/cflags.txt): without the option flow keeps $fp, which
 * holds the rider index here, live after the loop, and reorg annuls the slot of the first
 * player-mode test (bnel where retail has bne, docs/build/compiler-notes.md). */
#include "common.h"
extern f32 func_002AA2E8(void *,f32,f32);
extern s32 func_002E5CF8(s32,s32,void *);
extern void func_002C9828(void *,s32,void *,void *,s32,f32);
extern void func_L07_0040EFC8(void *,f32,void *,f32);
extern void func_002A0F48(void *);
extern f32 func_00283B98(f32,f32);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
extern void func_L07_00379180(f32);
extern void func_L00_00426478(void *);
extern void func_L07_0040F760(void *);
extern void func_L07_0040FA90(void *,s32);
extern void func_L07_004106B8(void *);
extern void func_L07_0040F0D0(void *);
extern void func_002AFDD8(void *,void *,void *,s32);
extern void func_L00_002B30E8(void);
extern s32 *D_L07_001FDEC0[];
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_00188660[];
extern u8 D_001886F0[];
extern u8 D_L07_001B9200[];
extern f32 D_L07_001B1784 __attribute__((sda));
extern f32 D_L07_001B1788 __attribute__((sda));
extern f32 D_L07_001B1708 __attribute__((sda));
typedef struct {u8 pad[0x80];f32 pos[4];u8 rest[0x31c-0x90];f32 health;u8 pad320[0x33c-0x320];s32 mode;u8 pad340[0x3a0-0x340];u8 *object;} Player;
extern Player D_00189E20;
typedef struct {u8 pad[0xe0];f32 pathpos[5];u8 *objects[5];u8 pad108[0x1a0-0x108];f32 target;f32 speed;} State;
/* Moves the five path riders along their path every frame and updates their sounds and effects. Also handles the player standing on one of them. */
void func_L07_0040EC08(u8 *moby)
{
 f32 oldpos[4],oldrot[4],delta[4],relative[4];
 s32 jointIndex,soundId;
 f32 step,target,speed,bend;
 u8 *child,*state;
 u8 *vars=*(u8 **)(moby+0x68),*sound;
 s32 pathid=*(s32 *)(vars+0x90);
 s32 *path;
 State *pathState=(State *)vars;
 D_L07_001ADAAC=0;
 path=D_L07_001FDEC0[pathid];
 target=pathState->target;
 speed=pathState->speed;
 ApproachValue(vars+0x11c,target,speed);
 sound=gSoundState+*(s32 *)(vars+0x1ac)*0x70;
 if(*(u8 **)(sound+0x88)!=moby || !sound[0x74]) *(s32 *)(vars+0x1ac)=PlayMobySound(2,12,moby);
 soundId=*(s32 *)(vars+0x1ac);
 if(soundId!=-1) qcopy(D_001886F0+soundId*0x70,D_L07_001B9200);
 {
 s32 i;
 for(i=0;i<5;i++) {
  child=pathState->objects[i];
  state=*(u8 **)(child+0x68);
  qcopy_nc(oldpos,child+0x10);
  qcopy_nc(oldrot,child+0xf0);
  SamplePathPosition(path,1,child+0x10,child+0xf0,0,pathState->pathpos[i]);
  bend=D_L07_001B1708;
  *(f32 *)(child+0x18)+=D_L07_001B1784;
  ComputePathHeadingAndTilt(path,pathState->pathpos[i],child+0xf0,bend);
  func_002A0F48(child);
  pathState->pathpos[i]+=*(f32 *)(vars+0x11c);
  if(pathState->pathpos[i]>=(f32)path[0]) pathState->pathpos[i]-=(f32)path[0];
  step=D_L07_001B1788*0.000290888245f;
  for(jointIndex=0;jointIndex<8;jointIndex++) *(f32 *)(state+0x15b4+jointIndex*0x20)=FastAddRotations(*(f32 *)(state+0x15b4+jointIndex*0x20),step);
  FastVecSub(delta,child+0x10,oldpos);
  CombineTransformsAndStore(state+0x20,delta,oldrot,child+0xf0);
  if(gHeroState.object==child || (*(u8 **)(state+0x108) && gHeroState.object==*(u8 **)(state+0x108)) || (*(u8 **)(state+0x10c) && gHeroState.object==*(u8 **)(state+0x10c))) {
   D_L07_001ADAAC=child;
   UpdateSnowEmitterEffect(pathState->pathpos[i]);
  }
  CameraModeNoOp(child);
  UpdateAttachedSwingshotNodes(child);
  UploadPathPointsToWorld(child,i);
  UpdateMobyMatrix(child);
  if(*(s16 *)(child+0xaa)==0x11d9 /* moby class 4569 */ || *(s16 *)(child+0xaa)==0x11db /* moby class 4571 */) UpdateShipAttachedParts(child);
  if(D_L07_001ADAAC) {
   FastVecSub(relative,gHeroState.pos,D_L07_001ADAAC+0x10);
   TransformVectorByObjectOrGiven(D_L07_001ADAAC,relative,relative,0);
   if(relative[2]<-3.0f && gHeroState.mode==0) RecordHeroPlayCounters();
  }
  if(gHeroState.mode==0 && gHeroState.health<1.0f) RecordHeroPlayCounters();
 }
}
}
