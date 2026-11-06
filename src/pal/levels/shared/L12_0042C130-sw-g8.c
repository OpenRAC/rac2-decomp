/* func_PAL_L12_0042C130, the PAL copy of func_L12_00426C08: the same C, with the rates and speeds
 * rescaled for 50 Hz and the random timers written with the 5/6 scale. */
#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L12_001B21C0 __attribute__((sda));
extern float D_L12_001B21C4 __attribute__((sda));
/* A float pair (lower, upper) read through two address forms. The sda incomplete array has no
 * .extern, so the assembler builds the upper bound with $at, and read as symbol+offset that load
 * stays ahead of the call while the lower bound takes the delay slot. The SDATA view gives the
 * $gp lower bound. */
extern float D_L12_001B21C8[] __attribute__((sda));
extern float D_L12_001B21C8_gp[] SDATA(D_L12_001B21C8);
extern int D_L12_001B29C8[] __attribute__((sda));
extern char D_0018A0E0[], D_00189EA0[];
extern int D_0018C0B0[];
extern void func_PAL_L12_0042CD98(void *);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern int func_00282978(void *);
extern void func_002A7750(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_002B1C20(void *,void *);
extern void func_PAL_L12_0042D378(void *);
extern int func_L00_00329520(void *,int);
extern void func_00282C88(void *);
extern float func_00282DB0(void *,void *);
extern float func_00282E48(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_PAL_L12_0042D200(void *,void *,int);
extern int func_L02_00332630(void *,void *);
extern int func_L02_0032E390(void *,int,int);
extern void func_L09_004051F8(void *);
extern float func_00283248(float,float);
extern void func_L01_00322288(void *,float);
extern int func_PAL_002AF6C0(void *,float);
extern int func_002A8D70(void *,int,int,int,int,int,float,float,float);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_PAL_L07_003FB6B0(void *);
extern void func_PAL_L12_0042D258(void *);
extern void func_PAL_L12_0042D5E8(void *);

void func_PAL_L12_0042C130(char *obj) {
    char *s = *(char **)(obj+0x68);
    /* The aligned local preserves the old position or a temporary vector. */
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    func_PAL_L12_0042CD98(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0072000003f,0.080000006f,0.010053098f,0.5026549f);
            F(s,0x1D0)=D_L12_001B21C4*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.5f;
            H(s,0x35A)=((s32)(func_002A7820(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x334)==1 && func_00282978(s+0x35A)) {
            if (func_002A77E0(3)) func_002A7750(obj,9,2);
            else func_002A7750(obj,8,2);
        } else if (H(s,0x336)) {
            if (func_002A77E0(2)) func_002A7750(obj,7,1);
            else func_002A7750(obj,6,1);
            H(s,0x336)=0;
            if (H(s,0x330)<250) H(s,0x330)=((s32)(func_002A7820(480,600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=D_L12_001B21C0*0.020000001f;
            F(s,0x134)=0.05f;
        }
        if (H(s,0x334)==1) func_002A7750(obj,9,2);
        else if (H(s,0x330)==0) func_002A7750(obj,1,0);
        break;
    case 2:
        if (func_002B3890(obj)) {
            func_002B60B0(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=D_L12_001B21C0*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.05f;
            H(s,0x35A)=((s32)(func_002A7820(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x334)!=1 && func_00282978(s+0x35A)) {
            func_002A7750(obj,3,1);
            H(s,0x330)=((s32)(func_002A7820(580,600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        vec=*(Quad *)(obj+0x10);
        flags=func_002B1C20(obj,s+0x50);
        if (flags&1) func_PAL_L12_0042D378(obj);
        else if (!func_L00_00329520(obj+0x10,W(s,0x230))) {
            qcopy(obj+0x10,&vec);
            func_00282C88(s+0xD0);
        } else if (flags&2) {
            if (H(s,0x334)==1) func_002A7750(obj,9,2);
            else {
                func_002A7750(obj,3,1);
                H(s,0x330)=((s32)(func_002A7820(580,600)) * 5 + 2) / 6;
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (!B(obj,0x31)) break;
        if (func_002B3868(obj)) {
            int choice=!func_002A77E0(4);
            if (B(obj,0x43)!=choice) func_PAL_002A7E68(obj,choice,0,8);
            H(s,0x332)=((s32)(func_002A7820(60,120)) * 5 + 2) / 6;
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) func_PAL_002A7E68(obj,0,0,17);
        } else if (H(s,0x332)==0) {
            if (!H(s,0x358) || func_00282DB0(s+0x320,D_0018A0E0)>0.8f) func_002A7750(obj,2,-1);
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=func_002A7940(); speed=func_002A7878(2,5);
            F(s,0x310)=func_00283180(angle)*speed;
            F(s,0x314)=func_00283198(angle)*speed;
            W(s,0x318)=0;
            func_00282CC0(s+0x310,s+0x310,s+0x300);
            if (W(s,0x238)!=-1) {
                vec=*(Quad *)(s+0x300);
                func_L02_0032EF10(&vec,s+0x310,s+0x310,W(s,0x238),1.5f);
            }
        }
        func_PAL_L12_0042D200(obj,s+0x310,0);
        if (U(obj,0x96)>25 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>150)) func_002A7750(obj,1,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=func_002A77E0(2)+4) func_PAL_002A7E68(obj,func_002A77E0(2)+4,0,8);
        }
        if (func_00282E48(obj+0x10,D_00189EA0)<D_L12_001B21C8_gp[0]) func_002A7750(obj,4,-1);
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
            if (B(obj,0x43)!=func_002A77E0(2)+2) func_PAL_002A7E68(obj,func_002A77E0(2)+2,0,8);
        }
        func_L02_00332630(obj,s+0x1F0);
        if (B(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 7:
        if (func_002B3868(obj) && B(obj,0x43)!=12) func_PAL_002A7E68(obj,12,0,8);
        func_L02_00332630(obj,s+0x1F0);
        if (B(obj,0x60)&2) func_002A7750(obj,3,-1);
        break;
    case 4:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,8);
            F(s,0x354)=func_002A7878(D_L12_001B21C8_gp[0],D_L12_001B21C8[1])+0.5f;
        }
        if ((func_PAL_L12_0042D200(obj,s+0x300,0)&128) || func_00282E80(obj+0x10,D_00189EA0)>F(s,0x354)) {
            if (func_002A77E0(2)) func_002A7750(obj,6,-1);
            else func_002A7750(obj,7,-1);
        }
        break;
    case 5:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=func_002A7940(); speed=func_002A7878(2,5);
            F(s,0x310)=func_00283180(angle)*speed;
            F(s,0x314)=func_00283198(angle)*speed;
            W(s,0x318)=0;
            func_00282CC0(s+0x310,s+0x310,s+0x300);
            if (W(s,0x238)!=-1) {
                vec=*(Quad *)(s+0x300);
                func_L02_0032EF10(&vec,s+0x310,s+0x310,W(s,0x238),1.5f);
            }
        }
        func_PAL_L12_0042D200(obj,s+0x310,0);
        if (U(obj,0x96)>25 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>150)) func_002A7750(obj,3,-1);
        break;
    case 8:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=func_002A77E0(2)+2) func_PAL_002A7E68(obj,func_002A77E0(2)+2,0,8);
        }
        if (B(obj,0x60)&2) func_002A7750(obj,9,-1);
        break;
    case 9:
        if (func_002B3868(obj) && B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,4);
        if (!(U(obj,0x96)&3)) F(s,0x33C)=(float)func_L02_0032E390(obj,D_0018C0B0[0],-1)*0.087266475f;
        func_PAL_L12_0042D200(obj,s+0x1F0,1);
        func_L09_004051F8(obj);
        if (F(s,0x1CC)<=1.25f) func_002A7750(obj,10,-1);
        break;
    case 10:
        if (func_002B3868(obj)) {
            F(s,0x340)=func_00283248(F(s,0x1F0)-F(obj,0x10),F(s,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) func_PAL_002A7E68(obj,8,2,8);
        }
        func_L01_00322288(obj,F(s,0x340));
        if (func_PAL_002AF6C0(obj,13.0f)) func_002A8D70(obj,1,0x4000001,0,1,0,0.75f,(float)B(s,0x34),1.0f);
        if (B(obj,0x60)&2) func_002A7750(obj,9,-1);
        break;
    case 14:
        if (func_002B3868(obj)) {
            if (B(obj,0x43)!=10) func_PAL_002A7E68(obj,10,0,5);
            W(s,0x1BC)=D_L12_001B29C8[0];
        }
        func_00282F20(&vec,s+0x1A0,1.0f);
        func_PAL_L12_0042D200(obj,&vec,0);
        func_PAL_L07_003FB6B0(obj);
        func_002A8C28(obj,obj+0x10,0x4000000,0,1,0,0.6f,(float)B(s,0x34),1.0f);
        if (F(s,0x190)>=F(obj,0x18)) {
            if (H(s,0x334)==1) func_002A7750(obj,8,2);
            else func_002A7750(obj,2,0);
            W(s,0x138)&=~0x11;
        }
        break;
    case 12: func_PAL_L12_0042D378(obj); break;
    }
    func_PAL_L12_0042D258(obj);
    if (B(obj,0x31)) func_PAL_L12_0042D5E8(obj);
}
