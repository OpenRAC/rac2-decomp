/* func_PAL_L07_00413B40, the PAL copy of func_L07_0040EC08: the same C, where rename func_L07_0040F0D0 becomes func_PAL_L07_00414008; rename func_L00_002B30E8 becomes func_PAL_L00_002B3000. */
/* func_PAL_L07_00413B40: the five path riders' update (Siberius). A unit of its own for -G8 and
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
extern void func_PAL_L07_00414008(void *);
extern void func_002AFDD8(void *,void *,void *,s32);
extern void func_PAL_L00_002B3000(void);
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
void func_PAL_L07_00413B40(u8 *obj)
{
 f32 oldpos[4],oldrot[4],delta[4],relative[4];
 s32 j,id;
 f32 step,target,speed,bend;
 u8 *child,*state;
 u8 *p=*(u8 **)(obj+0x68),*sound;
 s32 pathid=*(s32 *)(p+0x90);
 s32 *path;
 State *ps=(State *)p;
 D_L07_001ADAAC=0;
 path=D_L07_001FDEC0[pathid];
 target=ps->target;
 speed=ps->speed;
 func_002AA2E8(p+0x11c,target,speed);
 sound=D_00188660+*(s32 *)(p+0x1ac)*0x70;
 if(*(u8 **)(sound+0x88)!=obj || !sound[0x74]) *(s32 *)(p+0x1ac)=func_002E5CF8(2,12,obj);
 id=*(s32 *)(p+0x1ac);
 if(id!=-1) qcopy(D_001886F0+id*0x70,D_L07_001B9200);
 {
 s32 i;
 for(i=0;i<5;i++) {
  child=ps->objects[i];
  state=*(u8 **)(child+0x68);
  qcopy_nc(oldpos,child+0x10);
  qcopy_nc(oldrot,child+0xf0);
  func_002C9828(path,1,child+0x10,child+0xf0,0,ps->pathpos[i]);
  bend=D_L07_001B1708;
  *(f32 *)(child+0x18)+=D_L07_001B1784;
  func_L07_0040EFC8(path,ps->pathpos[i],child+0xf0,bend);
  func_002A0F48(child);
  ps->pathpos[i]+=*(f32 *)(p+0x11c);
  if(ps->pathpos[i]>=(f32)path[0]) ps->pathpos[i]-=(f32)path[0];
  step=D_L07_001B1788*0.0003490659f;
  for(j=0;j<8;j++) *(f32 *)(state+0x15b4+j*0x20)=func_00283B98(*(f32 *)(state+0x15b4+j*0x20),step);
  func_00282CF0(delta,child+0x10,oldpos);
  func_002AD6F0(state+0x20,delta,oldrot,child+0xf0);
  if(D_00189E20.object==child || (*(u8 **)(state+0x108) && D_00189E20.object==*(u8 **)(state+0x108)) || (*(u8 **)(state+0x10c) && D_00189E20.object==*(u8 **)(state+0x10c))) {
   D_L07_001ADAAC=child;
   func_L07_00379180(ps->pathpos[i]);
  }
  func_L00_00426478(child);
  func_L07_0040F760(child);
  func_L07_0040FA90(child,i);
  func_L07_004106B8(child);
  if(*(s16 *)(child+0xaa)==0x11d9 || *(s16 *)(child+0xaa)==0x11db) func_PAL_L07_00414008(child);
  if(D_L07_001ADAAC) {
   func_00282CF0(relative,D_00189E20.pos,D_L07_001ADAAC+0x10);
   func_002AFDD8(D_L07_001ADAAC,relative,relative,0);
   if(relative[2]<-3.0f && D_00189E20.mode==0) func_PAL_L00_002B3000();
  }
  if(D_00189E20.mode==0 && D_00189E20.health<1.0f) func_PAL_L00_002B3000();
 }
}
}
