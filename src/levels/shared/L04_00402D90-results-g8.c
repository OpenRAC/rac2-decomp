/* func_L04_0040AD28 (3,388 bytes; Barlow and Joba): the race results panel. This unit builds with
 * four opt-in switches (config/cflags.txt): -frac2-ga-no-lo-sum-pref (name row),
 * -frac2-ga-divisor-first (time / 60), -frac2-sched2-call-copy-fp-wait (0x96 row) and
 * -frac2-sched2-const-low-reg-first (0x2F79/0x2F99 order); docs/build/compiler-notes.md.
 * Owner standard of 12 November 2026. hud_coord and label_y are the owner-allowed dead-test helpers. */
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
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result;
    void *copy;
    if (mode == active) value = scale;
    result = (int)scaled;
    if (handle != 0) value = scale;
    copy = handle;
    if (copy != 0) value = half;
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
#define YS(v) Y(v)
#define TEXT(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define CENTER(y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FBD8(center,row_,0x80f0f0f0UL,str_,len_); }
#define ROW(x,id) { int row_ = Y(286); char *str_ = func_00288FB8(id); func_0027F5B8(x,row_,0x80f0f0f0UL,str_,-1); }
int func_L04_0040AD28(void)
{
    char buffer[128];
    unsigned char *m = D_L04_001B0914;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    int center = (int)((float)D_001A7340 * 0.5f);
    float angle = 0.56217057f, tangent;
    unsigned int tint;
    unsigned char *input;
    int count, shift, reward, time, minutes, x, row;
    void *icon;
    float scale, centerf, py;
    int one;
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
    { int n_ = func_00115DA8(buffer,func_00288FB8(0x2f72),D_L04_001B0904+1); int row_ = label_y3((void *)n_, 60.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FBD8(center,row_,0x80f0f0f0UL,buffer,len_); }
    { int row_ = hud_coord1(286.0f, D_L04_001B2D44, 0.5f, one); char *str_ = func_00288FB8(0x2f40); func_0027F5B8(119,row_,0x80f0f0f0UL,str_,-1); }
    ROW(356,0x2f41);
    ROW(181,0x2f3f);
    ROW(279,0x2f42);
    TEXT(center,110,func_00288FB8(D_L04_002C63C0[D_L04_001B0904].name));
    shift = D_001A79F0 == 11 ? 10 : 5;
    count = func_L04_0040A1D0(D_L04_001B0904);
    if ((D_L04_002C63C0[D_L04_001B0904].flags & 0x10000000) ||
        (D_L04_001B0904 > 0 && func_L04_0040A1D0(D_L04_001B0904-1)>0)) {
        int first, second, lang;
        if (D_L04_002C63C0[D_L04_001B0904].flags & 4) { lang = D_001A79F0_1; first=0x2f7a; second=0x2f9a; }
        else { lang = D_001A79F0_1; second=0x2f99; first=0x2f79; }
        if (lang != 11) second = first;
        TEXT(center,150-shift,func_00288FB8(second));
        { char *label; if (D_L04_002C63C0[D_L04_001B0904].flags&1) label=func_00288FB8(0x2f7c);
        else label=func_00288FB8(0x2f7b);
        TEXT(center,170-shift,label);
        if (D_001A79F0==11) {
            if (D_L04_002C63C0[D_L04_001B0904].flags&16) label=func_00288FB8(0x2f9b);
            else label=func_00288FB8(0x2f9c);
            TEXT(center,190-shift,label);
            if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2fc5); TEXT(center,210-shift,label) }
        } else if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2fc5); { int row_ = label_y(label, (float)(190-shift), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(label); func_0027FAA8(center,row_,0x80f0f0f0UL,label,len_); } } }
        if(count>=3) count=2;
        if(D_L04_002C63C0[D_L04_001B0904].rewards[count]) {
            char *fmt = D_L04_001B0940;
            char *str = func_00288FB8(0x2f7d);
            { unsigned char boost = D_001A7A0A;
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(boost) reward*=10; }
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e));
        } else { char *fmt = D_L04_001B0950; func_00115DA8(buffer,fmt,func_00288FB8(0x2f7d)); }
        TEXT(center,shift+210,buffer);
        { int *times; if (D_001A79F0==4) { times = D_001A7368; time = times[D_L04_001B0904]; } else { times = D_001A737C; time = times[D_L04_001B0904]; } }
        x = 0;
        if(time) {
            x = 110;
            if (time / 60 % 60 < 10) func_00115DA8(buffer,D_L04_001B0958,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            else func_00115DA8(buffer,D_L04_001B0968,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            { int col = center+46; TEXT(col,shift+230,buffer); }
        }
            { int col = center-x;
            char *fmt = func_00288FB8(0x2f7e);
            func_00115DA8(buffer,fmt,func_L04_0040A1D0(D_L04_001B0904));
            TEXT(col,shift+230,buffer); }
    } else {
            char *fmt;
            CENTER(150,func_00288FB8(0x2f73));
            fmt = D_L04_001B0940;
            { char *str = func_00288FB8(0x2f7d);
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(D_001A7A0A) reward*=10;
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e)); }
            { int row_ = label_y((void *)center, (float)(shift+210), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FAA8(center,row_,0x80f0f0f0UL,buffer,len_); }
    }
    func_002FC560(71,0x5360b);
    return 1;
}
