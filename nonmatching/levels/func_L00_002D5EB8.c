/* Tier opus-1, 3 November 2026: 1368/1376 bytes, 0 of 27 places (check.py, -O2 -G8 -ffunction-sections,
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
 int a=17,b=18,c=53;
 ok=1;
 for(i=0;i<56;i++) {
  if(D_L00_00262570[D_00139568[i]].exists) {
   if(i==10) continue;
   if(i==9) continue;
   if(!D_001A7AF8[i]) {ok=0; break;}
   if(i==14) continue;
   if(i==12) continue;
   if(i==a) continue;
   if(i==b) continue;
   if(i==c) continue;
   if(func_00287F60(i)<=0) continue;
   if(!D_L00_00262570[D_00139568[i]].state) {ok=0; break;}
  }
 }
 }
 if(ok && !D_001A7A00[0x7A]) {
  D_001A7A00[0x7A]=1; func_002E5E58(1,0,0); func_002B0A18(0x1233,-1); D_L00_001A903C=1;
 }
}
