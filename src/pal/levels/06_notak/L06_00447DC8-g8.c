/* func_PAL_L06_00447DC8, the PAL copy of func_L06_00443280: the same C at 50 Hz, with the
   timers from func_002A7820 scaled by 5/6, frame counts and rates converted, and PAL callees. */
#include "common.h"

extern float D_L06_001B1090 __attribute__((sda));
extern float D_L06_001B1094 __attribute__((sda));
extern int D_L06_001B2348;
extern void func_PAL_L06_004485C0(char *);
extern int func_002B3890(char *);
extern int func_002B3868(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_002B1C20(char *, char *);
extern void func_PAL_L06_00448AB8(char *);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(char *, char *, char *);
extern int func_PAL_L06_00448968(char *, char *, int);
extern int func_L02_0032E390(char *, int, int);
extern void func_L06_00444068(char *);
extern float func_00283248(float, float);
extern void func_L01_00322288(char *, float);
extern int func_PAL_002AF6C0(char *, float);
extern void func_002A8D70(char *, int, int, int, int, int, float, float, float);
extern void func_00282F20(char *, char *, float);
extern void func_L06_00443E18(char *);
extern void func_PAL_L06_00448CF0(char *);

#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))

void func_PAL_L06_00447DC8(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    char tmp[16];
    float angle, speed;
    int flags, anim;
    func_PAL_L06_004485C0(obj);
    if (!obj || B(obj,0x20) == 0xFE || B(obj,0x20) == 0xFD) return;
    switch (B(obj,0x95)) {
    case 0:
        if (func_002B3890(obj)) {
            func_002B60B0(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(st,0x124) = 0.0096f;
            F(st,0x134) = 0.5f;
        }
        F(st,0x1D0) = D_L06_001B1094 * 0.020000001f;
        if (H(st,0x314) == 1) {
            if (func_002A77E0(5) == 0) {
                func_002A7750(obj,5,2);
            } else {
                func_002A7750(obj,6,2);
            }
        } else if (H(st,0x316)) {
            func_002A7750(obj,3,1);
            H(st,0x316) = 0;
            if (H(st,0x310) < 250) H(st,0x310) = ((s32)func_002A7820(480,600) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (func_002B3890(obj)) {
            func_002B60B0(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(st,0x134) = 0.05f;
        }
        F(st,0x1D0) = D_L06_001B1090 * 0.020000001f;
        if (H(st,0x314) == 1) func_002A7750(obj,6,2);
        else if (!H(st,0x310)) func_002A7750(obj,1,0);
        break;
    case 2:
        if (func_002B3890(obj)) {
            func_002B60B0(obj, 0.0072000003f, 0.080000006f, 0.005026549f, 0.5026549f);
            F(st,0x124) = 0.0096f;
            F(st,0x134) = 0.05f;
        }
        F(st,0x1D0) = D_L06_001B1090 * 0.020000001f;
        if (H(st,0x314) == 1) break;
        else {
            func_002A7750(obj,3,1);
            H(st,0x310) = ((s32)func_002A7820(580,600) * 5 + 2) / 6;
        }
        break;
    case 3:
        flags = func_002B1C20(obj,st+0x50);
        if (flags & 1) func_PAL_L06_00448AB8(obj);
        else if (flags & 2) {
            if (H(st,0x314) == 1) {
                func_002A7750(obj,6,2);
            } else {
                func_002A7750(obj,3,1);
                H(st,0x310) = ((s32)func_002A7820(580,600) * 5 + 2) / 6;
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (func_002B3868(obj)) {
            anim = func_002A77E0(4) == 0;
            if (B(obj,0x43) != anim) func_PAL_002A7E68(obj,anim,0,8);
            H(st,0x312) = ((s32)func_002A7820(60,120) * 5 + 2) / 6;
        }
        if (B(obj,0x43) == 1) {
            if (B(obj,0x60) & 2) func_PAL_002A7E68(obj,0,0,17);
        } else if (!H(st,0x312)) func_002A7750(obj,2,-1);
        break;
    case 2:
        if (func_002B3868(obj)) {
            if (B(obj,0x43) != 6) func_PAL_002A7E68(obj,6,0,17);
            angle = func_002A7940();
            speed = func_002A7878(2.0f,5.0f);
            F(st,0x2F0) = func_00283180(angle)*speed;
            F(st,0x2F4) = func_00283198(angle)*speed;
            F(st,0x2F8) = 0;
            func_00282CC0(st+0x2F0,st+0x2F0,st+0x2E0);
        }
        func_PAL_L06_00448968(obj,st+0x2F0,0);
        if (U(obj,0x96)>25 && (F(st,0x1CC)<=0.5f || U(obj,0x96)>150)) func_002A7750(obj,1,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            if (B(obj,0x43) != func_002A77E0(2)+4) func_PAL_002A7E68(obj,func_002A77E0(2)+4,0,8);
        }
        break;
    case 4:
        if (func_002B3868(obj) && B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,8);
        if (func_PAL_L06_00448968(obj,st+0x2E0,0)&0x80) func_002A7750(obj,3,-1);
        break;
    case 5:
        if (func_002B3868(obj)) {
            if (B(obj,0x43) != func_002A77E0(2)+2) func_PAL_002A7E68(obj,func_002A77E0(2)+2,0,8);
        }
        if (B(obj,0x60)&2) func_002A7750(obj,6,-1);
        break;
    case 6:
        if (func_002B3868(obj) && B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,4);
        if (!(U(obj,0x96)&3)) F(st,0x31C) = (float)func_L02_0032E390(obj,I(st,0x200),-1)*0.087266475f;
        func_PAL_L06_00448968(obj,st+0x1F0,1);
        func_L06_00444068(obj);
        if (F(st,0x1CC)<=1.25f) func_002A7750(obj,7,-1);
        break;
    case 7:
        if (func_002B3868(obj)) {
            F(st,0x320) = func_00283248(F(st,0x1F0)-F(obj,0x10),F(st,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) func_PAL_002A7E68(obj,8,3,5);
        }
        func_L01_00322288(obj,F(st,0x320));
        if (func_PAL_002AF6C0(obj,13.0f)) func_002A8D70(obj,1,0x4000001,0,1,0,0.75f,(float)B(st,0x34),1.0f);
        if (B(obj,0x60)&2) func_002A7750(obj,6,-1);
        break;
    case 10:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=10) func_PAL_002A7E68(obj,10,0,5);
            I(st,0x1BC) = D_L06_001B2348;
        }
        func_00282F20(tmp,st+0x1A0,1.0f);
        func_PAL_L06_00448968(obj,tmp,0);
        if (F(st,0x190)>=F(obj,0x18)) {
            func_002A7750(obj,5,2);
            I(st,0x138) &= ~0x11;
        }
        break;
    }
    func_L06_00443E18(obj);
    if (B(obj,0x31)) func_PAL_L06_00448CF0(obj);
}
