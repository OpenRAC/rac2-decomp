/* func_0030A188 - 444 bytes.  Worker attempt, 27 October 2026 (draft below).

   Logic decoded, draft 412 B vs 444. Needs new file
   src/game/00308600-g8-qcopy.c + cflags `-O2 -G8 -ffunction-sections
   -frac2-qcopy -frac2-qcopy-barrier`.
   Retail: saves only s0..s6 (mine s0..s7); loop has 5 walking pointers s1..s5
   (A+0x10, B+0x10, E ints+4, D(0x229440)+0x10, F ints+4) and counter s0=0x12
   down to 0; b (sp+0x10) is copied to s6 for the loop; sw zero,0x341C($gp)
   sits in the jal func_282CF0 delay slot; the five array addresses are built
   with separate lui 0x23 (no shared hi) right after the qcopy.
   Tried: index form with i+1, explicit pointer walk with descending i.
   Unknown how retail gets that many pointers/regs without the extra s7/fp. */

#include "include_asm.h"
#include "common.h"

extern int ref_L00_0030A188_00 __attribute__((sda));
extern int ref_L00_0030A188_01 __attribute__((sda));
extern int ref_L00_0030A188_02 __attribute__((sda));
extern int ref_L00_0030A188_03 __attribute__((sda));
extern float ref_L00_0030A188_04 __attribute__((sda));
extern int ref_L00_0030A188_05 __attribute__((sda));
extern int ref_L00_0030A188_06 __attribute__((sda));
extern int ref_L00_0030A188_07 __attribute__((sda));

extern float ref_L00_0030A188_08[][4];
extern float ref_L00_0030A188_09[][4];
extern int ref_L00_0030A188_10[];
extern float ref_L00_0030A188_11[][4];
extern int ref_L00_0030A188_12[];

extern int D_001B2408;
extern short D_001B23E8[4];
extern short D_001B23F8[8];

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);

void func_0030A188(char *object)
{
    char *owner;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    int i;
    float (*pa)[4];
    float (*pb)[4];
    int *pc;
    float (*pd)[4];
    int *pe;

    if (ref_L00_0030A188_00 == 0)
        return;
    owner = *(char **)(object + 0x68);
    D_001B2408 = ref_L00_0030A188_01;
    ref_L00_0030A188_02 = 0x7F2020;
    ref_L00_0030A188_00 = 0;
    ref_L00_0030A188_03 = 0;
    func_00282CF0(a, owner + 0x10, owner);
    func_00282F20(b, a, ref_L00_0030A188_04 * 0.05f);
    qcopy(ref_L00_0030A188_08[0], owner);
    pa = ref_L00_0030A188_08 + 1;
    pb = ref_L00_0030A188_09 + 1;
    pc = ref_L00_0030A188_10 + 1;
    pd = ref_L00_0030A188_11 + 1;
    pe = ref_L00_0030A188_12 + 1;
    for (i = 18; i >= 0; i--) {
        func_00282CC0(pa, pb, b);
        pb++;
        pa++;
        *pc = 0;
        func_00282C88(pd);
        pd++;
        *pe = 0;
        pc++;
        pe++;
    }
    for (i = 0; i < 4; i++)
        D_001B23E8[i] = -1;
    D_001B23F8[0] = 8;
    D_001B23F8[1] = 4;
    D_001B23F8[2] = 8;
    D_001B23F8[3] = 4;
    D_001B23F8[4] = 4;
    D_001B23F8[5] = 2;
    D_001B23F8[6] = 4;
    D_001B23F8[7] = 2;
    ref_L00_0030A188_05 = 0;
    ref_L00_0030A188_06 = 0;
    ref_L00_0030A188_07 = 0;
}
