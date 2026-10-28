/* func_002C7050 - 584 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file src/game/002C7050-g8.c; needs config/cflags.txt line
   `src/game/002C7050-g8.c -O2 -G8 -ffunction-sections -g` (retail has the -g
   nops before c.eq.s; the existing 002BF6F0-g8.c has no -g).
   Same size, structure right; 22 masked lines are all register naming: retail
   s0 = obj+0x10 / later the sp+0x20 vector, s1 = random int, s4 = copy of s0
   used in func_300190(s4,s4); mine merges s4 into s1 (copy propagation) and
   swaps s0/s1.
   Tried: separate s4 variable, reusing s0 for the vector, declaration order
   of the three EffectVectors (now matches stack offsets). */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;

extern int D_001B1688 __attribute__((sda));
extern int func_00282978(short *a0);
extern void func_002B9180(char *a0);
extern float func_00283CE0(int a0);
extern int func_002A9568(int a0, int a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern void func_00300190(void *a0, void *a1);
extern float func_002A7878(float lo, float hi);
extern float func_00282DF0(char *a0);
extern void func_00282F20(void *a0, void *a1, float f12);
extern void func_00282D30(void *a0, void *a1, float f12);
extern int func_002A7820(int lo, int hi);
extern int func_00283CF0(float f12);
extern void func_002BCB00(void *a0, void *a1, int a2, int a3, int t0, int t1, int t2, int t3, int stk, float f12);

void func_002C7050(char *a0)
{
    char *s3 = a0 + 0x20;
    char *s0;
    char *s4;
    float f20;
    EffectVector keep;
    EffectVector v;
    EffectVector w;
    int s1;

    if (func_00282978((short *)(a0 + 0xA)) != 0) {
        func_002B9180(a0);
        return;
    }
    s0 = a0 + 0x10;
    f20 = func_00283CE0(*(s16 *)(a0 + 0xA));
    *(int *)(a0 + 4) = func_002A9568(*(int *)(s3 + 0x14), *(int *)(s3 + 0x10), f20 / func_00283CE0(*(s16 *)(s3 + 0x18)));
    func_00282CC0(s0, s0, s3);
    *(float *)(s3 + 8) -= *(float *)(s3 + 0xC);
    qcopy(keep.value, s0);
    s4 = s0;
    if (*(float *)(a0 + 0x1C) != 0.0f) {
        if (*(float *)(a0 + 0x1C) == 2.0f)
            func_00300190(s4, s4);
        *(float *)(a0 + 0x1C) = 2.0f;
    }
    if (*(s16 *)(s3 + 0x1A) != 0 && (D_001B1688 & 1)) {
        w.bits = 0;
        w.value[0] = func_002A7878(-1.0f, 1.0f);
        w.value[1] = func_002A7878(-1.0f, 1.0f);
        w.value[2] = func_002A7878(-1.0f, 1.0f);
        f20 = func_00282DF0(s3);
        v.bits = w.bits;
        s0 = v.value;
        func_00282F20(s0, s0, f20 * func_002A7878(0.15f, 0.25f));
        func_00282CC0(s0, s0, s3);
        func_00282D30(s0, s0, func_002A7878(0.75f, 0.95f));
        s1 = func_002A7820(0xF, 0x1E);
        func_002BCB00(s4, s0, *(int *)(a0 + 4), *(int *)(s3 + 0x14), s1, 0, *(u8 *)(a0 + 2), *(u8 *)(a0 + 3),
                      func_00283CF0(*(float *)(a0 + 0x1C)), *(float *)(a0 + 0xC));
    } else {
        func_00282D30(s3, s3, 0.96f);
    }
}
