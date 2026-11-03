/* 2026-11-03 w02 faithful-contract review, US object checks only.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 1648/1660 bytes,0/2 places.
 * Restored actual integer iterator/sound/selection returns and projectile-factory pointer returns. The existing state/count/vector allocation and shared sound tail remain.
 * Reopen: Real state/count and case-local vector lifetime; prior equivalent case guards tie.
 * No linked or cross-release match is claimed; earlier records follow.
 */
/* GPT-6.1 Sol (high effort), task v1212, USA v1.01.
 * Profile: game -O2 -G8 -ffunction-sections (requires a *-g8.c unit).
 * Retained check: 1648/1660 bytes, 0/2 placements (Barlow and Joba).
 * Required declarations are included below. No linked match is claimed.
 *
 * Compared with the earlier sol-low draft, the 64-byte settings record recovers
 * retail's base/index/+4 addressing; a separate case-2 target recovers its s1
 * lifetime; capturing the selected duration before clearing the timer recovers
 * the table-load/store ordering. State==choice recovers the random-loop branch
 * operand order. Early case returns recover case 2's initial origin pointer in
 * s0, followed by a copy to a persistent register.
 *
 * Still different: state pointer/count are s1/s2 rather than s2/s1; the random
 * state snapshot is loaded in a different order; origin/direction and FP live
 * ranges differ; the two sound calls share a tail unlike retail. Equal sizes
 * would not establish a match: this draft is still short by three instructions.
 *
 * Seventeen experimental checker runs, a final retained-source check, and one
 * allocator invocation (two private compiles).
 * Case-local vector arrays enlarged the frame; early vector pointer aliases
 * hoisted addresses and shortened the body to 1616/1620 bytes; TImode locals
 * enlarged the frame. A real attack-subrecord pointer made 1652 bytes but added
 * its own base register. A redundant conditional choice generated unwanted
 * nor/movn instructions (1656 bytes), so that form is not retained. Explicit
 * count decrement made 1640 bytes and changed the loop branch. All-FP-first
 * projectile arguments tied their integer-first form. Initializing yaw to zero
 * did not repair FP allocation. Capturing the case-2 side and using early
 * switch guards each produced exactly the same bytes as the retained form:
 * stopped on that three-wording tie. No toolchain flags were changed.
 *
 * Allocator evidence on the typed 1648-byte precursor: state pointer pseudo 91
 * has 47 refs/247 live instructions and receives s1; the query count and loop
 * induction pseudos coalesce into s2. Investigate real pointer/vector lifetime
 * evidence or a matched equivalent rather than declaration permutations.
 */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(unsigned char **)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
typedef unsigned int AttackQuad __attribute__((mode(TI)));
typedef struct { int v[5]; } AttackChoices;
extern AttackChoices D_L04_001B0A10;
extern struct { unsigned char pad[0x80]; float position[4]; unsigned char pad90[0x2290-0x90]; unsigned char *hero; } D_00189E20;
#define D_00189F00 ((unsigned char *)&D_00189E20 + 0xe0)
#define D_L04_0018C0B0 D_00189E20.hero
typedef struct {
 unsigned char pad0[0x260]; int triggerList;
 unsigned char pad264[0x10]; short elevated;
 unsigned char pad276[6]; float height;
 unsigned char pad280[4]; float tilt;
 unsigned char pad288[8]; float offset[4];
 unsigned char pad2a0[0x6c]; float length;
 unsigned char pad310[0x50]; int state, duration, timer;
 unsigned char pad36c[0x16c]; int alternate, alternateTimer;
 unsigned char pad4e0[0x284]; int cooldown, ready;
} AttackState;
typedef struct { int unused, flags; unsigned char pad8[0x38]; } AttackSettings;
extern AttackSettings D_L04_002C63C0[];

extern unsigned char *D_L04_001C3B40[];
extern int D_L04_001B090C __attribute__((sda));
extern int D_00138320 NOT_SDA,D_00138324 NOT_SDA;
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00277F48(void *,float,int,void *,int);
extern int func_002ABB78(void *);
extern void func_002A8F70(void *,void *,int,void *,void *,float);
extern void func_L04_0040E460(void *);
extern int func_002A8600(void *,int,int,int);
extern int func_002A86E8(void *,void *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int func_002A7820(int,int);
extern int func_002E5DA0(int,int,void *,int);
extern void func_L04_0040C0C0(void *,void *,int,int);
extern int func_00282948(void *);
extern void func_0029FCC0(void *,int,void *);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CD8(void *,void *,void *);
extern void func_L04_003F9320(void *,void *,void *,int);
extern int func_002E5CF8(int,int,void *);
extern unsigned char *func_L04_0040EC80(void *,void *,void *,void *,void *,void *,float,float);
extern int func_L00_002D6900(int);
extern void * func_L04_003FA5A8(void *,void *,void *,float,float,float,float,float);
extern void * func_L04_003FBD80(void *,void *);
void func_L04_0040EF50(unsigned char *m)
{
 AttackChoices choices;
 float origin[4],dir[4],delta[4],probe[4],temp[4];
 unsigned char *target; float pitch,yaw,aimPitch,aimYaw,extra; AttackState *p=*(AttackState **)(m+0x68); unsigned char *d; int count,i,state,choice;
 choices=D_L04_001B0A10;
 func_00282D30(probe,p->offset,3);
 func_00282CC0(probe,probe,D_00189F00);
 count=func_00277F48(probe,0.7f,0,D_L04_0018C0B0,0);
 if(count) {
  func_00282D30(delta,p->offset,7);
  for(i=0;i<count;i++) if(func_002ABB78(D_L04_001C3B40[i]) || H(D_L04_001C3B40[i],0xaa)==0x85)
   func_002A8F70(D_L04_001C3B40[i],D_L04_0018C0B0,0x10000,D_00189E20.position,delta,1);
 }
 func_L04_0040E460(m);
 if((D_L04_002C63C0[D_L04_001B090C].flags&1) && p->triggerList!=-1) {
  func_002A8600(&target,p->triggerList,0,0);
  while(target) {
   if(H(target,0xaa)==0xab8) {
    d=P(target,0x68);func_00282CF0(delta,target+16,m+16);
    if(!I(d,0) && func_L00_002EE290(delta)<1) {
     state=p->state;choice=I(d,4);
     if(choice==-1) do {choice=func_002A7820(1,4);} while(state==choice && I(d,4)==-1);
     if(choice==4) {p->alternate=1;p->alternateTimer=choices.v[4];}
     else {int duration; p->state=choice;duration=choices.v[choice];p->timer=0;p->duration=duration;}
     if(m[0x20]!=3)func_002E5DA0(0,0,m,0xab8);
     func_L04_0040C0C0(target+16,p->offset,8,0);I(d,0)=300;
    }
   }
   func_002A86E8(&target,target,0,0);
  }
 }
 if(p->alternate) {
  p->ready=0;
  if(func_00282948(&p->alternateTimer)) {p->alternate=0;p->ready=1;}
 }
 if(p->ready && func_00282948(&p->cooldown)) {p->ready=0;p->cooldown=40;}
 if(m[0x20]==3)return;
 switch(p->state) {
 case 0: break;
 case 1:
  if(func_00282948(&p->timer) && (D_00138320&5)) {
   p->timer=3;func_0029FCC0(m,((p->duration^1)&1),origin);
   if(p->elevated)func_002AF000(dir,p->length+0.5f,F(m,0xf8),-p->tilt);
   else func_002AF000(dir,p->length+0.5f,F(m,0xf8),-F(m,0xf4));
   func_00282CD8(temp,origin,dir);func_L04_003F9320(m,origin,dir,120);func_002E5CF8(7,0,m);
  }return;
 case 2: {
  unsigned char *target;
  if(func_00282948(&p->timer) && (D_00138324&5)) {
   extra=0;p->timer=30;func_0029FCC0(m,((p->duration^1)&1),origin);pitch=F(m,0xf8);
   if(p->elevated)func_002AF000(dir,p->length+0.5f+p->height,pitch,0);
   else func_002AF000(dir,p->length+0.5f+p->height,pitch,-F(m,0xf4));
   yaw=F(m,0xf4)-0.3490659f;
   target=func_L04_0040EC80(m,origin,dir,&aimPitch,&aimYaw,&extra,0.78539824f,30);
   if(target) {
    func_00282CF0(delta,origin,target+16);
    if(func_L00_002EE290(delta)<25) {pitch=aimPitch;yaw=aimYaw;}
   } else {aimPitch=pitch;aimYaw=yaw;extra=0.2f;}
   func_L00_002D6900(47);func_00282CD8(temp,origin,dir);
   func_L04_003FA5A8(m,origin,target,aimPitch,aimYaw,extra,pitch,yaw);func_002E5CF8(8,0,m);
  }return; }
 case 3:
  if(func_00282948(&p->timer) && (D_00138324&5)) {
   p->timer=30;func_00282CC0(temp,m+16,p->offset);*(AttackQuad *)origin=*(AttackQuad *)temp;func_L04_003FBD80(m,origin);
  }
  if(func_00282948(&p->duration))p->state=0;
  break;
 }
}
