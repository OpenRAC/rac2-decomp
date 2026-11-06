/* 6 November 2026: new best C below (692/692, 0/1 USA v1.01, 17 diff rows, reduced from 36).
 * Solved:
 *   1. FPR Allocation ($f0 vs $f1): loading `den = D_L14_001B039C` in both if (i < 2) and else
 *      arms turns `den` into a global pseudo across basic blocks, forcing both `t` and `den` into
 *      global-alloc. Lines 003DFC40..003DFC78 match retail 100% byte-for-byte.
 *   2. Tail Destination FPR: `den = u + t; uv[0] = den;` forces `add.s` destination into $f1 and
 *      the load of `*src` into $f0.
 *   3. Preheader Spills: `src = D_L14_001B03BC; src2 = D_L14_001B03B8;` placed immediately after
 *      `func_00281DE8` places 0xD0($sp) first and 0xD4($sp) second, matching retail 100%.
 *   4. GPR $s6: `n` is allocated $s6, matching retail 100%.
 *
 * Remaining differences (17 rows: 5 GPR + 12 scheduling rows):
 *   - Loop giv register tie ($fp vs $s7):
 *     Retail: $s0 is `v`, $s7 is `qzero_nc(&p.pos[i])`, $fp is byte offset 0, 16, 32, 48.
 *     Compiled: $s0 is `v`, $fp is `qzero_nc`, $s7 is byte offset.
 *     Both pseudos have 7 refs. In retail, `offset` was initialized at 003DFB48 (daddu $fp, 0)
 *     before `pointer` at 003DFB4C (daddu $s7, $s0), giving `offset` live_length 160 vs 156,
 *     which lowered its priority (875 vs 897) so `pointer` got $s7 and `offset` got $fp.
 *     In our code, `pointer` is initialized at 003DFB2C (addiu $fp, $sp, 0x40), so `offset`
 *     has shorter live_length and gets $s7.
 *   - Loop latch scheduling: the swap of $fp and $s7 shifts the Giv increments (003DFCA4 vs 003DFC98),
 *     which cascades into minor instruction reorderings with swc1 in the loop tail.
 * Profile: src/levels/14_aranos_prison/L14_003DFA60-g32.c with flags
 *   -O2 -G32 -Wa,-G32 -ffunction-sections -mno-split-addresses
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
 float angle,t,u,num,den;
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
  v[0]=D_L14_001B03A8;
  v[3]=1.0f;
  v[2]+=D_L14_001B03B0;
  p.color[i]=D_L14_001B03AC;
  uv=p.uv[i]; u=*src2; uv[0]=u;
  if(i<2){den=D_L14_001B039C;t=(float)n;t=t/den;} else{den=D_L14_001B039C;t=(float)(n+1);t=t/den;}
  den=u+t;
  p.uv[i][1]=*src;
  uv[0]=den;
  src+=2;
  src2+=2;
 }
 func_00280B90(&p,mtx,0);
}
