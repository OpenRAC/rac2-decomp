#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
typedef unsigned int B781AimQuad __attribute__((mode(TI)));
extern float func_00282C48(float);
extern void func_002AA898(void *, void *, float, float, float, float, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void *func_L04_003E5E40(void *, int, float);
extern int func_L04_00343498(void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L04_00404068(void *);
extern void func_L00_0033E220(void *, void *, unsigned int, float, int, int, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void func_PAL_L04_0041AB08(void *, void *, void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00282CF0(void *, void *, void *);

void func_PAL_L04_00408578(unsigned char *m, unsigned char *p)
{
    float point[4];
    float end[4];
    float total = *(float *)(p + 0x138) + *(float *)(p + 0x13c);
    float a, b, c, angle, factor;
    if (total < 0.10000001f) total = 0.10000001f;
    a = *(float *)(p + 0x130) * 11.459153f;
    b = total * 2.2573361f;
    c = *(float *)(p + 0x130) * 23.873238f;
    a = a * func_00282C48(a);
    c = 1.0f - (1.0f - c) * (1.0f - c);
    if (b > 1.0f) b = 1.0f;
    if (*(float *)(p + 0x1f4) != 0.0f) {
        if (func_00282C48(*(float *)(m + 0xf0) - *(float *)(p + 0x1f4)) < 0.003f) *(float *)(p + 0x1f4) = 0.0f;
        factor = *(float *)(p + 0x1f8);
        angle = *(float *)(p + 0x1f4);
    } else {
        factor = 1.0f;
        angle = (factor - b) * a + b * c;
        if (angle > factor) angle = factor;
        if (angle < -1.0f) angle = -1.0f;
        angle *= -0.52359885f;
    }
    func_002AA898(m + 0xf0, p + 0x128, angle, factor * 0.050400004f, 0.648f, factor * 0.03316126f, 0);
    if (*(unsigned char **)(p + 0x8c)) {
        unsigned char *child = *(unsigned char **)(p + 0x8c);
        if ((child[0x60] & 2) && child[0x42]) func_PAL_002A7E68(child, 0, 0, 2);
        *(short *)(*(unsigned char **)(p + 0x8c) + 0x32) = 30;
        (*(unsigned char **)(p + 0x8c))[0x31] = 1;
        *(B781AimQuad *)(*(unsigned char **)(p + 0x8c) + 0x10) = *(B781AimQuad *)(m + 0x10);
        *(B781AimQuad *)(*(unsigned char **)(p + 0x8c) + 0xf0) = *(B781AimQuad *)(m + 0xf0);
        (*(unsigned char **)(p + 0x8c))[0x30] = 0;
        func_PAL_002A0F68(*(void **)(p + 0x8c));
        func_002A0F48(*(void **)(p + 0x8c));
        *(unsigned short *)(*(unsigned char **)(p + 0x8c) + 0x34) |= 6;
    } else *(void **)(p + 0x8c) = func_L04_003E5E40(m, 0x8ef, 0.25f);
    if ((*(unsigned char **)(p + 0x164))[0xbc] == 5) {
        if (func_L04_00343498(m, 20.0f) != -1) {
            func_L00_002E6EF8(func_L04_00404068, m);
            func_L00_0033E220(p + 0x200, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            func_L00_0033E220(p + 0x210, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
            func_L00_0033E220(p + 0x220, m, 0x3096ffff, 94500.0f, -1, 0, 0.01f, 2, 0, -1);
        }
    }
    if (*(int *)(p + 0x244)) {
        func_00282CF0(point, *(unsigned char **)(p + 0x164) + 0x10, m + 0x10);
        if (func_L00_002EE290(point) < 100.0f) {
            *(B781AimQuad *)(point) = *(B781AimQuad *)(m + 0x10);
            point[2] -= 0.25f;
            *(B781AimQuad *)(end) = *(B781AimQuad *)(m + 0x10);
            func_PAL_L04_0041AB08(m, end, p + 0xd0, *(float *)(p + 0x138) + *(float *)(p + 0x13c));
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00408A58);
