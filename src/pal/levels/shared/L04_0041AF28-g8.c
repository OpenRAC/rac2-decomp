/* func_PAL_L04_0041AF28, the PAL copy of func_L04_004167B0: the same C, where the 60 Hz
 * times and rates become their 50 Hz values and the calls take PAL's own callees.
 * It needs -G8 and -g (the line labels give the nop pair before its div.s), so it has a
 * unit of its own; see config/cflags.txt. */
#include "common.h"
typedef int Quad1006 __attribute__((mode(TI)));
typedef struct { char pad0[0x24]; float scale; } Model1006;
typedef struct {
 char pad0[0x10];
 Quad1006 pos;
 char pad20[0x4];
 Model1006 * model;
 char pad28[0x4];
 float scale;
 u8 state;
 u8 enabled;
 s16 opacity;
 u16 flags;
 char pad36[0xc];
 u8 animState;
 u8 anim;
 char pad44[0x4];
 float animSpeed;
 char pad4c[0x14];
 u8 flags60;
 char pad61[0x5f];
 Quad1006 axis0;
 Quad1006 axis1;
 Quad1006 axis2;
 Quad1006 rotation;
} Object1006;

#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(void **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))

extern int D_L04_001B08F0 __attribute__((sda));
extern float func_00283248(float,float);
extern float func_00283B98(float,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282C48(float);
extern float func_00283BE0(float,float);
extern float func_002AA898(void *,float,void *,float,float,float,int);
extern char *D_L04_001B24DC;
extern float D_0018C2D8 NOT_SDA;
extern float D_00138288 NOT_SDA;
extern float D_0018A138 NOT_SDA;
/* Read as D_001A7A40[1]: an sda array at a nonzero offset is one unsplit lui+lbu pair. */
extern unsigned char D_001A7A40[] __attribute__((sda));
extern unsigned char D_00139605 NOT_SDA;
extern int D_L04_001A8FE8 __attribute__((sda));
extern Object1006 *D_L04_001B08F4 __attribute__((sda));
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_00282948(void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_L00_002EE290(void *);
extern void func_002AEC48(void *,void *,int,float,float);
extern void *func_0029EFD0(int);
extern void func_002B37E8(void *,void *);
extern void func_002AF1D0(void *,void *,int,int);
extern void func_0029FC20(void *,int,void *);
extern void func_002A91F0(void *,void *);
extern void func_PAL_L04_00410920(void *);
extern void func_PAL_L04_0041AB08(char *,void *,void *,float);

void func_PAL_L04_0041AF28(char *m,char *s) {
 float v[4] __attribute__((aligned(16)));
 float mat[16] __attribute__((aligned(16)));
 float a,b,c,target,scale,d,angle,period=0.6f; Object1006 *obj;
 if(!B(m,0xbc)) return;
 a=F(s,0x30c)+F(s,0x27c);
 if(a<0.10000001f) a=0.10000001f;
 b=F(s,0x308)*11.459153f;
 c=a*2.4999998f;
 d=F(s,0x308)*19.09859f;
 b*=func_00282C48(b);
 d=1.0f-(1.0f-d)*(1.0f-d);
 if(c>1.0f) c=1.0f;
 if(F(s,0x4c8)!=0.0f) {
  if(func_00282C48(F(m,0xf0)-F(s,0x4c8))<0.003f) F(s,0x4c8)=0;
  scale=5.0f;
  target=F(s,0x4c8);
 } else {
  scale=1.0f;
  target=(1.0f-c)*b+c*d;
  if(target>1.0f) target=1.0f;
  if(target<-1.0f) target=-1.0f;
  target*=-0.52359885f;
  if(B(m,0x20)!=3 && D_0018C2D8<0.2f) target=0;
 }
 func_002AA898(m+0xf0,target,s+0x300,scale*0.050400004f,0.648f,scale*0.03316126f,0);
 obj=(Object1006 *)(D_L04_001B24DC+(I(s,0x1dc)<<8));
 if(obj) {
  obj->scale=obj->model->scale*0.25f;
  obj->opacity=127; obj->enabled=1;
  obj->pos=*(Quad1006 *)(m+0x10); obj->rotation=*(Quad1006 *)(m+0xf0);
  obj->state=0;
  func_PAL_002A0F68(obj);func_002A0F48(obj);
  obj->flags|=6;
  if((obj->flags60&2) && (unsigned)(obj->animState-2)<4) func_PAL_002A7E68(obj,0,0,2);
  if(!I(s,0x36c)) {
   if(H(s,0x274) && (obj->anim==0 || obj->anim==2)) func_PAL_002A7E68(obj,1,0,10);
   if(!H(s,0x274) && obj->anim==1) {
    if(H(s,0x276)>=13) func_PAL_002A7E68(obj,2,0,2);
    else func_PAL_002A7E68(obj,0,0,5);
   }
  } else func_00282948(s+0x36c);
  if(obj->anim<2) {
   obj->animSpeed=F(s,0x30c)*3.0f/period;
   if(F(s,0x30c)>0.40000004f) obj->animSpeed*=3.0f;
  }
  if(B(m,0xbc)==5) {
   F(s,0x428)=D_00138288*-0.5f;
   F(s,0x424)=func_00282C48(F(m,0xf0))*-0.6f-F(m,0xf4);
  } else { F(s,0x424)=F(s,0x428)=0; }
  if(P(s,0x3b0) && D_L04_001A8FE8>=101) {
   func_00282CF0(v,(char *)P(s,0x3b0)+0x10,m+0x10);
   if(func_L00_002EE290(v)<9.0f) {
    angle=func_00283248(v[0],v[1]);
    angle=func_00283BE0(F(m,0xf8),angle);
    if(func_00282C48(angle)<1.5707964f) {
     if(I(s,0x3b4)<180) { I(s,0x424)=0; F(s,0x428)=-angle; }
     I(s,0x3b4)++;
    }
    if(I(s,0x3b4)>=601) I(s,0x3b4)=0;
   }
  }
  if(D_001A7A40[1]) F(s,0x430)=2.5f; else F(s,0x430)=1.0f;
  func_002AEC48(obj,s+0x3c0,0,0.115200005f,0.72f);
  if(!D_L04_001B08F4) {
   if(D_00139605) D_L04_001B08F4=func_0029EFD0(0x12df); else D_L04_001B08F4=func_0029EFD0(0x50a);
   if(D_L04_001B08F4) {
    func_002B37E8(D_L04_001B08F4,obj);
    D_L04_001B08F4->scale=D_L04_001B08F4->model->scale*0.25f;
    D_L04_001B08F4->flags|=0x106;
   }
  } else {
   func_002AF1D0(obj,D_L04_001B08F4,1,0);
   func_0029FC20(obj,1,mat);
   func_00282D30(v,mat+8,-0.03f);
   func_00282CC0((char *)D_L04_001B08F4+0x10,(char *)D_L04_001B08F4+0x10,v);
   qcopy_nc((char *)D_L04_001B08F4+0xc0,mat);
   qcopy_nc((char *)D_L04_001B08F4+0xd0,mat+4);
   qcopy_nc((char *)D_L04_001B08F4+0xe0,mat+8);
   func_PAL_002A0F68(D_L04_001B08F4);func_002A0F48(D_L04_001B08F4);
  }
 }
  if(D_L04_001B08F0) {
   *(Quad1006 *)v=*(Quad1006 *)(m+0x10);v[2]=D_0018A138;*(Quad1006 *)mat=*(Quad1006 *)(m+0x10);
   func_PAL_L04_0041AB08(m,mat,s+0x290,F(s,0x30c)+F(s,0x27c));
  }
  F(s,0x6c0)=func_00283B98(F(s,0x6c0),(F(s,0x30c)+F(s,0x27c)*4.0f)*0.2f+0.01f);
  func_002A91F0(s+0x450,s+0x6c0);
  func_PAL_L04_00410920(m);
}
