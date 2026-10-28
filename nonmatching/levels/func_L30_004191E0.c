/* func_L30_004191E0 - 368 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = whole L30_0040E660.c with func_L30_004191E0 written (default
   flags, no -g8 needed). Same size; control flow and registers match.
   Only scheduling differs in the two func_L05_0042F4E8 call setups (retail:
   cvt.s.w f0, lwc1 f2, lui/ori/mtc1 f1 (0.1f), addiu a0, lwc1 f12, ...; mine
   loads f12 before the 0.1f constant).
   Tried: all 56 int/float interleavings of the callee prototype (EABI split
   counters), local t/a/b with several orders, t*(b-a). */

#include "include_asm.h"

extern void func_42C028(int);
extern void func_316DB8(char *);
extern int D_0018C0E8;

void func_L30_00418670(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    func_42C028(3);
    D_0018C0E8 = *(int *)(st + 0x5C);
    func_316DB8(*(char **)(st + 0x50));
}

INCLUDE_ASM("asm/levels", func_L30_004130E8);

INCLUDE_ASM("asm/levels", func_L30_00413528);

INCLUDE_ASM("asm/levels", func_L30_004135A0);

INCLUDE_ASM("asm/levels", func_L30_004148F0);

INCLUDE_ASM("asm/levels", func_L30_00415090);

INCLUDE_ASM("asm/levels", func_L30_004153D8);

INCLUDE_ASM("asm/levels", func_L30_004158B0);

INCLUDE_ASM("asm/levels", func_L30_00416A88);

INCLUDE_ASM("asm/levels", func_L30_00416D88);

INCLUDE_ASM("asm/levels", func_L30_00417988);

typedef unsigned short u16;

extern char *func_316A50(int);
extern void func_32BFF0(void *, void *);
extern void func_2F56B0(void *, void *);

void func_L30_00418570(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    char *o;

    o = func_316A50(0xB28);
    if (o == 0) return;
    func_32BFF0(o, a0);
    func_2F56B0(o + 0xC0, o + 0xF0);
    *(u16 *)(o + 0x34) |= 0x100;
    *(char **)(st + 0x50) = o;
}


INCLUDE_ASM("asm/levels", func_L30_004186B0);

extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027DE50(int, int, int, int, int);
extern void func_L05_0042F4E8(void *, int, int, float, float, float, float, float);
extern short D_001A6480[];

void func_L30_004191E0(char *obj) {
    short *st = *(short **)(obj + 0x68);
    int d;
    float f;

    if (st[1] - st[0] < 2 && st[2] != 0) {
        if (*(int *)(st + 14) != 0) {
            func_002FC560(0x42, 0x48);
            func_0027DE50(0, D_001A6480[0xA9], 0, D_001A6480[0xA8], 0x80808080);
        }
    }
    if (*(int *)(st + 12) != 0) {
        d = st[1] - st[0];
        if (d < 10) {
            f = *(float *)(st + 4);
            func_L05_0042F4E8(obj + 0x10, 0x3C, 0, f + (*(float *)(st + 6) - f) * ((float)d * 0.1f), 0.5f, 0.0f, 0.0f, 0.0f);
        } else if ((unsigned short)(st[0] - 0x2E) < 4) {
            f = *(float *)(st + 4);
            func_L05_0042F4E8(obj + 0x10, 0x3C, 0, f + (*(float *)(st + 6) - f) * ((float)(st[0] - 0x2D) * 0.1f), 0.5f, 0.0f, 0.0f, 0.0f);
        }
    }
}

extern int func_2F4B08(char *);
extern void func_2EDD78(void *, char *);
extern void func_L00_00415AA0(char *);

void func_L30_0041A848(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    if (func_2F4B08(st) == 0) {
        func_2F4B08(st + 4);
        func_2EDD78((void *)func_L00_00415AA0, a0);
    } else {
        func_316DB8(a0);
    }
}

INCLUDE_ASM("asm/levels", func_L30_0041B848);
