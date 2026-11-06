/* func_PAL_L05_003D5D90, the PAL copy of func_L05_003D2048: the same C, where rename func_L05_003D33E8 becomes func_PAL_L05_003D7130; rename-macro func_002BDCE8 becomes func_PAL_002BE9A8; rename-macro func_002BCB00 becomes func_PAL_002BD790; rename func_003067D8 becomes func_00282E48; rename func_003719A8 becomes func_002E5DA0; rename func_003062A0 becomes func_00282948; rename func_003068F8 becomes func_00282F20; rename func_00306630 becomes func_00282CC0; rename func_00332B50 becomes func_002A7878; rename func_00332AF8 becomes func_002A7820; rename func_00347040 becomes func_PAL_002BE9A8; rename func_00332AB8 becomes func_002A77E0; .... */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
extern void func_PAL_L05_003D7130(char *);
extern float func_00282E48(void *,void *);
extern void func_002E5DA0(int,int,void *,int);
extern int func_00282948(void *);
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float),func_002A7940(void);
extern int func_002A7820(int,int),func_002A77E0(int);
extern char *func_PAL_002BE9A8(void *,int,float,void *,int,int,float,float,float);
extern char *func_L00_00333F90(void *,void *);
extern void func_002AF000(void *,float,float,float);
extern int func_002AAFA0(int,int);
extern char *func_PAL_002BD790(void *,void *,int,int,int,int,int,int,int,float);
extern void func_L00_002E6EF8(void *,void *),func_L05_003D2618(void);
extern int D_L05_001B3000[] __attribute__((sda));
extern char D_L05_001B96C0[],D_L05_001B98F0[],D_L05_0024D020[];
extern float D_L05_001AFC94 __attribute__((sda));
void func_PAL_L05_003D5D90(char *obj)
{
 BurstVector v,small,offset,pos,velocity;
 char *s=*(char **)(obj+0x68);
 int *timers=D_L05_001B3000;
 int color1,color2,duration;
 float scale,a,b;
 if (*(unsigned char *)(obj+0x20)==0) {
  func_PAL_L05_003D7130(obj);*(unsigned char *)(obj+0x20)=1;
  timers[*(int *)s]=4;
  if(func_00282E48(obj+0x10,D_L05_001B96C0)>200.0f) *(float *)(s+4)=4;
  else if(func_00282E48(obj+0x10,D_L05_001B96C0)>100.0f) *(float *)(s+4)=2;
  else if(func_00282E48(obj+0x10,D_L05_001B96C0)>25.0f) *(float *)(s+4)=1;
  else if(func_00282E48(obj+0x10,D_L05_001B96C0)>0.0f) *(float *)(s+4)=0.5f;
  func_002E5DA0(10,0,obj,0xFBF);
 }
 if(!func_00282948(&D_L05_001B3000[*(int *)s]) && !*(int *)(s+8)) {
  int i;
  void *smallp=&small,*posp=&pos;
  for(i=0;i<4;i++) {
   int j;
   char *effect,*record;
   float lim;
   scale=D_L05_001AFC94*8.0f;
   qcopy(&v,D_L05_0024D020+*(int *)s*64+i*16);
   v.f[0]+=0.1f;
   func_00282F20(smallp,D_L05_001B98F0,0.24000001f);
   func_00282F20(&offset,D_L05_001B98F0,0.5f);
   func_00282CC0(&v,&v,&offset);
   scale*=3.0f;
   lim=10.0f;
   for(j=0;(float)j<(lim=10.0f);j++) {
    pos.f[0]=v.f[0];pos.f[1]=v.f[1];pos.f[2]=v.f[2];
    velocity.f[0]=(func_002A7878(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[1]=(func_002A7878(0,0.1f)+ -0.05f)**(float *)(s+4);
    velocity.f[2]=(func_002A7878(0,0.1f)+ -0.05f)**(float *)(s+4);
    duration=func_002A7820(-3,3);
    effect=func_PAL_002BE9A8(posp,duration,0,&velocity,0x7F204080,0,1,1.02f,scale*210000.0f);
    if(effect) {
     record=effect+0x20;
     *(unsigned short *)(effect+0xA)=83;
     *(unsigned char *)(effect+8)=func_002A77E0(255);
     *(unsigned char *)(effect+3)=0x48;
     *(int *)(record+4)=2;*(unsigned char *)(record+0xA)=127;
     *(unsigned char *)(record+0xB)=*(unsigned char *)(effect+0xA);
    }
   }
  }
  if(!*(int *)(s+8)) {
   int k;
   for(k=0;k<10;k++) {
    char *effect,*record;
    float lim;
    v.f[0]=func_002A7878(-0.3f,0.3f)**(float *)(s+4);
    v.f[1]=func_002A7878(-0.3f,0.3f)**(float *)(s+4);
    v.f[2]=func_002A7878(-0.3f,0.3f)**(float *)(s+4);v.f[3]=0;
    effect=func_L00_00333F90(obj+0x10,&v);
    if(effect) {
     record=effect+0x30;
     func_00282F20(&v,&v,1.0f);func_00282CC0(effect+0x10,obj+0x10,&v);
     qcopy(effect+0x20,obj+0x10);
     *(float *)(record+0xC)=1;*(float *)(effect+0x1C)=0.05f;*(float *)(effect+0x2C)=0.25f;
    }
   }
   for(k=0;k<10;k++) {
    char *effect;
    a=func_002A7940();b=func_002A7940();
    func_002AF000(&v,func_002A7878(7,10.5f)*(*(float *)(s+4)*0.020000001f),b,a);
    v.f[2]+=0.060000002f;
    color1=func_002AAFA0(0x4F007FFF,0);color2=func_002AAFA0(0x1F00007F,0);
    duration=func_002A7820(50,100);
    effect=func_PAL_002BD790(obj+0x10,&v,color1,color2,duration,1,-1,-1,0,40000.0f);
    if(effect) *(int *)(effect+0x2C)=0;
   }
  }
 }
 func_L00_002E6EF8(func_L05_003D2618,obj);
}
