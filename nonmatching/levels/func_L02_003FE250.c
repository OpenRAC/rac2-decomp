/* 7 November 2026, label_y sweep: every text label y is label_y(text or buf, (float)Y, D_L02_001B3E04, 0.5f, 1), mode D_L02_001B3E00 (accepted HUD label idiom, definition above the function). Same profile: 1296/1300 bytes (was 1304), sweep-harness masked aligned diff 129 -> 123. Header box conversions through label_y too: worse. */
/*
 * GPT-6.1 Sol high tier, task v0936, 2026-10-29.
 * USA v1.01, pinned game -O2 -G8 -ffunction-sections.
 * Retained check.py: 1304/1300 bytes, 0 of 1 places match; no linked check.
 * A reused float for input conversion, multiplication, and addition makes
 * the three header conversions serial. It still uses f2 for the working
 * value and f0 for 0.5, where retail uses f0 and f2 respectively; independent
 * style/geometry loads still move into the conversions.
 * The byte-table address is hoisted to entry and stays live into the loop,
 * adding s6; retail starts its high-half lifetime after header conversion
 * and rebuilds the base for the loop. The constant 7 is also loop-hoisted.
 * Inline coordinate arguments and goto-based loop exits tie the old draft;
 * incomplete-array sda on the byte table retains 1304 bytes with worse base
 * sharing. A two-case switch is 1288 bytes with the wrong branch structure.
 * -frac2-gcse-unsplit-edges and -fno-schedule-insns2 do not solve either issue.
 * Canonical text styles are u64, matching their existing C implementations;
 * SDATA gives the unknown-sized pointer table a GP view without a false bound.
 * Next: recover the original UI rounding/layout expression and the byte-table
 * base scopes. All declarations are below; use a dedicated -g8.c unit.
 */
#include "common.h"
extern void func_L02_003FDDE8(char *,int);
extern int func_L02_003FE1B0(int), func_L02_003F9B70(int), func_L02_003FCDF8(int);
extern char *func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int);
extern void func_00280270(void *,u64,char *,int);
extern void func_0027F538(int,int,u64,char *,int);
extern void func_0027F5B8(int,int,u64,char *,int);
extern float D_L02_001B3E04;
extern int D_L02_001B12A4, D_L02_001B12A8, D_L02_001B12AC;
extern char D_L02_001B1228[], D_L02_001B1328[];
extern u8 D_001395B8[], D_00139568[];
extern char *D_L02_001B1190[] SDATA(D_L02_001B1190);
typedef struct { char pad[4]; u8 enabled; char rest[0xDB]; } MenuRec;
extern MenuRec D_L02_00264A70[];
extern int func_00288D58(void);
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
extern int D_L02_001B12D8 __attribute__((sda));
extern int D_L02_001B12DC __attribute__((sda));
extern int D_L02_001B12E0 __attribute__((sda));
extern int D_L02_001B12E8 __attribute__((sda));
extern int D_L02_001B12EC __attribute__((sda));
extern int D_L02_001B12F0 __attribute__((sda));
extern int D_L02_001B12F8 __attribute__((sda));
extern int D_L02_001B12FC __attribute__((sda));
extern int D_L02_001B1300 __attribute__((sda));
extern int D_L02_001B1308 __attribute__((sda));
extern int D_L02_001B130C __attribute__((sda));
extern int D_L02_001B1310 __attribute__((sda));
extern int D_L02_001B1318 __attribute__((sda));
extern int D_L02_001B131C __attribute__((sda));
extern int D_L02_001B1320 __attribute__((sda));
extern int D_L02_001B3E00;
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

void func_L02_003FE250(char *obj) {
    char box[32];
    char buf[64];
    char *state;
    char *text, *suffix;
    int value, i;
    int x,y,height;
    float scaled;
    MenuRec *r;
    func_L02_003FDDE8(obj,1);
    state=*(char **)(obj+0x68);
    text=func_00288FB8(func_L02_003FE1B0(*(short *)(state+0x118)));
    scaled = (float)D_L02_001B12A0;
    scaled *= D_L02_001B3E04;
    scaled += 0.5f;
    x = (int)scaled;
    scaled = (float)D_L02_001B12A4;
    scaled *= D_L02_001B3E04;
    scaled += 0.5f;
    y = (int)scaled;
    scaled = (float)D_L02_001B129C;
    scaled *= D_L02_001B3E04;
    scaled += 0.5f;
    height = (int)scaled;
    func_002802E0(box,x,y,D_L02_001B12A8,D_L02_001B12AC,D_L02_001B1298,height,D_L02_001B12B0,3);
    { u64 style=D_L02_001B1294; int length=func_001157AC(text); func_00280270(box,style,text,length); }
    if (*(short *)(state+0x118)!=0 || D_001395B8[func_L02_003F9B70(0)]) {
        text=func_00288FB8(0x2F44);
        suffix=func_00288FB8(0x2F5E);
        value=func_L02_003FCDF8(*(short *)(state+0x118));
        if(value<10000) func_00115DA8(buf,D_L02_001B1228,text,value,suffix);
        else func_00115DA8(buf,D_L02_001B1328,text,value);
{ int y=label_y(buf, (float)D_L02_001B12BC, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B12C0; int length=func_001157AC(buf); func_0027F5B8(D_L02_001B12B8,y,style,buf,length); }
    }
    if(D_001395B8[func_L02_003F9B70(*(short *)(state+0x118))]) {
        text=func_00288FB8(0x2F3E);
        func_00115DA8(buf,D_L02_001B1328,text,D_001395B8[func_L02_003F9B70(*(short *)(state+0x118))]);
{ int y=label_y(buf, (float)D_L02_001B12EC, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B12F0; int length=func_001157AC(buf); func_0027F5B8(D_L02_001B12E8,y,style,buf,length); }
    }
    if (*(short *)(state+0x118)!=0) {
        text=func_00288FB8(0x2F40);
{ int y=label_y(text, (float)D_L02_001B12CC, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B12D0; int length=func_001157AC(text); func_0027F538(D_L02_001B12C8,y,style,text,length); }
    }
    for(i=*(short *)(state+0x118)+1;i<14;i++) {
        if(!D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i]+8))]) continue;
        if(i>=12 && !func_00288D58()) continue;
        if(i==7) { r=&D_L02_00264A70[D_00139568[0x1E]]; if(!r->enabled) continue; }
        if(i==8) { r=&D_L02_00264A70[D_00139568[0x2A]]; if(!r->enabled) continue; }
        text=func_00288FB8(0x2F41);
{ int y=label_y(text, (float)D_L02_001B12DC, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B12E0; int length=func_001157AC(text); func_0027F538(D_L02_001B12D8,y,style,text,length); }
        break;
    }
    text=func_00288FB8(12095);
{ int y=label_y(text, (float)D_L02_001B12FC, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B1300; int length=func_001157AC(text); func_0027F538(D_L02_001B12F8,y,style,text,length); }
    text=func_00288FB8(12098);
{ int y=label_y(text, (float)D_L02_001B131C, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B1320; int length=func_001157AC(text); func_0027F538(D_L02_001B1318,y,style,text,length); }
    text=func_00288FB8(12099);
{ int y=label_y(text, (float)D_L02_001B130C, D_L02_001B3E04, 0.5f, 1); u64 style=D_L02_001B1310; int length=func_001157AC(text); func_0027F538(D_L02_001B1308,y,style,text,length); }
}
