#include "include_asm.h"

#include "common.h"
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_002E59F8(int);
extern char D_00188660[], D_00189EA0[];
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern char D_00188660[];
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void func_002A7A00(void *,float,float);
extern float func_00283CE0(int);
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern void func_002A8C00(void *,void *,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_PAL_L18_00439B10(char *,int);
extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } D_L18_001BFC00;
extern int D_L18_001B2348 __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern char D_00188660[];
extern char D_00189EA0[];
extern void func_002E59F8(int);

void func_PAL_L18_004384D8(u8 *obj) {
 float a[4] __attribute__((aligned(16))),b[4] __attribute__((aligned(16))),v[4] __attribute__((aligned(16)));
 struct { float direction[4] __attribute__((aligned(16))); int owner,mode; u8 type,flags;u16 id; float distance;int enabled; } hit;
 u8 *s=P(obj,0x68),*other;float t;
 func_0029FCC0(P(s,0x7c8),0,a);func_0029FCC0(P(s,0x7c8),1,b);F(s,0x7e0)=0;
 switch(H(s,0x806)) {
 case 0:
  qcopy(s+0x610,a);qcopy(s+0x620,b);qcopy(s+0x6b0,b);qcopy(s+0x6c0,a);
  if(I(s,0x7f0)!=-1) {
   u8 *entry=D_00188660+I(s,0x7f0)*0x70;
   if(P(entry,0x88)==obj && entry[0x74])func_002E59F8(I(s,0x7f0));
  }
  I(s,0x7f0)=-1;break;
 case 1:
  qcopy(s+0x610,a);qcopy(s+0x620,b);qcopy(s+0x6b0,b);qcopy(s+0x6c0,a);
  func_002A8C28(obj,a,0x10001,0,1,0,0.2f,(float)s[0x34],1);
  if(H(s,0x804)>=6) {
   u8 *target=s+0x760;
   u8 *p3=s+0x6a0,*p2=s+0x690,*p1=s+0x680,*p0=s+0x670;
   int i;
   for(i=1;i>=0;i--) {
    func_002A7A00(p0,0.2792527f,0.34906593f);
    func_002A7A00(p1,0.2792527f,0.34906593f);
    func_002A7A00(p2,2,5);func_002A7A00(p3,2,5);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   }
   H(s,0x804)=0;H(s,0x806)=2;
   if(!func_002E59B0(obj,I(s,0x7f0)))I(s,0x7f0)=func_002E5CF8(1,4,obj);
   if(P(s,0x7bc))qcopy(target,P(s,0x7bc)+0x10);else qcopy(target,s+0x1f0);
  } else F(s,0x7e0)=func_00283CE0(H(s,0x804))/func_00283CE0(5);
  break;
 case 2:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  func_002A8C28(obj,a,0x10001,0,1,0,0.2f,(float)s[0x34],1);
  if(H(s,0x804)<5) {
   t=func_00283CE0(H(s,0x804))/func_00283CE0(4);
   F(s,0x620)=a[0]+(F(s,0x760)-a[0])*t;
   F(s,0x624)=a[1]+(F(s,0x764)-a[1])*t;
   F(s,0x628)=a[2]+(F(s,0x768)-a[2])*t;
   qcopy(s+0x6c0,s+0x620);
   func_00282CF0(v,s+0x620,s+0x610);func_00282F20(v,v,0.040000003f);
   func_002A8C00(&hit,obj,0x210001,v,(float)s[0x34]);
   hit.type=5;hit.flags=3;hit.id=*(u16 *)(obj+0xaa);
   if(func_002761F8(s+0x610,s+0x620,0,obj,&hit)) {
    func_PAL_L18_00439B10(s+0x620,15);qcopy(s+0x760,s+0x620);H(s,0x804)=0;
    if(D_L18_001BFC00.object) {
     float *point=D_L18_001BFC00.position;
     u8 *attached;
     H(s,0x806)=3;attached=D_L18_001BFC00.object;P(s,0x7e4)=attached;
     qcopy(s+0x620,point);qcopy(s+0x770,attached+0x10);
    } else H(s,0x806)=4;
   }
  } else {H(s,0x806)=4;func_PAL_L18_00439B10(s+0x620,10);}
  break;
 case 3:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  if(H(s,0x804)<43 && (other=P(s,0x7e4)) && other[0x20]!=254 && other[0x20]!=253) {
   func_00282CF0(v,other+0x10,s+0x770);func_00282CC0(s+0x620,s+0x620,v);
   qcopy(s+0x6c0,s+0x620);qcopy(s+0x770,P(s,0x7e4)+0x10);
   if((D_L18_001B2348&15)==(((int)obj>>8)&15))func_PAL_L18_00439B10(s+0x620,1);
  } else {
   DamoselBeamState *state=(DamoselBeamState *)s;
   state->attached=0;state->mode=4;state->timer=0;
  }
  break;
 case 4:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  if(H(s,0x804)<4) {
   t=func_00283CE0(H(s,0x804))/func_00283CE0(4);
   F(s,0x620)=F(s,0x760)+(a[0]-F(s,0x760))*t;
   F(s,0x624)=F(s,0x764)+(a[1]-F(s,0x764))*t;
   F(s,0x628)=F(s,0x768)+(a[2]-F(s,0x768))*t;
   F(s,0x6c0)=F(s,0x760)+(b[0]-F(s,0x760))*t;
   F(s,0x6c4)=F(s,0x764)+(b[1]-F(s,0x764))*t;
   F(s,0x6c8)=F(s,0x768)+(b[2]-F(s,0x768))*t;
  } else {
   H(s,0x804)=0;H(s,0x806)=0;
   { u8 *p3=s+0x6a0,*p2=s+0x690,*p1=s+0x680,*p0=s+0x670;
   int i;
   for(i=1;i>=0;i--) {
    func_002A7A00(p0,0.2792527f,0.34906593f);
    func_002A7A00(p1,0.2792527f,0.34906593f);
    func_002A7A00(p2,1,1.7f);func_002A7A00(p3,1,1.7f);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   } }
  }
 }
 func_L18_00434128(obj);
}
