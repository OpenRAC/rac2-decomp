/*
 * func_L14_003DFA60 (692 bytes) -- tier opus-2, NOT MATCHING.
 * Best check.py: "14_aranos_prison: instruction at +0x10 differs", 0 of 1 places;
 * size 692/692 bytes; cdiff: 64 of 174 rows differ (several are relocation-only).
 * Profile: a unit of its own, e.g. src/levels/14_aranos_prison/L14_003DFA60-g32.c with
 *   config/cflags.txt line "<unit>\t-O2 -G32 -Wa,-G32 -ffunction-sections"
 *   (D_L14_001B0394..03B8 gp-relative, D_03BC absolute; declarations below).
 * Established: TI-mode Vec union + qzero_nc keep the Y store address unfolded
 *   (addiu sp,0x40; addu; swc1 4); the ternary gives the bnez sense; quotient t in
 *   the arms + "uv[0]=u+t" in the join removes the extra lw 0xD0 reload (reload's
 *   find_equiv_reg gives up on any MEM store between the V-table load and src+=2;
 *   the earlier "t=uv[0]+q per arm; uv[0]=t" form kept retail arm registers but was 696 B).
 * Still differs:
 *   1. n is in s7 (retail s6); the packet pointer starts in fp with the qzero giv
 *      in s0 (retail: v in s0, copy in s7, i*16 giv in fp); the preheader stores the
 *      0xD4 spill before 0xD0 (retail 0xD0 first).
 *   2. arm 1 (i<2) allocates cvt->f1, D_039C->f0, so its div.s does not cross-jump
 *      with arm 2 and the 0xD0 load fills arm 1's b delay slot.
 *   3. the sum u+t lands in f0 (retail f1) and the U store is scheduled late.
 * No declaration initializers; "u" is a local holding *src2 before its uses.
 */
#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
typedef union { float f[4]; Quad128 q; } Vec;
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; char tail[24]; u64 regs; } DrawPacket;
extern unsigned char *D_L14_001B259C_base[] __asm__("D_L14_001B259C") __attribute__((sda));
extern unsigned char D_001A7A44[] __attribute__((sda));
extern float D_L14_001B03BC[];
extern float D_L14_001B03B8[8] __attribute__((sda));
extern int D_L14_001B0394 __attribute__((sda));
extern float D_L14_001B039C __attribute__((sda));
extern float D_L14_001B03A0 __attribute__((sda));
extern float D_L14_001B03A4 __attribute__((sda));
extern float D_L14_001B03A8 __attribute__((sda));
extern int D_L14_001B03AC __attribute__((sda));
extern float D_L14_001B03B0 __attribute__((sda));
extern int func_L03_004197A8(void *);
extern void func_00283658(void *,void *);
extern void func_L03_002EFB60(void *,void *,float);
extern void func_00281DE8(void *,int,int,int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *,void *,float);
extern void func_00280B90(void *,void *,int);
void func_L14_003DFA60(char *self) {
 float mtx[16] __attribute__((aligned(16)));
 DrawPacket p __attribute__((aligned(16)));
 int n,i;
 float angle,t,u;
 float *v,*uv,*src,*src2;
 n=func_L03_004197A8(D_L14_001B259C_base[0]+(*(int *)(*(char **)(self+0x68)+4)<<8));
 func_00283658(mtx,self+0xC0);
 func_L03_002EFB60(mtx,mtx,*(float *)(self+0x2C)/ *(float *)(*(char **)(self+0x24)+0x24));
 qcopy(mtx+12,self+0x10);
 mtx[15]=1.0f;
 func_00281DE8(p.pos,D_L14_001B0394,0,0x80);
 src=D_L14_001B03BC;
 src2=D_L14_001B03B8;
 for(i=0;i<4;i++) {
  v=p.pos[i].f;
  angle=func_00283B98(D_L14_001B03A0*0.01745329424738884f,(float)i*1.5707964f);
  v[0]=func_00283180(angle)*D_L14_001B03A4;
  v[1]=func_00283198(angle)*D_L14_001B03A4;
  v[2]=0;
  qzero_nc(&p.pos[i]);
  p.pos[i].f[1]=(i>=2)?-1.0f:1.0f;
  if(i&1)v[2]=-1.0f; else v[2]=1.0f;
  if(D_001A7A44[0])v[1]=-v[1];
  func_00282F20(v,v,D_L14_001B03A4);
  v[2]+=D_L14_001B03B0;
  v[0]=D_L14_001B03A8;
  v[3]=1.0f;
  p.color[i]=D_L14_001B03AC;
  uv=p.uv[i];
  u=*src2;
  uv[0]=u;
  if(i<2)t=(float)n/D_L14_001B039C;
  else t=(float)(n+1)/D_L14_001B039C;
  uv[0]=u+t;
  p.uv[i][1]=*src;
  src+=2;src2+=2;
 }
 func_00280B90(&p,mtx,0);
}
