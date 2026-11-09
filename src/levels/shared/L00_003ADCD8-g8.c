/* func_L00_003ADCD8 (456 bytes, 27 places; not in the PAL catalogue).
 * Retail 003ADD64..003ADD70 is `lq v0,0(s6); lq v1,0(s5); sq v0,0(s5); sq v1,0(s6)` with
 * s6 = &a (sp+0x30) and s5 = &b (sp+0x34) in saved registers: a 16-byte swap helper applied to
 * two 4-byte pointer variables. On the EE both lq round down to sp+0x30, so retail rewrites the
 * same quadword and never swaps the pointers (an original bug). The swap helper below is private
 * to this unit (allowed by owner ruling, 9 November 2026); it uses $2 and $3 as qcopy uses $2.
 * The ignored result of func_002C3150 (it returns the particle pointer) puts the loop bound in
 * $v1 as retail has it.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int ref_L00_003ADCD8_0 __attribute__((sda));
extern float ref_L00_003ADCD8_1 __attribute__((sda));
extern float ref_L00_003ADCD8_2 __attribute__((sda));
extern int func_001163B0(void);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002A77E0(int);
extern void *func_002C3150(void *,void *,int,int,int,int,float);
static __inline__ void qswap(void *x, void *y) {
    __asm__ __volatile__("lq $2,0x0(%0)\n\tlq $3,0x0(%1)\n\tsq $2,0x0(%1)\n\tsq $3,0x0(%0)"
                         : : "r"(x), "r"(y) : "$2", "$3", "memory");
}
void func_L00_003ADCD8(char *a, char *b)
{
 float offset[4], position[4], delta[4];
 int i, count;
 unsigned char color;
 float distance;
 if(!b || *(short *)(b+0xAA)!=*(short *)(a+0xAA)) return;
 if((unsigned char)b[0x20]!=0xFE) { if((unsigned char)b[0x20]!=0xFD) {
 for(i=0;i<ref_L00_003ADCD8_0;) {
   if(func_001163B0()&1)
     qswap(&a, &b);
   i++;
   *(TI128 *)position=*(TI128 *)(a+0x10);
   count=func_00283CF0(func_002A7878(ref_L00_003ADCD8_1*0.5f,ref_L00_003ADCD8_1));
   color=count;
   func_00282CF0(delta,b+0x10,position);
   *(TI128 *)offset=*(TI128 *)delta;
   distance=func_00282DF0(offset);
   func_00282D30(offset,offset,func_002A7878(0,0.9f));
   func_00282CD8(delta,position,offset);
   func_00282F20(offset,offset,func_002A7878(1.0f/6.0f,distance/func_00283CE0(count*4)));
   { int c=func_002A77E0(255);
   func_002C3150(position,offset,0x604040FF,color,(unsigned char)c,0,ref_L00_003ADCD8_2); }
 }
}
}
}
