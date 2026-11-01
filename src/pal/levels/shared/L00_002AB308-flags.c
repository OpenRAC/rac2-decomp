#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x300];
    float f300;
    float f304;
    float f308;
    float f30C;
    float f310;
    float f314;
    unsigned char pad318[0x30];
    short f348;
    unsigned char pad34a[0x152];
    unsigned char f49C;
    unsigned char pad49d[0xdd3];
    int f1270;
    unsigned char pad1274[0x1bc];
    float f1430;
    float f1434;
    int f1438;
    short f143C;
    unsigned short f143E;
    unsigned char pad1440[0xe50];
    unsigned char *f2290;
    int f2294;
    unsigned char pad2298[0x4];
    int f229C;
} PointEffectHero;
extern PointEffectHero D_00189E20;
typedef struct {
    unsigned char pad0[0x320];
    float f320;
    float f324;
    unsigned char pad328[0x44];
    float f36C;
    unsigned char pad370[0x60];
    float f3D0;
    float f3D4;
    unsigned char pad3d8[0x44];
    float f41C;
    unsigned char pad420[0x60];
    float f480;
    unsigned char pad484[0xac];
    float f530;
} PointEffectJoints;
extern PointEffectJoints D_L00_0025BE10;
extern int func_L00_002ADF80(void);
extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002D3248(short, unsigned char, unsigned char, unsigned char, float, float);
extern void func_0029FCC0(char *, int, char *);
extern float func_002A7878(float, float);
extern void func_PAL_L00_00337918(void *, void *, float);

/* Drive articulated offsets and emit the active pair of joint effects. */
void func_PAL_L00_002AC088(void)
{
    Quadword position;
    unsigned char *matrix;
    float left, right, draw;
    int index;

    if (D_00189E20.f1270) {
        D_L00_0025BE10.f36C = 0.01f;
        D_L00_0025BE10.f41C = 0.01f;
    }
    if (func_L00_002ADF80())
        return;
    if ((func_00282C48(D_00189E20.f300) > 0.015f ||
         func_00282C48(D_00189E20.f304) > 0.015f ||
         func_00282C48(D_00189E20.f308) > 0.01745329424738884f ||
         func_00282C48(D_00189E20.f30C) > 0.01745329424738884f ||
         func_00282C48(D_00189E20.f310) > 0.01745329424738884f ||
         func_00282C48(D_00189E20.f314) > 0.01745329424738884f) &&
        D_00189E20.f348 != 1) {
        D_L00_0025BE10.f324 = -D_00189E20.f308;
        D_L00_0025BE10.f3D4 = -D_00189E20.f30C;
        left = func_00283248(0.2f, D_00189E20.f300) * 1.2f;
        right = -func_00283248(0.2f, D_00189E20.f304) * 1.2f;
        if (left > 0.785398244857788f)
            left = 0.785398244857788f;
        if (left < -0.174532949924469f)
            left = -0.174532949924469f;
        if (right > 0.174532949924469f)
            right = 0.174532949924469f;
        if (right < -0.785398244857788f)
            right = -0.785398244857788f;
        D_L00_0025BE10.f480 = left;
        D_L00_0025BE10.f530 = right;
        D_L00_0025BE10.f320 = -func_00283BE0(D_00189E20.f310, -left);
        D_L00_0025BE10.f3D0 = -func_00283BE0(D_00189E20.f314, -right);
    }
    if (!(D_00189E20.f143E & 0x80)) {
        if (D_00189E20.f2294 == 3)
            func_L00_002D3248(1, 2, 1, 0, 0.021f, 0.002f);
        if (D_00189E20.f229C == 4 && D_00189E20.f49C && D_00189E20.f49C < 10)
            func_L00_002D3248(1, 2, 0, 1, 0.016f, 0.002f);
        if (D_00189E20.f1438 > 0 && D_00189E20.f143C) {
            matrix = 0;
            if (D_00189E20.f143E & 1)
                matrix = D_00189E20.f2290 + 0xC0;
            --D_00189E20.f1438;
            func_0029FCC0((char *)D_00189E20.f2290, 22, (char *)&position);
            for (index = 0; index < D_00189E20.f143C; ++index) {
                draw = func_002A7878(-D_00189E20.f1434, D_00189E20.f1434);
                func_PAL_L00_00337918(&position, matrix, D_00189E20.f1430 + draw);
            }
            func_0029FCC0((char *)D_00189E20.f2290, 23, (char *)&position);
            for (index = 0; index < D_00189E20.f143C; ++index) {
                draw = func_002A7878(-D_00189E20.f1434, D_00189E20.f1434);
                func_PAL_L00_00337918(&position, matrix, D_00189E20.f1430 + draw);
            }
        }
    } else {
        D_00189E20.f1438 = 0;
    }
}
