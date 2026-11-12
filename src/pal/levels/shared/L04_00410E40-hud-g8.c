#include "include_asm.h"

#include "common.h"

/* func_PAL_L04_00410E40: the PAL copy of func_L04_0040C880 (src/levels/shared/L04_00402D90-hud-g8.c),
   with the same flags. PAL runs at 50 Hz, so the fade-in timeline is shorter: its 150-frame base is 125,
   every window bound goes through pal_frames, and the fade rates are 1/25 and 1/12 (v1.01: 1/30, 1/15).

   pal_frames is an inline function: the compiler integrates it with constant arguments substituted, so
   entry 4's bounds fold to 100, 124, 130 and 142 but keep the divide-by-zero check on the divisor, as in
   retail. The other entries' bounds are computed one at a time through j, from the window start kept
   in first; retail evaluates each argument afresh into one register. */
typedef struct { int v[5]; } B1202Five;
extern B1202Five D_L04_001B09B0, D_L04_001B09C8, D_L04_001B09E0, D_L04_001B09F8;
extern int D_L04_001A8FE8 __attribute__((sda));
extern unsigned char *D_L04_001A904C;
typedef struct { unsigned char pad[0xb0]; float tan_half; } ProjectionState;
extern ProjectionState D_L04_001BDB80;
extern float D_L04_001B2D44;
extern int D_001A7B90;
extern int D_L04_001B2D40;

/* Upstream's hud_coord (src/game/00326A10-g8.c), unchanged, with this level's display-mode global.
   The display-mode test has no effect on the result, but it is real: its load and compare go at
   flow2, after allocation, which leaves the saved but unused register ($s5, as in retail). */
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
/* Typed interleaving (docs/build/compiler-notes.md, "Source methods shared with RAC1"): the same two
   integer and five float arguments, in the same order within each register bank. */
extern void func_00300A00(int,float,int,float,float,float,float);
extern void func_002FC560(int,unsigned long long);
/* A 60 Hz frame count as PAL's 50 Hz one, rounded to nearest. */
static __inline__ int pal_frames(int n)
{
    return (n * 5 + 2) / 6;
}

void func_PAL_L04_00410E40(unsigned char *m)
{
    B1202Five x = D_L04_001B09B0;
    B1202Five y = D_L04_001B09C8;
    B1202Five start = D_L04_001B09E0;
    B1202Five end = D_L04_001B09F8;
    int colors[5];
    unsigned char *p = *(unsigned char **)(m+0x68);
    int frame,i,j,right,a,b,c,d;
    int sprite,s1;
    float angle, sine, sign, fx, fy;
    int one, top, off;
    if (m[0xbc]==3 || m[0xbc]==4 || m[0xbc]==1 || m[0xbc]==2) frame=125-*(int *)(p+0x394);
    else frame=D_L04_001A8FE8+125;
    if (!D_L04_001A904C) return;
    for(i=0;i<5;i++) {
        if(i==4) { a=pal_frames(120);b=pal_frames(149);c=pal_frames(156);d=pal_frames(171); }
        else { int first; j=i*30; first=j; a=pal_frames(j); j=first+30; b=pal_frames(j); j=first+30; c=pal_frames(j); j=first+45; d=pal_frames(j); }
        colors[i]=0;
        if(frame>=a && frame<b) colors[i]=func_00283D38(0,start.v[i],(float)(frame-a)*0.04f);
        else if(frame>=b && frame<c && b!=c) colors[i]=start.v[i];
        else if(frame>=c && frame<d) colors[i]=func_00283D38(start.v[i],end.v[i],(float)(frame-c)*0.083333336f);
        else if(frame>=d) colors[i]=end.v[i];
    }
    i=0;
    off=0x8710;
    angle=0.56217057f;
    sine=func_00283198(angle);
    sine=sine/func_00283180(angle);
    D_L04_001BDB80.tan_half=sine;
    func_0027AB40();

    one=1;
    for(;i<2;i++) {
        if(i==0) {j=10;right=31;sign=1.0f;} else {j=498;right=478;sign=-1.0f;}
        fx=(float)j;
        s1=func_00336D50((char *)D_L04_001A904C+off,58);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        func_00300A00(s1,(float)j,0x60442d00,(float)top,sign,1.0f,0.0f);
        sprite=func_00336D50((char *)D_L04_001A904C+off,59);
        top=hud_coord(120.0f,D_L04_001B2D44,0.5f,one);
        func_00300A00(sprite,(float)j,0x55f0c070,(float)top,sign,1.0f,0.0f);
        sprite=func_00336D50((char *)D_L04_001A904C+off,60);
        func_00300A00(sprite,fx,0x55f0c070,(float)hud_coord(120.0f,D_L04_001B2D44,0.5f,one),sign,1.0f,0.0f);
        fy=(float)right;
        for(j=0;j<5;j++) {
            func_00300A00(func_00336D50((char *)D_L04_001A904C+0x8710,61),fy,colors[j],(float)(D_001A7B90?y.v[j]:x.v[j]),0.8f,0.8f,0.0f);
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
