/* func_PAL_L04_00413590, the PAL copy of func_L04_0040EF50: the same C, where rename func_L04_0040E460 becomes func_PAL_L04_00412AA0; rename func_L04_0040C0C0 becomes func_PAL_L04_00410678; rename func_L04_003F9320 becomes func_PAL_L04_003FD4F8; rename func_L04_003FA5A8 becomes func_PAL_L04_003FE7B0; rename func_L04_003FBD80 becomes func_PAL_L04_003FFF88; lit 3 becomes 2. */

/* Bodies whose retail bytes reach their globals through $gp: this file is built -G8.
   Measured here: cc1 emits `sw $r,SYM` as a macro and GAS expands it. Outside a delay
   slot it always becomes `lui $at,%hi ; sw %lo($at)` (HI16/LO16) whatever the attribute;
   inside a delay slot (.set nomacro: one instruction only) it becomes the $gp-relative
   form with a GPREL16 relocation, whose symbol must therefore be named GP + the retail
   displacement. `sda` only adds `.extern SYM,size`. */

/* func_L04_0040AC30 reaches its globals off $gp too, but its body is not matched
   yet; its marker stays in L04_00402D90.c and the attempt is in the wave-8 drafts. */

/* 0x001A8ED0 is absolute in func_L04_0040AC80 and $gp-relative here, so it is
   reached under a second name, declared small data.  The store to 0x001A8EE4 is
   written last in the source: cc1 emits the last store of a straight-line run
   first and then the source order, which is the order retail has. */
/* The record func_L04_004044B8 walks: the fields it uses, at the retail's offsets. */
/* 0x001A7B90 is the boot's resident data, reached off $gp in the delay slot. */
/* Updates the record's flag from the two point tests, prints the message when the
   record has one and its counter runs, then advances the counter and the value. */
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
extern void func_PAL_L04_00412AA0(void *);
extern int func_002A8600(void *,int,int,int);
extern int func_002A86E8(void *,void *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern int func_002A7820(int,int);
extern int func_002E5DA0(int,int,void *,int);
extern void func_PAL_L04_00410678(void *,void *,int,int);
extern int func_00282948(void *);
extern void func_0029FCC0(void *,int,void *);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CD8(void *,void *,void *);
extern void func_PAL_L04_003FD4F8(void *,void *,void *,int);
extern int func_002E5CF8(int,int,void *);
extern unsigned char *func_L04_0040EC80(void *,void *,void *,void *,void *,void *,float,float);
extern int func_L00_002D6900(int);
extern void * func_PAL_L04_003FE7B0(void *,void *,void *,float,float,float,float,float);
extern void * func_PAL_L04_003FFF88(void *,void *);
void func_PAL_L04_00413590(unsigned char *m)
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
 func_PAL_L04_00412AA0(m);
 if((D_L04_002C63C0[D_L04_001B090C].flags&1) && p->triggerList!=-1) {
  func_002A8600(&target,p->triggerList,0,0);
  while(target) {
   if(H(target,0xaa)==0xab8) {
    d=P(target,0x68);func_00282CF0(delta,target+16,m+16);
    if(!I(d,0) && func_L00_002EE290(delta)<1) {
     choice=p->state;state=choice;
     if(I(d,4)==-1) do {choice=func_002A7820(1,4);} while(state==choice && I(d,4)==-1);
     if(choice==4) {p->alternate=1;p->alternateTimer=choices.v[4];}
     else {int duration; p->state=choice;duration=choices.v[choice];p->timer=0;p->duration=duration;}
     if(m[0x20]!=3)func_002E5DA0(0,0,m,0xab8);
     func_PAL_L04_00410678(target+16,p->offset,8,0);I(d,0)=250;
    }
   }
   func_002A86E8(&target,target,0,0);
  }
 }
 if(p->alternate) {
  p->ready=0;
  if(func_00282948(&p->alternateTimer)) {p->alternate=0;p->ready=1;}
 }
 if(p->ready && func_00282948(&p->cooldown)) {p->ready=0;p->cooldown=33;}
 if(m[0x20]==3)return;
 switch(p->state) {
 case 0: break;
 case 1:
  if(func_00282948(&p->timer) && (D_00138320&5)) {
   p->timer=2;func_0029FCC0(m,((p->duration^1)&1),origin);
   if(p->elevated)func_002AF000(dir,p->length+0.6f,F(m,0xf8),-p->tilt);
   else func_002AF000(dir,p->length+0.6f,F(m,0xf8),-F(m,0xf4));
   func_00282CD8(temp,origin,dir);func_PAL_L04_003FD4F8(m,origin,dir,100);func_002E5CF8(7,0,m);
   if(func_00282948(&p->duration))p->state=0;
  }return;
 case 2: {
  unsigned char *target; float tilt;
  if(func_00282948(&p->timer) && (D_00138324&5)) {
   yaw=0;extra=0;p->timer=25;func_0029FCC0(m,((p->duration^1)&1),origin);tilt=F(m,0xf8);
   if(p->elevated)func_002AF000(dir,p->length+0.6f+p->height,tilt,yaw);
   else {func_002AF000(dir,p->length+0.6f+p->height,tilt,-F(m,0xf4));yaw=F(m,0xf4);}
   pitch=tilt;yaw-=0.3490659f;
   target=func_L04_0040EC80(m,origin,dir,&aimPitch,&aimYaw,&extra,0.78539824f,30);
   if(target) {
    func_00282CF0(delta,origin,target+16);
    if(func_L00_002EE290(delta)<25) {pitch=aimPitch;yaw=aimYaw;}
   } else {aimPitch=pitch;aimYaw=yaw;extra=0.2f;}
   func_L00_002D6900(47);func_00282CD8(temp,origin,dir);
   func_PAL_L04_003FE7B0(m,origin,target,aimPitch,aimYaw,extra,pitch,yaw);func_002E5CF8(8,0,m);
   if(func_00282948(&p->duration))p->state=0;
  }return; }
 case 3:
  if(func_00282948(&p->timer) && (D_00138324&5)) {
   p->timer=25;func_00282CC0(temp,m+16,p->offset);*(AttackQuad *)origin=*(AttackQuad *)temp;func_PAL_L04_003FFF88(m,origin);
   if(func_00282948(&p->duration))p->state=0;
  }
  break;
 }
}
