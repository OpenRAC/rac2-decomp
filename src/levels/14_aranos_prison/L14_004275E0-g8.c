#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L14_001B18B0 __attribute__((sda));
extern float D_L14_001B18B4 __attribute__((sda));
/* A float pair (lower, upper), read through two address forms as in func_L12_00426C08. */
extern float D_L14_001B18B8[] __attribute__((sda));
extern float D_L14_001B18B8_gp[] SDATA(D_L14_001B18B8);
extern int D_L14_001B20C8[] __attribute__((sda));
extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0[];
extern void func_L14_004281D0(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_002B1C20(void *,void *);
extern void func_L02_003CEA28(void *);
extern float func_00282DB0(void *,void *);
extern float func_00282E48(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_L02_003CE8B0(void *,void *,int);
extern int func_L02_00332630(void *,void *);
extern int func_L02_0032E390(void *,int,int);
extern void func_L02_003CEC70(void *);
extern float func_00283248(float,float);
extern void func_L01_00322288(void *,float);
extern int func_002AEB60(void *,float);
extern int func_002A8D70(void *,int,float,float,int,float,int,int,int);
extern int func_002A8C28(void *,void *,float,float,int,float,int,int,int);
extern void func_00282F20(void *,void *,float);
extern void func_L07_003F6F00(void *);
extern void func_L02_003CE908(void *);
extern void func_L14_00428A08(void *);

void func_L14_004275E0(char *obj) {
    char *s = *(char **)(obj+0x68);
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    func_L14_004281D0(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.005f,0.06666667f,0.006981317885220051f,0.4188791f);
            F(s,0x1D0)=D_L14_001B18B4*0.016666668f;
            F(s,0x124)=0.006666667f;
            F(s,0x134)=0.5f;
            H(s,0x33A)=func_002A7820(0,30);
        }
        if (H(s,0x314)==1 && func_00282978(s+0x33A)) {
            if (func_002A77E0(3)) func_002A7750(obj,9,2);
            else func_002A7750(obj,8,2);
        } else if (H(s,0x316)) {
            if (func_002A77E0(2)) func_002A7750(obj,7,1);
            else func_002A7750(obj,6,1);
            H(s,0x316)=0;
            if (H(s,0x310)<300) H(s,0x310)=func_002A7820(480,600);
        }
        break;
    case 1:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(s,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(s,0x134)=0.05f;
        }
        if (H(s,0x314)==1) func_002A7750(obj,9,2);
        else if (H(s,0x310)==0) func_002A7750(obj,1,0);
        break;
    case 2:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(s,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(s,0x124)=0.006666667f;
            F(s,0x134)=0.05f;
            H(s,0x33A)=func_002A7820(0,30);
        }
        if (H(s,0x314)!=1 && func_00282978(s+0x33A)) {
            func_002A7750(obj,3,1);
            H(s,0x310)=func_002A7820(580,600);
        }
        break;
    case 3:
        flags=func_002B1C20(obj,s+0x50);
        if (flags&1) func_L02_003CEA28(obj);
        else if (flags&2) {
            if (H(s,0x314)==1) func_002A7750(obj,9,2);
            else {
                func_002A7750(obj,3,1);
                H(s,0x310)=func_002A7820(580,600);
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (!B(obj,0x31)) break;
        if (func_002B3868(obj)) {
            int choice=!func_002A77E0(4);
            if (B(obj,0x43)!=choice) func_002A7470(obj,choice,0,10);
            H(s,0x312)=func_002A7820(60,120);
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) func_002A7470(obj,0,0,20);
        } else if (H(s,0x312)==0) {
            if (!H(s,0x338) || func_00282DB0(s+0x300,D_0018A0E0)>0.8f) func_002A7750(obj,2,-1);
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_002A7470(obj,6,0,20);
            angle=func_002A7940(); speed=func_002A7878(2,5);
            F(s,0x2F0)=func_00283180(angle)*speed;
            F(s,0x2F4)=func_00283198(angle)*speed;
            W(s,0x2F8)=0;
            func_00282CC0(s+0x2F0,s+0x2F0,s+0x2E0);
            if (W(s,0x218)!=-1) {
                vec=*(Quad *)(s+0x2E0);
                func_L02_0032EF10(&vec,s+0x2F0,s+0x2F0,W(s,0x218),1.5f);
            }
        }
        func_L02_003CE8B0(obj,s+0x2F0,0);
        if (U(obj,0x96)>30 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>180)) func_002A7750(obj,1,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=func_002A77E0(2)+4) func_002A7470(obj,func_002A77E0(2)+4,0,10);
        }
        if (func_00282E48(obj+0x10,D_00189EA0)<D_L14_001B18B8_gp[0]) func_002A7750(obj,4,-1);
        else if (B(obj,0x60)&2) {
            switch (func_002A77E0(3)) {
            case 0:func_002A7750(obj,6,-1);break;
            case 1:func_002A7750(obj,7,-1);break;
            case 2:func_002A7750(obj,5,-1);break;
            }
        }
        break;
    case 6:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=func_002A77E0(2)+2) func_002A7470(obj,func_002A77E0(2)+2,0,10);
        }
        func_L02_00332630(obj,s+0x1F0);
        if (B(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 7:
        if (func_002B3868(obj) && B(obj,0x43)!=12) func_002A7470(obj,12,0,10);
        func_L02_00332630(obj,s+0x1F0);
        if (B(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 4:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_002A7470(obj,6,0,10);
            F(s,0x334)=func_002A7878(D_L14_001B18B8_gp[0],D_L14_001B18B8[1])+0.5f;
        }
        if ((func_L02_003CE8B0(obj,s+0x2E0,0)&128) || func_00282E80(obj+0x10,D_00189EA0)>F(s,0x334)) {
            if (func_002A77E0(2)) func_002A7750(obj,6,-1);
            else func_002A7750(obj,7,-1);
        }
        break;
    case 5:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_002A7470(obj,6,0,20);
            angle=func_002A7940(); speed=func_002A7878(2,5);
            F(s,0x2F0)=func_00283180(angle)*speed;
            F(s,0x2F4)=func_00283198(angle)*speed;
            W(s,0x2F8)=0;
            func_00282CC0(s+0x2F0,s+0x2F0,s+0x2E0);
            if (W(s,0x218)!=-1) {
                vec=*(Quad *)(s+0x2E0);
                func_L02_0032EF10(&vec,s+0x2F0,s+0x2F0,W(s,0x218),1.5f);
            }
        }
        func_L02_003CE8B0(obj,s+0x2F0,0);
        if (U(obj,0x96)>30 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>180)) func_002A7750(obj,3,-1);
        break;
    case 8:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=func_002A77E0(2)+2) func_002A7470(obj,func_002A77E0(2)+2,0,10);
        }
        if (B(obj,0x60)&2) func_002A7750(obj,9,-1);
        break;
    case 9:
        if (func_002B3868(obj) && B(obj,0x43)!=6) func_002A7470(obj,6,0,5);
        if (!(U(obj,0x96)&3)) F(s,0x31C)=(float)func_L02_0032E390(obj,D_0018C0B0[0],-1)*0.087266475f;
        func_L02_003CE8B0(obj,s+0x1F0,1);
        func_L02_003CEC70(obj);
        if (F(s,0x1CC)<=1.25f) func_002A7750(obj,10,-1);
        break;
    case 10:
        if (func_002B3868(obj)) {
            F(s,0x320)=func_00283248(F(s,0x1F0)-F(obj,0x10),F(s,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) func_002A7470(obj,8,2,10);
        }
        func_L01_00322288(obj,F(s,0x320));
        if (func_002AEB60(obj,13.0f)) {
            char *t=*(char **)(s+0x200);
            int play=1;
            if (t && H(t,0xAA)==0x964 && U(obj,0x96)<=59) play=0;
            if (play) func_002A8D70(obj,1,0.75f,1.0f,0x4000001,1.0f,0,1,0);
        }
        if ((B(obj,0x60)&2) && func_00282E80(obj+0x10,s+0x1F0)>1.25f) func_002A7750(obj,9,-1);
        break;
    case 14:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=10) func_002A7470(obj,10,0,5);
            W(s,0x1BC)=D_L14_001B20C8[0];
        }
        func_00282F20(&vec,s+0x1A0,1.0f);
        func_L02_003CE8B0(obj,&vec,0);
        func_L07_003F6F00(obj);
        func_002A8C28(obj,obj+0x10,0.6f,1.0f,0x4000000,1.0f,0,1,0);
        if (F(s,0x190)>=F(obj,0x18)) {
            if (H(s,0x314)==1) func_002A7750(obj,8,2);
            else func_002A7750(obj,2,0);
            W(s,0x138)&=~0x11;
        }
        break;
    case 12: func_L02_003CEA28(obj); break;
    }
    func_L02_003CE908(obj);
    if (B(obj,0x31)) func_L14_00428A08(obj);
}
