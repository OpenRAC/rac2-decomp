#include "include_asm.h"

#include "common.h"
extern float func_00283180(float), func_00283198(float);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);
extern void func_0027D330(int), func_L01_002B35E8(int), func_PAL_L00_002B9CD8(void *, void *, int, int), func_002E5CF8(int, int, void *);
extern void func_00335438(void *, void *, int, int, int), func_00335370(void *), func_003353C8(void *);
extern void func_PAL_002A7E68(void *, int, int, int), func_PAL_L00_002D2668(int, int, float);
extern unsigned char D_001A7A45;
extern int D_L01_001B1FA8;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState D_00189E20;

void func_PAL_L01_0039A520(unsigned char *m) {
    float a[4], b[4], c[4], d[4];
    char *p = *(char **)(m + 0x68);
    a[0] = func_00283180(*(float *)(p + 0x1C))*2.5f;
    a[1] = func_00283198(*(float *)(p + 0x1C))*2.5f;
    a[2] = 0;
    func_00282CC0(a, a, p + 0x10);
    func_00282C88(b);
    b[2] = func_00283B98(*(float *)(p + 0x1C), 3.1415929794311523f);
    func_0027D330(8);
    if (D_00189E20.state == 3) func_L01_002B35E8(0);
    func_PAL_L00_002B9CD8(a, b, 0x6F, 0);
    func_002E5CF8(0, 0, m);
    c[0] = func_00283180(*(float *)(p + 0x1C))*1.25f;
    c[1] = func_00283198(*(float *)(p + 0x1C))*1.25f;
    c[2] = 0;
    c[0] += func_00283180(func_00283B98(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    c[1] += func_00283198(func_00283B98(*(float *)(p + 0x1C), 1.5707964897155762f))*4.0f;
    func_00282CC0(c, c, p + 0x10);
    c[2] += 1;
    func_00282C88(d);
    d[2] = func_00283BE0(*(float *)(p + 0x1C), 1.5707964897155762f);
    func_00335438(c, d, 1, 0, 0);
    func_00335370(c);
    func_003353C8(d);
    qcopy_nc(m + 0x10, D_00189E20.pos);
    qcopy_nc(m + 0xF0, D_00189E20.rot);
    if (m[0x43] != 1) func_PAL_002A7E68(m, 1, 0, 0);
    func_PAL_L00_002D2668(0x7B, 0, 0.0f);
    if (D_001A7A45) *(unsigned short *)(m + 0x34) |= 0x8000;
    D_00189E20.flag = 1;
    D_L01_001B1FA8 = 1;
    m[0x20] = 2;
    *(int *)(p + 0x6C) = 50;
}

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x60 - 0x1C];
    f32 f60;
    f32 f64;
    f32 f68;
} State_397870;
typedef struct {
    u8 pad0[0x24];
    f32 f24;
} Class_397870;
typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    u8 b20;
    u8 pad2[0x24 - 0x21];
    Class_397870 *cls;
    u8 pad3[0x2C - 0x28];
    f32 f2C;
    u8 pad4[0x68 - 0x30];
    State_397870 *st;
    u8 pad5[0xF0 - 0x6C];
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} Obj_397870;
extern void func_PAL_L01_0039B2D0(Obj_397870 *a0);
extern float D_L01_001AF50C __attribute__((sda));
extern float D_L01_001AF510 __attribute__((sda));
extern float D_L01_001AF514 __attribute__((sda));
extern float D_L01_001AF528 __attribute__((sda));
extern int D_L01_001AF54C __attribute__((sda));
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002A77E0(int);
extern void func_PAL_L01_0039AE48(Obj_397870 *);

void func_PAL_L01_0039AC80(Obj_397870 *a0)
{
    State_397870 *s1 = a0->st;
    float f;

    a0->f2C = a0->cls->f24 * D_L01_001AF50C;

    if (a0->b20 == 1) {
        f = func_00283198(a0->fFC);
        a0->f18 = s1->f18 + D_L01_001AF510 + D_L01_001AF514 * f;
        a0->fF0 = func_00283B98(a0->fF0, s1->f68);
        a0->fF4 = func_00283B98(a0->fF4, s1->f64);
        a0->fF8 = func_00283B98(a0->fF8, s1->f60);
        a0->fFC = func_00283B98(a0->fFC, 0.0003490659f * D_L01_001AF528);
    }

    func_PAL_L01_0039AE48(a0);
    if (func_002A77E0(D_L01_001AF54C) == 0)
        func_PAL_L01_0039B2D0(a0);
}
