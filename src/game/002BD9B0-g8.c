#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int func_00282978(short *p);
extern void func_002B9180(void *p);
extern float func_00283CE0(int n);
extern int func_002A9568(int a, int b, float f);
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_002A7878(float lo, float hi);
extern int func_002A7820(int lo, int hi);
extern float func_00282DF0(void *v);
extern void func_00282F20(void *dst, void *src, float len);
extern void func_00282D30(void *dst, void *src, float scale);
extern void *func_002BD8B0(void *a0, void *a1, int a2, int a3, int a4, int a5, float f);
extern int D_001B1688 __attribute__((sda));

void func_002BD9B0(char *p)
{
    char *s = p + 0x20;
    float inv;
    float len;
    float keep[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));

    if (func_00282978((short *)(p + 0xA))) {
        func_002B9180(p);
        return;
    }
    inv = 1.0f / func_00283CE0(*(short *)(s + 0x18));
    *(float *)(p + 0xC) = func_00283CE0(*(short *)(p + 0xA)) * *(float *)(s + 0x1C) * inv;
    *(int *)(p + 4) = func_002A9568(*(int *)(s + 0x14), *(int *)(s + 0x10), func_00283CE0(*(short *)(p + 0xA)) * inv);
    func_00282CC0((p + 0x10), (p + 0x10), s);
    *(float *)(s + 8) -= 0.001f;
    qcopy(keep, p + 0x10);
    if (*(short *)(s + 0x1A) != 0 && (D_001B1688 & 1)) {
        *(TI *)w = 0;
        w[0] = func_002A7878(-1.0f, 1.0f);
        w[1] = func_002A7878(-1.0f, 1.0f);
        w[2] = func_002A7878(-1.0f, 1.0f);
        *(TI *)v = *(TI *)w;
        len = func_00282DF0(s);
        func_00282F20(v, v, len * func_002A7878(0.21f, 0.25f));
        func_00282CC0(v, v, s);
        func_00282D30(v, v, func_002A7878(0.75f, 0.95f));
        func_002BD8B0((p + 0x10), v, *(int *)(p + 4), *(int *)(s + 0x14), func_002A7820(15, 20), 0, *(float *)(p + 0xC));
    } else {
        func_00282D30(s, s, 0.96f);
    }
}
