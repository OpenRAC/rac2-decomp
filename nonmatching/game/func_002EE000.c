/* Closer C3, 1 November 2026: struct views and inline helpers tie. Measured `float *t2 = temp;` at the top of the arm: an ALU
 * insn in the block moves all six registers to retail's (4 rows left, the extra addiu itself). So the spans model
 * above is right: retail has one more counted insn between the gain and the old angle.
 */
/* GPT-6.1 Sol worker, 28 October 2026: 564/564 bytes, 0/28 places.
 * Current pinned compiler, default -G8 profile. Six instructions differ:
 * f1/f2 are exchanged for the D_001AC244 and object +0x30 expression operands.
 * Three wordings (inline, split locals, precomputed previous product) tie.
 * All other instructions match after relocation. Needs a sibling -g8.c unit;
 * declarations included below. D_001B5390 must be NOT_SDA, or its load is hoisted
 * across the state query and costs another saved register.
 *
 * Opus 5.5 worker (xhigh), 31 October 2026: this C is unchanged and still gives
 * 564/564 bytes, 0/28 places, the same six instructions (+0xF8, +0x10C, +0x120,
 * +0x12C, +0x130, +0x138). Why they differ, from the dumps and a diagnostic:
 * - sched1 orders the block neg, gain, K, old, ... The old angle ranks above the
 *   0.98 and 8.0 loads because the store's anti-dependence gives it two dependents
 *   (rank_for_schedule). {old, old*0.98} and {gain, gain*K} then have equal
 *   QTY_CMP_PRI (4 refs, same span), so local-alloc gives $f1 to the first born.
 * - One more counted insn in that block fixes it. A real integer insn lands right
 *   after K (no hazard, second issue slot), and all six registers become retail's.
 *   Measured with `char *p = owner + 0x1230`; its addiu is the only remaining
 *   difference, so that form is a diagnostic, not a candidate.
 * - So retail seems to have an insn there that local-alloc counts and final does
 *   not emit: a (use reg) from combine's distribute_notes (which also fires when
 *   the search stops at a preceding jump) or a tied no-op move. No C form for it
 *   has been found. sched2 hides the insn, so the output order does not show it.
 * Tried without success: `char *p = o + 0x30` for the later call (gcse cprop, then
 * flow deletes the copy); locals for the gain, 0.98 and the second term. Flags -g,
 * -frac2-qcopy, -fno-force-mem, -fno-sched-interblock, -fno-sched-spec,
 * -fno-rerun-loop-opt, -fno-rerun-cse-after-loop, -fno-regmove, -fno-caller-saves
 * and -fstrict-aliasing keep the six; -ffast-math, -fno-gcse and
 * -fno-expensive-optimizations are worse. do-while(0) loop notes are scheduling
 * barriers: two placements changed the order and added a word, and a barrier after
 * the gain contradicts retail's K timing. A constant set in an earlier block is
 * moved by update_equiv_regs, but the simulated orders do not give retail's (not
 * compiled); the old angle would work there but cannot qualify as a MEM.
 */
#include "common.h"
typedef float Vec000[4] __attribute__((aligned(16)));
extern char *func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern float func_00282E20(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern float func_00283C80(float,float);
extern void func_002A91F0(void *,void *);
extern void func_00283810(void *,void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_00282F20(void *,void *,float);
extern float D_001AC244 __attribute__((sda));
extern char *D_001B5390 NOT_SDA;
void func_002EE000(unsigned char *owner)
{
 char *o=func_002ED688(owner); Vec000 old, temp; float sign,a,b;
 if(!o) return;
 if(func_002EE6A8(owner)!=8 && func_002EE6A8(owner)!=9) {
 qcopy(old,o+0x30);
 a=func_00282E20(o+0x90);
 sign=1.0f;
 *(float *)(o+0x34)=-func_00283248(a,*(float *)(o+0x98));
 *(float *)(o+0x38)=func_00283248(*(float *)(o+0x90),*(float *)(o+0x94));
 if(func_00283BE0(*(float *)(o+0x38),old[2])<0.0f) sign=-1.0f;
 b=func_00283C80(old[2],*(float *)(o+0x38));
 if(func_002EE6A8(owner)!=2 && func_002EE6A8(owner)!=12) {
  *(float *)(o+0x30)=*(float *)(o+0x30)*0.98f + (b * -sign)*(D_001AC244*1.4137166738510132f)*8.0f;
  if(*(float *)(o+0x30)>1.4137166738510132f) *(float *)(o+0x30)=1.4137166738510132f;
  else if(*(float *)(o+0x30)<-1.4137166738510132f) *(float *)(o+0x30)=-1.4137166738510132f;
  func_002A91F0(temp,o+0x30);
  func_00283958(temp,owner+0xC0);
 } else {
  func_002A91F0(temp,o+0x30);
  func_00283810(o+0x40,o+0x40,temp,0.0125f);
  func_00283958(o+0x40,owner+0xC0);
 }
 } else {
  char *p=D_001B5390;
  func_00282F20(owner+0xC0,p+0x10,*(float *)(o+0x140));
  func_00282F20(owner+0xE0,p,-1.0f);
  func_00282F20(owner+0xD0,p+0x20,-1.0f);
 }
}
