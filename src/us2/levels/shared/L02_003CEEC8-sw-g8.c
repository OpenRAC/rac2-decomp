#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define U8(p, o) (*(unsigned char *)((p) + (o)))
#define U16(p, o) (*(unsigned short *)((p) + (o)))
#define S(p, o) (*(short *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0 __attribute__((nosda));
extern int D_L02_001B30C8;
extern float D_L02_001B00F8 __attribute__((sda));
extern float D_L02_001B00F8_abs MACRO_ADDR;
extern volatile float D_L02_001B00FC MACRO_ADDR;
extern void func_L02_003CE4D0(void *);
extern void func_L02_003CEA28(void *);
extern void func_L02_003CE908(void *);
extern void func_L02_003CEE40(void *);
extern void func_L02_003CEC70(void *);
extern void func_L02_003CF1B8(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_002B1C20(void *, void *);
extern int func_L02_003CE8B0(void *, void *, int);
extern int func_L02_0032E390(void *, int, int);
extern int func_US2_002AF9C8(void *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern int func_L02_0032EF10(void *, void *, void *, int, float);
extern int func_L01_00322288(void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A8D70(void *, int, int, int, int, int, float, float, float);
extern int func_L02_00332630(char *, void *);
extern int func_002A8C28(void *, float, float *, int, float, float, int, int, int);

void func_US2_L02_003CEEC8(char *o)
{
    char *p = *(char **)(o + 0x68);
    float angle, speed;
    int r;
    Quad temp;

    func_L02_003CE4D0(o);
    switch (U8(o, 0x95)) {
    case 0:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.005f, 0.06666667f, 0.006981317885220051f,
                         0.41887909173965454f);
            F(p, 0x1D0) = 0.06666667f;
            F(p, 0x124) = 0.006666666828095913f;
            F(p, 0x134) = 0.5f;
            S(p, 0x33A) = func_002A7820(0, 30);
        }
        if (S(p, 0x314) == 1) {
            if (func_00282978(p + 0x33A)) {
                if (func_002A77E0(3))
                    func_002A7750(o, 9, 2);
                else
                    func_002A7750(o, 8, 2);
                break;
            }
        }
        if (S(p, 0x316)) {
            if (func_002A77E0(2))
                func_002A7750(o, 7, 1);
            else
                func_002A7750(o, 6, 1);
            S(p, 0x316) = 0;
            if (S(p, 0x310) < 300)
                S(p, 0x310) = func_002A7820(480, 600);
        }
        break;
    case 1:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(p, 0x1D0) = 0.06666667f;
            F(p, 0x134) = 0.05f;
        }
        if (S(p, 0x314) == 1) {
            func_002A7750(o, 9, 2);
        } else if (S(p, 0x310) == 0)
            func_002A7750(o, 1, 0);
        break;
    case 2:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.005f, 0.06666667f, 0.01745329424738884f,
                         1.047197699546814f);
            F(p, 0x1D0) = 0.06666667f;
            F(p, 0x124) = 0.006666666828095913f;
            F(p, 0x134) = 0.05f;
            S(p, 0x33A) = func_002A7820(0, 30);
        }
        if (S(p, 0x314) != 1 && func_00282978(p + 0x33A)) {
            func_002A7750(o, 3, 1);
            S(p, 0x310) = func_002A7820(580, 600);
        }
        break;
    case 3: {
        unsigned int flags;
        flags = func_002B1C20(o, p + 0x50);
        if (flags & 1)
            func_L02_003CEA28(o);
        else if (flags & 2) {
            if (S(p, 0x314) == 1)
                func_002A7750(o, 9, 2);
            else {
                func_002A7750(o, 3, 1);
                S(p, 0x310) = func_002A7820(580, 600);
            }
        }
        break;
    }
    }
    switch (U8(o, 0x20)) {
    case 1:
        if (U8(o, 0x31)) {
            if (func_002B3868(o)) {
                r = !func_002A77E0(4);
                if (U8(o, 0x43) != r)
                    func_002A7470(o, r, 0, 10);
                S(p, 0x312) = func_002A7820(60, 120);
            }
            if (U8(o, 0x43) == 1) {
                if (U8(o, 0x60) & 2)
                    func_002A7470(o, 0, 0, 20);
            } else if (!S(p, 0x312) &&
                       (!S(p, 0x338) || func_00282DB0(p + 0x300, D_0018A0E0) > 0.8f))
                func_002A7750(o, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 6)
                func_002A7470(o, 6, 0, 20);
            angle = func_002A7940();
            speed = func_002A7878(2, 5);
            F(p, 0x2F0) = func_00283180(angle) * speed;
            F(p, 0x2F4) = func_00283198(angle) * speed;
            F(p, 0x2F8) = 0;
            func_00282CC0(p + 0x2F0, p + 0x2F0, p + 0x2E0);
            if (I(p, 0x218) != -1) {
                temp = *(Quad *)(p + 0x2E0);
                func_L02_0032EF10(&temp, p + 0x2F0, p + 0x2F0, I(p, 0x218), 1.5f);
            }
        }
        func_L02_003CE8B0(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 30 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 180))
            func_002A7750(o, 1, -1);
        break;
    case 3:
        if (func_002B3868(o) && U8(o, 0x43) != func_002A77E0(2) + 4)
            func_002A7470(o, func_002A77E0(2) + 4, 0, 10);
        if (func_00282E48(o + 0x10, D_00189EA0) < D_L02_001B00F8_abs)
            func_002A7750(o, 4, -1);
        else if (U8(o, 0x60) & 2) {
            switch (func_002A77E0(3)) {
            case 0:
                func_002A7750(o, 6, -1);
                break;
            case 1:
                func_002A7750(o, 7, -1);
                break;
            case 2:
                func_002A7750(o, 5, -1);
                break;
            }
        }
        break;
    case 6:
        if (func_002B3868(o) && U8(o, 0x43) != func_002A77E0(2) + 2)
            func_002A7470(o, func_002A77E0(2) + 2, 0, 10);
        func_L02_00332630(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 3, -1);
        break;
    case 7:
        if (func_002B3868(o) && U8(o, 0x43) != 12)
            func_002A7470(o, 12, 0, 10);
        func_L02_00332630(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 3, -1);
        break;
    case 4:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 6)
                func_002A7470(o, 6, 0, 10);
            {
                float upper = D_L02_001B00FC;
                F(p, 0x334) = func_002A7878(D_L02_001B00F8, upper) + 0.5f;
            }
        }
        if ((func_L02_003CE8B0(o, p + 0x2E0, 0) & 0x80) ||
            func_00282E80(o + 0x10, D_00189EA0) > F(p, 0x334)) {
            if (func_002A77E0(2))
                func_002A7750(o, 6, -1);
            else
                func_002A7750(o, 7, -1);
        }
        break;
    case 5:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 6)
                func_002A7470(o, 6, 0, 20);
            angle = func_002A7940();
            speed = func_002A7878(2, 5);
            F(p, 0x2F0) = func_00283180(angle) * speed;
            F(p, 0x2F4) = func_00283198(angle) * speed;
            F(p, 0x2F8) = 0;
            func_00282CC0(p + 0x2F0, p + 0x2F0, p + 0x2E0);
            if (I(p, 0x218) != -1) {
                temp = *(Quad *)(p + 0x2E0);
                func_L02_0032EF10(&temp, p + 0x2F0, p + 0x2F0, I(p, 0x218), 1.5f);
            }
        }
        func_L02_003CE8B0(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 30 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 180))
            func_002A7750(o, 3, -1);
        break;
    case 8:
        if (func_002B3868(o) && U8(o, 0x43) != func_002A77E0(2) + 2)
            func_002A7470(o, func_002A77E0(2) + 2, 0, 10);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 9, -1);
        break;
    case 9:
        if (func_002B3868(o) && U8(o, 0x43) != 6)
            func_002A7470(o, 6, 0, 5);
        if (!(U16(o, 0x96) & 3))
            F(p, 0x31C) = func_L02_0032E390(o, D_0018C0B0, -1) * 0.087266475f;
        func_L02_003CE8B0(o, p + 0x1F0, 1);
        func_L02_003CEC70(o);
        if (F(p, 0x1CC) <= 1.25f)
            func_002A7750(o, 10, -1);
        break;
    case 10:
        if (func_002B3868(o)) {
            F(p, 0x320) = func_00283248(F(p, 0x1F0) - F(o, 0x10),
                                       F(p, 0x1F4) - F(o, 0x14));
            if (U8(o, 0x43) != 8)
                func_002A7470(o, 8, 2, 10);
        }
        func_L01_00322288(o, F(p, 0x320));
        if (func_US2_002AF9C8(o, 13))
            func_002A8D70(o, 1, 0x4000001, 0, 1, 0, 0.75f, U8(p, 0x34), 1);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 9, -1);
        break;
    case 14:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 10)
                func_002A7470(o, 10, 0, 5);
            I(p, 0x1BC) = D_L02_001B30C8;
        }
        func_00282F20(&temp, p + 0x1A0, 1);
        func_L02_003CE8B0(o, &temp, 0);
        func_L02_003CF1B8(o);
        func_002A8C28(o, 0.6f, (float *)(o + 0x10), 0x4000000, 1, 1, 0, 1, 0);
        if (F(p, 0x190) >= F(o, 0x18)) {
            if (S(p, 0x314) == 1)
                func_002A7750(o, 8, 2);
            else
                func_002A7750(o, 2, 0);
            I(p, 0x138) &= -18;
        }
        break;
    case 12:
        func_L02_003CEA28(o);
        break;
    }
    func_L02_003CE908(o);
    if (U8(o, 0x31))
        func_L02_003CEE40(o);
}
