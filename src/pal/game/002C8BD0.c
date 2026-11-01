#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002C8BD0);

#include "common.h"
extern void func_00300190(char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern float func_002A7878(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00282978(char *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002B9180(char *);
extern int D_001B1688 __attribute__((sda));
extern char D_001B5200[];
extern char D_00189EA0[];
extern float func_00282E48(char *, char *);
extern void func_00282CF0(char *, char *, char *);

void func_PAL_002C8D68(char *p)
{
    char *d, *position = p + 16, *hero, *base;
    float v[4], origin[4];
    float a, b;
    d = p + 32;
    func_00300190(position, position);
    func_00282D30(d, d, 0.9f);
    *(float *)(d + 8) -= *(float *)(d + 12);
    func_00282CC0(position, position, d);
    hero = D_00189EA0;
    if (func_00282E48(position, hero) < 1.05f) {
      base = hero - 128;
      if (*(float *)(base + 0x170) != 0) {
        qcopy(origin, hero);
        func_00282CF0((char *)v, position, (char *)origin);
        a = func_002A7878(0.1f, 2.0f);
        func_00282F20((char *)v, (char *)v, *(float *)(base + 0x170) * 0.2f + a * 0.020000001f * 0.15f);
        *(unsigned char *)(p + 8) += (int)(*(short *)(d + 22) * *(float *)(base + 0x170) * 0.5f);
        func_00282CC0(position, position, (char *)v);
    }
    }
    if (D_001B1688 % 10 == 0) {
        *(float *)(d + 28) = func_00283B98(*(float *)(d + 28), 1.0f);
        a = func_00283198(*(float *)(d + 28));
        func_00282F20((char *)v, D_001B5200, a * 0.0075f);
        func_00282CC0(d, d, (char *)v);
    }
    if (*(short *)(d + 20) >= 160) {
        if (*(short *)(p + 10) < *(short *)(d + 20)) {
            a = func_00283CE0(*(short *)(p + 10)); b = func_00283CE0(*(short *)(d + 20));
            *(int *)(p + 4) = (func_00283CF0((a /= b) * 128.0f) << 24) | 0x353535;
        } else *(int *)(p + 4) = 0x9F353535;
    } else {
        if (*(short *)(p + 10) < *(short *)(d + 20)) {
            a = func_00283CE0(*(short *)(p + 10)); b = func_00283CE0(*(short *)(d + 20));
            *(int *)(p + 4) = (func_00283CF0((a /= b) * 64.0f) << 24) | 0x909090;
        } else *(int *)(p + 4) = 0x40909090;
    }
    *(unsigned char *)(p + 8) += *(unsigned char *)(d + 22);
    if (func_00282978(p + 10)) func_002B9180(p);
}


