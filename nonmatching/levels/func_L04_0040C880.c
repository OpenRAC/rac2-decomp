/* sol-high, USA v1.01. 8 November 2026: 1360/1360 bytes, 0/2 places, first mismatch +0x198
 * (was +0x8). Flags: -O2 -G8 -ffunction-sections -frac2-gcse-unsplit-edges in a -g8.c unit.
 * Fixed: hud_coord dead-test helper (owner ruling) gives retail's ghost callee-saved reg and the
 * p spill at sp+0xA0; colour is func_00300A00's 2nd int arg (majority prototype) and the inner
 * draw nests the lookup call; j doubles as the i*30 temp, the x position and the inner index,
 * i as the side counter (retail s0/s4 reuse); four == tests (andi re-extend); b!=c folded into
 * the second condition; top precomputed for draws 58/59 so (float)j there is a gcse copy of fx
 * (retail f22->f20); ProjectionState view for the 0xB0 store; quotient kept in sine; block two
 * uses its own locals; -frac2-gcse-unsplit-edges puts frame<c in v1.
 * Remaining (about 10 rows): (1) else arm: cse swaps b=a+30;c=b into c=a+30;b=c (c is the
 * canonical reg); putting d between stops the swap but then b outranks c (12/36 vs 12/38);
 * (2) one (7 refs, live 244) loses s5 to the hoisted 0x8710 (7 refs, live 232): sched1 puts
 * one=1 above the sin call; inside the loop it is const-propagated; literal 1 kills the ghost;
 * (3) draw 58: mov.s f20,f22 and daddu a0,v0 swapped, ori/mov.s f12 swapped (f20 stays live
 * to draw 59). Tried: helper for draws 58/59 (pair or single), label_y with sprite handle,
 * literal angle, one before angle/at start/after lookup, c-before-b declarations,
 * -fno-sched-interblock, -frac2-keep-block-order.
 */
#include "common.h"
typedef struct { int v[5]; } B1202Five;
extern B1202Five D_L04_001B09B0, D_L04_001B09C8, D_L04_001B09E0, D_L04_001B09F8;
extern int D_L04_001A8FE8 __attribute__((sda));
extern unsigned char *D_L04_001A904C;
typedef struct { unsigned char pad[0xb0]; float tan_half; } ProjectionState;
extern ProjectionState D_L04_001BDB80;
extern float D_L04_001B2D44;
extern int D_001A7B90;
extern int D_L04_001B2D40;
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L04_001B2D40 == active)
        scaled = 1.0f;
    return result;
}
extern int func_00283D38(int,int,float);
extern float func_00283198(float),func_00283180(float);
extern void func_0027AB40(void);
extern int func_00336D50(char *,int);
extern void func_00300A00(int,int,float,float,float,float,float);
extern void func_002FC560(int,unsigned long long);
void func_L04_0040C880(unsigned char *m)
{
    B1202Five x = D_L04_001B09B0;
    B1202Five y = D_L04_001B09C8;
    B1202Five start = D_L04_001B09E0;
    B1202Five end = D_L04_001B09F8;
    int colors[5];
    unsigned char *p = *(unsigned char **)(m+0x68);
    int frame,i,j,right,a,b,c,d;
    int sprite;
    float angle, sine, sign, fx, fy;
    int one, top;
    if (m[0xbc]==3 || m[0xbc]==4 || m[0xbc]==1 || m[0xbc]==2) frame=150-*(int *)(p+0x394);
    else frame=D_L04_001A8FE8+150;
    if (!D_L04_001A904C) return;
    for(i=0;i<5;i++) {
        if(i==4) { a=120;b=149;c=156;d=171; }
        else { j=i*30; a=j;b=a+30;c=b;d=a+45; }
        colors[i]=0;
        if(frame>=a && frame<b) colors[i]=func_00283D38(0,start.v[i],(float)(frame-a)*0.033333335f);
        else if(frame>=b && frame<c && b!=c) colors[i]=start.v[i];
        else if(frame>=c && frame<d) colors[i]=func_00283D38(start.v[i],end.v[i],(float)(frame-c)*0.06666667f);
        else if(frame>=d) colors[i]=end.v[i];
    }
    angle=0.56217057f;
    sine=func_00283198(angle);
    sine=sine/func_00283180(angle);
    D_L04_001BDB80.tan_half=sine;
    func_0027AB40();

    one=1;
    for(i=0;i<2;i++) {
        if(i==0) {j=10;right=31;sign=1.0f;} else {j=498;right=478;sign=-1.0f;}
        fx=(float)j;
        sprite=func_00336D50((char *)D_L04_001A904C+0x8710,58);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        func_00300A00(sprite,0x60442d00,(float)j,(float)top,sign,1.0f,0.0f);
        sprite=func_00336D50((char *)D_L04_001A904C+0x8710,59);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        func_00300A00(sprite,0x55f0c070,(float)j,(float)top,sign,1.0f,0.0f);
        sprite=func_00336D50((char *)D_L04_001A904C+0x8710,60);
        func_00300A00(sprite,0x55f0c070,fx,(float)hud_coord(120.0f,D_L04_001B2D44,0.5f,one),sign,1.0f,0.0f);
        fy=(float)right;
        for(j=0;j<5;j++) {
            func_00300A00(func_00336D50((char *)D_L04_001A904C+0x8710,61),colors[j],fy,(float)(D_001A7B90?y.v[j]:x.v[j]),0.8f,0.8f,0.0f);
        }
        func_002FC560(71,0x5360b);
    }
    if(m[0x20]!=3) {
        float turn, ratio;
        turn=*(float *)(p+0x28c);
        turn*=0.008726647f;
        ratio=func_00283198(turn);
        ratio=ratio/func_00283180(turn);
        D_L04_001BDB80.tan_half=ratio;
        func_0027AB40();
    }
}
