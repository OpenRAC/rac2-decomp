/* functional: high. From the near-miss draft (2224/2228 bytes; scheduling and register allocation differ); the draft wrote s+0x31C/0x31D and object+0x34 |= 2 on every call, where retail writes them only inside the s+0x302 bit 0 / s+0x31F branch (fixed). Placed in levels 09 and 20; names are level 09's. */
#include "common.h"
#define B(p,o) (*(u8 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define S(p,o) (*(s16 *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
typedef struct { char bytes[48]; } Config;
extern float D_L09_001B0F08 __attribute__((sda));
extern float D_L09_001B0F0C __attribute__((sda));
extern float D_L09_001B0F10 __attribute__((sda));
extern float D_L09_001B0F1C __attribute__((sda));
extern float D_L09_001B0F20 __attribute__((sda));
extern float D_L09_001B0F24 __attribute__((sda));
extern float D_L09_001B0F30 __attribute__((sda));
extern u8 D_L09_001B10D0[] SDATA(D_L09_001B10D0);
extern char D_L09_001A8F20[];
extern char *D_L09_001FE6C0[];
extern int func_00283CF0(float);
extern void func_002B60B0(char *,float,float,float,float);
extern float func_L01_003377C8(void *);
extern char *func_0029EFD0(int);
extern void func_0029FCC0(char *,int,void *);
extern void func_0029FC20(char *,int,void *);
extern void func_00283678(void *,void *);
extern void func_002A0F48(char *);
extern void func_002AB028(void *);
extern void func_002A10E8(char *);
extern void func_00282CF0(void *,void *,void *);
extern char *func_L02_0032B468(char *,int,void *,void *,int,int,void *,void *,float,void *);
extern int func_001163B0(void);
extern void func_002B3380(char *,void *,void *);
extern void func_L09_003F7C50(char *,int,int);
extern void func_L09_003F73E8(char *);
extern void func_002A7750(char *,int,int);
extern float func_002A89A8(void *,int,float);
extern int func_002A7820(int,int);
extern void func_L09_003F7518(char *,int,int,int);

void func_L09_003F7CE0(char *object)
{
 char *config;
 char *s=P(object,0x68), *child, *cs, *colors, *part, *slots, *slots2, *part2;
 float transform[16], pos[4];
 float a,b,c,d,angle;
 char *zero;
 int i, j, k, state;
 F(object,0x2C)*=D_L09_001B0F08;

 B(s,0x60)=14; F(s,0x6C)=0.36666667461395264f; F(s,0x70)=0.11666667461395264f;
 F(s,0x78)=0.008333333767950535f; F(s,0x7C)=0.004166666883975267f; F(s,0x8C)=0.4f;
 I(s,0x98)=9; B(s,0x62)=17; B(s,0xBC)=5; B(s,0xBD)=9; B(s,0xBF)=7; B(s,0xC2)=10; B(s,0xC3)=17;
 F(s,0x90)=F(s,0x310); F(s,0xF8)=0.45f; F(s,0x30)=1.7f;
 B(s,0x61)=18; B(s,0x66)=20; B(s,0x67)=255; B(s,0x2F)=8;
 F(s,0x74)=0.004166666883975267f; B(s,0x28)=3;
 I(s,0x2F8)=0; I(s,0x2F0)=0; I(s,0x2F4)=0;
 F(s,0x80)=0.7f; F(s,0x84)=0.7f; B(s,0xBE)=4; B(s,0x2A)=2; B(s,0x4D)=0; B(s,0x2E)=1;
 B(s,0x48)=func_00283CF0(25.0f); B(s,0x4A)=func_00283CF0(16.0f);
 B(s,0x1E8)=12; B(s,0x1E9)=11;
 angle=D_L09_001B0F24*0.00027777778450399637f;
 a=D_L09_001B0F0C*0.00027777778450399637f;
 b=D_L09_001B0F10*0.01666666753590107f;
 c=D_L09_001B0F1C*0.000004848137436842313f;
 d=D_L09_001B0F20*0.0002908882452175021f;
 F(s,0x100)=0.7f; F(s,0x10C)=1.0f; F(s,0x108)=0.5f; F(s,0x110)=0.7853982448577881f;
 F(s,0x130)=0.349065899848938f; F(s,0x12C)=angle; F(s,0x104)=0.5f;
 func_002B60B0(object,a,b,c,d);
 I(s,0x138)|=0x80; I(s,0x1DC)=0; F(s,0x1D4)=3.0f; H(s,0x1E4)=0; H(s,0x1E2)=0; I(s,0x1D0)=0;
 if(I(s,0x2BC)!=-1)func_L01_003377C8(D_L09_001FE6C0[I(s,0x2BC)]);
 if(I(s,0x2B4)!=-1)func_L01_003377C8(D_L09_001FE6C0[I(s,0x2B4)]);
 if(I(s,0x2B8)!=-1)func_L01_003377C8(D_L09_001FE6C0[I(s,0x2B8)]);
 child=func_0029EFD0(0xD0E);
 if(child){
 P(s,0x2F8)=child; H(child,0x32)=H(object,0x32); B(child,0x30)=B(object,0x30);
 *(u64 *)(child+0x38)=*(u64 *)(object+0x38); I(child,0x78)=I(object,0x78); B(child,0x31)=1;
 F(child,0x2C)*=D_L09_001B0F08;
 func_0029FCC0(object,0,child+0x10); qcopy(child+0xF0,object+0xF0);
 cs=P(child,0x68); zero=D_L09_001A8F20; *(Config *)(cs+0x20)=*(Config *)(s+0x20);
 F(cs,0x20)=F(s,0x20); H(cs,0x24)=H(s,0x24); B(cs,0x2F)=4;
 F(cs,0x30)=0.7f; B(cs,0x2A)=2; B(cs,0x2E)=1; B(cs,0x4A)=3; B(cs,0x4D)=1;
 P(cs,0x70)=object; B(cs,0x28)=B(s,0x28);
 func_0029FC20(object,0,transform); func_00283678(child+0xC0,transform);
 func_002A0F48(child); func_002AB028(child+0xC0); func_002A10E8(child);
 slots=s+0x2F0;
 for(i=0;i<2;i++,slots+=4){
 func_0029FCC0(P(s,0x2F8),i,pos); func_00282CF0(pos,pos,P(s,0x2F8)+0x10);
 part=func_L02_0032B468(P(s,0x2F8),0xD66,pos,zero,0,0,zero,zero,0.0f,zero);
 if(part && S(part,0xAA)==0xD66){ if(B(part,0x20)==254)continue; if(B(part,0x20)==253)continue; H(part,0x32)=H(object,0x32); P(slots,0)=part; H(part,0x34)|=2;}
 }
 colors=cs+0x50; config=cs+0x20;
 for(j=0;j<10;j++)B(colors,j)=D_L09_001B10D0[j];
 switch(func_001163B0()%3){
 case 0:B(cs+0x50,4)=func_00283CF0((2.0f/S(s,0x24))*255.0f); B(cs+0x50,8)=func_00283CF0((1.0f/S(s,0x24))*255.0f);break;
 case 1:B(cs+0x50,5)=func_00283CF0((2.0f/S(s,0x24))*255.0f); B(cs+0x50,9)=func_00283CF0((1.0f/S(s,0x24))*255.0f);break;
 case 2:B(cs+0x50,7)=func_00283CF0((2.0f/S(s,0x24))*255.0f);break;
 }
 func_002B3380(P(s,0x2F8),cs+0x50,config);H(P(s,0x2F8),0x7C)&=0xFCFF;
 }
 if(B(s,0x302)&1){ B(s,0x302)=(B(s,0x302)|1)&0xFD;
 if(B(s,0x31F)){
 B(object,0x31)=0; I(object,0x98)=0; H(object,0x34)=(H(object,0x34)|1)&0xEFFF;
 part=P(s,0x2F8);
 if(part && S(part,0xAA)==0xD0E && B(part,0x20)!=254 && B(part,0x20)!=253){
 H(part,0x34)|=1; B(P(s,0x2F8),0x31)=0; I(P(s,0x2F8),0x98)=0; H(P(s,0x2F8),0x34)&=0xEFFF;}
 slots2=s+0x2F0;
 for(k=1;k>=0;k--,slots2+=4){part2=P(slots2,0);if(part2 && S(part2,0xAA)==0xD66 && B(part2,0x20)!=254 && B(part2,0x20)!=253){H(part2,0x34)|=1; B(P(slots2,0),0x31)=0;}}
 B(s,0x31C)=0; B(s,0x31D)=1; H(object,0x34)|=2;
 }}
 if(F(s,0x4BC)<10.0f)F(s,0x4BC)=D_L09_001B0F30;
 func_L09_003F7C50(object,I(s,0x2B4),-1); func_L09_003F73E8(object); I(P(s,0x304),0)=0;
 if(I(s,0x2B0)!=-1){I(s,0x2DC)=I(s,0x2B0); I(s,0x138)|=4;func_002A7750(object,1,1);
 if(func_002A89A8(object+0x10,0,0.5f)<F(object,0x18)-F(s,0x10C)-0.1f)
 func_L09_003F7518(object,2,0,func_002A7820(5,10));
 else func_L09_003F7518(object,13,0,func_002A7820(10,20));
 }else{func_002A7750(object,5,1);state=func_001163B0()&1;func_L09_003F7518(object,state,0,func_002A7820(10,20));}
 I(s,0x2D8)=I(s,0x2D0);
}
