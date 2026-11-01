#include "include_asm.h"

extern float func_00283CE0(int a);
extern void func_00282CC0(char *p, char *q, char *r);
extern int func_00283D38(int, int, float);
extern unsigned char *D_001F2560;

/* blends a sub-object into a position, adds a float field, stores an interpolated value in the
   word at +4 and scales the frame count into a byte table at +2 */
void func_PAL_002BC58C(char *a0)
{
    char *s0 = a0;
    char *s1 = a0 + 32;
    unsigned int r;
    float f;

    func_00282CC0(s0 + 16, s0 + 16, s1);
    if (func_00282978(s0 + 10) != 0) {
        func_002B9180(s0);
        return;
    }
    *(float *)(s0 + 12) = *(float *)(s0 + 12) + *(float *)(s1 + 0x1C);
    f = func_00283CE0(*(int *)(s1 + 0x18));
    r = func_00283D38(*(int *)(s1 + 0x14), *(int *)(s1 + 0x10),
                      (float)*(short *)(s0 + 0xA) / f);
    *(int *)(s0 + 4) = r;
    if (*(short *)(s0 + 0xA) < 5) {
        *(int *)(s0 + 4) = (r & 0xFFFFFF) | (((int)(*(short *)(s0 + 0xA) * (r >> 24))) / 5 << 24);
    }
    *(unsigned char *)(s0 + 2) = D_001F2560[((*(int *)(s1 + 0x18) - *(short *)(s0 + 0xA)) * 10) / *(int *)(s1 + 0x18)];
}


INCLUDE_ASM("asm/pal/game", func_PAL_002BC6A0);

#include "common.h"
extern int func_00282978(char *p);
extern void func_002B9180(char *p);
extern int func_00283CF0(float f);
extern void func_00282CC0(char *a, char *b, char *c);
extern void func_00282D30(char *a, char *b, float f);

/* decays a float field by 0.04 with a saturating early-out that consults a helper and returns; otherwise adds 12000 to a second field, nudges a third by 0.0484 while it stays below 0.225, merges two 255-scaled byte lanes into a header word, hands a sub-object to two helpers and decrements a byte counter */
void func_PAL_002BC808(char *p)
{
    char *q = p + 32;
    float v;
    int a, b;
    int h;

    v = *(float *)(q + 28) + (-0.048f);
    *(float *)(q + 28) = v;
    if (v <= 0.0f || func_00282978(p + 10) != 0) {
        func_002B9180(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 14400.001f;
    if (*(float *)(q + 24) < 0.225f) {
        *(float *)(q + 24) = *(float *)(q + 24) + 0.058080003f;
    }
    a = func_00283CF0(*(float *)(q + 24) * 255.0f) & 0xff;
    b = func_00283CF0(*(float *)(q + 28) * 255.0f);
    h = *(unsigned short *)(p + 4);
    *(int *)(p + 4) = h | (a << 16) | (b << 24);
    func_00282CC0(p + 16, p + 16, q);
    func_00282D30(q, q, 0.88f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) - 1;
}

