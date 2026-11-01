/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* opus-1 (Claude Opus 5.5, xhigh), 31 October 2026: -O2 -G0 -ffunction-sections, own unit.
 * Best: 480/480 bytes, 0/28 USA v1.01 places, 2 instructions differ: the x-offset
 * sum's second operand, retail lwc1 $f2/add.s $f0,$f0,$f2, here $f1. Every other word
 * agrees, including the mode/offsetY load order the earlier drafts could not reach.
 * Declaring offsetY const gives that order: its load loses the anti-dependence on the
 * x store, so its priority falls from 15 to 10 and sched2 runs scale, mode, offsetY.
 * Without const, priorities tie and offsetY wins on dependent count (3 against 2).
 * Remaining: px takes $f2 only if offsetY's qty is born in the insn right after the add
 * at local-alloc (find_free_reg's fake_death). So sched1 must order add, offsetY, mode
 * while sched2 orders add, mode, offsetY, and both passes compute the same priorities.
 * Tried with no improvement: x read in an earlier block (kept across the calls in $f20;
 * global pseudos get no REG_EQUIV from a load, so update_equiv_regs does not sink it).
 * Next: a source shape that frees one memory slot, or delays the add, in sched1 only.
 * Declarations included below. No linked build claimed.
 */
#include "common.h"
extern void func_00335E68(char *,int);
extern float *func_00335E10(char *);
extern void func_00336B90(char *,int),func_00336B98(char *,int);
extern void func_00336498(char *,unsigned,unsigned),func_003364B0(char *,unsigned,unsigned);
extern void func_0026F808(int *,int *,int *);
extern int D_001A7A00 MACRO_ADDR, D_001A7A0C MACRO_ADDR;
typedef struct { char pad[0x22b4]; unsigned char mode; char gap[0x277]; int end, start; } StatusGlobals;
extern StatusGlobals D_00189E20;
extern float ref_L00_0034AA30_00 MACRO_ADDR,ref_L00_0034AA30_02 MACRO_ADDR;
extern const float ref_L00_0034AA30_01 MACRO_ADDR;
extern int ref_L00_0034AA30_03 MACRO_ADDR;
void func_0034AA30(char *o)
{
 float *out=func_00335E10(o+0xf4);
 if(D_001A7A00<80) {
  struct { int a,b,c; } range;
  float x, y, scale, offsetY;
  int iy;
  int mode;
  func_00335E68(o+0xf4,1);
  range.c=0;range.a=D_00189E20.start;range.b=D_00189E20.end;
  if(!range.a)func_0026F808(&range.a,&range.b,&range.c);
  func_00336B90(o+0xf4,range.b-range.a);
  func_00336B98(o+0xf4,(D_001A7A0C>>5)-range.a);
  x=ref_L00_0034AA30_00+(*(float **)(o+8))[0];
  scale=ref_L00_0034AA30_02;
  mode=ref_L00_0034AA30_03;
  offsetY=ref_L00_0034AA30_01;
  out[0]=x;
  y=(offsetY+(*(float **)(o+8))[1])*scale+0.5f;
  if(mode==1)iy=(int)(y+-5.0f);
  else iy=(int)y;
  out[1]=iy;
  if(D_00189E20.mode==1) {
   func_00336498(o+0xf4,0x60808080,0x60808080);
   func_003364B0(o+0xf4,0x40808080,0x40808080);
  } else {
   func_00336498(o+0xf4,0x8049c1ff,0x80001eff);
   func_003364B0(o+0xf4,0x50f0c070,0x50f0c070);
  }
 } else func_00335E68(o+0xf4,0);
}
