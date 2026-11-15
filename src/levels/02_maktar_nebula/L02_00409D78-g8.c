/* Per-frame update of a Maktar Nebula object. State 0 sets up its timers; state 1 runs a
   series of tests on its state record and two global records, calling func_0028A180,
   func_00288E18 and func_L01_002EABA8 with the ids listed below.

   `base` is one local for the flags record and the first two blocks on D_0018C958. Holding
   several values gives it the references and live length that win $s0 over `s`; separate
   locals, or one local holding one address throughout, leave `s` in $s0. */
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
extern u32 D_001A7390[] __attribute__((sda));
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
extern void func_0028A180(int,int),func_00288E18(int,int),func_L01_002EABA8(int,int,int,int,int);
extern int func_L02_00400CC8(void *),func_00282948(void *),func_L02_003D6BB0(void *),func_002B38B8(void *);
extern void func_L00_003672F8(void),func_L00_002B9D60(void *,void *,int,int);
/* Watches how the player is doing and shows a help hint or message when the player seems stuck and has not seen it recently. Update handler of moby class 3108. */
void func_L02_00409D78(char *moby) {
    HintState *hints=*(HintState **)(moby+0x68);

    switch(B(moby,0x20)) { default: return; case 0: {
        B(moby,0x30)=255; hints->value60=0;hints->value64=0;hints->value50=0;hints->value90=0;
        hints->value94=1200;hints->value2C=180;hints->value98=600;
        SetMobyState(moby,1,-1);
    break; } case 1: {
        HintHistory *base;
        int mode=GetTableEntryShort(2);
        if(mode==2 && GetTableEntryShort(0)!=mode) {
            base=(HintHistory *)&D_001395B8;
            if(!(((HintFlags *)base)->intro&4) && IsPointInCuboid(gHeroPosition,hints->value9C) && (D_001A7390[0]-gProgressStatistics.time1CC>432000 || !gProgressStatistics.count1C8)) {
                ((HintFlags *)base)->intro|=4;QueueHintMessage(0xa3c,0x93);
            }
        }
        base=&gSubtitleHistory;
        if(base->countF0<65535) {
            if(gItemOwnedFlags[0x2E]) base->countF0=65535;
            else if(IsPointInCuboid(gHeroPosition,I(hints,0))) {
                if(base->countF0) {
                    if(timer_sda-base->timeF4>1080 || !base->timeF4)RequestSubtitleVoiceLine(0x9bd,0x14);
                    else if(base->timeF4<timer_sda)base->timeF4=timer_sda;
                } else {
                    base->countF0++; if(base->timeF4<timer_sda)base->timeF4=timer_sda;
                    base->levelsF8=(base->levelsF8|(1<<gCurrentMapIndex[0]))|0x80000000;
                }
            }
        }
        if(D_L02_001A8FF0 && !I(D_L02_0027FD48,0) && I(D_L02_0027FD48,0x24)==-1) {
            base=&gSubtitleHistory;
            if(base->flags158>=0)RequestSubtitleVoiceLine(0x9c5,0x1c);
            if(base->time154+base->count152>=D_001A7390[0]-2) {
                int count = base->count152+1;
                base->count152=count;
                if((count&0xffff)>=3600){RequestSubtitleVoiceLine(0x9c5,0x1c);base->count152=0;}
            } else {if(base->time154<D_001A7390[0])base->time154=D_001A7390[0];base->count152=0;}
        }
        TriggerSubtitleInCuboid(0x9bf,0x16,2,hints->value10,hints->value14);
        if(gSubtitleHistory.count120<65535) {
            if(gProgressStatistics.count54>=3 || IsPointInCuboid(gHeroPosition,hints->value24))gSubtitleHistory.count120=65535;
            else if(IsPointInCuboid(gHeroPosition,hints->value20)) {
                if(timer_sda-gSubtitleHistory.time124>1080 || !gSubtitleHistory.time124)RequestSubtitleVoiceLine(0x9c1,0x18);
                else if(gSubtitleHistory.time124<timer_sda)gSubtitleHistory.time124=timer_sda;
            }
        }
        TriggerSubtitleInCuboid(0x9c2,0x19,1,hints->value30,hints->value34);
        if(!gSubtitleHistory.count138) {
            if(!hints->value3C && unlock_sda)hints->value3C=1;
            if(gItemOwnedFlags[0x26])gSubtitleHistory.count138=65535;
            if(hints->value3C && IsPointInCuboid(gHeroPosition,hints->value38))RequestSubtitleVoiceLine(0x9c3,0x1a);
        }
        TriggerSubtitleInCuboid(0x9c4,0x1b,0,hints->value44,-1);
        if(IsArenaChallengeRunning(gMobyPool_L02+(hints->value68<<8))) {
            if(FastFloatHelperD(&hints->value94) && (((D_001395B8.timers>>gCurrentMapIndex[0])^1)&1)) {
                if(!gProgressStatistics.countF0 || D_001A7390[0]-gProgressStatistics.timeF4>42000)QueueHintMessage(0x9c9,0x20);
                D_001395B8.timers|=1<<gCurrentMapIndex[0];
            }
            if(IsChainbladeStateActive(gMobyPool_L02+(hints->value6C<<8)) && (!gProgressStatistics.count1BC || D_001A7390[0]-gProgressStatistics.time1C0>72000) && FastFloatHelperD(&hints->value98) && gSubtitleHistory.value2C0>=0)RequestSubtitleVoiceLine(0x9e3,0x3a);
        }
        if(D_L02_001A8FF0) {
            if(IsPointInCuboid(gHeroPosition,hints->value4C) && !gSubtitleHistory.count15C) {QueueHintMessage(0x9c6,0x1d);hints->value90=216000;}
            if(FastFloatHelperD(&hints->value90)){QueueHintMessage(0x9c6,0x1d);hints->value90=216000;}
            if(D_001A7390[0]-gProgressStatistics.time1A8<60)hints->value90=216000;
        }
        if(IsPointInCuboid(gHeroPosition,hints->value78) && (!gProgressStatistics.count1BC || D_001A7390[0]-gProgressStatistics.time1C0>72000) && !D_001395B8.hint && gSubtitleHistory.value2C0>=0)RequestSubtitleVoiceLine(0x9e3,0x3a);
        if(IsPointInCuboid(gHeroPosition,hints->value38))D_001395B8.hint=1;
        if(gItemOwnedFlags[0x2E])TriggerSubtitleInCuboid(0x9f1,0x48,2,hints->value7C,-1);
        if(gFrameCounter_L02<3 && gItemOwnedFlags[0x26] && !IsThirdPendingFlagSet(objects_sda+(hints->value88<<8)) && IsPointInCuboid(gHeroPosition,hints->value80)) {
            char *q;
            SetFlagToOne();q=D_L02_001B368C+(hints->value84<<7);ResetHeroPositionAndDirection(q+0x30,q+0x70,0,1);
        }
        if(IsPointInCuboid(gHeroPosition,hints->value28)) {
            if(D_001A7390[0]-gSubtitleHistory.time61C>120 || !gSubtitleHistory.time61C)RequestSubtitleVoiceLine(0xa2b,0x82);
            else if(gSubtitleHistory.time61C<D_001A7390[0])gSubtitleHistory.time61C=D_001A7390[0];
        }
    }
    }
}
