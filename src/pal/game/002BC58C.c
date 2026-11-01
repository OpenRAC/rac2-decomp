#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002BC58C);

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

