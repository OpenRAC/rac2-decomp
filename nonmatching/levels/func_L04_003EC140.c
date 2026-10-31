/* Complete C reconstruction; not linked and no matching credit.
 * 2026-10-30, game -O2 -G8 -ffunction-sections:
 * 912/912 bytes, USA v1.01 0/1 and USA v2.00 0/1. PAL identity absent.
 * The real three-component phase/target/step/acceleration arrays, 64-byte matrix
 * and complete transformed vector preserve the retail 0x120 frame. Initializing
 * factor/attached after memset restores the prologue. Only six non-relocation
 * words differ: three pointer initializations and three loop increments around
 * the two-axis approach call. An explicit pointer loop and bank-preserving call
 * interleaving did not close them. Five trials; reopen with measured loop
 * induction/scheduling evidence. The canonical float-return contract is retained.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { char reserved[0x33C]; void *attached; int mode; } HeroAttachment;
extern HeroAttachment D_00189E20;
extern float D_L04_001B0124 __attribute__((sda));
extern float D_L04_001B0108[] SDATA(D_L04_001B0108);
extern float D_L04_001B0118[] SDATA(D_L04_001B0118);
extern float D_L04_001B0120;
extern float D_L04_001B0110;
extern float D_L04_001B00E8 __attribute__((sda));
extern float D_L04_001B00EC;
extern float D_L04_001B00F0;
extern float D_L04_001B00F8 __attribute__((sda));
extern float D_L04_001B00FC;
extern float D_L04_001B0100;
extern void func_00115484(void *, int, int);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282C48(float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00283B98(float, float);
extern float func_00283198(float);

void func_L04_003EC140(char *actor)
{
    float step[3];
    float acceleration[3];
    float target[3];
    float phase[3];
    float matrix[16] __attribute__((aligned(16)));
    float relative[4] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    float factor;
    int attached;
    int i;

    qcopy(actor + 0x10, state + 0x1B0);
    func_00115484(phase, 0, 12);
    factor = 1.0f;
    attached = 0;
    if (D_00189E20.attached == actor && D_00189E20.mode != 0) {
        attached = 1;
        if (D_00189E20.mode == 1) {
            factor = D_L04_001B0124;
            *(int *)(state + 0x1D0) = 0;
            *(int *)(state + 0x1D4) = 0;
            *(int *)(state + 0x1D8) = 0;
        }
        func_00283698(matrix, actor + 0xC0);
        func_00282CF0(relative, (char *)&D_00189E20 + 0x80, actor + 0x10);
        func_00283098(relative, relative, matrix);
        phase[0] += -relative[1] * 0.3330000043f;
        phase[1] += relative[0] * 1.5f;
    }
    for (i = 0; i < 2; i++) {
        acceleration[i] = D_L04_001B0118[i] *
                          ((func_00282C48(phase[i]) + 1.0f) * 0.0002777777845f);
        step[i] = acceleration[i] * factor;
        if (attached)
            target[i] = D_L04_001B0108[i] * phase[i];
        else
            target[i] = 0.0f;
        func_002AA548((float *)(state + 0x1C4) + i,
                     (float *)(state + 0x1D0) + i,
                     target[i], step[i], acceleration[i], 0.1f);
    }
    acceleration[2] = D_L04_001B0120 * 0.0002777777845f;
    step[2] = acceleration[2] * factor;
    if (attached)
        target[2] = D_L04_001B0110;
    else
        target[2] = 0.0f;
    func_002AA548((float *)(state + 0x1CC), (float *)(state + 0x1D8),
                 target[2], step[2], acceleration[2], 0.1f);
    *(float *)(actor + 0xF0) = *(float *)(state + 0x1C4);
    *(float *)(actor + 0xF4) = *(float *)(state + 0x1C8);
    *(float *)(actor + 0x18) += *(float *)(state + 0x1CC);
    *(float *)(state + 0x1A8) = func_00283B98(*(float *)(state + 0x1A8),
                                          D_L04_001B00E8 * 0.0002908882452f);
    *(float *)(actor + 0xF0) += D_L04_001B00F8 *
        (func_00283198(*(float *)(state + 0x1A8)) * 0.01745329425f);
    *(float *)(state + 0x1AC) = func_00283B98(*(float *)(state + 0x1AC),
                                          D_L04_001B00EC * 0.0002908882452f);
    *(float *)(actor + 0xF4) += D_L04_001B00FC *
        (func_00283198(*(float *)(state + 0x1AC)) * 0.01745329425f);
    *(float *)(state + 0x1C0) = func_00283B98(*(float *)(state + 0x1C0),
                                          D_L04_001B00F0 * 0.0002908882452f);
    *(float *)(actor + 0x18) += D_L04_001B0100 *
        func_00283198(*(float *)(state + 0x1C0));
}
