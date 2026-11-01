/* GPT-6.1 Sol worker v0614, 28 October 2026. Not linked.
 * Profile: -O2 -G8 -ffunction-sections -g -mno-split-addresses.
 * Retained: 1288/1300 bytes, 0/28 places; separate early wait arm was
 * 1304/1300 bytes. The shared wait label reproduces the real state-zero
 * control flow. Eight-entry retail jump table decoded from boot 0x26DD50.
 * Remaining: camera base becomes camera+0x144 instead of camera, float-zero
 * stores become integer stores, absolute/GP address scheduling and saved
 * object register differ. Next: actual camera field model/base lifetime.
 * All required declarations are below. Earlier screening's straight-line
 * description was incorrect: this is an eight-state transition dispatcher.
 * Closer C2, 1 November 2026: retail mixes two address forms. Data loads are macro loads of length 2 (lui+lw, not
 * moved into call slots, one $gp store in a delay slot), as -mno-split-addresses plus MACRO_ADDR gives for
 * D_001B23xx; D_001AD7xx is sda ($gp everywhere). But the jump table and D_001A63A8 / D_001B5200 are split: lui and
 * addiu have other insns between them, which only split mode gives. Neither profile does both yet. Also needed:
 * float zero through a local (swc1, not sw) and the camera as a plain base (+0x144 stays in the offset).
 */
#include "common.h"
extern short D_001B2310 MACRO_ADDR, D_001B2312 MACRO_ADDR, D_001B2318 NOT_SDA, D_001B231E NOT_SDA;
extern unsigned char D_001B231D MACRO_ADDR, D_001B2344 MACRO_ADDR, D_001B2345 MACRO_ADDR;
extern short D_001B2346 NOT_SDA;
extern float D_001B2314 NOT_SDA;
extern char *D_001B2340 NOT_SDA;
extern int D_001AD7E4 MACRO_ADDR, D_001AD7E8 MACRO_ADDR, D_001AD7F8 MACRO_ADDR;
extern short D_001AD7FC MACRO_ADDR, D_001AD800 MACRO_ADDR, D_001AD804 MACRO_ADDR;
typedef union { char b[0x500]; short h[0x280]; float f[0x140]; } CameraState;
extern CameraState D_001A63A8, D_001B5200;
extern float D_001B90F0 NOT_SDA;
extern short D_0018A000;
extern int func_00282978(short *);
extern void func_002B6D28(void), func_00283360(void *), func_0027AB40(void);
extern float func_00283B98(float,float), func_00283198(float), func_00283180(float), func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027D098(void (*)(void),int);
extern void func_002FFCF8(void), func_002FFFE0(void), func_002FF3F8(void);
extern void func_002FF968(char *), func_002FFD78(char *);
extern char *func_002FFB68(char *);
extern void func_00287EB0(int), func_00288508(int), func_002AD860(int);
extern void func_002B49E0(int,int,int,int,int);
void func_002FF450(void)
{
    char *object;
    float angle, sine;
    switch(D_001B2310) {
    case 0:
        if (func_00282978(&D_001B2312)) {
            if (D_001AD7E4 &&
                (D_001A63A8.h[0x72/2]!=3 || D_001A63A8.h[0x6c/2]>=6000) &&
                D_001AD7E8++<181) goto wait_for_transition;
            func_002B6D28();
            D_001B5200.f[0x144/4]=25.0f;
            D_001B5200.f[0x148/4]=900.0f;
            D_001B5200.f[0x140/4]=25.0f;
            D_001AD7E4=0;
            D_001AD7E8=0;
            func_00283360(D_001B5200.b+0x370);
            object=D_001B2340;
            D_001B2310=1;
            D_001B2312=D_001AD7FC;
            D_001B5200.f[0x150/4]=0.0f;
            D_001B5200.f[0x158/4]=0.0f;
            D_001B5200.f[0x154/4]=0.0f;
            D_001B231E=0;
            qcopy(object+0xf0,D_001B5200.b+0x150);
            if(D_001B2345) *(float *)(object+0xf4)=func_00283B98(*(float *)(object+0xf4),-1.5707964897155762f);
            angle=0.5621705651283264f;
            sine=func_00283198(angle);
            D_001B90F0=sine/func_00283180(angle);
            func_0027AB40();
            *(unsigned short *)(object+0x34)&=0xffbe;
        } else {
wait_for_transition:
            func_0027D098(func_002FFCF8,0);
        }
        break;
    case 1:
        func_002FF968(D_001B2340);
        if(func_00282978(&D_001B2312)) {
            D_001B2312=D_001AD800;
            D_001B2314=1.0f/func_00283CE0((short)D_001AD800);
            D_001B2310=2;
            D_001B2344=0;
        }
        break;
    case 2:
        object=D_001B2340;
        func_002FF968(object);
        func_002FFD78(object);
        if(func_00282978(&D_001B2312)) {
            D_001B2312=2;
            D_001B2310=3;
            D_001B2346=128;
            func_0027D098(func_002FFFE0,0);
        }
        break;
    case 3:
        object=D_001B2340;
        func_0027D098(func_002FFFE0,0);
        if(func_00282978(&D_001B2312)) {
            D_001B2312=12;
            D_001B2310=4;
            D_001B2340=func_002FFB68(object);
        }
        break;
    case 4:
        if(D_001B2340) func_002FF968(D_001B2340);
        func_0027D098(func_002FFFE0,0);
        D_001B2346=func_00283CF0(func_00283CE0(D_001B2312)*0.0833333358168602f*128.0f);
        if(func_00282978(&D_001B2312)) {
            D_001B2310=5;
            D_001B2312=D_001AD804;
            D_001B2346=0;
        }
        break;
    case 5:
        if(D_001B2340) func_002FF968(D_001B2340);
        if(func_00282978(&D_001B2312)) {
            D_001B2312=3;
            D_001B2310=6;
        }
        break;
    case 6:
        if(D_001B2340) func_002FF968(D_001B2340);
        func_0027D098(func_002FFCF8,0);
        if(func_00282978(&D_001B2312)) {
            D_001B2312=0;
            D_001B2314=1.0f/func_00283CE0(D_001AD7F8);
            D_001B231D=1;
            D_001B231E=1;
            D_0018A000=D_001AD7F8+5;
            func_002FF3F8();
            D_001B2340=0;
            func_00287EB0(D_001B2318);
            func_00288508(D_001B2318);
            if(D_001B2345) func_002AD860(D_001B2318);
            D_001B2310=7;
        }
        break;
    case 7:
        if(D_001B2312++>=D_001AD7F8) func_002B49E0(0,2,0,0,0);
        else func_0027D098(func_002FFCF8,0);
        break;
    }
}
