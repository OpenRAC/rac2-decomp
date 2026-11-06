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


/* func_PAL_L04_00406D90, the PAL copy of func_L04_004029D8: the same C, where the rates become
   per-50 Hz-frame values (0.3691667f to 0.443f, 0.0116667f to 0.014f, 0.0333333f to 0.04f), the
   timer's 60.0f becomes the scaled (x * 300.0f + 2.0f) * 0.16666667f, and func_002A05A8 becomes
   func_PAL_002A0F68. */
extern float func_00283CE0(int);
extern char *D_L04_001FE340[];
extern void func_002C96F8(void *, void *, void *, void *, float, float);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *a0);
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int func_00283CF0(float);
extern void *func_L04_003E5E40(unsigned char *a0, void *a1, float f12);

void func_PAL_L04_00406D90(unsigned char *m) {
    unsigned char *s = *(unsigned char **)(m + 0x68);
    float f;
    unsigned char *o;
    s[0xA2] = s[0x9C];
    *(Q16_B0e5d8f83 *)(m+0x10) = *(Q16_B0e5d8f83 *)(s+0xB0);
    *(Q16_B0e5d8f83 *)(m+0xF0) = *(Q16_B0e5d8f83 *)(s+0xC0);
    s[0xA0] = 0;
    f = func_00283CE0(s[0xA2]-1);
    *(float *)(s+0x134) = 0.44300002f - f * 0.014f - (1.0f - (float)*(int *)(s+0x1A8)*0.1f)*0.040000003f;
    *(int *)(s+0x138)=0;
    *(int *)(s+0x158)=0;
    *(int *)(s+0x13C)=0;
    *(short *)(s+0x142)=0;
    *(short *)(s+0x140)=0;
    *(int *)(s+0x160)=0;
    *(int *)(s+0x24C)=0;
    if (*(int *)(s+0x54)==-1) *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x50)];
    else *(char **)(s+0x110)=D_L04_001FE340[*(int *)(s+0x54)];
    *(float *)(s+0xA8)=5.0f;
    *(float *)(s+0x1F8)=1.0f;
    *(int *)(s+0xAC)=0;
    *(int *)(s+0x114)=0;
    *(int *)(s+0x118)=0;
    *(int *)(s+0x128)=0;
    *(int *)(s+0x12C)=0;
    *(int *)(s+0x130)=0;
    *(int *)(s+0x244)=0;
    *(int *)(s+0x1F4)=0;
    *(int *)(s+0x144)=0;
    s[0xA4]=0; s[0xA5]=0; *(short *)(s+0xA6)=0;
    *(int *)(s+0x154)=0;
    *(int *)(s+0x150)=0;
    *(int *)(s+0x148)=0;
    *(int *)(s+0x178)=0;
    *(int *)(s+0x248)=0;
    *(int *)(s+0x14C)=0;
    *(int *)(s+0x15C)=0;
    s[0xA1]=0;
    qzero(s+0xD0); qzero(s+0xE0); qzero(s+0x100);
    o=*(unsigned char **)(s+0x110);
    func_002C96F8(o,s+0x114,s+0x118,s+0xF0,*(float *)(s+0xA8),*(float *)(o+0x1C));
    *(float *)(s+0x16C)=func_002A7878_range(-1.5f,1.5f);
    *(int *)(s+0x174)=func_00283CF0((func_002A7878_range(3.0f,6.0f)*300.0f + 2.0f) * 0.16666667f);
    *(int *)(s+0x170)=0;
    *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
    *(unsigned short *)(m+0x34)=(*(unsigned short *)(m+0x34)&0xFFBE)|0x1400;
    if (!*(void **)(s+0x8C)) {
        *(void **)(s+0x8C)=func_L04_003E5E40(m,(void *)0x8EF,0.25f);
        if (!*(void **)(s+0x8C)) goto done;
    }
    {
    unsigned char *child=*(unsigned char **)(s+0x8C);
    *(unsigned short *)(child+0x34)&=0xFFBE;
    }
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0x10)=*(Q16_B0e5d8f83 *)(m+0x10);
    *(Q16_B0e5d8f83 *)(*(unsigned char **)(s+0x8C)+0xF0)=*(Q16_B0e5d8f83 *)(m+0xF0);
    (*(unsigned char **)(s+0x8C))[0x30]=0;
    func_PAL_002A0F68(*(void **)(s+0x8C));
    func_002A0F48(*(void **)(s+0x8C));
done:
    *(short *)(s+0x17E)=0; *(short *)(s+0x17C)=-1;
    *(int *)(s+0x180)=0; m[0x20]=2;
    *(int *)(s+0x120)=-1;
    *(int *)(s+0x240)=*(int *)(s+0x1C0)=*(int *)(s+0x124)=
    *(int *)(s+0x11C)=*(int *)(s+0x1AC)=*(int *)(s+0x1A0)=*(int *)(s+0x19C)=0;
}
