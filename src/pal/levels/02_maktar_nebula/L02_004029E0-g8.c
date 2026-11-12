#include "common.h"

/* func_PAL_L02_004029E0: the PAL copy of v2.00's func_US2_L02_003FF808
 * (src/us2/levels/02_maktar_nebula/L02_003FF808-g8.c), itself the v2.00 copy of func_L02_003FE250, the
 * Maktar Nebula menu panel. The same C, flags and helpers, with PAL's text ids. As in v2.00, the
 * header text is drawn with func_00280190 when func_PAL_L02_00402928 returns nonzero, and three
 * label x positions come from per-language tables indexed by D_001A7BB4. */
extern void func_L02_003FDDE8(char *,int);
extern int func_L02_003FE1B0(int), func_L02_003F9B70(int), func_L02_003FCDF8(int);
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
extern float D_L02_001B3E04;
extern int D_L02_001B12A4;
extern int D_L02_001B12A8;
extern int D_L02_001B12AC;
extern char D_L02_001B1228[], D_L02_001B1328[];
extern unsigned char D_001395B8[], D_00139568[];
extern int *D_L02_001B1190[] SDATA(D_L02_001B1190);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L02_00264A70[];
extern int D_L02_001B1294 __attribute__((sda));
extern int D_L02_001B1298 __attribute__((sda));
extern int D_L02_001B129C __attribute__((sda));
extern int D_L02_001B12A0 __attribute__((sda));
extern int D_L02_001B12B0 __attribute__((sda));
extern int D_L02_001B12B8 __attribute__((sda));
extern int D_L02_001B12BC __attribute__((sda));
extern int D_L02_001B12C0 __attribute__((sda));
extern int D_L02_001B12C8 __attribute__((sda));
extern int D_L02_001B12CC __attribute__((sda));
extern int D_L02_001B12D0 __attribute__((sda));
extern int D_L02_001B12D8[] SDATA(D_L02_001B12D8);
extern int D_L02_001B12DC __attribute__((sda));
extern int D_L02_001B12E0 __attribute__((sda));
extern int D_L02_001B12E8 __attribute__((sda));
extern int D_L02_001B12EC __attribute__((sda));
extern int D_L02_001B12F0 __attribute__((sda));
extern int D_L02_001B12F8 __attribute__((sda));
extern int D_L02_001B12FC __attribute__((sda));
extern int D_L02_001B1300 __attribute__((sda));
extern int D_L02_001B1308[] SDATA(D_L02_001B1308);
extern int D_L02_001B130C __attribute__((sda));
extern int D_L02_001B1310 __attribute__((sda));
extern int D_L02_001B1318[] SDATA(D_L02_001B1318);
extern int D_L02_001B131C __attribute__((sda));
extern int D_L02_001B1320 __attribute__((sda));
extern int D_L02_001B3E00;
#define SEL (*(short *)(state+0x118))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
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
    int mode = D_L02_001B3E00;
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

void func_PAL_L02_004029E0(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*unit,*str; int *x5,*x7,*x8; int i,value,y2,y3,y4,y5,y6,y7,y8,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half,h;
    func_L02_003FDDE8(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)func_00288FB8(func_L02_003FE1B0(SEL)));
    bx=hud_coord((float)D_L02_001B12A0, D_L02_001B3E04, 0.5f);
    by=hud_coord((float)D_L02_001B12A4, D_L02_001B3E04, 0.5f);
    bh=hud_coord((float)D_L02_001B129C, D_L02_001B3E04, 0.5f);
    func_002802E0(box,bx,by,D_L02_001B12A8,D_L02_001B12AC,D_L02_001B1298,bh,D_L02_001B12B0,3);
    if(func_PAL_L02_00402928()) { c1=D_L02_001B1294; func_00280190(box,c1,text,func_001157AC(text)); }
    else { c1=D_L02_001B1294; func_00280270(box,c1,text,func_001157AC(text)); }
    if(SEL==0 && !D_001395B8[func_L02_003F9B70(0)]) goto counts;
    {
        text=((char *)func_00288FB8(0xE69)); unit=((char *)func_00288FB8(0xE83)); value=func_L02_003FCDF8(SEL);
        if(value<10000) { func_00115DA8(buffer,D_L02_001B1228,text,(u64)value,unit); str=buffer; }
        else { func_00115DA8(buffer,D_L02_001B1328,text,(u64)value); str=buffer; }
        y2=hud_coord((float)D_L02_001B12BC, D_L02_001B3E04, 0.5f); c2=D_L02_001B12C0; func_0027F5B8(D_L02_001B12B8,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[func_L02_003F9B70(SEL)]) {
        text=((char *)func_00288FB8(0xE63));
        func_00115DA8(buffer,D_L02_001B1328,text,D_001395B8[func_L02_003F9B70(SEL)]); str=buffer;
        y3=(int)((float)D_L02_001B12EC * D_L02_001B3E04 + 0.5f); do { c3=D_L02_001B12F0; } while(0); func_0027F5B8(D_L02_001B12E8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)func_00288FB8(0xE65)); h=0.5f; y4=hud_coord((float)D_L02_001B12CC, D_L02_001B3E04, h); c4=D_L02_001B12D0; func_0027F538(D_L02_001B12C8,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<14;i++) {
        if(!D_001395B8[func_L02_003F9B70(D_L02_001B1190[i][2])]) continue;
        if(i>=12 && !func_00288D58()) continue;
        if(i==7 && !((MenuRecord *)(D_L02_00264A70 + D_00139568[0x1e] * 0xe0))->enabled) continue;
        if(i==8 && !((MenuRecord *)(D_L02_00264A70 + D_00139568[0x2a] * 0xe0))->enabled) continue;
        text=((char *)func_00288FB8(0xE66)); x5=&D_L02_001B12D8[D_001A7BB4]; h=0.5f; y5=hud_coord((float)D_L02_001B12DC, D_L02_001B3E04, h); c5=D_L02_001B12E0; func_0027F538(*x5,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)func_00288FB8(0xE64)); y6=hud_coord((float)D_L02_001B12FC, D_L02_001B3E04, half); c6=D_L02_001B1300; func_0027F538(D_L02_001B12F8,y6,c6,text,func_001157AC(text));
    text=((char *)func_00288FB8(0xE67)); x7=&D_L02_001B1318[D_001A7BB4]; y7=label_y(x7, (float)D_L02_001B131C, D_L02_001B3E04, half, 1); c7=D_L02_001B1320; func_0027F538(*x7,y7,c7,text,func_001157AC(text));
    text=((char *)func_00288FB8(0xE68)); x8=&D_L02_001B1308[D_001A7BB4]; y8=hud_coord((float)D_L02_001B130C, D_L02_001B3E04, half); c8=D_L02_001B1310; func_0027F538(*x8,y8,c8,text,func_001157AC(text));
}
