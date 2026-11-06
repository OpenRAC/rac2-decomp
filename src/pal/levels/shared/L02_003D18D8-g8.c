/* func_PAL_L02_003D18D8, the PAL copy of func_L02_003CD970: the same C at 50 Hz, with the speeds and
 * turn rates scaled by 6/5 or 36/25, the random timers by 5/6 and the frame counts rescaled. */
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

/* The distance bound is read absolutely in state 3 and through GP in state 4.
 * Both symbols resolve to the same word in each of the three programs. */
extern float D_L02_001B00F8[] __attribute__((sda));
extern float D_L02_001B00F8_abs MACRO_ADDR;

extern void func_PAL_L02_003D24B8(void *);
extern void func_PAL_L02_003D2A10(void *);
extern void func_PAL_L02_003D28F0(void *);
extern void func_PAL_L02_003D2E28(void *);
extern void func_L02_003CEC70(void *);
extern void func_PAL_L02_003D31A0(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_002B1C20(void *, void *);
extern int func_PAL_L02_003D2898(void *, void *, int);
extern int func_L02_0032E390(void *, int, int);
extern int func_PAL_002AF6C0(void *, float);
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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern int func_L02_0032EF10(void *, void *, void *, int, float);
extern int func_L01_00322288(void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A8D70(void *, int, int, int, int, int, float, float, float);
extern int func_L02_00332630(char *, void *);
/* The integer and floating argument banks retain their independent order. */
extern int func_002A8C28(void *, float, float *, int, float, float, int, int, int);

void func_PAL_L02_003D18D8(char *o)
{
    char *p = *(char **)(o + 0x68);
    float angle, speed;
    int r;
    Quad temp;

    func_PAL_L02_003D24B8(o);
    switch (U8(o, 0x95)) {
    case 0:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.0072000003f, 0.080000006f, 0.010053098f,
                         0.5026549f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x124) = 0.0096f;
            F(p, 0x134) = 0.5f;
            S(p, 0x33A) = ((int)(func_002A7820(0, 30)) * 5 + 2) / 6;
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
            if (S(p, 0x310) < 250)
                S(p, 0x310) = ((int)(func_002A7820(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.0072000003f, 0.080000006f, 0.025132746f,
                         1.2566373f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x134) = 0.05f;
        }
        if (S(p, 0x314) == 1) {
            func_002A7750(o, 9, 2);
        } else if (S(p, 0x310) == 0)
            func_002A7750(o, 1, 0);
        break;
    case 2:
        if (func_002B3890(o)) {
            func_002B60B0(o, 0.0072000003f, 0.080000006f, 0.025132746f,
                         1.2566373f);
            F(p, 0x1D0) = 0.080000006f;
            F(p, 0x124) = 0.0096f;
            F(p, 0x134) = 0.05f;
            S(p, 0x33A) = ((int)(func_002A7820(0, 30)) * 5 + 2) / 6;
        }
        if (S(p, 0x314) != 1 && func_00282978(p + 0x33A)) {
            func_002A7750(o, 3, 1);
            S(p, 0x310) = ((int)(func_002A7820(580, 600)) * 5 + 2) / 6;
        }
        break;
    case 3: {
        unsigned int flags;
        flags = func_002B1C20(o, p + 0x50);
        if (flags & 1)
            func_PAL_L02_003D2A10(o);
        else if (flags & 2) {
            if (S(p, 0x314) == 1)
                func_002A7750(o, 9, 2);
            else {
                func_002A7750(o, 3, 1);
                S(p, 0x310) = ((int)(func_002A7820(580, 600)) * 5 + 2) / 6;
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
                    func_PAL_002A7E68(o, r, 0, 8);
                S(p, 0x312) = ((int)(func_002A7820(60, 120)) * 5 + 2) / 6;
            }
            if (U8(o, 0x43) == 1) {
                if (U8(o, 0x60) & 2)
                    func_PAL_002A7E68(o, 0, 0, 17);
            } else if (!S(p, 0x312) &&
                       (!S(p, 0x338) || func_00282DB0(p + 0x300, D_0018A0E0) > 0.8f))
                func_002A7750(o, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 6)
                func_PAL_002A7E68(o, 6, 0, 17);
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
        func_PAL_L02_003D2898(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 25 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 150))
            func_002A7750(o, 1, -1);
        break;
    case 3:
        if (func_002B3868(o) && U8(o, 0x43) != func_002A77E0(2) + 4)
            func_PAL_002A7E68(o, func_002A77E0(2) + 4, 0, 8);
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
            func_PAL_002A7E68(o, func_002A77E0(2) + 2, 0, 8);
        func_L02_00332630(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 3, -1);
        break;
    case 7:
        if (func_002B3868(o) && U8(o, 0x43) != 12)
            func_PAL_002A7E68(o, 12, 0, 8);
        func_L02_00332630(o, p + 0x1F0);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 3, -1);
        break;
    case 4:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 6)
                func_PAL_002A7E68(o, 6, 0, 8);
            {
                float upper = D_L02_001B00F8[1];
                F(p, 0x334) = func_002A7878(D_L02_001B00F8[0], upper) + 0.5f;
            }
        }
        if ((func_PAL_L02_003D2898(o, p + 0x2E0, 0) & 0x80) ||
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
                func_PAL_002A7E68(o, 6, 0, 17);
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
        func_PAL_L02_003D2898(o, p + 0x2F0, 0);
        if (U16(o, 0x96) > 25 && (F(p, 0x1CC) <= 0.5f || U16(o, 0x96) > 150))
            func_002A7750(o, 3, -1);
        break;
    case 8:
        if (func_002B3868(o) && U8(o, 0x43) != func_002A77E0(2) + 2)
            func_PAL_002A7E68(o, func_002A77E0(2) + 2, 0, 8);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 9, -1);
        break;
    case 9:
        if (func_002B3868(o) && U8(o, 0x43) != 6)
            func_PAL_002A7E68(o, 6, 0, 4);
        if (!(U16(o, 0x96) & 3))
            F(p, 0x31C) = func_L02_0032E390(o, D_0018C0B0, -1) * 0.087266475f;
        func_PAL_L02_003D2898(o, p + 0x1F0, 1);
        func_L02_003CEC70(o);
        if (F(p, 0x1CC) <= 1.25f)
            func_002A7750(o, 10, -1);
        break;
    case 10:
        if (func_002B3868(o)) {
            F(p, 0x320) = func_00283248(F(p, 0x1F0) - F(o, 0x10),
                                       F(p, 0x1F4) - F(o, 0x14));
            if (U8(o, 0x43) != 8)
                func_PAL_002A7E68(o, 8, 2, 8);
        }
        func_L01_00322288(o, F(p, 0x320));
        if (func_PAL_002AF6C0(o, 13))
            func_002A8D70(o, 1, 0x4000001, 0, 1, 0, 0.75f, U8(p, 0x34), 1);
        if (U8(o, 0x60) & 2)
            func_002A7750(o, 9, -1);
        break;
    case 14:
        if (func_002B3868(o)) {
            if (U8(o, 0x43) != 10)
                func_PAL_002A7E68(o, 10, 0, 5);
            I(p, 0x1BC) = D_L02_001B30C8;
        }
        func_00282F20(&temp, p + 0x1A0, 1);
        func_PAL_L02_003D2898(o, &temp, 0);
        func_PAL_L02_003D31A0(o);
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
        func_PAL_L02_003D2A10(o);
        break;
    }
    func_PAL_L02_003D28F0(o);
    if (U8(o, 0x31))
        func_PAL_L02_003D2E28(o);
}
