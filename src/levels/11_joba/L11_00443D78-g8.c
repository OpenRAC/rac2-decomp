/* Draws the menu panel: header box, value line, count line and labels. */
#include "common.h"
extern void func_L11_00443940(void *,int);
extern int func_L11_00443CE0(int), func_L11_0043E108(int), func_L11_00442958(int), func_00288D58(void);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_0027F5B8(int,int,u64,char *,int), func_0027F538(int,int,u64,char *,int);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int),func_00280270(void *,u64,char *,int);
extern int D_L11_001B1650 __attribute__((sda));
extern int D_L11_001B1654 __attribute__((sda));
extern int D_L11_001B1658 __attribute__((sda));
extern int D_L11_001B165C __attribute__((sda));
extern int D_L11_001B1660 __attribute__((sda));
extern int D_L11_001B1664;
extern int D_L11_001B1668;
extern int D_L11_001B166C;
extern int D_L11_001B1670 __attribute__((sda));
extern int D_L11_001B1674 __attribute__((sda));
extern int D_L11_001B1678 __attribute__((sda));
extern int D_L11_001B167C __attribute__((sda));
extern int D_L11_001B1680 __attribute__((sda));
extern int D_L11_001B1684 __attribute__((sda));
extern int D_L11_001B1688 __attribute__((sda));
extern int D_L11_001B168C __attribute__((sda));
extern int D_L11_001B1690 __attribute__((sda));
extern int D_L11_001B1694 __attribute__((sda));
extern int D_L11_001B1698 __attribute__((sda));
extern int D_L11_001B169C __attribute__((sda));
extern int D_L11_001B16A0 __attribute__((sda));
extern int D_L11_001B16A4 __attribute__((sda));
extern int D_L11_001B16A8 __attribute__((sda));
extern int D_L11_001B16AC __attribute__((sda));
extern int D_L11_001B16B0 __attribute__((sda));
extern int D_L11_001B16B4 __attribute__((sda));
extern int D_L11_001B16B8 __attribute__((sda));
extern int D_L11_001B16BC __attribute__((sda));
extern int D_L11_001B16C0 __attribute__((sda));
extern int D_L11_001B16C4 __attribute__((sda));
extern int D_L11_001B16C8 __attribute__((sda));
extern int D_L11_001B16CC __attribute__((sda));
extern int D_L11_001B16D0 __attribute__((sda));
extern int D_L11_001B16D4 __attribute__((sda));
extern int D_L11_001B16D8 __attribute__((sda));
extern int D_L11_001B16DC __attribute__((sda));
extern int D_L11_001B16E0 __attribute__((sda));

extern float D_L11_001B3E04;
extern char D_L11_001B15A0[],D_L11_001B16E8[];
extern unsigned char D_00139568[],D_001395B8[];
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L11_00279BA0[];
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
extern int D_L11_001B3E00;
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

void func_L11_00443D78(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*label,*unit,*str,*t1,*t2,*t3,*t4,*t5; int i,value,y2,y3,y4,y5,y6,y7,y8,one,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half;
    one=1;
    func_L11_00443940(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L11_00443CE0(SEL)));
    bx=hud_coord((float)D_L11_001B1660, D_L11_001B3E04, 0.5f);
    by=hud_coord((float)D_L11_001B1664, D_L11_001B3E04, 0.5f);
    bh=hud_coord((float)D_L11_001B1658, D_L11_001B3E04, 0.5f);
    func_002802E0(box,bx,by,D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,bh,D_L11_001B1670,3);
    c1=D_L11_001B1650; func_00280270(box,c1,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[func_L11_0043E108(0)]) goto counts;
    if(SEL==one && !D_001395B8[func_L11_0043E108(one)]) goto counts;
    {
        do {
            text=((char *)func_00288FB8(0x2f44)); unit=((char *)func_00288FB8(0x2f5e)); value=func_L11_00442958(SEL);
            if(value<10000) { func_00115DA8(buffer,D_L11_001B15A0,text,value,unit); str=buffer; goto draw1; }
            func_00115DA8(buffer,D_L11_001B16E8,text,value);
        } while(0);
        str=buffer;
    draw1:
        y2=hud_coord((float)D_L11_001B167C, D_L11_001B3E04, 0.5f); c2=D_L11_001B1680; func_0027F5B8(D_L11_001B1678,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[func_L11_0043E108(SEL)]) {
        t1=((char *)func_00288FB8(0x2f3e));
        func_00115DA8(buffer,D_L11_001B16E8,t1,D_001395B8[func_L11_0043E108(SEL)]); str=buffer;
        y3=(int)((float)D_L11_001B16AC * D_L11_001B3E04 + 0.5f); do { c3=D_L11_001B16B0; } while(0); func_0027F5B8(D_L11_001B16A8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { t1=((char *)func_00288FB8(0x2f40)); y4=hud_coord((float)D_L11_001B168C, D_L11_001B3E04, 0.5f); c4=D_L11_001B1690; func_0027F538(D_L11_001B1688,y4,c4,t1,func_001157AC(t1)); }
    for(i=SEL+1;i<13;i++) {
        half=0.5f;
        if(!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
        if(i>=11 && !func_00288D58()) continue;
        if(i==8 && !((MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0))->enabled) continue;
        t2=((char *)func_00288FB8(0x2f41)); y5=hud_coord((float)D_L11_001B169C, D_L11_001B3E04, half); c5=D_L11_001B16A0; func_0027F538(D_L11_001B1698,y5,c5,t2,func_001157AC(t2)); break;
    }
    half=0.5f;
    text=((char *)func_00288FB8(0x2f3f)); y6=hud_coord((float)D_L11_001B16BC, D_L11_001B3E04, half); c6=D_L11_001B16C0; func_0027F538(D_L11_001B16B8,y6,c6,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f42)); y7=hud_coord((float)D_L11_001B16DC, D_L11_001B3E04, half); c7=D_L11_001B16E0; func_0027F538(D_L11_001B16D8,y7,c7,text,func_001157AC(text));
    text=((char *)func_00288FB8(0x2f43)); y8=hud_coord((float)D_L11_001B16CC, D_L11_001B3E04, half); c8=D_L11_001B16D0; func_0027F538(D_L11_001B16C8,y8,c8,text,func_001157AC(text));
}
