/* func_US2_L04_0040C224 (placed in levels 04 and 11): the USA v2.00 race-challenge panel, the copy
   of v1.01's func_L04_0040AD28. Plain C, built with -O2 -G8 -ffunction-sections -g in a unit of its
   own and no compiler switches. label_y and hud_coord are the owner-allowed dead-test helpers that
   keep retail's block boundaries after each conversion. Each title arm looks up its own string
   (jump2 cross-jumps the identical tails), one `label` carries every looked-up string the panel
   draws, and `count` carries the pulsing tint from func_00283D38, then the clear count, then the
   time (reused locals).

   Against v1.01: the text ids are 0x16A lower, the clear count is clamped right after
   func_L04_0040A1D0 returns, and the time is drawn with func_0027FB40 at center + 50 (v1.01:
   func_0027FAA8 at center + 46). */
#include "common.h"
extern int D_001A7340, D_001A7B90;
extern int D_001A79F0;
extern int D_001A79F0_1 __attribute__((sda));
extern unsigned char D_00138180[];
extern unsigned char D_001A7A0A;
extern int D_L04_001B0904 __attribute__((sda));
extern unsigned char *D_L04_001B0914 __attribute__((sda));
extern unsigned char *D_L04_001A904C;
extern float D_L04_001B2D44;
extern int D_L04_001B2008;
extern float D_L04_001BDB80[];
extern int D_001A7368[] MACRO_ADDR;
extern int D_001A737C[];
typedef struct { int name, flags, rewards[3]; unsigned char reserved[44]; } RaceChallenge;
extern RaceChallenge D_L04_002C63C0[];
extern char D_L04_001B0940[], D_L04_001B0950[], D_L04_001B0958[], D_L04_001B0968[];
extern float func_00283198(float), func_00283180(float);
extern void func_0027AB40(void);
extern void *func_00336D50(void *, int);
extern void func_00300A00(void *, float, unsigned int, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(const char *);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern int func_0027FBD8(int, int, unsigned long, char *, int);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern void func_0027F5B8(int, int, unsigned long, char *, int);
extern int func_L04_0040A1D0(int);
extern void func_002FC560(int, unsigned long);
extern int D_L04_001B2D40;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord1(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active) scaled = scale;
    if (result != 0) scaled = scale;
    copy = result;
    if (copy != 0) scaled = half;
    return result;
}
#define Y(v) hud_coord((float)(v), D_L04_001B2D44, 0.5f)
#define TEXT(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define TEXTY(x,y,s) { char *str_ = (s); int row_ = hud_coord((float)(y), D_L04_001B2D44, 0.5f); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define CENTER(y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FBD8(center,row_,0x80f0f0f0UL,str_,len_); }
#define ROW(x,id) { int row_ = Y(286); char *str_ = func_00288FB8(id); func_0027F5B8(x,row_,0x80f0f0f0UL,str_,-1); }
int func_US2_L04_0040C224(void)
{
    char buffer[128];
    unsigned char *m = D_L04_001B0914;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    int center = (int)((float)D_001A7340 * 0.5f);
    float angle = 0.56217057f, tangent;
    unsigned int tint;
    unsigned char *input;
    int count, shift, reward, x;
    void *icon;
    float scale, centerf, py;
    int one;
    char *label;
    float w, v;
    tangent = func_00283198(angle);
    tangent /= func_00283180(angle);
    centerf = (float)center;
    D_L04_001BDB80[44] = tangent;
    func_0027AB40();
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x45);
    py = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    w = 1.0f;
    func_00300A00(icon,centerf,0x60442d00,py,w,scale,(float)0);
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x44);
    w = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    v = 1.0f;
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    func_00300A00(icon,centerf,0x55f0c070,w,v,scale,0.0f);
    x = D_L04_001B2008 % 50;
    count = func_00283D38(0x80ffde8d,0x60442d00, x >= 25 ? 1.0f-(float)(x-25)*0.04f : (float)x*0.04f);
    one = 1;
    input = D_00138180;
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x2000)) tint = count;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4a);
    func_00300A00(icon,259.0f,tint,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, one),1.0f,1.0f,0.0f);
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x8000)) tint = count;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4b);
    func_00300A00(icon,251.0f,tint,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, one),1.0f,1.0f,0.0f);
    if (m[0x20] != 3) {
        float projection_angle = *(float *)(p+0x28c)*0.008726647f;
        float sine = func_00283198(projection_angle);
        D_L04_001BDB80[44] = sine / func_00283180(projection_angle);
        func_0027AB40();
    }
    { int n_ = func_00115DA8(buffer,func_00288FB8(0x2e08),D_L04_001B0904+1); int row_ = label_y3((void *)n_, 60.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FBD8(center,row_,0x80f0f0f0UL,buffer,len_); }
    { int row_ = hud_coord1(286.0f, D_L04_001B2D44, 0.5f, one); char *str_ = func_00288FB8(0x2dd6); func_0027F5B8(119,row_,0x80f0f0f0UL,str_,-1); }
    ROW(356,0x2dd7);
    ROW(181,0x2dd5);
    ROW(279,0x2dd8);
    { label = func_00288FB8(D_L04_002C63C0[D_L04_001B0904].name); { int row_ = Y(110); int len_ = func_001157AC(label); func_0027FAA8(center,row_,0x80f0f0f0UL,label,len_); } }
    shift = D_001A79F0 == 11 ? 10 : 5;
    count = func_L04_0040A1D0(D_L04_001B0904);
    if(count>=3) count=2;
    if ((D_L04_002C63C0[D_L04_001B0904].flags & 0x10000000) ||
        (D_L04_001B0904 > 0 && func_L04_0040A1D0(D_L04_001B0904-1)>0)) {
        if (D_L04_002C63C0[D_L04_001B0904].flags & 4) label = func_00288FB8(D_001A79F0_1 == 11 ? 0x2e30 : 0x2e10);
        else label = func_00288FB8(D_001A79F0_1 == 11 ? 0x2e2f : 0x2e0f);
        TEXTY(center,150-shift,label);
        { if (D_L04_002C63C0[D_L04_001B0904].flags&1) label=func_00288FB8(0x2e12);
        else label=func_00288FB8(0x2e11);
        TEXT(center,170-shift,label);
        if (D_001A79F0==11) {
            if (D_L04_002C63C0[D_L04_001B0904].flags&16) label=func_00288FB8(0x2e31);
            else label=func_00288FB8(0x2e32);
            TEXT(center,190-shift,label);
            if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2e5b); TEXT(center,210-shift,label) }
        } else if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2e5b); { int row_ = label_y(label, (float)(190-shift), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(label); func_0027FAA8(center,row_,0x80f0f0f0UL,label,len_); } } }
        if(D_L04_002C63C0[D_L04_001B0904].rewards[count]) {
            char *fmt = D_L04_001B0940;
            char *str = func_00288FB8(0x2e13);
            { unsigned char boost = D_001A7A0A;
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(boost) reward*=10; }
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2df4));
        } else { char *fmt = D_L04_001B0950; func_00115DA8(buffer,fmt,func_00288FB8(0x2e13)); }
        TEXT(center,shift+210,buffer);
        { int *times; if (D_001A79F0==4) { times = D_001A7368; count = times[D_L04_001B0904]; } else { times = D_001A737C; count = times[D_L04_001B0904]; } }
        x = 0;
        if(count) {
            x = 110;
            if (count / 60 % 60 < 10) func_00115DA8(buffer,D_L04_001B0958,func_00288FB8(0x305e),count/3600%60,count/60%60,count/6%10);
            else func_00115DA8(buffer,D_L04_001B0968,func_00288FB8(0x305e),count/3600%60,count/60%60,count/6%10);
            { int col = center+50; char *str_ = buffer; int row_ = label_y(str_, (float)(shift+230), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FB40(col,row_,0x80f0f0f0UL,str_,len_); }
        }
            { int col = center-x;
            char *fmt = func_00288FB8(0x2e14);
            func_00115DA8(buffer,fmt,func_L04_0040A1D0(D_L04_001B0904));
            TEXT(col,shift+230,buffer); }
    } else {
            char *fmt;
            label = func_00288FB8(0x2e09); CENTER(150,label);
            fmt = D_L04_001B0940;
            { char *str = func_00288FB8(0x2e13);
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(D_001A7A0A) reward*=10;
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2df4)); }
            { int row_ = label_y((void *)center, (float)(shift+210), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FAA8(center,row_,0x80f0f0f0UL,buffer,len_); }
    }
    func_002FC560(71,0x5360b);
    return 1;
}
