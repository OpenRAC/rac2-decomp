/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Closer C3, 1 November 2026: 1336/1376, -O2 -G8 -ffunction-sections, flags from the old draft no longer matter.
 * Found: `x = a || (b && c)` tests that end in r=1 / r=0 are `if (cond) return 1; return 0;` helpers: reorg steals the
 * r=0 into each branch slot and the dead else goes, which gives retail's `beqz a1 / r=0 / r=1 / beqz r`. The set test is
 * an inline switch; state compares unsigned through the entry pointer. D_0018C2EC is an incomplete array (split %hi in v0);
 * D_0018C350 is an incomplete array with `p + -1`; D_001A7A7A is MACRO_ADDR; the hero block is an `la` through a struct view.
 * The last loop has no loop.c work: p walks D_00139568 as a real local, 17, 18 and 53 are locals set before it (they
 * stay in fp, s7, s6), 14, 12, 10, 9 are not. Rolling moves everything down to `ok=0; break` to the bottom and
 * duplicate_loop_exit_test copies it, so i==10/9 fold in the entry copy.
 * Left: frame (retail 8 saved, we have 7: 0xE0 and the table must stay in s3/s2 across the call in the last loop,
 * they are reset in the rolled test and in the entry copy, and we rematerialize), retail takes a fresh `lui v0` for
 * D_00139568 where gcse PRE reuses the first loop's high part, the entry copy's `b` into the bottom test (retail
 * keeps its own test: v0 against v1, so no cross-jump), a2 for 10 and 14 (retail's constants look global: moved up a
 * block by sched1), the la of D_001A7398 in a0 after the index load.
 */
#include "common.h"
extern int D_L00_001B19C8;
extern int D_0018C350[];
extern int D_001A7A00, D_0018C2EC[];
extern unsigned char D_001A7A28[], D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[], D_001A7398[];
extern unsigned char D_001A7AF8[];
extern unsigned char D_001A7A7A MACRO_ADDR;
typedef struct { char p[0x340]; int f340; char q[0x1248-0x344]; int f1248; } H;
extern char D_00189E20[];
typedef struct { int exists; unsigned char state; char pad[7]; int index; char pad2[58]; short value; char pad3[32]; int limit; char pad4[112]; } Entry1269;
extern Entry1269 D_L00_00262570[];
extern void func_L00_002D5E30(int*,int*,int*);
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
 if (D_001A7A00!=count) {
  if (ref_L00_002D5EB8_00>=11 && D_001A7A00<count) {
   if (!D_0018C958) func_0028A180(0x9a9,0);
   func_L00_003F1300(); func_L00_0030C7F8(0x168); func_002B0A18(0x1235,-1); func_002E5E58(6,0,0);
  }
  D_0018C2EC[0]=count; D_001A7A00=count;
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
 if((D_L00_001B19C8&127) || D_001A7A7A) return;
 {
 unsigned char *p=D_00139568; int a=17,b=18,c=53;
 ok=1;
 for(i=0;i<56;i++,p++) {
  if(D_L00_00262570[*p].exists) {
   if(i==10) continue;
   if(i==9) continue;
   if(!D_001A7AF8[i]) {ok=0; break;}
   if(i==14) continue;
   if(i==12) continue;
   if(i==a) continue;
   if(i==b) continue;
   if(i==c) continue;
   if(func_00287F60(i)<=0) continue;
   if(!D_L00_00262570[*p].state) {ok=0; break;}
  }
 }
 }
 if(ok && !D_001A7A7A) {
  D_001A7A7A=1; func_002E5E58(1,0,0); func_002B0A18(0x1233,-1); D_L00_001A903C=1;
 }
}
