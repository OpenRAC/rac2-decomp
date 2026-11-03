/*
 * Tier: opus-2 (v2175; first reached by opus b1065). Recompiled in v2/c04 as an "-g8.c" unit
 * with -O2 -G8 -ffunction-sections: 952/952 bytes, 0/1 places; exactly one instruction
 * differs: retail 0x0040EF30 is `bnez v0` (non-annulled, `lw fp,0x50(sp)` in the slot),
 * this C gives `bnel v0,zero` with the same slot. Everything else (prologue order, all
 * eight spill slots, the relative-vector setup) matches after relocation normalisation.
 * What fixed the earlier differences:
 * - +0x58 store/load order: the path-speed arguments are struct members read after the
 *   D_L07_001ADAAC store (in-struct loads do not depend on the scalar store).
 * - spill slots: GCSE PRE reaching regs are numbered in hash-bucket order,
 *   (14029 + base regno + offset) mod T; declaring p ninth (regno 93) and the loop counter
 *   in its own block (regno 126) with T = 95 gives retail's slot order.
 * - player fields through `D_00189E20` (boot data, not D_L07_), position as `.pos`.
 * Remaining bnel (reorg.c): flow.c mark_set_1 never kills sets of HARD_FRAME_POINTER ($fp,
 * holding i), so $fp is live at every flow2 block start. reorg fills the first `mode`
 * branch first (fill_eager, pass 1); mark_target_live_regs' find_dead_or_set_registers
 * spends its jump budget (10, 5 per conditional) on the second mode test and the health
 * bc1f before the latch's `lw fp`, so `lw fp` sets a live reg on the opposite thread and the
 * slot is annul-false. Retail behaves as if 0x0040EF4C's slot (non-annulled `lw fp`) were
 * filled first, or as if `lw fp` stood before the first test pre-reorg (fill_simple, then
 * relax_delay_slots redirects past the latch's redundant copy). try_merge_delay_insns cannot
 * un-annul it (the latch label stops it). Tried without effect: nested ifs, a Player
 * pointer, -g, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -frac2-no-null-pointer-checks (all 1 diff), -fno-thread-jumps (2 diffs).
 * Next idea: a source shape that leaves the first mode branch unfilled in reorg pass 1.
 * Declarations needed by this standalone draft follow.
 */
#include "common.h"
extern void func_313DD8(void *,f32,f32);
extern s32 func_355488(s32,s32,void *);
extern void func_338D68(void *,s32,void *,void *,s32,f32);
extern void func_L07_0040EFC8(void *,f32,void *,f32);
extern void func_308EE8(void *);
extern f32 func_2E5318(f32,f32);
extern void func_2E4340(void *,void *,void *);
extern void func_317618(void *,void *,void *,void *);
extern void func_379180(f32);
extern void func_40F6B0(void *);
extern void func_L07_0040F760(void *);
extern void func_L07_0040FA90(void *,s32);
extern void func_L07_004106B8(void *);
extern void func_L07_0040F0D0(void *);
extern void func_31B090(void *,void *,void *,s32);
extern void func_2B1E80(void);
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
void func_L07_0040EC08(u8 *obj)
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
 func_313DD8(p+0x11c,target,speed);
 sound=D_00188660+*(s32 *)(p+0x1ac)*0x70;
 if(*(u8 **)(sound+0x88)!=obj || !sound[0x74]) *(s32 *)(p+0x1ac)=func_355488(2,12,obj);
 id=*(s32 *)(p+0x1ac);
 if(id!=-1) qcopy(D_001886F0+id*0x70,D_L07_001B9200);
 {
 s32 i;
 for(i=0;i<5;i++) {
  child=ps->objects[i];
  state=*(u8 **)(child+0x68);
  qcopy_nc(oldpos,child+0x10);
  qcopy_nc(oldrot,child+0xf0);
  func_338D68(path,1,child+0x10,child+0xf0,0,ps->pathpos[i]);
  bend=D_L07_001B1708;
  *(f32 *)(child+0x18)+=D_L07_001B1784;
  func_L07_0040EFC8(path,ps->pathpos[i],child+0xf0,bend);
  func_308EE8(child);
  ps->pathpos[i]+=*(f32 *)(p+0x11c);
  if(ps->pathpos[i]>=(f32)path[0]) ps->pathpos[i]-=(f32)path[0];
  step=D_L07_001B1788*0.000290888245f;
  for(j=0;j<8;j++) *(f32 *)(state+0x15b4+j*0x20)=func_2E5318(*(f32 *)(state+0x15b4+j*0x20),step);
  func_2E4340(delta,child+0x10,oldpos);
  func_317618(state+0x20,delta,oldrot,child+0xf0);
  if(D_00189E20.object==child || (*(u8 **)(state+0x108) && D_00189E20.object==*(u8 **)(state+0x108)) || (*(u8 **)(state+0x10c) && D_00189E20.object==*(u8 **)(state+0x10c))) {
   D_L07_001ADAAC=child;
   func_379180(ps->pathpos[i]);
  }
  func_40F6B0(child);
  func_L07_0040F760(child);
  func_L07_0040FA90(child,i);
  func_L07_004106B8(child);
  if(*(s16 *)(child+0xaa)==0x11d9 || *(s16 *)(child+0xaa)==0x11db) func_L07_0040F0D0(child);
  if(D_L07_001ADAAC) {
   func_2E4340(relative,D_00189E20.pos,D_L07_001ADAAC+0x10);
   func_31B090(D_L07_001ADAAC,relative,relative,0);
   if(relative[2]<-3.0f && D_00189E20.mode==0) func_2B1E80();
  }
  if(D_00189E20.mode==0 && D_00189E20.health<1.0f) func_2B1E80();
 }
}
}
