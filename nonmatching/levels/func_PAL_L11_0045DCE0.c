/* func_PAL_L11_0045DCE0 (2,500 bytes), NONMATCHING: the PAL copy of func_L11_004580E8
 * (src/levels/11_joba/L11_004580E8-fighter-g8.c). Build as its own unit with
 * -O2 -G8 -ffunction-sections -g -frac2-sched-call-addr-float -frac2-la-float-vars-last
 * -fno-rerun-loop-opt. 50 Hz changes: gravity 1/360 -> 0.004, particle life 120 -> 100, spark
 * frame count n -> (n * 5 + 2) / 6, case 5 rates and the spin clamp (0.004..0.12) rescaled.
 * 2500/2500 bytes, 0/1 places. A `Quad *c` for scratch.v.c makes gcse PRE number sp+0x40
 * before sp+0x30, so the preheader's integer order (i, sp+0x40, sp+0x30, 6) now matches.
 * Left: (1) FP constants in the preheader: retail 1.0, 0.3333, 45000; ours 0.3333, 45000, 1.0.
 * The three loads tie on every sched1 key (priority, weight, class, dependent count), so luid
 * decides: retail's order means 1.0 was hoisted by loop pass 1 (like 6) and 0.3333/45000 by the
 * -frerun-loop-opt pass. Plain constants with the rerun pass do that, but the rerun pass then
 * also hoists high(&D_L11_001A8F20) (cse2 stretches its life to 7) and leaves 45000 (life 1).
 * (2) Call setup: at sched1 cycle 56, high(&D_L11_001A8F20) (insn 320) and the split
 * lui $a3,0x8080 (1552) tie on priority/weight/class/deps; luid puts the high first, retail
 * issues lui $a3 first and the high just before its lo_sum; mov.s $f14 follows from that.
 * Swept singly: 57 sched/la/loop/ga switches and 55 cse/gcse/reload switches, plus
 * -mno-split-addresses and the rerun-loop switches: none improves.
 * The never-taken `skip` test keeps gcse PRE from hoisting &D_L11_001A8F20's %hi into $fp;
 * third as a user variable lets the first loop pass hoist 0.3333 so -fno-rerun-loop-opt keeps
 * the second pass from hoisting that %hi.
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
void func_PAL_L11_0045DCE0(char *p) {
 char *q=*(char **)(p+0x68),*other,*entry;
 union { struct { float a[4],b[4],c[4]; } v; char damage[48]; } scratch;
 float f; int i,n; unsigned int r,g,blue;
 switch(*(u8 *)(p+0x20)) {
 case 0: {
  *(u8 *)(q+0x148)=func_00283CF0(15);*(u8 *)(q+0x14A)=func_00283CF0(4);
  {float speed, max, damping, turn, gravity, limit;
  *(float *)(q+0x160)=func_002A7878(-*(float *)(q+0x160),*(float *)(q+0x160))*0.017453294f;
  *(u8 *)(p+0x30)=128;*(int *)(q+0x24)=0;
  speed=0.3f;max=0.75f;damping=0.5f;turn=1.134464144706726f;gravity=0.004f;limit=0.523598849773407f;
  *(u8 *)(q+0x128)=3;*(int *)(q+0x130)=0;
  *(float *)(q+0x4C)=gravity;
  *(float *)(q+0x20)=speed;*(float *)(q+0x28)=max;*(float *)(q+0x2C)=damping;*(float *)(q+0x30)=turn;*(float *)(q+0x50)=limit;*(float *)(q+0x54)=0.1f;
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
   int skip=0; /* FAKEMATCH: never-taken test hides &D_L11_001A8F20 from gcse PRE */
   for(i=0;i<3;i++) {float third=0.3333f,scale=45000; /* FAKEMATCH: set-once copies so loop pass 1 hoists both */
    {Quad *c=(Quad *)scratch.v.c;*c=*(Quad *)(p+0x10);func_L00_0031D670(scratch.v.b,c,scratch.v.a,(float)i*third);}
    n=func_002A77E0(6);if(func_002A77E0(2))n=-n;
    f=func_00283CE0((D_L11_001B1F84*5+2)/6);
    {
    float t=(float)*(s16 *)(q+0x16C)/f*scale+5000;
    Particle *particle;
    if(skip)continue; /* FAKEMATCH: dead branch, see skip */
    particle=func_002BDCE8(scratch.v.b,n,0.025f,1,1,&D_L11_001A8F20,0x80808080,0,t);
    if(particle) {ParticleAttributes *attributes;particle->lifetime=100;attributes=&particle->attributes;attributes->mode=2;attributes->alpha=127;attributes->duration=(u8)particle->lifetime;}
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
   *(float *)(q+0x160)=f;func_002B60B0(p,(t+t)*0.0004000000189989805f,t*0.020000001415610313f,0.0016755163669586182f,0.12566372752189636f);
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
  f=func_00282E20(q+0xC0);min=0.004000000189989805f;max=0.12000000476837158f;
  if(f<min)f=min;if(f>max)f=max;
  f=f-min;
  *(float *)(p+0xF4)=func_00283B98(
    ({float fraction=f/0.11600000411272049f;
      (fraction*7+1)*0.017453294f;}),*(float *)(p+0xF4));
 }
 if(*(u8 *)(p+0x20)>=2)func_L00_002E6EF8(func_L11_00458C38,p);
 if(*(void **)(p+0xB8)) {other=func_L11_004417E8(*(void **)(p+0xB8));if(*(float *)(p+0x18)<*(float *)(other+8)-1){*(int *)(p+0x98)=0;*(u16 *)(p+0x34)=(*(u16 *)(p+0x34)|0x41)&0xEFFF;func_002A7750(p,1,-1);}}
 if(func_002A9640(p,0x10000,0))func_002A7750(p,6,-1);
 *(u8 *)(p+0xA8)=255;if(*(u16 *)(p+0x96)<0xFFFF)(*(u16 *)(p+0x96))++;
}
