/* func_L00_003AB6F0 - 448 bytes.  Worker attempt, 27 October 2026 (draft below).

   444 B vs 448 B; code is right, only callee-saved register assignment
   differs.
   Retail: s0 = rand/p, s1 = q (p+0x20), s2 = loop counter, s3=0x7F, s4=arg,
   s5=2, s6=10 (loop1); s7=2 in loop2.
   Mine: v in s2, counter s3, 0x7F s5, 2 s6, 10 s7 (one more register live, so
   +frame 0x40 vs 0x50 and order of sd/addiu in prologue).
   Tried: for vs do-while(--i>=0); local declaration order (4 permutations); q
   as sub-struct pointer computed before the 2EF250 call; MACRO_ADDR on data
   array (needed: gives lui/addiu per use).
   Needs: include common.h at top of the file (MACRO_ADDR). */

#include "common.h"
extern char D_L00_001A8F20[] MACRO_ADDR;
extern int func_0031A728(int range);
extern int func_002EF250(float);
extern char *func_00334888(int, int, char *, int, int, float, float, float, float);

typedef struct {
    int w0;
    int w4;
    char pad8[2];
    unsigned char bA;
    unsigned char bB;
} SparkSub;

typedef struct {
    char pad0[8];
    unsigned char b8;
    unsigned char b9;
    short sA;
    char pad0C[0x14];
    SparkSub sub;
} Spark;

void func_L00_003AB6F0(int unused, int arg)
{
    int i;
    Spark *p;
    SparkSub *q;
    int v;

    i = 1;
    do {
        v = func_0031A728(16);
        p = (Spark *)func_00334888(arg, func_0031A728(2) ? -v : v, D_L00_001A8F20, 0x7F204080, 1, 0.04f, 1.0f, 0.9f, 50000.0f);
        if (p) {
            q = &p->sub;
            p->sA = 10;
            p->b9 = func_002EF250(4.0f) + 0x40;
            q->w4 = 2;
            q->bA = 0x7F;
            q->bB = (unsigned char)p->sA;
        }
    } while (--i >= 0);
    v = 16;
    i = 1;
    do {
        p = (Spark *)func_00334888(arg, v, D_L00_001A8F20, 0x7FFFFFFF, 1, 0.02f, 1.0f, 0.97f, 15000.0f);
        v = -v;
        if (p) {
            q = &p->sub;
            p->sA = 2;
            p->b9 = func_002EF250(4.0f) + 0x40;
            p->b8 = func_0031A728(255);
            q->w4 = 2;
            q->bA = 0x7F;
            q->bB = (unsigned char)p->sA;
        }
    } while (--i >= 0);
}
