/* 6 November 2026: current game compiler, isolated -O2 -G8 -ffunction-sections
 * unit: 952/952 bytes, 0/1 in each USA release; no canonical PAL identity.
 * Tested 23 candidate compiler flags and 12 syntactic groupings around mode/health
 * checks: all retain the single bnel/bnez difference at +0x328.
 * Root cause verified in GCC 2.95 source (resource.c:find_dead_or_set_registers):
 * on Branch 1's fallthrough path, conditional Branch 2 (+5) and Branch 3 (+5)
 * hit jump_count >= 10, aborting before reaching the latch lw fp (insn 573).
 * Because flow.c:mark_set_1 never kills HARD_FRAME_POINTER ($fp), fp remains live
 * in opposite_needed, forcing must_annul=1 (bnel). Retained C below is unchanged.
 * 6 November 2026, round 9: env-gated probes, forced on in all 8511 game units.
 * A, resource.c jump limit 10 -> 11/15/16/20: target matches (1/1); 367 units change at 11,
 * 560 at 20; sampled matched functions regress (4/4, e.g. func_L00_00308538 27 -> 0 places).
 * B, flow.c mark_set_1 kills $fp after reload when !frame_pointer_needed (also with $fp not
 * live at function end): target still 1 diff; 0 units change. Both hypotheses falsified.
 * 6 November 2026, round 11: 11 more shapes, all still the one bnel at +0x328: separate ifs,
 * `if(mode!=0) continue;`, nested `if(mode==0) if(health<1)`, `{ f(); continue; }`, a
 * continue inside the relative test, and do/while/for(;;) loop forms. Why no C shape helps:
 * the pre-reorg tail RTL is the same for all of them (all three branches target the latch
 * label, no BARRIER before it, so mark_target_live_regs starts at block 0 and fp is never
 * REG_DEAD). fp leaves opposite_needed only if branch 2 is already a SEQUENCE with its
 * non-annulled `lw fp` when branch 1 is filled (mark_set_resources then sees the slot set
 * before the budget ends). fill_eager walks branches in insn order and branch 1 always fills
 * in pass 1 from the latch thread, so retail needs branch 1 unfilled in pass 1 (for example a
 * pre-reorg jump-to-jump target that relax_delay_slots threads). -fno-thread-jumps keeps
 * bnez but takes `lui a0` from the unthreaded target (1 diff at +0x32c).
 */
/* 6 November 2026: current game compiler, isolated -O2 -G8 -ffunction-sections
 * unit: 952/952 bytes, 0/1 in each USA release; no canonical PAL identity.
 * Tested 23 candidate compiler flags and 12 syntactic groupings around mode/health
 * checks: all retain the single bnel/bnez difference at +0x328.
 * Root cause verified in GCC 2.95 source (resource.c:find_dead_or_set_registers):
 * on Branch 1's fallthrough path, conditional Branch 2 (+5) and Branch 3 (+5)
 * hit jump_count >= 10, aborting before reaching the latch lw fp (insn 573).
 * Because flow.c:mark_set_1 never kills HARD_FRAME_POINTER ($fp), fp remains live
 * in opposite_needed, forcing must_annul=1 (bnel). Retained C below is unchanged.
 * 6 November 2026, round 9: env-gated probes, forced on in all 8511 game units.
 * A, resource.c jump limit 10 -> 11/15/16/20: target matches (1/1); 367 units change at 11,
 * 560 at 20; sampled matched functions regress (4/4, e.g. func_L00_00308538 27 -> 0 places).
 * B, flow.c mark_set_1 kills $fp after reload when !frame_pointer_needed (also with $fp not
 * live at function end): target still 1 diff; 0 units change. Both hypotheses falsified.
 */
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
