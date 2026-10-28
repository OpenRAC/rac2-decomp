/* func_L09_003EA798 - 564 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Size matches; 50 masked lines differ, all instruction order and FP/int
   register numbering (byte store order, f0/f12 roles in the func_002B60B0 arg
   block). Needs flags -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-
   barrier. Tried retail store order, args as locals computed before the float
   stores (this made the arg block land early like retail), K*D operand order. */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));

extern int func_00283CF0(float);
extern void func_002B60B0(char *, float, float, float, float);
extern float func_L09_0033E7A0(int);
extern int func_L09_003EA2D0(char *, int, int);
extern void func_002A7750(char *, int, int);
extern unsigned int D_L09_001FE6C0[];
extern float D_L09_001B0C00 __attribute__((sda));
extern float D_L09_001B0C04 __attribute__((sda));
extern float D_L09_001B0C08 __attribute__((sda));
extern float D_L09_001B0C0C __attribute__((sda));

/* Initialises the state block of a new object: copies its position and heading into the
   block, sets the tuning constants and starts the first animation. */
void func_L09_003EA798(char *object) {
    char *state = *(char **)(object + 0x68);
    char *pos = object + 0x10;
    int entry;
    float ax;
    float ay;
    float az;
    float aw;

    *(Quadword *)(state + 0x330) = *(Quadword *)pos;
    *(Quadword *)(state + 0x340) = *(Quadword *)(object + 0xF0);
    *(unsigned char *)(state + 0x48) = func_00283CF0(25.0f);
    *(unsigned char *)(state + 0x4A) = func_00283CF0(19.2f);
    *(unsigned char *)(state + 0x1F2) = 4;
    *(unsigned char *)(state + 0x1EC) = 4;
    *(unsigned char *)(state + 0x1EE) = 4;
    *(unsigned char *)(state + 0x1F3) = 8;
    *(unsigned char *)(state + 0x1F6) = 1;
    *(unsigned char *)(state + 0x28) = 3;
    *(unsigned char *)(state + 0x2F) = 2;
    *(unsigned char *)(state + 0x191) = 2;
    *(unsigned char *)(state + 0x192) = 2;
    *(unsigned char *)(state + 0x196) = 2;
    *(unsigned char *)(state + 0x197) = 2;
    *(unsigned char *)(state + 0x1ED) = 8;
    *(unsigned char *)(state + 0x1EF) = 8;
    *(unsigned char *)(state + 0x190) = 5;
    ax = 0.00027777778f * D_L09_001B0C00;
    ay = 0.016666668f * D_L09_001B0C04;
    az = 4.8481374e-06f * D_L09_001B0C08;
    aw = 0.00029088825f * D_L09_001B0C0C;
    *(float *)(state + 0x1A8) = 0.0025f;
    *(float *)(state + 0x1B0) = 1.5f;
    *(float *)(state + 0x1BC) = 0.4f;
    *(float *)(state + 0x30) = 1.0f;
    *(int *)(state + 0x1C8) = 5;
    *(float *)(state + 0x1AC) = 0.0013888889f;
    *(int *)(state + 0x19C) = 0;
    *(int *)(state + 0x1A0) = 0;
    *(int *)(state + 0x1B4) = 0;
    *(short *)(state + 0x1B8) = 0;
    *(int *)(state + 0x54) = 0;
    *(int *)(state + 0x58) = 0;
    *(int *)(state + 0x5C) = 0;
    *(int *)(state + 0x7C) = 0;
    *(float *)(state + 0x50) = 3.5f;
    *(float *)(state + 0x60) = 3.1415927f;
    *(float *)(state + 0x80) = 0.5235988f;
    *(float *)(state + 0x1A4) = 0.0025f;
    func_002B60B0(object, ax, ay, az, aw);
    *(int *)(state + 0x354) = *(int *)(state + 0x374);
    func_L09_0033E7A0(*(int *)(state + 0x36C));
    func_L09_0033E7A0(*(int *)(state + 0x350));
    entry = *(int *)(state + 0x36C);
    if (entry != -1) {
        *(Quadword *)pos = *(Quadword *)(D_L09_001FE6C0[entry] + 0x10);
        func_L09_003EA2D0(object, entry, -1);
        *(int *)(state + 0x380) = 0;
    } else {
        *(int *)(state + 0x380) = 1;
    }
    func_002A7750(object, 1, 1);
}
