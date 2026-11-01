#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00405268);

#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
typedef union { Q16_B0e5d8f83 q; float f[4]; } EffectVector;
typedef struct { EffectVector row[4]; } EffectMatrix4;
extern int func_002A8600(unsigned char **, int, int, int);
extern int func_002A86E8(unsigned char **, unsigned char *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, char *);
extern float func_002AA2E8(float *, float, float);
extern int func_00282978(short *);

/* Blend the nearby pressure-surface contact using a full64-byte inverse matrix. */
void func_PAL_L04_00406B68(unsigned char *object, unsigned char *state) {
    EffectVector delta;
    EffectMatrix4 inverse;
    unsigned char *nearby;
    unsigned char *contact;
    int kind;
    float distance;
    if (*(int *)(state + 0x80) == -1) return;
    func_002A8600(&nearby, *(int *)(state + 0x80), 0, 0);
    while (nearby) {
        kind = *(short *)(nearby + 0xAA);
        if (kind == 0x474 || kind == 0xCEF) {
            func_00282CF0(&delta, nearby + 0x10, object + 0x10);
            distance = func_00282DB0(&delta, &delta);
            if (!(20.0f < distance)) {
                func_00283388(&inverse);
                func_00283698(&inverse, nearby + 0xC0);
                func_002830C0(&delta, &delta, &inverse);
                if (func_00282C48(delta.f[0]) < 2.8f && func_00282C48(delta.f[1]) < 1.25f && func_00282C48(delta.f[2]) < 1.5f) {
                    contact = *(unsigned char **)(nearby + 0x68);
                    if (*(short *)(state + 0x140) == 0 && (*(unsigned char **)(state + 0x164))[0x20] != 3)
                        func_002E5CF8(0, 0, (char *)nearby);
                    *(unsigned short *)(state + 0x140) = *(unsigned short *)contact;
                }
            }
        }
        func_002A86E8(&nearby, nearby, 0, 0);
    }
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x142) = 1;
        func_002AA2E8((float *)(state + 0x13C), 0.120000005f, 0.008f);
        if (*(short *)(state + 0x140)) func_00282978((short *)(state + 0x140));
    } else {
        *(short *)(state + 0x142) = 0;
        func_002AA2E8((float *)(state + 0x13C), 0.0f, 0.004f);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00406D90);
