/* func_L01_003D2C88 - 456 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Flags -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -g (the
   -g gives the nop pair before div.s; copies as TI assignments). 452 vs 456
   B. Remaining 5 lines: retail builds the two level-global accesses as lui
   v0/v1,0x19 + lw/sh with the offset in the instruction (lw v1,-0x5C20(v0);
   sh v0,-0x3348(v1)); mine uses the assembler macro (lui at; sh 0(at)). Those
   are probably fields of one struct symbol (D_00189E20+0x5C0 and +0x2E98) but
   that variant CSEs the base into one register. Also angle math needs
   separate 'scale = func_00283CE0(60)' temp for retail order. */

#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));

extern int D_001A79F0;
extern char *D_L01_0018A3E0;
extern unsigned short D_L01_0018CCB8;
extern int D_L01_001B2088 __attribute__((sda));
extern int D_L01_001B05C0 __attribute__((sda));
extern int D_L01_001B05C4;

extern float func_00283CE0(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L01_0031AB20(char *, char *, int, float, float, float);
extern int func_L01_0031BC68(int, int, float);

/* Per-frame step of a spinning object. */
void func_L01_003D2C88(char *object) {
    char *state = *(char **)(object + 0x68);
    float pos[4];
    float rot[4];
    float tmp[4];
    float angle;
    float scale;

    *(Quadword *)pos = *(Quadword *)(object + 0x10);
    *(Quadword *)rot = *(Quadword *)(object + 0xF0);
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned short *)(object + 0x34) |= 0x1000;
        *(unsigned int *)(state + 0xDC) |= 1;
        *(unsigned char *)(object + 0x20) = 1;
        if (*(short *)(object + 0xAA) == 0xE2A)
            *(float *)(state + 0x88) = 12.0f;
        break;
    case 1:
        scale = *(float *)(object + 0x2C) / *(float *)(*(char **)(object + 0x24) + 0x24);
        func_L01_0031AB20(object, state + 0x50, *(int *)(state + 0xE0),
                          *(float *)(state + 0xEC) * scale, *(float *)(state + 0xE4) * scale,
                          *(float *)(state + 0xE8) * scale);
        if (D_L01_0018A3E0 == object && D_001A79F0 == 2)
            D_L01_0018CCB8 = 0xFFFF;
        break;
    }
    if (*(unsigned char *)(object + 0x31)) {
        angle = func_00283CE0(D_L01_001B2088 % 60);
        scale = func_00283CE0(60);
        angle *= 6.2831855f;
        angle /= scale;
        *(int *)(object + 0x78) = func_L01_0031BC68(D_L01_001B05C0, D_L01_001B05C4, angle - 3.1415927f);
    }
    func_00282CF0(tmp, object + 0x10, pos);
    func_002AD6F0(state + 0xA0, tmp, rot, object + 0xF0);
}
