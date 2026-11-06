/* Per-frame update of a Maktar Nebula object. State 0 sets up its timers; state 1 runs a
   series of tests on its state record and two global records, calling func_0028A180,
   func_PAL_00289730 and func_PAL_L01_002EBFB8 with the ids listed below.

   `base` is one local for the flags record and the first two blocks on D_0018C958. Holding
   several values gives it the references and live length that win $s0 over `s`; separate
   locals, or one local holding one address throughout, leave `s` in $s0.

   func_PAL_L02_0040E800, the PAL copy of func_L02_00409D78: the same C, where every frame
   count read from D_001A7390 is scaled to 50 Hz, ((s32)(x) * 5 + 2) / 6, including the
   values stored back, and the frame limits shrink to 5/6 (1080 to 900, 120 to 100, 1200 to
   1000, 180 to 150, 600 to 500, 3600 to 3000, 432000 to 360000, 42000 to 35000, 72000 to
   60000, 216000 to 180000; the 60 of the time1A8 test stays). Retail reads the counter through $gp (timer_sda) except in the
   countF0 and count152 blocks and the time1A8 test, which use the lui form: there it is the
   plain scalar D_001A7390, whose fixed-scalar MEM lets sched1 lift the countF0 == 0 arm's
   load above the countF0 store (an array element, D_001A7390[0], is in-struct and stays
   behind it). */
#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
extern char D_00189EA0[], D_L02_0027FD48[];
typedef struct HintFlags { u8 pad[0x75]; u8 intro, timers; u8 pad77[5]; u8 hint; } HintFlags;
extern HintFlags D_001395B8;
typedef struct HintHistory {
    char pad0[0xf0];
    u16 countF0; char padF2[2]; u32 timeF4; u32 levelsF8;
    char padFC[0x24];
    u16 count120; char pad122[2]; u32 time124;
    char pad128[0x10]; u16 count138;
    char pad13A[0x18]; u16 count152; u32 time154; s32 flags158; u16 count15C;
    char pad15E[0x162]; s32 value2C0;
    char pad2C4[0x358]; u32 time61C;
} HintHistory;
typedef struct PlayerHistory {
    char pad0[0x54]; u16 count54;
    char pad56[0x9a]; u16 countF0; char padF2[2]; u32 timeF4;
    char padF8[0xb0]; u32 time1A8;
    char pad1AC[0x10]; u16 count1BC; char pad1BE[2]; u32 time1C0;
    char pad1C4[4]; u16 count1C8; char pad1CA[2]; u32 time1CC;
} PlayerHistory;
typedef struct HintState {
    char pad0[0x10];
    s32 value10;
    s32 value14;
    char pad18[0x8];
    s32 value20;
    s32 value24;
    s32 value28;
    s32 value2C;
    s32 value30;
    s32 value34;
    s32 value38;
    s32 value3C;
    char pad40[0x4];
    s32 value44;
    char pad48[0x4];
    s32 value4C;
    s32 value50;
    char pad54[0xc];
    s32 value60;
    s32 value64;
    s32 value68;
    s32 value6C;
    char pad70[0x8];
    s32 value78;
    s32 value7C;
    s32 value80;
    s32 value84;
    s32 value88;
    char pad8C[0x4];
    s32 value90;
    s32 value94;
    s32 value98;
    s32 value9C;
} HintState;
extern HintHistory D_0018C958;
extern PlayerHistory D_0018C750;
extern u32 D_001A79F0[] __attribute__((sda));
extern u32 D_001A7390 MACRO_ADDR;
extern u32 timer_sda SDATA(D_001A7390);
extern u8 D_001A7AF8[] MACRO_ADDR;
extern int D_L02_001A8FF0 MACRO_ADDR;
extern int unlock_sda SDATA(D_L02_001A9010);
extern char *D_L02_001B359C MACRO_ADDR;
extern char *objects_sda SDATA(D_L02_001B359C);
extern char *D_L02_001B368C MACRO_ADDR;
extern int D_L02_001B30C8 MACRO_ADDR;
extern void func_002A7750(void *,int,int);
extern int func_L01_00305E18(int),func_002ACBC8(void *,int);
extern void func_0028A180(int,int),func_PAL_00289730(int,int),func_PAL_L01_002EBFB8(int,int,int,int,int);
extern int func_L02_00400CC8(void *),func_00282948(void *),func_L02_003D6BB0(void *),func_002B38B8(void *);
extern void func_L00_003672F8(void),func_PAL_L00_002B9CD8(void *,void *,int,int);
void func_PAL_L02_0040E800(char *e) {
    HintState *s=*(HintState **)(e+0x68);

    switch(B(e,0x20)) { default: return; case 0: {
        B(e,0x30)=255; s->value60=0;s->value64=0;s->value50=0;s->value90=0;
        s->value94=1000;s->value2C=150;s->value98=500;
        func_002A7750(e,1,-1);
    break; } case 1: {
        HintHistory *base;
        int mode=func_L01_00305E18(2);
        if(mode==2 && func_L01_00305E18(0)!=mode) {
            base=(HintHistory *)&D_001395B8;
            if(!(((HintFlags *)base)->intro&4) && func_002ACBC8(D_00189EA0,s->value9C) && ((((int)(timer_sda) * 5 + 2) / 6)-D_0018C750.time1CC>360000 || !D_0018C750.count1C8)) {
                ((HintFlags *)base)->intro|=4;func_0028A180(0xa3c,0x93);
            }
        }
        base=&D_0018C958;
        if(base->countF0<65535) {
            if(D_001A7AF8[0x2E]) base->countF0=65535;
            else if(func_002ACBC8(D_00189EA0,I(s,0))) {
                if(base->countF0) {
                    if((((int)(D_001A7390) * 5 + 2) / 6)-base->timeF4>900 || !base->timeF4)func_PAL_00289730(0x9bd,0x14);
                    else if(base->timeF4<(((int)(D_001A7390) * 5 + 2) / 6))base->timeF4=(((int)(D_001A7390) * 5 + 2) / 6);
                } else {
                    base->countF0++; if(base->timeF4<(((int)(D_001A7390) * 5 + 2) / 6))base->timeF4=(((int)(D_001A7390) * 5 + 2) / 6);
                    base->levelsF8=(base->levelsF8|(1<<D_001A79F0[0]))|0x80000000;
                }
            }
        }
        if(D_L02_001A8FF0 && !I(D_L02_0027FD48,0) && I(D_L02_0027FD48,0x24)==-1) {
            base=&D_0018C958;
            if(base->flags158>=0)func_PAL_00289730(0x9c5,0x1c);
            if(base->time154+base->count152>=(((int)(D_001A7390) * 5 + 2) / 6)-2) {
                int count = base->count152+1;
                base->count152=count;
                if((count&0xffff)>=3000){func_PAL_00289730(0x9c5,0x1c);base->count152=0;}
            } else {if(base->time154<(((int)(D_001A7390) * 5 + 2) / 6))base->time154=(((int)(D_001A7390) * 5 + 2) / 6);base->count152=0;}
        }
        func_PAL_L01_002EBFB8(0x9bf,0x16,2,s->value10,s->value14);
        if(D_0018C958.count120<65535) {
            if(D_0018C750.count54>=3 || func_002ACBC8(D_00189EA0,s->value24))D_0018C958.count120=65535;
            else if(func_002ACBC8(D_00189EA0,s->value20)) {
                if((((int)(timer_sda) * 5 + 2) / 6)-D_0018C958.time124>900 || !D_0018C958.time124)func_PAL_00289730(0x9c1,0x18);
                else if(D_0018C958.time124<(((int)(timer_sda) * 5 + 2) / 6))D_0018C958.time124=(((int)(timer_sda) * 5 + 2) / 6);
            }
        }
        func_PAL_L01_002EBFB8(0x9c2,0x19,1,s->value30,s->value34);
        if(!D_0018C958.count138) {
            if(!s->value3C && unlock_sda)s->value3C=1;
            if(D_001A7AF8[0x26])D_0018C958.count138=65535;
            if(s->value3C && func_002ACBC8(D_00189EA0,s->value38))func_PAL_00289730(0x9c3,0x1a);
        }
        func_PAL_L01_002EBFB8(0x9c4,0x1b,0,s->value44,-1);
        if(func_L02_00400CC8(D_L02_001B359C+(s->value68<<8))) {
            if(func_00282948(&s->value94) && (((D_001395B8.timers>>D_001A79F0[0])^1)&1)) {
                if(!D_0018C750.countF0 || (((int)(timer_sda) * 5 + 2) / 6)-D_0018C750.timeF4>35000)func_0028A180(0x9c9,0x20);
                D_001395B8.timers|=1<<D_001A79F0[0];
            }
            if(func_L02_003D6BB0(D_L02_001B359C+(s->value6C<<8)) && (!D_0018C750.count1BC || (((int)(timer_sda) * 5 + 2) / 6)-D_0018C750.time1C0>60000) && func_00282948(&s->value98) && D_0018C958.value2C0>=0)func_PAL_00289730(0x9e3,0x3a);
        }
        if(D_L02_001A8FF0) {
            if(func_002ACBC8(D_00189EA0,s->value4C) && !D_0018C958.count15C) {func_0028A180(0x9c6,0x1d);s->value90=180000;}
            if(func_00282948(&s->value90)){func_0028A180(0x9c6,0x1d);s->value90=180000;}
            if((((int)(D_001A7390) * 5 + 2) / 6)-D_0018C750.time1A8<60)s->value90=180000;
        }
        if(func_002ACBC8(D_00189EA0,s->value78) && (!D_0018C750.count1BC || (((int)(timer_sda) * 5 + 2) / 6)-D_0018C750.time1C0>60000) && !D_001395B8.hint && D_0018C958.value2C0>=0)func_PAL_00289730(0x9e3,0x3a);
        if(func_002ACBC8(D_00189EA0,s->value38))D_001395B8.hint=1;
        if(D_001A7AF8[0x2E])func_PAL_L01_002EBFB8(0x9f1,0x48,2,s->value7C,-1);
        if(D_L02_001B30C8<3 && D_001A7AF8[0x26] && !func_002B38B8(objects_sda+(s->value88<<8)) && func_002ACBC8(D_00189EA0,s->value80)) {
            char *q;
            func_L00_003672F8();q=D_L02_001B368C+(s->value84<<7);func_PAL_L00_002B9CD8(q+0x30,q+0x70,0,1);
        }
        if(func_002ACBC8(D_00189EA0,s->value28)) {
            if((((int)(timer_sda) * 5 + 2) / 6)-D_0018C958.time61C>100 || !D_0018C958.time61C)func_PAL_00289730(0xa2b,0x82);
            else if(D_0018C958.time61C<(((int)(timer_sda) * 5 + 2) / 6))D_0018C958.time61C=(((int)(timer_sda) * 5 + 2) / 6);
        }
    }
    }
}
