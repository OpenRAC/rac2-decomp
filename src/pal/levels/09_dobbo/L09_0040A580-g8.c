/* func_PAL_L09_0040A580, the PAL copy of func_L09_00405610 in L09_00405610-g8.c: the same C, where the
   timers take the 50 Hz scale, the turn and blend rates change, and callees take their PAL names. */
#include "common.h"

typedef int DobboQuad __attribute__((mode(TI)));
extern int D_L09_001B1428 __attribute__((sda));
extern float D_L09_001B13F4 __attribute__((sda));
extern float D_L09_001B13F8 __attribute__((sda));
extern float D_L09_001B13F8_1[] __attribute__((sda)); /* { lower, upper } bounds, read as a pair */
extern char D_L09_00189EA0[];
extern void func_PAL_L09_00409DC8(char *);
extern int func_002B3890(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern void func_002A7750(char *, int, int);
extern int func_002A7820(int, int);
extern int func_002B1C20(char *, void *);
extern void func_PAL_L09_0040A050(char *);
extern int func_002B3868(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_PAL_L09_00409AC8(char *, int);
extern void func_PAL_L09_00409B48(char *, int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L02_0032EF10(void *, void *, void *, int, float);
extern int func_PAL_L09_00409F00(char *, void *, int);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_L02_00332630(char *, void *);
extern float func_00283248(float, float);
extern void func_PAL_002B5E30(char *, float);
extern int func_L02_0032E390(char *, void *, int);
extern void func_L09_004051F8(char *);
extern void func_L01_00322288(char *, float);
extern int func_PAL_002AF6C0(char *, float);
extern void func_002A8D70(char *, int, int, int, int, int, float, float, float);
extern void func_PAL_L09_00409F38(char *);
extern void func_PAL_L09_0040A268(char *);

#define BYTE(p,o) (*(u8 *)((p)+(o)))
#define HALF(p,o) (*(s16 *)((p)+(o)))
#define WORD(p,o) (*(s32 *)((p)+(o)))
#define FLOAT(p,o) (*(float *)((p)+(o)))

void func_PAL_L09_0040A580(char *obj)
{
    DobboQuad position;
    char *data;
    char *target;
    int flags;
    int animation;
    float angle, speed;
    if (D_L09_001B1428) return;
    data = *(char **)(obj + 0x68);
    func_PAL_L09_00409DC8(obj);
    if (!obj || BYTE(obj,0x20) == 0xFE || BYTE(obj,0x20) == 0xFD) return;
    switch (BYTE(obj,0x95)) {
    case 0:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0016000001f,0.040000003f,0.010053098f,0.5026549f);
            FLOAT(data,0x124)=0.0096f;
            FLOAT(data,0x134)=0.5f;
        }
        if (HALF(data,0x334)==1 && func_00282948(data+0x35C)) {
            if (!func_002A77E0(4)) func_002A7750(obj,9,2);
            else func_002A7750(obj,8,2);
        } else if (HALF(data,0x336)) {
            if (!func_002A77E0(1)) func_002A7750(obj,7,1);
            else func_002A7750(obj,6,1);
            HALF(data,0x336)=0;
            if (HALF(data,0x330)<250) HALF(data,0x330)=(((int)(func_002A7820(480,600)) * 5 + 2) / 6);
        }
        break;
    case 1:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0032000002f,0.10000001f,0.010053098f,0.5026549f);
            FLOAT(data,0x1D0)=D_L09_001B13F4*0.020000001f;
            FLOAT(data,0x134)=0.05f;
        }
        if (HALF(data,0x334)==1) func_002A7750(obj,9,2);
        else if (!HALF(data,0x330)) func_002A7750(obj,1,0);
        break;
    case 2:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0048f,0.10000001f,0.010053098f,0.5026549f);
            FLOAT(data,0x1D0)=D_L09_001B13F4*0.020000001f;
            FLOAT(data,0x124)=0.0096f;
            FLOAT(data,0x134)=0.05f;
            WORD(data,0x35C)=(((int)(func_002A7820(0,30)) * 5 + 2) / 6);
        }
        if (HALF(data,0x334)!=1 && func_00282948(data+0x35C)) {
            func_002A7750(obj,3,1);
            HALF(data,0x330)=(((int)(func_002A7820(580,600)) * 5 + 2) / 6);
        }
        break;
    case 3:
        flags=func_002B1C20(obj,data+0x50);
        if (flags&1) func_PAL_L09_0040A050(obj);
        else if (flags&2) {
            if (HALF(data,0x334)==1) func_002A7750(obj,9,2);
            else {
                func_002A7750(obj,3,1);
                HALF(data,0x330)=(((int)(func_002A7820(580,600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    switch (BYTE(obj,0x20)) {
    case 1:
        if (!BYTE(obj,0x31)) break;
        if (func_002B3868(obj)) {
            animation=!func_002A77E0(4);
            if (BYTE(obj,0x43)!=animation) func_PAL_002A7E68(obj,animation,0,17);
            HALF(data,0x332)=(((int)(func_002A7820(60,120)) * 5 + 2) / 6);
        }
        if (BYTE(obj,0x43)==1) {
            if (BYTE(obj,0x60)&2) func_PAL_002A7E68(obj,0,0,17);
        } else if (!HALF(data,0x332)) func_002A7750(obj,2,-1);
        break;
    case 2:
        if (func_002B3868(obj)) {
            func_PAL_L09_00409AC8(obj,20);
            angle=func_002A7940(); speed=func_002A7878(2.0f,5.0f);
            FLOAT(data,0x310)=func_00283180(angle)*speed;
            FLOAT(data,0x314)=func_00283198(angle)*speed;
            WORD(data,0x318)=0;
            func_00282CC0((data+0x310),(data+0x310),data+0x300);
            if (WORD(data,0x234)!=-1) {
                position=*(DobboQuad *)(data+0x300);
                func_L02_0032EF10(&position,(data+0x310),(data+0x310),WORD(data,0x234),1.5f);
            }
        }
        func_PAL_L09_00409F00(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>25 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>150)) func_002A7750(obj,1,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            if (BYTE(obj,0x43)!=func_002A77E0(2)+4) func_PAL_002A7E68(obj,func_002A77E0(2)+4,0,8);
        }
        if (func_00282E48(obj+0x10,D_L09_00189EA0)<D_L09_001B13F8) func_002A7750(obj,4,-1);
        else if (BYTE(obj,0x60)&2) {
            switch (func_002A77E0(3)) {
            case 0: func_002A7750(obj,6,-1); break;
            case 1: func_002A7750(obj,7,-1); break;
            case 2: func_002A7750(obj,5,-1); break;
            }
        }
        break;
    case 6:
        if (func_002B3868(obj)) {
            if (BYTE(obj,0x43)!=func_002A77E0(2)+2) func_PAL_002A7E68(obj,func_002A77E0(2)+2,0,8);
        }
        func_L02_00332630(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 7:
        if (func_002B3868(obj)) {
            if (BYTE(obj,0x43)!=12) func_PAL_002A7E68(obj,12,0,8);
        }
        func_L02_00332630(obj,data+0x1F0);
        if (BYTE(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 4:
        if (func_002B3868(obj)) {
            func_PAL_L09_00409B48(obj,10);
            FLOAT(data,0x238)=func_002A7878(D_L09_001B13F8,D_L09_001B13F8_1[1])+0.5f;
        }
        if ((func_PAL_L09_00409F00(obj,data+0x300,0)&0x80) || FLOAT(data,0x238)<func_00282E80(obj+0x10,D_L09_00189EA0)) {
            if (func_002A77E0(2)) func_002A7750(obj,6,-1);
            else func_002A7750(obj,7,-1);
        }
        break;
    case 5:
        if (func_002B3868(obj)) {
            func_PAL_L09_00409B48(obj,20);
            angle=func_002A7940(); speed=func_002A7878(2.0f,5.0f);
            FLOAT(data,0x310)=func_00283180(angle)*speed;
            FLOAT(data,0x314)=func_00283198(angle)*speed;
            WORD(data,0x318)=0;
            func_00282CC0((data+0x310),(data+0x310),data+0x300);
            if (WORD(data,0x234)!=-1) {
                position=*(DobboQuad *)(data+0x300);
                func_L02_0032EF10(&position,(data+0x310),(data+0x310),WORD(data,0x234),1.5f);
            }
        }
        func_PAL_L09_00409F00(obj,(data+0x310),0);
        if (*(u16 *)(obj+0x96)>25 && (FLOAT(data,0x1CC)<=0.5f || *(u16 *)(obj+0x96)>150)) func_002A7750(obj,3,-1);
        break;
    case 8:
        if (func_002B3868(obj)) {
            FLOAT(data,0x114)=0.025551625f;
            FLOAT(data,0x11C)=1.2775812f;
            if (BYTE(obj,0x43)!=func_002A77E0(2)+2) func_PAL_002A7E68(obj,func_002A77E0(2)+2,0,8);
        }
        target=*(char **)(data+0x200);
        func_PAL_002B5E30(obj,func_00283248(FLOAT(target,0x10)-FLOAT(obj,0x10),FLOAT(target,0x14)-FLOAT(obj,0x14)));
        flags = BYTE(obj,0x60);
        flags &= 2;
        if (flags) {
            FLOAT(data,0x114)=0.010053098f;
            FLOAT(data,0x11C)=0.5026549f;
            func_002A7750(obj,9,-1);
        }
        break;
    case 9:
        if (func_002B3868(obj)) func_PAL_L09_00409B48(obj,5);
        if (!(*(u16 *)(obj+0x96)&3)) FLOAT(data,0x33C)=func_L02_0032E390(obj,*(void **)(data+0x200),-1)*0.08726647496f;
        func_PAL_L09_00409F00(obj,data+0x1F0,1);
        func_L09_004051F8(obj);
        if (FLOAT(data,0x1CC)<=1.25f) func_002A7750(obj,10,-1);
        break;
    case 10:
        if (func_002B3868(obj)) {
            FLOAT(data,0x340)=func_00283248(FLOAT(data,0x1F0)-FLOAT(obj,0x10),FLOAT(data,0x1F4)-FLOAT(obj,0x14));
            if (BYTE(obj,0x43)!=8) func_PAL_002A7E68(obj,8,2,8);
        }
        func_L01_00322288(obj,FLOAT(data,0x340));
        if (func_PAL_002AF6C0(obj,13.0f)) func_002A8D70(obj,1,0x4000001,0,1,0,0.75f,(float)BYTE(data,0x34),1.0f);
        if (BYTE(obj,0x60)&2) func_002A7750(obj,9,-1);
        break;
    }
    func_PAL_L09_00409F38(obj);
    if (BYTE(obj,0x31)) func_PAL_L09_0040A268(obj);
}
