/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, task v0876: USA v1.01 game -O2 -G8 -ffunction-sections.
 * Best check.py: 1320/1320 bytes, 0/1 places. Four instructions at
 * +0x3DC..+0x3E8 differ: old timer is in v1 and decremented timer in v0;
 * retail assigns these oppositely. Other non-relocated instructions agree.
 * Corrected float literals, paired min/max array views, explicit GP aliases,
 * separate spawn-result lifetimes, player-base derivation and the canonical
 * particle-call integer/FP interleaving recover all earlier differences.
 * Direct initialization-result store matches the case-0 store order. Use a
 * u8 dereference (not an unsigned cast on char) for the enabled byte.
 * Signed/ushort timer locals and early break tie. -mno-split-addresses fixes
 * FP scalar loads but disrupts integer bases; paired macro views avoid that.
 * No linked build: address bindings remain unqualified. Declarations below.
 */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern float func_002A7940(void),func_002A78D8(float,float),func_00283B98(float,float),func_00283198(float),func_00283248(float,float),func_00282E80(void *,void *),func_L02_002F21C0(void *,void *);
extern void func_002A7750(char *,int,int),func_002833F0(void *,void *),func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *);
extern char *func_002A9640(char *,int,int);
extern void func_002AAA00(void *,void *,int,float,float,float,float);
extern void func_0029F390(char *);
extern int func_002B3868(char *),func_002A7820(int,int),func_002A77E0(int);
extern void func_00282F20(void *,void *,float);
extern void func_L01_002E1680(void *,void *,int,int,int,float,float,float);
extern int func_002E5CF8(int,int,char *);
extern char *func_L00_00326620(char *,int,int);
extern void func_L00_0032A258(char *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_0029F338(char *);
extern void func_L00_00324F18(char *,void *,float,float,float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern char D_00189EA0[];
extern float D_L03_001B0AE0_1[] MACRO_ADDR, D_L03_001B0AE8_1[] MACRO_ADDR, D_L03_001B0B30_1[] MACRO_ADDR;
extern float D_L03_001B0AE0 __attribute__((sda));
extern float D_L03_001B0AE8 __attribute__((sda));
extern float D_L03_001B0AF0 __attribute__((sda));
extern float D_L03_001B0AF4 __attribute__((sda));
extern float D_L03_001B0AF8 __attribute__((sda));
extern float D_L03_001B0B30 __attribute__((sda));
extern char D_L03_001B0B10_GP[] SDATA(D_L03_001B0B10), D_L03_001B0B08_GP[] SDATA(D_L03_001B0B08), D_L03_001B0B00_GP[] SDATA(D_L03_001B0B00);
extern char D_L03_001A8F20[] __attribute__((sda));
extern int D_L03_001B0B40 __attribute__((sda));
void func_L03_003E1C88(char *obj)
{
 float v[4] __attribute__((aligned(16)));
 float angles[4] __attribute__((aligned(16)));
 char mat[0x30] __attribute__((aligned(16)));
 char *vars=*(char **)(obj+0x68);
 float a;
 switch ((unsigned char)obj[0x20]) {
 case 0:
  qcopy(vars,obj+0x10);
  *(int *)(obj+0x48)=0;obj[0x42]=0;*(int *)(obj+0x44)=0;obj[0x43]=1;
  *(float *)(vars+0x10)=func_002A7940();*(float *)(vars+0x14)=func_002A7940();
  *(float *)(vars+0x18)=func_002A78D8(D_L03_001B0AE0,D_L03_001B0AE0_1[1])*0.0002908882452175021f;
  *(float *)(vars+0x1C)=func_002A78D8(D_L03_001B0AE8,D_L03_001B0AE8_1[1])*0.0002908882452175021f;
  *(float *)(vars+0x3C)=0.10471977f;*(float *)(vars+0x38)=0.0017453294713050127f;
  func_002A7750(obj,1,-1); break;
 case 1:
  if (!*(u8 *)(obj+0x31)) break;
  *(float *)(vars+0x10)=func_00283B98(*(float *)(vars+0x10),*(float *)(vars+0x18));
  *(float *)(vars+0x14)=func_00283B98(*(float *)(vars+0x14),*(float *)(vars+0x1C));
  *(float *)(obj+0xF0)=D_L03_001B0AF0*func_00283198(*(float *)(vars+0x10));
  *(float *)(obj+0xF4)=D_L03_001B0AF4*func_00283198(*(float *)(vars+0x14));
  *(Quad *)angles=0;angles[0]=*(float *)(vars+0x10);angles[2]=*(float *)(vars+0x14);
  *(Quad *)v=*(Quad *)angles;func_002833F0(mat,v);
  func_00282D30(obj+0x10,mat+0x10,D_L03_001B0AF8);
  func_00282CC0(obj+0x10,obj+0x10,vars);
  if (!*(int *)(vars+0x30)) {
   char *p=func_002A9640(obj,0x4010000,0);
   if(p){qcopy(vars+0x20,p+0x10);func_002A7750(obj,2,-1);}
  }
  if(func_L02_002F21C0(obj+0x10,D_00189EA0)<200.0f) {
   char *playerbase=D_00189EA0-0x80;
   a=func_00283B98(func_00283248(*(float *)(playerbase+0x80)-*(float *)(obj+0x10),*(float *)(playerbase+0x84)-*(float *)(obj+0x14)),1.5707964f);
   func_002AAA00(obj+0xF8,vars+0x34,0,a,*(float *)(vars+0x38),*(float *)(vars+0x38),*(float *)(vars+0x3C));
   a=func_00283248(func_00282E80(D_00189EA0,obj+0x10),*(float *)(obj+0x18)-*(float *)(playerbase+0x88))*0.63661975f;
   if(a>1.0f)a=1.0f;else if(a<0.0f)a=0.0f;
   *(float *)(obj+0x44)=1.0f-a;func_0029F390(obj);
  } break;
 case 2:
  if(func_002B3868(obj)) {
   *(unsigned short *)(obj+0x96)=func_002A7820(20,30);
   *(float *)(obj+0xF0)*=4.0f;*(float *)(obj+0xF4)*=4.0f;
   func_00282F20(vars+0x20,vars+0x20,1.0f/6.0f);
  }
  *(Quad *)v=0;v[2]=1.0f/15.0f;
  if(!func_002A77E0(2))func_L01_002E1680(obj+0x10,v,1,0x40202020,1,0.0066666672937572f,0.9f,1.02f);
  *(float *)(obj+0xF8)=func_00283B98(*(float *)(obj+0xF8),0.20943954586982727f);
  func_00282CC0(obj+0x10,obj+0x10,vars+0x20);
  { int timer=*(unsigned short *)(obj+0x96); *(unsigned short *)(obj+0x96)=timer-1; if(!timer)func_002A7750(obj,3,-1); }
  break;
 case 3: {
  char *p;
  func_002E5CF8(0,0,obj);p=func_L00_00326620(obj,0x113D,(unsigned char)obj[0x30]);
  if(p){func_L00_0032A258(p,D_L03_001B0B10_GP,D_L03_001B0B08_GP,D_L03_001B0B00_GP,65535,1,D_L03_001B0B40,6,65535,255,0);func_0029F338(p);}
  func_L00_00324F18(obj,v,D_L03_001B0B30,D_L03_001B0B30_1[1],D_L03_001B0B30_1[2]);
  func_002ABBB8(obj,D_L03_001A8F20,v,0.0f,0.0f,10,5,15,0.0f,0.0f,9.0f,*(float *)(obj+0x2C)*30.0f,-1,0.0f,0,0,-1,0,0x810001);
  func_0029F338(obj);break;
 }
 }
}
