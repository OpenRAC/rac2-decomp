/* 9 November 2026 (o69): still 11 rows (body unchanged). Sched dumps: sched1 issues the case-0 float stores in source (luid) order and sched2 keeps it, so the 0x54 swap is a source-order effect, not a dependence (retail stores 0.1 from a fresh li.s, swc1, base $s3). With retail's store order fixed (tenth=0.1f named, 4 int stores + 0x170/|=0x14 movable) hill-climbs (~4k compiles) reach 15 rows: only gravity/0.1 swap $f1/$f0 (gravity born last dies first, so it is allocated first and takes $f0). Local-alloc model: retail needs gravity born before the 0x160 store (overlapping the product) or 0.1 born at least 7 insns after gravity, while limit < 1.134 < .75 < .5 < .3 lifetimes stay ordered. Case 5 sched1: store 819 depends only on the t load (816), chosen at t=4 over $f14/$f15 by weight -1. Search stopped by a full /tmp. */
/* 9 November 2026 (o64): 15 -> 11 rows (USA 2476/2476, 0/1, first diff now +0x128; check.py --diff 101 -> 97 rows). Case 0 is now register-exact: local-alloc gives gravity $f1 only when its life overlaps the 0x160 product and 0.1 has the shortest life (modelled from the .lreg births/deaths); a statement-order hill-climb (~16k compiles, 0x24/0x130 int stores interleaved, six named constants, 0.1 inline) reaches it with the 0x54 store issued second instead of last (2 rows). Body below is that C. No order found with retail store order AND registers; do/while(0) groups in case 0 cost 20-1000 rows. Case 5 (9 rows) unchanged: groups around the store/args (combine sinks the products and constants into the $f12-$f15 moves after the barrier), statement-expression barrier in the last arg, duplicated per-path tails, ternary negation, K3/K4 locals: 15-23. Every -frac2-* switch in cflags.txt: no change (qcopy 35). Permuter 1500 s: only size-changing outputs. */
/* 9 November 2026 (o38, PRE slot order): not spill-slot blocked. Only one PRE copy spills (fp+48, reg 402, S=295), so no slot order to fix; the 15 rows are case 0 FPR allocation and case 5 sched1 order. */
/* 8 November 2026 (Sonnet round o28, lesson 49): re-measured 2476/2476, 0/1 at +0xC8, 15 rows. Locals audited (speed..minimum, t, f each one register in retail; no fake locals). Case 0: retail's register pattern needs the gravity load to overlap the 0x160 product's life (f0) so gravity takes f1 and 0.1 later takes f0; all 5040 declaration orders (gravity as a local, retail store order), 4000 random declaration x store orders, the product held in a local and stored at each of 10 places, and one-statement-per-line (-g notes): none below 15. Case 5: the store wins sched1 (ready at t=4 with priority equal to the $f14/$f15 loads, register weight -1); a store whose value is computed in the same block (permuter: unconditional -f) goes last, as retail, but no honest source does it: comma store in each of the 5 arguments, pointer local for q+0x160, K*(t+t) orders, k1-k4 locals, f*=K, ternary, early return: all 15-20. Permuter 1500 s: nothing honest. */
/* 8 November 2026: measured again (USA, 2476/2476 bytes, 0/1 at +0xC8): 15 rows in two places.
 * Fixed the loop preheader: `float scale=45000;` beside life/mode/alpha (used as lifetime*scale)
 * gives 45000 a longer life, so loop pass 1 hoists it ahead of 1.0 (it was "not desirable").
 * Still open: case 0 (gravity/0.1 in $f0/$f1: local-alloc priority; a 1500-step statement-order
 * hill-climb and do/while(0) groups did not fix it) and case 5 (the 0x160 store wins sched1 by
 * register weight; a turn() helper, statement expressions, locals, a group did not move it).
 * Round 2 (same day), no change: case 0 hill-climb from the all-registers-right order, 0.1 or
 * gravity as literal/named/late local (sched1 issues all constant loads before the stores, so
 * 0.1's life stays 20 insns vs gravity's 10); case 5 with K3/K4 as locals set before the store,
 * a copied angle local, a ternary store, a comma store in the last argument. A store after the
 * call cannot reach the delay slot (reorg will not move a store across a call).
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain the pointer return of func_0032C700 and the typed scheduler callback.
 * The shared scratch covers 48 bytes, including all three vectors.
 * USA remains 0/1 at +0xC8; constant order and loop allocation are unresolved.
 * Earlier measurements below describe earlier sources or toolchains.
 */
/* Tier: opus-1 (Claude Opus 5.5, xhigh). USA v1.01 (v2.00 identical; not in PAL).
 * Best check: 2476/2476 bytes, 0 of 1 places match. cdiff: 107 of 619 rows differ,
 * all but 22 of them relocation-only (unlinked symbol and $gp offsets).
 * Build it as its own unit with -O2 -G8 -ffunction-sections -g (e.g.
 * src/levels/11_joba/L11_00453358-state-g8.c plus that cflags.txt line): -G8 for the
 * SDATA tunings, -g plus the statement-expression line breaks for the nop pairs
 * before both div.s.
 * Remaining (22 rows, three places):
 *  - case 0: gravity (0.0027778) and 0.1 swap $f1/$f0 (local-alloc order after sched1).
 *    Gravity store first with gravity's constant loaded last gives retail's other five
 *    registers. Inline constants in the order .3,.75,.5,1.134,.5236,.1,gravity give all
 *    seven registers, but then the 0x4C store comes last.
 *  - loop preheader: li.s 1.0 ($f20) is scheduled before 45000 ($f22). Retail's order
 *    needs 45000 hoisted in loop pass 1 ahead of 1.0; here it is hoisted in pass 2.
 *  - case 5: swc1 $f20,0x160($s3) issues after the 0.016667 constant instead of in the
 *    jal delay slot (sched1 prefers the store, which frees a register). Locals, const
 *    data and argument order did not move it.
 * Load-bearing choices (each measured): the life/mode/alpha locals in the inner loop
 * block (loop pass 1 hoists them; 120 then spills and is rematerialised in the loop,
 * so 2/127 win $fp/$s7); the axis local before the loop (whole-address reload into
 * $a2); one qcopy per branch (cross-jumped into the shared lq/sq); one Collision
 * pointer per block (separate %lo, shared %hi); the bounce scale read before the
 * counter increment; and the real return types of func_00282978, func_00277F48,
 * func_002AA548 and func_002B4FF0, which change $v0 lifetimes and reload's
 * round-robin choices later in the function.
 * func_002BDCE8 is defined as (TI128 *, int, TI128 *, int, int, float, float, float,
 * float). It is declared here with the same registers in a different interleaving,
 * (void *, int, float, float, float, void *, unsigned, int, float), which gives
 * retail's argument-load order. Disclose that, or find the source shape that does it.
 * Earlier attempts: sol-low (control flow), sol-high (rotation/state 6, division nops).
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern float func_00283CE0(int),func_002A7878(float,float),func_00282E20(void *),func_00283B98(float,float),func_L02_002F21C0(void *,void *);
extern int func_002A77E0(int),func_002761F8(void *,void *,int,void *,int),func_00277258(void *,int,void *,float),func_002B3868(void *),func_00282948(void *),func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void *func_002A9640(void *,unsigned int,int);
extern int func_002B4FF0(void *,void *,float);
extern float func_002AA548(void *,void *,float,float,float,float);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282D30(void *,void *,float),func_00283028(void *,void *,void *),func_L00_0031D670(void *,void *,void *,float),func_002E59F8(int),func_002A8BD0(void *,void *,int,float);
extern void func_L00_002E6EF8(void (*)(void *),void *);
extern int func_00277F48(float,void *,int,void *,void *);
typedef struct { int unused; int mode; short unused8; u8 alpha, duration; } ParticleAttributes;
typedef struct { char unused[10]; s16 lifetime; char unused12[20]; ParticleAttributes attributes; } Particle;
extern Particle *func_002BDCE8(void *,int,float,float,float,void *,unsigned,int,float);
extern char *func_L11_004417E8(void *);
extern char *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_002B60B0(void *,float,float,float,float);
extern void func_L11_00458C38(void *);
typedef struct { char pad0[0x18]; char *hit; int count; float point[4]; float pad30[4]; float normal[4]; } Collision;
extern Collision D_L11_001C0D00;
extern char D_00188660[];
/* Whether the moby hit belongs to the same class as this one's owner. */
static inline int func_IsOwnerClass(char *hit,char *vars) {
 int same=0;
 if(hit && *(char **)(vars+0x15C))same=*(s16 *)(hit+0xAA)==*(s16 *)(*(char **)(vars+0x15C)+0xAA);
 return same;
}
extern Quad D_L11_001A8F20;
extern float D_L11_001B1F80 SDATA(D_L11_001B1F80);
extern float D_L11_001B1F88 SDATA(D_L11_001B1F88);
extern float D_L11_001B1F8C SDATA(D_L11_001B1F8C);
extern float D_L11_001B1F94 SDATA(D_L11_001B1F94);
extern float D_L11_001B1F98 SDATA(D_L11_001B1F98);
extern float D_L11_001B1FA8 SDATA(D_L11_001B1FA8);
extern float D_L11_001B1FAC SDATA(D_L11_001B1FAC);
extern float D_L11_001B1F9C SDATA(D_L11_001B1F9C);
extern int D_L11_001B1F84 SDATA(D_L11_001B1F84);
extern int D_L11_001B1F90 SDATA(D_L11_001B1F90);
extern int D_L11_001B1FA4 SDATA(D_L11_001B1FA4);
typedef struct { float x,y,z; } FadeColor;
extern FadeColor D_L11_001B1FB0;
void func_L11_004580E8(char *p) {
 char *q=*(char **)(p+0x68),*other,*entry;
 union { struct { float a[4],b[4],c[4]; } v; char damage[48]; } scratch;
 float f; int i,n; unsigned int r,g,blue;
 switch(*(u8 *)(p+0x20)) {
 case 0: {
  *(u8 *)(q+0x148)=func_00283CF0(15);*(u8 *)(q+0x14A)=func_00283CF0(4);
  {float speed, max, damping, turn, gravity, limit;
  *(float *)(q+0x160)=func_002A7878(-*(float *)(q+0x160),*(float *)(q+0x160))*0.017453294f;
  *(u8 *)(p+0x30)=128;*(int *)(q+0x24)=0;
  speed=0.3f;max=0.75f;damping=0.5f;turn=1.134464144706726f;gravity=0.0027777778450399637f;limit=0.523598849773407f;
  *(u8 *)(q+0x128)=3;*(int *)(q+0x130)=0;
  *(float *)(q+0x4C)=gravity;*(float *)(q+0x54)=0.1f;
  *(float *)(q+0x28)=max;*(float *)(q+0x2C)=damping;*(float *)(q+0x30)=turn;*(float *)(q+0x50)=limit;*(float *)(q+0x20)=speed;
  *(int *)(q+0x58)|=0x14;*(float *)(p+0x2C)*=D_L11_001B1F88;*(int *)(q+0x170)=-1;
  *(u16 *)(p+0x34)=(*(u16 *)(p+0x34)&0xEFFF)|0x41;*(int *)(p+0x98)=0;
  }
  func_002A7750(p,1,-1);return;
 }
 case 2:case 3:
  func_00282CC0(scratch.v.a,p+0x10,q+0xC0);
  *(float *)(q+0xC8)-=*(float *)(q+0x4C);
  if(*(u8 *)(p+0x20)==3 && *(float *)(q+0xC8)<0) *(u8 *)(p+0x20)=2;
  func_00282978(q+0x16C);
  if(*(s16 *)(q+0x16C)) {
   Quad *axis=&D_L11_001A8F20;
   for(i=0;i<3;i++) {
    *(Quad *)scratch.v.c=*(Quad *)(p+0x10);func_L00_0031D670(scratch.v.b,scratch.v.c,scratch.v.a,(float)i*0.3333f);
    n=func_002A77E0(6);if(func_002A77E0(2))n=-n;
    f=func_00283CE0(D_L11_001B1F84);
    {
    int life=120,mode=2,alpha=127;
    float scale=45000;
    Particle *particle=func_002BDCE8(scratch.v.b,n,0.025f,1,1,axis,0x80808080,0,
      ({float lifetime=(float)*(s16 *)(q+0x16C)/f;
        lifetime*scale+5000;}));
    if(particle) {ParticleAttributes *attributes;particle->lifetime=life;attributes=&particle->attributes;attributes->mode=mode;attributes->alpha=alpha;attributes->duration=(u8)particle->lifetime;}
    }
   }
  }
  if(func_002761F8(p+0x10,scratch.v.a,0,p,0) && !func_IsOwnerClass(D_L11_001C0D00.hit,q)) qcopy(p+0x10,D_L11_001C0D00.point);
  else qcopy(p+0x10,scratch.v.a);
  if(!func_00277258(p+0x10,0,p,D_L11_001B1F80))break;
  if(*(u8 *)(p+0x20)!=2) {Collision *col=&D_L11_001C0D00;if(!(*(float *)(p+0x18)-col->point[2]<0))break;}
  {Collision *col=&D_L11_001C0D00;
  if(func_IsOwnerClass(col->hit,q))break;}
  func_00282F20(scratch.v.b,D_L11_001C0D00.normal,D_L11_001B1F80);
  func_00282CC0(p+0x10,D_L11_001C0D00.point,scratch.v.b);
  func_00283028(q+0xC0,q+0xC0,D_L11_001C0D00.normal);
  func_002E5CF8(1,0,p);
  if(*(u8 *)(p+0x20)==2) {float bounce;*(u8 *)(p+0x20)=3;bounce=D_L11_001B1F8C;(*(u16 *)(q+0x16E))++;func_00282D30(q+0xC0,q+0xC0,bounce);}
  if(*(s16 *)(q+0x16E)>=D_L11_001B1F90) *(u8 *)(p+0x20)=5;
  break;
 case 4: {
  float f;
  if(func_002B3868(p)){int duration=D_L11_001B1FA4;*(int *)(q+0x150)=duration;*(float *)(q+0x154)=1/func_00283CE0(duration);}
  *(FadeColor *)scratch.v.a=D_L11_001B1FB0;
  f=(float)*(int *)(q+0x150)**(float *)(q+0x154);
  r=func_00283CF0((scratch.v.a[0]-255)*f+255);g=func_00283CF0(scratch.v.a[1]*f);blue=func_00283CF0(scratch.v.a[2]*f);
  {unsigned int color=blue<<16;
  color|=0xFF000000;
  color|=g<<8;
  color|=r;
  *(unsigned int *)(p+0x78)=color;}
  if(func_00282948(q+0x150))func_002A7750(p,6,-1);
  break;
 }
 case 5: {
  float f,t;
  if(func_002B3868(p)) {
   p[0xBC]=0;f=func_002A7878(15,40)*0.017453294f;if(func_002A77E0(2))f=-f;
   t=D_L11_001B1F98;
   *(float *)(q+0x160)=f;func_002B60B0(p,(t+t)*0.00027777778450399637f,t*0.01666666753590107f,0.0011635529808700085f,0.10471977293491364f);
  } else if(!*(u8 *)(p+0xBC)) {
   other=func_L11_004417E8(*(void **)(p+0xB8));
   if(*(float *)(p+0x18)<*(float *)(other+8)+D_L11_001B1F94) {
    float *height=(float *)(p+0x18);
    other=func_L11_004417E8(*(void **)(p+0xB8));
    func_002AA548(height,q+0xC8,*(float *)(other+8)+D_L11_001B1F94,*(float *)(q+0x40),*(float *)(q+0x40),*(float *)(q+0x48));
   }else p[0xBC]=1;
  }else if(*(u8 *)(p+0xBC)==1) {
   if(*(u8 *)(p+0x31))func_002B4FF0(p,*(char **)(q+0x164)+16,*(float *)(q+0x160));
   other=func_L11_004417E8(*(void **)(p+0xB8));*(float *)(p+0x18)=*(float *)(other+8)+D_L11_001B1F94;
   if(*(u8 *)(p+0x31)) {f=func_L02_002F21C0(p+0x10,*(char **)(q+0x164)+16);if(f<D_L11_001B1F9C*D_L11_001B1F9C)func_002A7750(p,4,-1);}
  }
  if(!func_002E59B0(p,*(int *)(q+0x170))) *(int *)(q+0x170)=func_002E5CF8(2,4,p);
  break;
 }
 case 6:
  if(func_002B3868(p)) {
   func_0032C700(p+16,1,10,10,2,20,60,1,D_L11_001B1FA8,0,1,1,0,0);
   func_002E5CF8(0,0,p);func_002A8BD0(scratch.damage,p,0x810001,*(float *)(q+0x158));
   scratch.damage[24]=2;scratch.damage[25]=1;*(u16 *)(scratch.damage+26)=*(u16 *)(p+0xAA);
   func_00277F48(D_L11_001B1FAC,p+16,16,p,scratch.damage);
   *(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;func_002A7750(p,1,-1);
  if(func_002E59B0(p,*(int *)(q+0x170))) {
   int sound=*(int *)(q+0x170);if(sound!=-1){entry=D_00188660+sound*0x70;if(*(char **)(entry+0x88)==p&&*(u8 *)(entry+0x74))func_002E59F8(sound);}
   *(int *)(q+0x170)=-1;
  }return;
  }
  break;
 default: case 1: break;
 }
 {
  float f;
  float min,max;
  f=func_00282E20(q+0xC0);min=0.0033333336468786f;max=0.10000000894069672f;
  if(f<min)f=min;if(f>max)f=max;
  f=f-min;
  *(float *)(p+0xF4)=func_00283B98(
    ({float fraction=f/0.09666667878627777f;
      (fraction*7+1)*0.017453294f;}),*(float *)(p+0xF4));
 }
 if(*(u8 *)(p+0x20)>=2)func_L00_002E6EF8(func_L11_00458C38,p);
 if(*(void **)(p+0xB8)) {other=func_L11_004417E8(*(void **)(p+0xB8));if(*(float *)(p+0x18)<*(float *)(other+8)-1){*(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;func_002A7750(p,1,-1);}}
 if(func_002A9640(p,0x10000,0))func_002A7750(p,6,-1);
 *(u8 *)(p+0xA8)=255;if(*(u16 *)(p+0x96)<0xFFFF)(*(u16 *)(p+0x96))++;
}
