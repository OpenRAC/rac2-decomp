/* 8 November 2026 (Sonnet round, s22): no honest form exists. Retail spills params a/b to sp+0x30/0x34 (the stack home of the params) and swaps through their addresses, so the TI128 access over a 4-byte slot is the original bug itself. Declaring a real char *v[4] (16-byte, aligned) and swapping through &v[0]/&v[1] gives a different frame (0xA0, extra s7, v at sp+0) so 0/27 and further from retail. Declaration-order variants (delta/offset/position first, count before i; pa/pb initialised before the if; i++ moved to the loop end) all stay 0/27 with the same permutation. Best C stays s21/best1.c. */
/* 8 November 2026 (Sonnet round, s21): legal spellings of the swap, 0/27 but only a register permutation left. Two qcopy via a TI128 temp: 476 bytes (extra stack copy). Plain TI128 swap `t1=*pa; t2=*pb; *pb=t1; *pa=t2;` with `pa=(TI128 *)&a, pb=(TI128 *)&b` set inside `if(N>0){ i=0; ... do{...}while(i<N); }` gives retail's lq/lq/sq/sq on hoisted saved regs, 456 bytes, differing only in which s-regs hold i/&a/&b/delta (i s6 vs s3, &a s5 vs s6, &b s4 vs s5, delta s3 vs s4); init-order, store-order and pointer-decl-order variants do not change it. It also reads a TI128 through the address of a 4-byte pointer local (out of bounds, misaligned &b), so it would need an owner ruling even if the registers matched. Best C: scratch s21/best1.c. */
/* 8 November 2026: no RAC1/RAC4 twin. An lq/lq/sq/sq swap scan of both repos' asm finds only RAC1 func_L00_0024A798 (store_current_level_table_value, a different routine, not matched in C); RAC1's common.h has no swap helper either. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss. Final state: exact only with a new quadword-swap (qswap) helper in common.h; the owner ruled that helper out, so it stays a near miss. */
/* func_L00_003ADCD8 - 456 bytes. opus-1 (Claude Opus 5.5), task v2197, 3 November 2026.
 *
 * NOT LANDABLE: exact bytes need a quadword-swap helper that include/common.h
 * does not have. With the local probe helper below the body gives
 * 27 of 27 places (USA), 27 of 27 (v2.00); not in the PAL catalogue.
 * Flags: -O2 -G8 -ffunction-sections (put it in L00_003A8E28-g8.c, take the
 * marker out of L00_003A8E28.c; that file declares
 * `extern void func_L00_003ADCD8(void *, void *);` at func_L00_003ADEA0, which
 * must become (char *, char *) or the parameters cast).
 *
 * Retail 003ADD64..003ADD70 is `lq v0,0(s6); lq v1,0(s5); sq v0,0(s5); sq v1,0(s6)`
 * with s6 = &a (sp+0x30), s5 = &b (sp+0x34) hoisted into saved registers: an
 * asm with "r" operands, like qcopy, not a C TImode move (that would address
 * 0x30(sp) directly). On the EE both lq round down to sp+0x30, so the retail
 * "swap" rewrites the same quadword: it never swaps the pointers (an original
 * bug: a 16-byte swap helper applied to two 4-byte pointer variables).
 * The helper uses $2 and $3 as qcopy uses $2. Without it, C cannot produce this
 * sequence without out-of-bounds TImode dereferences (rejected 30 October 2026).
 * The ignored result of func_002C3150 (it returns the particle pointer, see
 * src/game/002C3150-qcopy.c) puts the loop bound in $v1 as retail has it.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int ref_L00_003ADCD8_0 __attribute__((sda));
extern float ref_L00_003ADCD8_1 __attribute__((sda));
extern float ref_L00_003ADCD8_2 __attribute__((sda));
extern int func_1163B0(void);
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
static __inline__ void qswap_probe(void *x, void *y) {
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
   if(func_1163B0()&1)
     qswap_probe(&a, &b);
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
