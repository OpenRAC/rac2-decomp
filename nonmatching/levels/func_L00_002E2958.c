/* 6 November 2026 (round 10): retail survey of the exempted roles shows the rule is too
 * wide. No-nop witnesses are all at function entry (cleared history: f_002EF240 in 28
 * level programs, boot f_00283CE0, handwritten boot f_00129218/2C0/368); the only built
 * beneficiary is func_00283CE0 (own section). After a gas-filled branch slot the same
 * roles keep the nop (this site, 27 programs). A rule that exempts only when both
 * history slots were already dummy before the mtc1 fits every site. Any C giving
 * retail's bytes gives gas the same history, so no C or flag change can add the nop.
 */
/* 6 November 2026: own unit with -frac2-keep-block-order -frac2-hazard-labels does not
 * add the missing nop: the gap is gas's mtc1 a0->f0 / cvt.s.w exemption
 * (tools/compiler/transformers/restrict_mtc1_exemption.py), a toolchain question, not C.
 */
/* Tier: opus-1 (v1494). USA v1.01 game compiler, own unit with
 * -O2 -G0 -ffunction-sections -frac2-keep-block-order (needed: without it the
 * prologue and dispatch order change).
 * Best check.py: 608/608 bytes, 0/27 places. Every instruction agrees except ONE:
 * retail has a hazard nop between `mtc1 a0,f0` and `cvt.s.w f0,f0` at +0x104
 * (L00 0x002E2A58/5C, the first instruction after the case-0 `beqz v0` whose delay
 * slot gas fills with a nop). This toolchain's reconstructed transfer-delay rule
 * (u4_mtc1_helper.py + restrict_mtc1_exemption.py: prev insn mtc1 $4->$f0,
 * prev-prev insn the dummy left by a gas-filled branch slot, reader cvt.s.w f0,f0)
 * omits that nop, so ours is one word short there and the aligned case-1/2 loop head
 * then takes a pad nop at +0x194 instead; past that point the bytes agree again.
 * No C wording can change it: the slot must stay a nop and mtc1 a0,f0 must follow,
 * so gas sees exactly the exempted history. Retail is a counterexample to the
 * exemption (docs/COMPILER-NOTES.md "Transfer hazards": 4 of 8 first-transfer
 * witnesses need the nop). It matches if the assembler emits that nop.
 * What fixed the rest (vs the 604-byte sol-high draft): a separate counter for the
 * case-1/2 loop (sharing `i` with the case-0 loop made it cross a call, so sched1
 * hoisted the `i = next` copy above func_L00_002E2C30 and the counter took s0) and an
 * explicit `next = j + 1` that crosses the call while `j` stays in a1; that also put
 * the cached high half/state base in a2/a3 and the upload arguments in retail order.
 * Declarations needed are below (catalogue names of the boot helpers placed in
 * every level: func_0027C540, func_002FCB00, func_0027C660, func_00283CF0,
 * func_0027DDC0).
 */
#include "common.h"

typedef struct { int key, base, a08, a0c, width, top, mode, count, step, duration; } DrawRec_2958;
typedef struct { int buffers[7]; short buffer, pad1e, index, pad22, active; short pad26; int timer; char pad2c[0x36c-0x2c]; int delay, fade; char pad374[0x384-0x374]; int style; } DrawState_2958;
extern DrawState_2958 D_L00_001BC200;
extern DrawRec_2958 D_L00_001BC588[];
extern void func_0027C540(int);
/* The upload helper (src/game/002FC8D0.c) returns a packed 64-bit texture descriptor. */
extern long long func_002FCB00(int,int,int,int);
extern int D_001A72DC __attribute__((section(".sdata")));
extern float D_001B18E0 __attribute__((section(".sdata")));
extern void func_L00_002E2C30(int,float);
extern void func_L00_002E3340(int,float);
extern void func_L00_002E3520(void);
extern void func_0027C660(void);
extern int func_00283CF0(float);
extern void func_0027DDC0(int,int,int,int);
void func_L00_002E2958(void) {
 int i; float alpha;
 if(D_L00_001BC200.active) {
  func_0027C540(0);
  func_002FCB00((int)((char *)D_L00_001BC200.buffers[(short)(D_L00_001BC200.buffer^1)]+16),D_001A72DC,512,416);
  func_L00_002E3520();
  switch(D_L00_001BC588[D_L00_001BC200.index].mode) {
  case 0:
   for(i=0;i<D_L00_001BC588[D_L00_001BC200.index].count;i++) {
    if(D_L00_001BC588[D_L00_001BC200.index].duration<D_L00_001BC200.timer*2)
     alpha=(1.0f-(float)D_L00_001BC200.timer/(float)D_L00_001BC588[D_L00_001BC200.index].duration)*2.0f;
    else alpha=1.0f;
    func_L00_002E3340(i,alpha);
   }
   break;
  case 1: case 2:
   {
   int j=0;
   if(j<D_L00_001BC588[D_L00_001BC200.index].count) do {
    int next=j+1;
    func_L00_002E2C30(j,1.0f-((float)D_L00_001BC200.timer-(float)(D_L00_001BC588[D_L00_001BC200.index].count-next)*(float)D_L00_001BC200.delay)/(float)D_L00_001BC200.fade);
    j=next;
   } while(j<D_L00_001BC588[D_L00_001BC200.index].count);
   }
   break;
  }
  func_0027C660();
 }
 func_0027DDC0(0,0,0,func_00283CF0(D_001B18E0*128.0f));
}
