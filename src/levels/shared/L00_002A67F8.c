#include "common.h"
extern int D_001A79F8[] __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern int D_L00_001A903C MACRO_ADDR;
extern unsigned char D_001A7A70[] __attribute__((sda));
extern unsigned int D_001A7AF0 MACRO_ADDR;
typedef struct {
 char pad0[0x18c];
 unsigned short f18c;
 char pad18e[0x14e];
 unsigned short f2dc;
 char pad2de[0x142];
 unsigned short f420;
 char pad422[0x22];
 unsigned short f444;
 char pad446[0x172];
 unsigned short f5b8;
 char pad5ba[0xb2];
 unsigned short f66c;
} State_flags;
extern State_flags D_0018C958;
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 unsigned short f1bc;
 char pad1be[0x2];
 unsigned int f1c0;
 unsigned int f1c4;
 char pad1c8[0xc];
 unsigned short f1d4;
 char pad1d6[0xa];
 unsigned short f1e0;
 char pad1e2[0x2];
 unsigned int f1e4;
 unsigned int f1e8;
} State_stats;
extern State_stats D_0018C750;
extern unsigned short D_0018C84C[];
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 int f1bc;
 char pad1c0[0x3e];
 short f1fe;
 char pad200[0x20];
 short f220;
 char pad222[0x55e];
 int f780;
 int f784;
 int f788;
 int f78c;
 char pad790[0xab8];
 int f1248;
 char pad124c[0x208];
 short f1454;
 char pad1456[0xe3a];
 char * f2290;
 int f2294;
 char pad2298[0x4];
 int f229c;
 char pad22a0[0x25c];
 short f24fc;
} State_b;
extern State_b D_00189E20;

extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned char D_001A7AF8[] __attribute__((sda));


extern unsigned int D_001A7390 MACRO_ADDR;
extern int D_001B19C8 MACRO_ADDR;
typedef struct { char pad[0x100]; float x,y; } InputState;
extern InputState D_00138180;
extern unsigned char D_00139568[];
typedef struct { char pad[12]; int kind; char rest[0xd0]; } CountedEntry;
extern CountedEntry D_L00_00262570[];
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);
extern float func_00282C48(float);
extern int func_00288E18(int,int);
extern int func_0029D830(void);
extern void func_L00_002F59A8(void);
/* Every frame, tracks player stats and unlocks. It counts quick left-right stick flicks, counts long airborne times, and checks a few conditions that award skill points. */
void func_L00_002A67F8(void)
{
    float stick[4], stickMagnitude;
    int isNegative,slot,itemCount;
    State_b *heroState;
    if((gEquipmentBits&0xbb50)==0xbb50 && !D_001A7A70[0xD]) {
        D_001A7A70[0xD]=1;
        (void)PlaySoundFromGlobalBank(1,0,0);
        SetEntryValueByIndex(0x1233,-1);
        D_L00_001A903C=1;
    }
    if(!gSubtitleHistory.f18c && gCurrentMapIndex<5 && !gProgressStatistics.f1d4 && gHeroState.f2294!=1 && gHeroState.f2294!=29) {
        qzero_nc(stick);
        stick[0]=gPadState.x;
        stick[1]=gPadState.y;
        stickMagnitude=FloatAbs(stick[0]);
        isNegative=stick[0]<0.0f;
        heroState=&gHeroState;
        switch(heroState->f780) {
        case 0:
            if(stickMagnitude>0.8f) {
                heroState->f784=isNegative;
                heroState->f780=1;
                heroState->f788=0;
                heroState->f78c=0;
            }
            break;
        case 1:
            ++heroState->f788;
            if(stickMagnitude<0.2f) {
                if(heroState->f788>=11) { heroState->f78c=0; heroState->f780=2; } else
                heroState->f780=0;
            } else if(heroState->f784!=isNegative) {
                if(heroState->f788>=11) { heroState->f78c=0; heroState->f780=3; } else
                heroState->f780=0;
            }
            break;
        case 2:
            ++heroState->f78c;
            if(stickMagnitude>0.8f && isNegative!=heroState->f784) {
                heroState->f78c=0; heroState->f780=3;
                break;
            }
            if(gHeroState.f78c>120) gHeroState.f780=0;
            break;
        case 3:
            ++heroState->f78c;
            if(heroState->f78c>40 && heroState->f78c>heroState->f788+20) {
                if(gProgressStatistics.f1e0<65535) ++gProgressStatistics.f1e0;
                if(D_001A7390>gProgressStatistics.f1e4) gProgressStatistics.f1e4=D_001A7390;
                { unsigned int bit = 1u << gCurrentMapIndex; gProgressStatistics.f1e8=(gProgressStatistics.f1e8|bit)|0x80000000u; }
                if(gProgressStatistics.f1e0>=2) RequestSubtitleVoiceLine(0x9ca,0x21);
                heroState->f780=0;
            } else if(stickMagnitude<0.2f || isNegative==gHeroState.f784) gHeroState.f780=0;
            break;
        }
    }
    if(D_001B19C8>0 && (D_001B19C8&127)==0) {
        if(!gSubtitleHistory.f2dc && !D_0018C84C[0]) {
            unsigned char *map=gItemSlotToRecord;
            CountedEntry *entries=gWeaponTable_L00;
            itemCount=0;
            for(slot=0;slot<56;slot++) {
                if(!entries[*(unsigned char *)(slot+(unsigned int)map)].kind && slot!=10 && gItemOwnedFlags[slot]) itemCount++;
            }
            if(itemCount>=9) RequestSubtitleVoiceLine(0x9e6,0x3d);
        }
        if(gHeroState.f229c==17 && gHeroState.f1bc>300 && !gHeroState.f24fc && !gSubtitleHistory.f5b8 && !gHeroState.f1fe && *(int *)(*(char **)(gHeroState.f2290+0x24)+0x134)) RequestSubtitleVoiceLine(0xa23,0x7a);
        if(gPlayerBolts[2]==80 && !gSubtitleHistory.f66c) {
            if(!D_001A7A70[7]) {
                D_001A7A70[7]=1;
                (void)PlaySoundFromGlobalBank(1,0,0);
                SetEntryValueByIndex(0x1233,-1);
                D_L00_001A903C=1;
            }
            RequestSubtitleVoiceLine(0xa32,0x89);
        }
        if(!gSubtitleHistory.f420) {
            State_b *hero=&gHeroState;
            unsigned char *items=D_001A7A80;
            if(items[hero->f1248]&32) RequestSubtitleVoiceLine(0xa01,0x58);
        }
        if(gCurrentMapIndex==5) gSubtitleHistory.f444=65535;
    }
    if(!gHeroState.f1454) gHeroState.f220=0;
    else if(gHeroState.f2294) ++gHeroState.f220;
    if(gHeroState.f220>90) {
        if(gProgressStatistics.f1bc<65535) ++gProgressStatistics.f1bc;
        if(D_001A7390>gProgressStatistics.f1c0) gProgressStatistics.f1c0=D_001A7390;
        { unsigned int bit = 1u << gCurrentMapIndex; gProgressStatistics.f1c4=(gProgressStatistics.f1c4|bit)|0x80000000u; }
    }
    if(D_001B19C8<5 || (D_001B19C8&511)==21) UpdateEntryStates();
    AdvanceCheckedCursor();
}
