/* func_0030CAD0 - 508 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft 500 B vs 508 (2 instructions). Needs new file
   src/game/00308600-g8-qcopy.c + cflags `-O2 -G8 -ffunction-sections
   -frac2-qcopy -frac2-qcopy-barrier`, marker removed from 00308600.c.
   Loop shape, registers (s0..s6), the 8 separate `lui at; sh` stores (8
   scalar shorts, source order = retail store order), the -1 short array loop
   with its own counter k all match.
   Remaining: retail builds the loop's pointer bases in two steps: `lui a1;
   addiu a1,-0x6670` then `addiu s3,a1,4` (and s4=v1+0x10, s5=v0+4, s0=a0 copy
   then s2=s0+0x10) = 2 extra instructions; mine folds the +4/+0x10 into the
   %lo (`lui; addiu s3,a0,4`). Also mine assigns the two int pointers s5/s3
   the other way round (first store goes to s5, retail s3).
   Tried: index form (no strength reduction -> far off), explicit pointer walk
   (right loop), declaration order permutations, separate counters.
   func_0030A188 is the same family (see its handoff): same loop, plus 2
   symbols for the chain array.
   Second pass: size now MATCHES (508) by writing the base pointers as `c =
   ref_09; c++;` (and d, e) instead of `ref_09 + 1`; that gives the separate
   `addiu x,4` step. Remaining diffs are only register numbering of the 6 loop
   variables (retail p=s0,i=s1,q=s2,c=s3,d=s4,e=s5; mine
   i=s4,p=s3,q=s5,c=s2,d=s1,e=s0) plus ~3 store-order lines in the sh block.
   Permuting the init order of p/c/d/e did not fix it (tried all 24).
   The same `x++` trick should be tried in func_0030A188. */

#include "include_asm.h"
#include "common.h"

extern int D_001A79F0;
extern int D_001A8BB0;
extern char D_001C1490[];
extern char D_001C14E0[];

extern int ref_L00_0030CAD0_00 __attribute__((sda));
extern int ref_L00_0030CAD0_01 __attribute__((sda));
extern float ref_L00_0030CAD0_02 __attribute__((sda));
extern int ref_L00_0030CAD0_03 __attribute__((sda));
extern int ref_L00_0030CAD0_04 __attribute__((sda));
extern int ref_L00_0030CAD0_05 __attribute__((sda));
extern int ref_L00_0030CAD0_06 __attribute__((sda));
extern int ref_L00_0030CAD0_07 __attribute__((sda));

extern float ref_L00_0030CAD0_08[][4];
extern int ref_L00_0030CAD0_09[];
extern float ref_L00_0030CAD0_10[][4];
extern int ref_L00_0030CAD0_11[];

extern int D_001B24A0;
extern short D_001B2480[4];
extern short D_001B2490;
extern short D_001B2492;
extern short D_001B2494;
extern short D_001B2496;
extern short D_001B2498;
extern short D_001B249A;
extern short D_001B249C;
extern short D_001B249E;

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);

void func_0030CAD0(char *object)
{
    char *owner = *(char **)(object + 0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    int i;
    int k;
    float (*p)[4];
    float (*q)[4];
    int *c;
    float (*d)[4];
    int *e;

    if (D_001A79F0 == 1 && D_001A8BB0 == 2)
        owner = D_001C1490;
    if (D_001A79F0 == 20 && D_001A8BB0 == 2)
        owner = D_001C14E0;
    if (ref_L00_0030CAD0_00 == 0)
        return;
    D_001B24A0 = ref_L00_0030CAD0_01;
    ref_L00_0030CAD0_00 = 0;
    ref_L00_0030CAD0_03 = 0;
    func_00282CF0(a, owner + 0x10, owner);
    func_00282F20(b, a, ref_L00_0030CAD0_02 * 0.05f);
    qcopy(ref_L00_0030CAD0_08[0], owner);
    p = ref_L00_0030CAD0_08;
    q = p + 1;
    c = ref_L00_0030CAD0_09;
    d = ref_L00_0030CAD0_10;
    e = ref_L00_0030CAD0_11;
    c++;
    d++;
    e++;
    for (i = 0; i < 19; i++) {
        func_00282CC0(q, p, b);
        p++;
        q++;
        *c++ = 0;
        func_00282C88(d);
        d++;
        *e++ = 0;
    }
    for (k = 0; k < 4; k++)
        D_001B2480[k] = -1;
    D_001B2494 = 8;
    D_001B2496 = 4;
    D_001B249E = 2;
    D_001B2490 = 8;
    D_001B2498 = 4;
    D_001B2492 = 4;
    D_001B249A = 2;
    D_001B249C = 4;
    ref_L00_0030CAD0_05 = 0;
    ref_L00_0030CAD0_06 = 0;
    ref_L00_0030CAD0_07 = 0;
}
