#include "common.h"

/* func_PAL_L11_004495E8: the PAL copy of v2.00's func_US2_L11_004455E0
 * (src/us2/levels/11_joba/L11_004455E0-g8.c), the Joba copy of the v2.00 menu panel. The same C,
 * flags and helpers, with PAL's text ids. The v2.00 notes follow.
 * Its loop label differs from the twin's in two ways. The label's y goes through hud_coord1, the
 * display-mode test of hud_coord alone, and its colour is read in a one-pass group like the count
 * line's. With the full hud_coord the loop is three insns longer, loop.c keeps the constant 8 of
 * `i == 8` inside it, and the colour load is scheduled into the label's y. */
extern void func_L11_00443940(char *,int);
extern int func_L11_00443CE0(int), func_L11_0043E108(int), func_L11_00442958(int);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int);
extern void func_00280270(void *,u64,char *,int);
extern void func_00280190(void *,u64,char *,int);
extern int func_PAL_L02_00402928(void);
extern unsigned char D_001A7BB4 MACRO_ADDR;
extern void func_0027F538(int,int,u64,char *,int);
extern void func_0027F5B8(int,int,u64,char *,int);
extern int func_00288D58(void);
extern float D_L11_001B3E04;
extern int D_L11_001B1664;
extern int D_L11_001B1668;
extern int D_L11_001B166C;
extern char D_L11_001B15A0[], D_L11_001B16E8[];
extern unsigned char D_001395B8[], D_00139568[];
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L11_00279BA0[];
extern int D_L11_001B1650 __attribute__((sda));
extern int D_L11_001B1654 __attribute__((sda));
extern int D_L11_001B1658 __attribute__((sda));
extern int D_L11_001B1660 __attribute__((sda));
extern int D_L11_001B1670 __attribute__((sda));
extern int D_L11_001B1678 __attribute__((sda));
extern int D_L11_001B167C __attribute__((sda));
extern int D_L11_001B1680 __attribute__((sda));
extern int D_L11_001B1688 __attribute__((sda));
extern int D_L11_001B168C __attribute__((sda));
extern int D_L11_001B1690 __attribute__((sda));
extern int D_L11_001B1698[] SDATA(D_L11_001B1698);
extern int D_L11_001B169C __attribute__((sda));
extern int D_L11_001B16A0 __attribute__((sda));
extern int D_L11_001B16A8 __attribute__((sda));
extern int D_L11_001B16AC __attribute__((sda));
extern int D_L11_001B16B0 __attribute__((sda));
extern int D_L11_001B16B8 __attribute__((sda));
extern int D_L11_001B16BC __attribute__((sda));
extern int D_L11_001B16C0 __attribute__((sda));
extern int D_L11_001B16C8[] SDATA(D_L11_001B16C8);
extern int D_L11_001B16CC __attribute__((sda));
extern int D_L11_001B16D0 __attribute__((sda));
extern int D_L11_001B16D8[] SDATA(D_L11_001B16D8);
extern int D_L11_001B16DC __attribute__((sda));
extern int D_L11_001B16E0 __attribute__((sda));
extern int D_L11_001B3E00;
#define SEL (*(short *)(state+0x1e8))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
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
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
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
/* hud_coord1: hud_coord with its display-mode test only (the same kind of dead test). */
static __inline__ int hud_coord1(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == 1)
        scaled = scale;
    return result;
}

void func_PAL_L11_004495E8(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*unit,*str; int *x5,*x7,*x8; int i,value,y2,y3,y4,y5,y6,y7,y8,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half,h;
    func_L11_00443940(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L11_00443CE0(SEL)));
    bx=hud_coord((float)D_L11_001B1660, D_L11_001B3E04, 0.5f);
    by=hud_coord((float)D_L11_001B1664, D_L11_001B3E04, 0.5f);
    bh=hud_coord((float)D_L11_001B1658, D_L11_001B3E04, 0.5f);
    func_002802E0(box,bx,by,D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,bh,D_L11_001B1670,3);
    if(func_PAL_L02_00402928()) { c1=D_L11_001B1650; func_00280190(box,c1,text,func_001157AC(text)); }
    else { c1=D_L11_001B1650; func_00280270(box,c1,text,func_001157AC(text)); }
    if(SEL==0 && !D_001395B8[func_L11_0043E108(0)]) goto counts;
    if(SEL==1 && !D_001395B8[func_L11_0043E108(1)]) goto counts;
    {
        text=((char *)func_00288FB8(0xE69)); unit=((char *)func_00288FB8(0xE83)); value=func_L11_00442958(SEL);
        if(value<10000) { func_00115DA8(buffer,D_L11_001B15A0,text,(u64)value,unit); str=buffer; }
        else { func_00115DA8(buffer,D_L11_001B16E8,text,(u64)value); str=buffer; }
        y2=hud_coord((float)D_L11_001B167C, D_L11_001B3E04, 0.5f); c2=D_L11_001B1680; func_0027F5B8(D_L11_001B1678,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[func_L11_0043E108(SEL)]) {
        text=((char *)func_00288FB8(0xE63));
        func_00115DA8(buffer,D_L11_001B16E8,text,D_001395B8[func_L11_0043E108(SEL)]); str=buffer;
        y3=(int)((float)D_L11_001B16AC * D_L11_001B3E04 + 0.5f); do { c3=D_L11_001B16B0; } while(0); func_0027F5B8(D_L11_001B16A8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)func_00288FB8(0xE65)); h=0.5f; y4=hud_coord((float)D_L11_001B168C, D_L11_001B3E04, h); c4=D_L11_001B1690; func_0027F538(D_L11_001B1688,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<13;i++) {
        if(!D_001395B8[func_L11_0043E108(D_L11_001B14F8[i][2])]) continue;
        if(i>=11 && !func_00288D58()) continue;
        if(i==8 && !((MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0))->enabled) continue;
        text=((char *)func_00288FB8(0xE66)); x5=&D_L11_001B1698[D_001A7BB4]; h=0.5f; y5=hud_coord1((float)D_L11_001B169C, D_L11_001B3E04, h); do { c5=D_L11_001B16A0; } while(0); func_0027F538(*x5,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)func_00288FB8(0xE64)); y6=hud_coord((float)D_L11_001B16BC, D_L11_001B3E04, half); c6=D_L11_001B16C0; func_0027F538(D_L11_001B16B8,y6,c6,text,func_001157AC(text));
    text=((char *)func_00288FB8(0xE67)); x7=&D_L11_001B16D8[D_001A7BB4]; y7=label_y(x7, (float)D_L11_001B16DC, D_L11_001B3E04, half, 1); c7=D_L11_001B16E0; func_0027F538(*x7,y7,c7,text,func_001157AC(text));
    text=((char *)func_00288FB8(0xE68)); x8=&D_L11_001B16C8[D_001A7BB4]; y8=hud_coord((float)D_L11_001B16CC, D_L11_001B3E04, half); c8=D_L11_001B16D0; func_0027F538(*x8,y8,c8,text,func_001157AC(text));
}
