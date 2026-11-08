/* 8 November 2026 (Sonnet round, s21): plain TI128 spelling of the +8 clear tried, 632/636 (see levels/func_L01_003BCEC8.c); no legal form found. */
/* functional: high. The near-miss draft (632/636 bytes) with common.h's qcopy/qzero asm helpers written as plain quadword copies and clears. Retail clears the private block's first quadword through s + 8 (`addiu a0,s1,8; sq zero,0(a0)`); SQ ignores the low four address bits, so with the 16-aligned private block that clears s+0..s+0xF, which is what this C writes (a host 16-byte store at s + 8 would clear s+8..s+0x17 instead). Level 01's callees mapped through functions.tsv. */
/* func_L01_003BCEC8 (Oozla, level 01 only): debris piece update. State 0 destroys it; state 1 switches
 * to state 2 with a 10-frame fade timer when the timer (private+0x30) expires; state 2 fades alpha (+0x23)
 * from the timer and destroys it at expiry. It spins (private+0x40 and obj+0xF8 by func_00283B98), eases
 * obj+0xF0 toward private+0x44, and outside state 2 tilts (obj+0xF4), moves by the private velocity scaled
 * by the float at 0x1AFE30 (z kept, then lowered by private+0x38 down to private+0x3C); in state 2 the tilt
 * eases to 10 degrees. When the line from the old position (z + 1) to the new one hits (func_002761F8),
 * the position resets to 0x1BF920, the velocity and +0x10 clear and it starts fading.
 * From the near-miss draft nonmatching/levels/func_L01_003BCEC8.c. */
#include "common.h"

typedef int DebrisQ __attribute__((mode(TI)));

extern int func_00282948(void *);
extern void func_0029F338(void *);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float D_L01_001AFE30 __attribute__((sda));
extern DebrisQ D_L01_001BF920;

void func_L01_003BCEC8(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    DebrisQ pos;
    float saved, scale, tilt, next;

    pos = *(DebrisQ *)(obj + 0x10);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_0029F338(obj);
        return;
    case 1:
        if (func_00282948(s + 0x30) != 0) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (func_00282948(s + 0x30) != 0) {
            func_0029F338(obj);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(obj + 0x23) = func_00283CF0((float)*(int *)(s + 0x30) * 12.8f);
        break;
    }
    *(float *)(s + 0x40) = func_00283B98(*(float *)(s + 0x40), 0.034906592f);
    *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                           *(float *)(s + 0x18) * func_00283198(*(float *)(s + 0x40)));
    *(float *)(obj + 0xF0) = *(float *)(obj + 0xF0) + (*(float *)(s + 0x44) - *(float *)(obj + 0xF0)) * 0.02f;
    if (*(unsigned char *)(obj + 0x20) != 2) {
        tilt = func_00283180(*(float *)(s + 0x40)) * 0.17453295f;
        scale = D_L01_001AFE30;
        *(float *)(obj + 0xF4) = tilt;
        saved = *(float *)(s + 8);
        *(float *)(s + 8) = 0.0f;
        func_00282D30(s, s, scale);
        *(float *)(s + 8) = saved;
        func_00282CC0(obj + 0x10, obj + 0x10, s);
        next = *(float *)(s + 8) - *(float *)(s + 0x38);
        *(float *)(s + 8) = next;
        if (next < *(float *)(s + 0x3C))
            *(float *)(s + 8) = *(float *)(s + 0x3C);
    } else {
        *(float *)(obj + 0xF4) = *(float *)(obj + 0xF4) + (0.17453295f - *(float *)(obj + 0xF4)) * 0.1f;
    }
    ((float *)&pos)[2] += 1.0f;
    if (func_002761F8(&pos, obj + 0x10, 2, obj, 0) != 0) {
        *(DebrisQ *)(obj + 0x10) = D_L01_001BF920;
        *(DebrisQ *)s = 0; /* retail: sq zero through s + 8, which the EE aligns down to s */
        *(int *)(s + 0x38) = 0;
        *(DebrisQ *)(s + 0x10) = 0;
        if (*(unsigned char *)(obj + 0x20) != 2) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
        }
    }
}
