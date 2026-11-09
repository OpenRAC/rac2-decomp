/* 9 November 2026 (o84, dump-driven, local-alloc for the first-coordinate FPRs): insn `f13 = ysum + p[1]` gives BOTH inputs a qty_phys_sugg of f13 (combine_regs with a hard output never ties), so the higher QTY_CMP_PRI wins f13. p[1] (reg 122): 2 refs over 2 insns = 0.5. With `ys*(float)row + yb` (retail's operand order: mul.s f13,f13,f22; add.s f13,f13,f2) ys/ys*row/sum tie into one qty of 6 refs, pri 12/life; it wins only if life <= 12 insns (tie goes to the lower qty), i.e. ys loaded at sched1 position >= 4. sched1 gives plain float loads prio 28 vs 27 for the int->float loads (90/93 vs 83/87), so ys is always issued 1st or 2nd (chain life 16 -> 0.375): all 24 declaration orders with the tied form keep p[1] in f13. Retail's ys-last order needs ys's sched1 priority below 27; no C found. Body C unchanged (14 rows). */
/* 9 November 2026 (o38, PRE slot order): partly PRE. Spilled PRE copies 372..385 (S=163, max_cuid 324-327) give slots o+0x258, o+0x3b4, o+0x98, row+1, o+0x2a0, o+0x210, o+0x17c, o+0xe4. Retail's first six are bucket order with row+1 after o+0x2a0 (row reg 104..121 at S=163, or reg 86 at S=169/171/173 = max_cuid 336-347). o+0x258/o+0x3b4 last fits no S and no base reg 81-99 (exhaustive, S 51-799): retail gave them hard regs in global and reload evicted them (slots after all alter_reg slots). Not fixable by bucket order alone. */
/* 9 November 2026 (Sonnet round 3, lesson 42/49 sweeps): no gain. Exact-row measure (slot offsets counted) 33; post-loop locals in slot order (o+0x258, o+0x210, o+0x17c, o+0x2a0) 29 exact but 29 slot-blind (worse than 14); `ids=(short*)ref+3; id=ids+(row<<2)*5` gives the separate la then +6 form but 17 slot-blind rows and moves spill slots; operand order of the first coordinate y (P1+(yb+ys*row)) 17 vs 18; all 24 float-local declaration orders and expression/local masks of xb,yb,xs,ys: no change in FPR numbers (load order is yb,ys,xb,xs against retail yb,xs,xb,ys). Body C unchanged (14 rows). */
/* 8 November 2026 (Sonnet round 2, lesson 49): fake locals removed/reshaped: `ids` is now the plain array cast with +3 shorts (row base la + 6 no longer folds: 35 -> 16 differing rows, same 1452 bytes), `record` inlined, first-y written yb + ys*row (14 rows). Not helpful: the xb/yb/xs/ys scalars as expressions (31), base/stride pair copies as expressions (128-243), currentSlots/currentWeapons removed (110). Permuter (1500 s, -j2) best 420 vs base 435, only the yb+ys*row swap above. Left: eight spill-slot offsets, la/+6 form (retail la a3 then addiu 6 separate), first-coordinate FPR numbers. Profile: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_0026F7A0 is declared int(void *) but src/game/0026EA00.c is unsigned int(void). Unsigned return: 39 -> 39 rows. Calling it with no argument (as src declares) gives 106 rows: retail loads the argument, so the src definition is incomplete rather than this note being wrong. */
/* 8 November 2026 (Sonnet round): rewrite from the note C with -fno-rerun-loop-opt (own cflags line, removed) re-measured 1452/1452, 35 real differing rows, all spill-slot order plus first-coordinate FPR numbers; 1 permuter run (1500 s, -j2) best score 390 vs 435 but 1448 bytes (worse), nothing adopted. */
/* 8 November 2026 re-measure on master's compiler; retained near miss, not linked.
 * USA v1.01: unchanged, 1452/1452 bytes, 0/28 places, first difference +0x4c, same rows.
 * New finding: the spill-slot order is gcse's PRE reaching-reg order, which is
 * hash-bucket order ((14029 + regno + const) mod 163 for o+K; o is reg 84).
 * Retail's slots (o+0x98, o+0x2a0, row+1, o+0x210, o+0x17c, o+0xe4, o+0x258,
 * o+0x3b4) need the row counter's pseudo at 104..121, so row+1 lands after
 * o+0x2a0. Declaring the per-cell scalars (colour pointers, layout floats,
 * table pointers, four pos pointers) at the top of the if-block, row and col
 * last, gives row reg 104 and retail's order for the first six with the code
 * unchanged. o+0x258 and o+0x3b4 still come first: no odd bucket count with
 * o = reg 84 puts them last, so retail must give them slots later (reload
 * spill or caller-save area). Row address: retail is la sym then +6; every
 * index form tried here (row<<2, row*4, row*4+col, plain ids) folds sym+6
 * into the HIGH/LO_SUM. Not improved overall, so the C below is kept.
 * Round 2 (same day, func_00281A08 named-local idiom): plain locals take spill
 * slots in declaration order ahead of PRE registers. Post-loop locals (o+0x2a0,
 * next = row + 1, o+0x210, o+0x17c, o+0xe4) with loop expressions kept: 1452
 * bytes, slots in declaration order, but retail's colour constant and the two
 * o+0x98 copies sit between row and o+0x2a0, so they must be locals too; any
 * local used inside the loop (colour, o+0x98, o+0x3b4) takes a callee-saved
 * register and shrinks the body to 1436/1444. o+0x258/o+0x3b4 last fits PRE.
 */
/* 6 November 2026 follow-up; retained near miss, not linked.
 * USA v1.01: 1452/1452 bytes, 0/28 places, first difference +0x4c.
 * Profile: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt.
 * 39 real differing instruction rows in the boot, versus 82 for the previous
 * retained C/profile; relocation immediate fields are excluded from that count.
 * Disabling the second loop pass fixes the owned-weapon table setup, final
 * ammo lookup (including mult/addu instead of mtlo/madd), branch delay slots,
 * final layout-record copies and the row-loop tail register. Writing bar
 * coordinates as stride*index+base fixes six operand-register differences.
 * Separate first-coordinate scalar reads improve one further instruction.
 * Remaining: pointer spill slots, row table-address formation/scheduling and
 * first-coordinate FPR allocation. The bar coordinate block now agrees.
 * New controls: independent first-coordinate scalar-load permutations;
 * explicit owner-relative pointer locals (all together and individually);
 * table-base groups and record/halfword row views; explicit next-row and
 * do-loop forms; meaningful coordinate groups; owner/FP argument interleaving;
 * scheduling/CSE/loop flags. None beats this candidate. Groups shorten the
 * body, explicit background/frame locals give 1444 bytes, and owner/FP
 * interleavings tie. No dead stores, wrappers or extra memory reads were added.
 * No linked build run. Earlier measurements below are historical.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1452/1452 bytes, 0/28 placements; first difference 0x4c.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* sol-high, USA v1.01, game -O2 -G8 -ffunction-sections.
 * Best: 1452/1452 bytes, 0/28 places; first mismatch +0x4C.
 * Retail 0xE0 frame and saved-register assignments are reproduced. Explicit
 * branch-local weapon/slot table bases recover s4/s5/s6 and spill the shared
 * colour constant, matching most of the central call sequence. Inline position
 * reads reproduce the short-lived pointer allocation. Reading the four layout
 * scalars before the first colour store reproduces its instruction scheduling.
 * Remaining: pointer spill slots, row address formation, first coordinate FPR
 * coalescing, operand registers in bar positioning, and branch-edge address setup.
 * A separate final table lookup preserves retail's rematerialisation boundary;
 * retaining the first table locals there instead shrinks the body to 1436 bytes.
 * -G0, -fno-strength-reduce and -mno-split-addresses did not improve the result.
 * No linked validation. All needed declarations follow; compile in a G8 unit.
 */
#include "include_asm.h"
extern void func_00335E68(void *,int);
extern int func_00335E20(void *);
extern void func_00335E38(void *,float,float,float,float);
extern void func_00336320(void *),func_00336A78(void *),func_00336828(void *);
extern void func_00336920(void *,int,int);
typedef struct {int x,y;} MenuIntegerPair;
typedef struct {short a,b,c,id,e;} MenuGridEntry;
extern MenuGridEntry ref_00347468_10[];
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139868[],D_00139688[];
typedef struct { char pad0[0x3c]; unsigned short icon; char pad3e[0x2e]; int max; char pad70[0x18]; unsigned short ammo; char pad8a[0x56]; } MenuWeaponRecord;
extern MenuWeaponRecord D_L00_00239BA0[];
extern void func_00336B90(void *,int),func_00336B98(void *,int);
extern void func_00336F20(int,int *,int *,int *);
extern void func_00336498(void *,int,int);
extern void func_00336548(void *);
extern int func_0026F7A0(void *);
extern void *D_L00_001F2880[];
extern void func_003472B8(void *),func_00347468(void *);
extern int D_L00_001AE750,D_L00_001AE754,D_L00_001AE748,D_L00_001AE74C;
extern float D_L00_001AE758,D_L00_001AE75C;
extern MenuIntegerPair D_L00_001AE588[],D_L00_001AE590[];
typedef struct {float x,y;} MenuFloatPair;
extern MenuFloatPair D_L00_001AE598[],D_L00_001AE5A0[];
void func_003478F0(char *o)
{
 if(*(int *)(o+0x4f8)) {
  int row,col;

  func_00336320(o);func_00336320(o+0x4c);func_00336320(o+0x130);
  for(row=0;row<6;row++) {
   short *ids=(short *)ref_00347468_10;
   short *id=ids+(row<<2)*5+3;
   for(col=0;col<4;col++,id+=5) {

    { int *color=((int *)func_00335E20(o+0x3b4));
      float xb=(float)D_L00_001AE750;
      float yb=(float)D_L00_001AE754;
      float ys=D_L00_001AE75C;
      float xs=D_L00_001AE758;
      *color=0x60241700;
      func_00335E38(o+0x3b4,(xs*(float)col+xb)+(*(float **)(o+0x498))[0],(yb+(ys*(float)row))+(*(float **)(o+0x498))[1],0.0f,0.0f);
    }
    *((int *)func_00335E20(o+0x98))=0x30f0c070;
    *((int *)func_00335E20((o+0x3b4)))=0x60241700;
    func_00335E68((o+0x1c8),0);func_00335E68((o+0x378),0);
    if(D_001A7AF8[*id]) {
     MenuWeaponRecord *weapons=D_L00_00239BA0;
     unsigned char *slots=D_00139568;
     func_00336920((o+0x378),weapons[slots[*id]].icon,0);

     func_00335E38((o+0x378),(53.5f*(float)col+(float)D_L00_001AE748)+(*(float **)(o+0x498))[0],(47.0f*(float)row+(float)D_L00_001AE74C)+(*(float **)(o+0x498))[1],0.0f,0.0f);
     if(weapons[slots[*id]].icon==0xea7e) {
      *((int *)func_00335E20((o+0x378)))=0x80808080;
     } else {
      MenuIntegerPair base=D_L00_001AE588[0],stride=D_L00_001AE590[0];
      int a,b,color;
      func_00336B90((o+0x1c8),weapons[slots[*id]].max);
      func_00336B98((o+0x1c8),D_00139868[*id]>>5);

      func_00335E38((o+0x1c8),(float)(stride.x*col+base.x)+(*(float **)(o+0x498))[0],(float)(stride.y*row+base.y)+(*(float **)(o+0x498))[1],0.0f,0.0f);
      func_00335E68((o+0x1c8),1);
      a=0;b=0;color=0;
      func_00336F20(*id,&a,&b,&color);func_00336498((o+0x1c8),a,b);
      *((int *)func_00335E20((o+0x378)))=color;
      if(weapons[slots[*id]].max<=0) {func_00336B90((o+0x1c8),100);func_00336B98((o+0x1c8),100);}
     }
     if(D_00139688[*id]==0) {
      unsigned char *currentSlots=D_00139568;
      MenuWeaponRecord *currentWeapons=D_L00_00239BA0;
      if(currentWeapons[currentSlots[*id]].ammo!=0) *((int *)func_00335E20(o+0x3b4))=0x60202080;
     }
     func_00335E68((o+0x378),1);
     if(func_0026F7A0(D_L00_001F2880[0])==*id) *((int *)func_00335E20(o+0x98))=0x80ffde8d;
    }
    {
     MenuFloatPair stride=D_L00_001AE598[0],base=D_L00_001AE5A0[0];

     func_00335E38(o+0x98,(stride.x*(float)col+base.x)+(*(float **)(o+0x498))[0],(stride.y*(float)row+base.y)+(*(float **)(o+0x498))[0],0.0f,0.0f);
    }
    func_00336320((o+0x3b4));func_00336828((o+0x378));func_00336548((o+0x1c8));func_00336320(o+0x98);
   }
  }
  func_00336320(o+0xe4);func_00336320(o+0x17c);func_00336A78(o+0x210);func_00336A78(o+0x258);func_00336A78(o+0x2a0);
  func_003472B8(o);func_00347468(o);
 }
}
