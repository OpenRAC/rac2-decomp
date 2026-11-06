#include "common.h"

/* func_US2_L00_00375F40, the USA v2.00 copy of func_L00_00374C18: the same C with two more calls. */

/* Partial layouts measured from the menu, controller and resource accesses. */
typedef struct {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
    int f60;
    int f64;
    int f68;
    int f6c;
    int f70;
    int f74;
    int f78;
    int f7c;
    int f80;
    int f84;
    int f88;
    int f8c;
    int f90;
    int f94;
    float f98;
    int f9c;
    int fa0;
    int fa4;
    float fa8;
    float fac;
    float fb0;
    float fb4;
    float fb8;
    float fbc;
    char rest[0x684];
} PurchaseMenuState;
extern PurchaseMenuState D_L00_0022F7C0[];
#define MENU ((char *)D_L00_0022F7C0)
extern float D_L00_001AD570 __attribute__((sda));
extern int D_L00_001B259C, D_L00_001B25A0, D_L00_001B25A4;
typedef struct {
    int pad[0x140 / 4];
    float x, y;
    char pad148[0x78];
    int held, pressed;
} PurchaseMenuInput;
extern PurchaseMenuInput D_00138180[];
typedef struct {
    int pad[0x4B40 / 4];
    struct { int value; char pad[16]; } entries[0];
} MenuResourceTable;
extern MenuResourceTable D_0014B540[];
extern short D_00152CE4 NOT_SDA;
extern unsigned char D_00139568[];
typedef struct {
    char prefix[0x3C];
    unsigned short value;
    char tail[0xE0 - 0x3E];
} MenuShopClass;
extern char D_L00_00262570[];
extern void func_L00_0030C788(int);
extern void func_002B7CE0(int);
extern int func_002B0CE0(int, int, int);
extern void func_00294420(int);
extern void func_00294988(int);
extern void func_002F5220(void),func_002B6658(void),func_002E5F60(void);
extern void func_US2_L00_002A6DD0(void);
extern void func_002B9390(void),func_002914B8(void),func_002F52B8(void);
extern int func_002B4B70(int,int);
extern int func_0028E138(int);
extern void func_00335370(void *),func_003353C8(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_L00_002EDCF0(float);
extern float func_00283B98(float,float);
extern void func_002A0F48(void *);
extern void func_00282D30(void *,void *,float);
extern void func_L00_0037A2E8(void),func_US2_002FC008(void);
extern void func_US2_L00_00375EC0(void),func_US2_L00_00375A30(void);
extern void func_L00_0030C7C0(int),func_L00_0030C748(int,int),func_L00_0030C710(int);
extern void func_US2_0029CA98(void),func_002E4AC8(void);
#define MF(o) (*(float *)(m + (o)))
/* Advances the purchase menu and its model previews, then runs the shared update. */
void func_US2_L00_00375F40(void)
{
    int i, v;
    char *m;
    float x, y;
    double d;
    float vec[4];

    func_002B0CE0(6, 0, 1);
    switch (D_L00_0022F7C0[0].f00) {
    case 0:
        func_002B7CE0(1);
        D_L00_001AD570 += 0.1f;
        func_L00_0030C788(1);
        if (D_L00_001AD570 >= 1.0f) {
            D_L00_0022F7C0[0].f00 = 1;
            D_L00_001AD570 = 1.0f;
            D_L00_0022F7C0[0].f04 = 0;
        }
        break;
    case 2:
        D_L00_001AD570 += 0.1f;
        func_L00_0030C788(0);
        if (D_L00_001AD570 < 1.0f)
            break;
        D_L00_001AD570 = 1.0f;
        if (D_L00_0022F7C0[0].f08) {
            D_L00_0022F7C0[0].f08 = 0;
            if (D_L00_0022F7C0[0].fa0 >= 0) {
                v = D_0014B540[0].entries[D_L00_0022F7C0[0].fa0].value;
                func_002B7CE0(1);
                func_00294420(v);
                func_002B7CE0(1);
                func_00294988(v);
            } else {
                D_00152CE4 = -1;
            }
        }
        D_L00_0022F7C0[0].f04 = 0;
        if (!D_L00_0022F7C0[0].f60) {
            func_002F5220();
            func_002B6658();
            func_002E5F60();
            func_US2_L00_002A6DD0();
            func_002B9390();
        }
        func_002B4B70(0, 0);
        func_0028E138(1);
        if (!D_L00_0022F7C0[0].f60) {
            func_00335370(MENU + 0xD0);
            func_003353C8(MENU + 0xE0);
        }
        func_002914B8();
        func_002F52B8();
        break;
    case 1:
        if (D_00138180[0].held & 0x8000)
            D_L00_001B259C++;
        else
            D_L00_001B259C = 0;
        if (D_00138180[0].held & 0x2000)
            D_L00_001B25A0++;
        else
            D_L00_001B25A0 = 0;
        if (D_L00_0022F7C0[0].f90 == 0) {
            D_L00_0022F7C0[0].f94 += 3;
            if (D_L00_0022F7C0[0].f94 >= 128) {
                D_L00_0022F7C0[0].f94 = 128;
                D_L00_0022F7C0[0].f90 = 2;
            }
        } else if (D_L00_0022F7C0[0].f90 == 1) {
            D_L00_0022F7C0[0].f94 -= 16;
            D_L00_0022F7C0[0].f98 *= 0.9f;
            if (D_L00_0022F7C0[0].f94 <= 0) {
                D_L00_0022F7C0[0].f94 = 0;
                D_L00_0022F7C0[0].f90 = 3;
            }
        }
        if (D_L00_0022F7C0[0].f88) {
            for (i = 0; i < D_L00_0022F7C0[0].f34; i++) {
                float stickScale = 0.0033333334f;
                m = (char *)D_L00_0022F7C0[0].f2c + i * 256;
                func_00283098(m + 16, MENU + 0xC0, (char *)D_L00_0022F7C0[0].f28 + 0xC0);
                func_00282CC0(m + 16, m + 16, (char *)D_L00_0022F7C0[0].f28 + 16);
                MF(0x2C) = *(float *)(*(char **)(m + 0x24) + 0x24) * D_L00_0022F7C0[0].f98;
                if (*(short *)(m + 0xAA) == 0x10E3)
                    m[0x23] = D_L00_0022F7C0[0].f94 / 2;
                else
                    m[0x23] = D_L00_0022F7C0[0].f94;
                if (D_L00_0022F7C0[0].f50 != 2) {
                    MF(0xF8) = func_00283B98(MF(0xF8), func_L00_002EDCF0(0.01f));
                } else {
                    x = D_00138180[0].x * stickScale;
                    y = D_00138180[0].y * stickScale;
                    if (D_L00_0022F7C0[0].fa4 <= 0) {
                        D_L00_0022F7C0[0].fb4 = func_00283B98(D_L00_0022F7C0[0].fb4,
                            (D_L00_0022F7C0[0].fa8 - D_L00_0022F7C0[0].fb4) * 0.006666667f);
                        D_L00_0022F7C0[0].fb8 = func_00283B98(D_L00_0022F7C0[0].fb8,
                            (D_L00_0022F7C0[0].fac - D_L00_0022F7C0[0].fb8) * 0.006666667f);
                        D_L00_0022F7C0[0].fbc = func_00283B98(D_L00_0022F7C0[0].fbc,
                            (D_L00_0022F7C0[0].fb0 - D_L00_0022F7C0[0].fbc) * 0.006666667f);
                    } else {
                        D_L00_0022F7C0[0].fbc = func_00283B98(D_L00_0022F7C0[0].fbc, x);
                        D_L00_0022F7C0[0].fb8 = func_00283B98(D_L00_0022F7C0[0].fb8, y);
                    }
                    MF(0xF0) = D_L00_0022F7C0[0].fb4;
                    MF(0xF4) = D_L00_0022F7C0[0].fb8;
                    MF(0xF8) = D_L00_0022F7C0[0].fbc;
                    d = x;
                    if (d < 0.0)
                        d = 0.0 - d;
                    if (d > (double)0.0001f)
                        goto moved;
                    d = y;
                    if (d < 0.0)
                        d = 0.0 - d;
                    if (d > (double)0.0001f) {
                    moved:
                        D_L00_0022F7C0[0].fa4 = 180;
                    }
                }
                func_002A0F48(m);
                if (D_L00_0022F7C0[0].f50 != 2) {
                    func_00282D30(vec, m, 0.0009765625f);
                    MF(0x10) += MF(0x10) - vec[0];
                    MF(0x14) += MF(0x14) - vec[1];
                    func_002A0F48(m);
                }
            }
            if (D_L00_0022F7C0[0].fa4 > 0)
                D_L00_0022F7C0[0].fa4--;
        }
        if (D_L00_0022F7C0[0].f8c)
            func_L00_0037A2E8();
        else if (D_L00_0022F7C0[0].f90 == 3 && D_L00_0022F7C0[0].f84 == 0 &&
                 D_L00_0022F7C0[0].f6c == 0)
            func_US2_002FC008();
        D_L00_0022F7C0[0].f04++;
        func_US2_L00_00375EC0();
        func_US2_L00_00375A30();
        D_L00_001B25A4 = D_00138180[0].pressed;
        if (D_L00_0022F7C0[0].f50 == 0 &&
            *(int *)(MENU + 0x144 + D_L00_0022F7C0[0].f80 * 24) == 1) {
            func_L00_0030C7C0(*(int *)(MENU + 0x140 + D_L00_0022F7C0[0].f80 * 24));
            {
                int selected = *(int *)(MENU + 0x140 + D_L00_0022F7C0[0].f80 * 24);
                unsigned int classIndex = D_00139568[selected];
                func_L00_0030C748(((MenuShopClass *)D_L00_00262570)[classIndex].value, 10);
            }
        } else {
            func_L00_0030C7C0(0);
        }
        func_0028E138(1);
        if (D_L00_0022F7C0[0].f50 != 2)
            func_L00_0030C710(180);
        func_US2_0029CA98();
        break;
    }
    func_002E4AC8();
}
