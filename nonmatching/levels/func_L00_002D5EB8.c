/* 9 November 2026 (Sonnet round 3, lesson 49 audit): remaining locals (ok, p, skip, a/b/c already literals) are real; re-measured 1376/1376, 29 rows. Skip-test spellings on the literal C: plain continues / || chain / nested / indexed table give 1336 bytes (323 rows, jump1 copies the exit test); value forms `skip = !exists || i==10 || i==9` (93), ternary (92), if/else (93), `skip=(i==10||i==9)` 62 rows 1372 bytes; none gives beq for 10/9. Indexed D_00139568[i] 92. 25-minute permuter (-j2) 1170 -> 970 only via dead code (`i = 0` reuse for a 0 argument, a skip assignment after a break): not honest. No match. */
/* 8 November 2026 (Sonnet round 2, lesson 49): dropping the a/b/c locals (write 17/18/53 as literals in the compares) moves hi(D_00139568)/hi(table) to retail's s4/s5 and 17/18/53 to fp/s7/s6: 46 -> 29 differing rows (first diff +0x3F0 now the entry copy). Body below is that C. Left: retail makes a fresh lui for the entry lbu (ours reuses s4), 10/9 are `addiu a2,10; beq` (ours xori), one nop. Every skip spelling tried (|| chain, continue forms, 10/9 first, nested if) is worse (93 or wrong size). */
/* 8 November 2026 (Sonnet round): re-measured, 100 differing rows, first diff +0x3F0. Retail keeps hi(D_00139568) in s4 and hi(table) in s5 (ours s7/fp), constants 17/18/53 in fp/s7/s6. 25-minute permuter (-j2) best 2110 -> 1690 only via an address-taken local (`new_var = &a`) and a comma on &count: not honest. No match. */
/* 8 November 2026, re-measured on master's compiler (sticky-volatile default, mtc1 fix):
 * unchanged, 1376/1376, 0/27 USA, 46 positions; check.py first difference +0x3F0.
 * Mechanism of the last loop, from cc1 dumps (-dj -dG -dL): expand_end_loop rotates
 * the exists/10/9/D_001A7AF8 tests to the bottom. Retail needs (1) direct beq for 10/9,
 * (2) NO exit-test copy at jump1, so cse1 follows the bottom test's branch into the body
 * (single-use top label) and keeps 0xE0/table base in one pseudo (s3/s2) across the call,
 * (3) the entry copy made later by the post-loop JUMP_AFTER_REGSCAN pass.
 * duplicate_loop_exit_test refuses only on a CODE_LABEL, call, LOOP_BEG/CONT note or
 * more than 30 insns (LOOP_TEST_THRESHOLD is 30, not 20). This draft's skip merges give
 * the labels (2)+(3) but xori for 10/9. Plain `if(!exists) continue; if(i==10) continue;
 * if(i==9) continue;` (or the && form) gives retail's exact branch layout but only 20
 * insns, so jump1 copies the test and 0xE0/base are rematerialized (1368 bytes).
 * `do { k = *p; } while(0);` before the exists test blocks jump1, keeps s2/s3 and puts
 * 10/14 in a2 as retail, but its loop notes also block the post-loop copy (1332 bytes).
 * Value forms (`use = a && b && c`, `if(!skip && i==10) skip=1`, else-if chains, switch,
 * inline listed() helper) give movn/movz, range checks or lose the rotation.
 * D_001A7AF8 without MACRO_ADDR cross-jumps into the entry copy. Indexed
 * D_00139568[i] gives a loop.c giv with retail's fresh lui but hoists 0xE0/14/12.
 * Next: a referenced label inside the rotated region that cse1/jump2 thread away
 * before the post-loop jump, with 10/9 still expanded as branch compares.
 */
/* 6 November 2026, Codex loop-shape follow-up: 1376/1376 bytes, 0/27 USA places,
 * -O2 -G8 -ffunction-sections in an isolated shared -g8.c unit. check.py reports
 * "instruction at +0x3f0 differs" at every place; 46 instruction positions differ
 * after excluding relocation address fields (first real register difference +0x64).
 * This improves the previous 1368-byte draft but is not a match or a linked result.
 * New source: a real D_00139568 cursor, an accumulated short-circuit skip predicate,
 * and a one-pass group assigning the actual 18/53 exception constants. This recovers
 * the 0x60 frame and keeps stride 0xE0 in s3 and the entry-table base in s2 across
 * the last call. The group's b/c locals are initialized before use; every cursor
 * increment stays in the for latch, including on continue paths. No dead operations.
 * Remaining: map/table address registers in the earlier loop (s7/fp versus s4/s5),
 * last-loop entry scheduling, exception-constant allocation, xori/zero branches for
 * 10/9 instead of direct comparisons, flag-base register, and final store/arg order.
 * New controls that did not close it: while/do/explicit latch and early-return loops;
 * combined/nested predicates, inline and tri-state predicates; real one-pass groups;
 * short-circuit OR/AND and skip updates; byte/short predicate types; map storage
 * declarations; -fno-gcse, -fno-rerun-loop-opt, -fno-rerun-cse-after-loop,
 * -fno-thread-jumps, -fno-sched-interblock, -fno-schedule-insns,
 * -fno-strength-reduce, -fmove-all-movables, -fno-expensive-optimizations,
 * -frac2-keep-block-order and -fno-force-mem. No usable RAC1/RAC4 donor found.
 * Next useful experiment needs evidence for source lifetimes or late exit-test
 * duplication; do not repeat these equivalent loop/flag trials. PAL/US2 not checked.
 * The D5E30 declaration now agrees with its int definition; discarded-return code
 * is byte-identical to the previous void declaration. The older analysis follows
 * as history and describes its own indexed, ungrouped draft, not this candidate.
 */
/* Previous draft, tier opus-1, 3 November 2026: 1368/1376 bytes, 0 of 27 places (check.py, -O2 -G8 -ffunction-sections,
 * would need a `-g8.c` unit; the old 1336 draft no longer applies).
 * Declarations that matter: D_001A7A28, D_001A7398 and D_001A7AF8 are MACRO_ADDR incomplete arrays (tied
 * lui/lbu and unsplit la, which also stops the cross-jumped entry copy in the last loop); D_001A7A00 is an
 * sda unsigned char array: the count goes through *(int *)D_001A7A00 and the flag is D_001A7A00[0x7A], a
 * sym+off 2-insn macro load that keeps it out of the `beqz ok` delay slot (MACRO_ADDR puts it there as $gp).
 * The last loop indexes D_00139568[i] (fixes the s4/s5 order and the epilogue).
 * Left, all in the last loop: retail keeps 0xE0 in s3 and the table base (s5+0x2570) in s2, sets both in
 * the entry copy and the rotated bottom test, and reuses them (and a p giv in s1) after the call; 17/18/53
 * sit in fp/s7/s6 (frame 0x60, we have 0x50 and 7 saved regs); 14 and 10 live in a2.  That looks like the
 * exit test was duplicated by the rerun jump pass after loop.c (cse1 then sees one EBB from the test to the
 * state check), while ours is duplicated at jump1 (21 insns, no label or call left by iteration 2).  Finding
 * the construct that stops jump1's duplicate_loop_exit_test but not the rerun one should fix all of it.
 * ref_L00_002D5EB8_00 is the sda int at the `>= 11` test.
 */
#include "common.h"
extern int D_L00_001B19C8;
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
typedef struct { char p[0x340]; int f340; char q[0x1248-0x344]; int f1248; } H;
extern char D_00189E20[];
typedef struct { int exists; unsigned char state; char pad[7]; int index; char pad2[58]; short value; char pad3[32]; int limit; char pad4[112]; } Entry1269;
extern Entry1269 D_L00_00262570[];
extern int func_L00_002D5E30(int*,int*,int*);
extern void func_0028A180(int,int), func_L00_003F1300(void), func_L00_0030C7F8(int), func_002B0A18(int,int), func_002E5E58(int,int,int);
extern int func_00288D58(void), func_00287F60(int);
extern void func_L00_0037E6A8(int,int), func_00287EB0(int), func_00288508(int);
extern int ref_L00_002D5EB8_00 __attribute__((sda));
static inline int special(int i) { int r=0; switch(i) {case 12:case 14:case 17:case 18:case 53: r=1; break;} return r; }
static inline int unlocked(Entry1269 *e,int i){ if(e->state>=2 || (e->state==1 && special(i))) return 1; return 0;}
static inline int owned(int i){ if(D_L00_00262570[D_00139568[i]].exists){ int n=func_00287F60(i); if(n>=2 || (n==1 && special(i))) return 1; } return 0; }
void func_L00_002D5EB8(void) {
 int count, i, j, ok;
 if ((D_L00_001B19C8&15)==1 && D_L00_001B19C8!=1) return;
 count=4;
 {int *p=D_0018C350; func_L00_002D5E30(p,p + -1,&count);}
 for(j=0;j<10;j++) if(D_001A7A28[j]) count++;
 if (*(int *)D_001A7A00!=count) {
  if (ref_L00_002D5EB8_00>=11 && *(int *)D_001A7A00<count) {
   if (!D_0018C958) func_0028A180(0x9a9,0);
   func_L00_003F1300(); func_L00_0030C7F8(0x168); func_002B0A18(0x1235,-1); func_002E5E58(6,0,0);
  }
  D_0018C2EC[0]=count; *(int *)D_001A7A00=count;
 }
 for(i=0;i<56;i++) {
  if (D_L00_00262570[D_00139568[i]].state) {
   if (!func_00288D58()) continue;
   if (func_00287F60(i)==1) continue;
  }
  {
   Entry1269 *e=&D_L00_00262570[D_00139568[i]];
   int sel = 0;
   if (e->exists) sel = e->state == 3;
   if (sel) continue;
  }
  if(func_00287F60(i)<=0) continue;
  {
   Entry1269 *e=&D_L00_00262570[D_00139568[i]];
   if((D_00139868[i]>>5)<e->limit || e->limit<=0) continue;
   if(i==31 || i==9 || i==45) { func_L00_0037E6A8(i,D_L00_00262570[D_00139568[i]].value); continue; }
   {
    H *h=(H*)D_00189E20;
    if(h->f1248==i) {
     if(!h->f340) continue;
     if(D_001A7398[e->index]!=i) continue;
     func_L00_0037E6A8(i,e->value); continue;
    }
   }
  }
  if(func_00288D58()) {
   Entry1269 *e=&D_L00_00262570[D_00139568[i]];
   if(!e->exists) continue;
   if(unlocked(e,i)) {
    if(owned(i)) { func_00287EB0(i); func_00288508(i); }
   }
  } else { func_00287EB0(i); func_00288508(i); }
 }
 if((D_L00_001B19C8&127) || D_001A7A00[0x7A]) return;
 {
 unsigned char *p=D_00139568; 
 ok=1;
 for(i=0;i<56;i++,p++) {
  int skip = !D_L00_00262570[*p].exists;
  if(!skip) skip=i==10;
  if(!skip) skip=i==9;
  if(!skip) {
   if(!D_001A7AF8[i]) {ok=0; break;}
   if(i==14) continue;
   if(i==12) continue;
   if(i==17) continue;
   if(i==18) continue;
   if(i==53) continue;
   if(func_00287F60(i)<=0) continue;
   if(!D_L00_00262570[*p].state) {ok=0; break;}
  }
 }
 }
 if(ok && !D_001A7A00[0x7A]) {
  D_001A7A00[0x7A]=1; func_002E5E58(1,0,0); func_002B0A18(0x1233,-1); D_L00_001A903C=1;
 }
}
