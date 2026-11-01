#include "include_asm.h"

#include "common.h"
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L06_00380B10(void *, void *, int, float, float);
extern float D_L06_001B1AC0 __attribute__((sda));
extern float D_L06_001B1AC4 __attribute__((sda));
extern float D_L06_001B1AC8 __attribute__((sda));
extern float D_L06_001B1ACC __attribute__((sda));
extern float D_L06_001B1AD0 __attribute__((sda));
extern float D_L06_001B1AD4 __attribute__((sda));
extern float D_L06_001B1AD8 __attribute__((sda));
extern float D_L06_001B1ADC __attribute__((sda));
extern int D_L06_001B1AE0 __attribute__((sda));
extern int D_L06_001B1AE4 __attribute__((sda));
extern int D_L06_001B1AE8 __attribute__((sda));

void func_PAL_L06_00461850(char *a0) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, a0 + 0x10);
    pos[2] += 3.3f + func_002A7878(-0.05f, 0.05f);
    pos[0] += func_002A7878(-0.1f, 0.1f);
    pos[1] += func_002A7878(-0.1f, 0.1f);
    offset[0] = func_00283180(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[1] = func_00283198(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[2] = 0;
    func_00282CC0(pos, pos, offset);
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.020000001f, D_L06_001B1ACC * 0.020000001f);
    func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.020000001f, D_L06_001B1ACC * 0.020000001f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.5f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.020000001f, 0.036000002f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) == 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.020000001f, D_L06_001B1ADC * 0.020000001f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
}

typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float,float);
extern char *func_002A9640(char *,int,int);
extern void func_00282D30(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_0029F338(char *);
extern void func_L00_0033E220(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void func_PAL_L00_003281C0(char *,int,float);
extern void func_L01_0031A278(char *,void *,float,float,float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_PAL_L00_00328480(char *,void *,int,float,int,void *,float,unsigned int,float,float,int);
extern char D_L06_001B1C08[] SDATA(D_L06_001B1C08);
extern char D_L06_001B1C00[] SDATA(D_L06_001B1C00);
extern char D_L06_001B1C10[] SDATA(D_L06_001B1C10);
extern char D_L06_001A8F20[] MACRO_ADDR;
extern int D_L06_001B1C30 __attribute__((sda));

void func_PAL_L06_00467544(char *obj)
{
    float pos[4], a[4], b[4], c[4];
    char *stateData = *(char **)(obj + 0x68);
    char *hit;
    int state = *(unsigned char *)(obj + 0x20);
    int i;

    *(Quad *)a = 0;
    a[2] = *(float *)(obj + 0x2C) * 21.5f;
    *(Quad *)pos = *(Quad *)a;
    switch (state) {
    case 0:
        func_L00_0033E220(pos, obj, 0x50801420, -1, 0, -1, 0, 96, 430500.0f, 0.0f);
        func_L00_0033E220(pos, obj, 0x40801420, -1, 1, -1, 0, 96, 73500.0f, 0.75f);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        hit = func_002A9640(obj, 0x4010000, 0);
        if (hit && !*(int *)stateData) {
            *(Quad *)a = 0;
            a[1] = a[0] = 3.0f;
            *(float *)(hit + 0x18) = 0.75f;
            func_00282D30(b, hit + 0x10, func_002A7878(6.0f, 8.0f));
            qcopy(c, b);
            func_00282CF0(b, b, a);
            func_00282CC0(c, c, a);
            func_PAL_L00_0032C328(obj, b, D_L06_001B1C08, D_L06_001B1C00,
                             65535, -1, D_L06_001B1C30, 9, state, 255, 0);
            func_002A7750(obj, 2, -1);
        }
        ((unsigned char *)obj)[0xA8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(obj, D_L06_001B1C10, D_L06_001B1C08, D_L06_001B1C00,
                         65535, 0, D_L06_001B1C30, 7, 62, 255, 0);
        func_PAL_L00_003281C0(obj, 1, pos[2] * 0.33333334f);
        func_L01_0031A278(obj, a, pos[0], pos[1], pos[2]);
        func_PAL_002AC718(obj, D_L06_001A8F20, a, 0, 0, 8, 3, 3, 0, 0, 9, 0.35f,
                      -1, 0, 0, 0, -1, 0, 0x810001);
        for (i = 0; i < 4; i++) {
            b[0] = (i / 2 * 2 - 1) * 0.020000001f;
            b[1] = (i % 2 * 2 - 1) * 0.020000001f;
            b[2] = 0.14000002f;
            func_00283098(b, b, obj + 0xC0);
            func_PAL_L00_00328480(obj, a, 3, 0, 1, b, 5, 0x7FFF8080, 0.45f, 0.6f, 0);
        }
        func_0029F338(obj);
        break;
    }
}
