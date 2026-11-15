/* func_L03_003F09C0 needs its own unit: -G8 for the $gp-relative words and -frac2-zero-ti-por
 * (config/cflags.txt) for the local quadword clear, which retail keeps as `por` + `sq`.
 *
 * Two timers decide the shape of the help tests. `now - prev > 120` tests the long arm first:
 * the arm's cross-jumped tail then ends in a jump to a label where v0 is live, so reorg annuls
 * the `bnel` slot. The history[138] test is `!count && near`, else the timer, as near's failure
 * reaches the timer test in retail.
 */
#include "common.h"

typedef struct {
    u8 prefix[0x80]; float position[4];
    u8 pad90[0x128]; int field1B8;
    u8 pad1BC[0x20D8]; int field2294;
    u8 pad2298[0x1C]; u8 field22B4;
} Hero;
extern Hero D_00189E20;
typedef union {
    u8 bytes[0xA3];
    struct { u8 pad[0x78]; unsigned char bit0:1; unsigned char other:7; } bits;
} Flags;
extern Flags D_001395B8;
typedef struct { u8 pad00[0x70]; u32 field70; u8 pad74[0x7C]; u16 fieldF0; u16 padF2; u32 fieldF4; } HelpState;
extern HelpState D_0018C750;
/* Subtitle history records: count, last frame, and per-level flags. */
typedef struct { u16 count, pad; u32 time, levels; } SubtitleHistory;
extern SubtitleHistory D_0018C958[];
typedef struct {
    int active; u8 pad04[0x20]; int key; int type;
} VoiceState;
extern VoiceState D_L03_00282078;
extern u8 D_L03_001BFB80[];
extern u8 *D_L03_001B2B0C[] __attribute__((sda));
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u16 *D_L03_001FB5A0[];
extern int D_L03_001B2A38 __attribute__((sda));
extern int D_L03_001B0F20 __attribute__((sda));
extern u32 D_001A7390[] __attribute__((sda));
extern int D_001A79F0;
extern int D_L03_001B2548 __attribute__((nosda));
/* The published map identifies the persistent save block at this base. */
typedef struct { u8 pad00[0x12]; u8 field12; u8 pad13[0xFA]; u8 mapDataSet; u8 pad10E[0xD804 - 0x10E]; } PlayerProgress;
extern PlayerProgress D_001A79F8 __attribute__((sda));
extern u8 D_001A7BED[] __attribute__((sda));
extern void func_L00_003672F8(void);
extern void func_L00_002B9D60(void *,void *,int,int);
extern int func_002AD860(int);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_002ACBC8(void *,int);
extern int func_00288AA0(void *,int);
extern int func_00288BE8(void *);
extern void func_002F5CB8(void *,void *);
extern void func_L03_003F1470(void *);
extern int func_00282948(void *);
extern int func_00288E18(int,int);
extern void func_00288D90(void);
extern void func_L01_002EABA8(int,int,int,int,int);
extern float func_00282E48(void *,void *);
extern int func_L03_003112F8(void);
extern void func_L00_002E6CF0(void *,void *);
extern void func_L00_003E4948(void *);
#define I(p,n) (*(int *)((p)+(n)))
/* Per-frame update of moby class 3109: at Endako it watches where the hero is and starts the right help voice-over lines. */
void func_L03_003F09C0(u8 *entity) {
    u8 *state = *(u8 **)(entity+0x68);
    int mode = entity[0x20];
    u16 *p;
    u8 *record;
    union { float f[4]; unsigned int q __attribute__((mode(TI))); } point;
    switch (mode) {
    case 0:
        entity[0x30] = 0xFF;
        I(state,0x74) = 0;
        if (gPlayerBolts.mapDataSet) {
            if (!D_001395B8.bytes[0xD]) {
                u8 *entry;
                SetFlagToOne();
                entry = D_L03_001B2B0C[0] + I(state,0x70)*0x80;
                ResetHeroPositionAndDirection(entry+0x30,entry+0x70,0,1);
                HandleRequestSlotState(13);
            }
            if (gPlayerBolts.mapDataSet) {
                for(p=D_L03_001FB5A0[I(state,0x80)];
                    (I(state,0x80)&255)!=255 && I(state,0x80)<=D_L03_001B2A38 && p &&
                    ((p != 0 && (short)p[-1]>=0) || p==D_L03_001FB5A0[I(state,0x80)]); p++) {
                    record = D_L03_001B2A1C[0] + ((*p&0x7fff)<<8);
                    if(!record) break;
                    MarkMobySpawned(record);
                }
            }
        }
        SetMobyState(entity,1,-1);
        break;
    case 1:
        if (!D_001395B8.bytes[0xD] && IsPointInCuboid(gHeroState.position,I(state,0x6C)))
            D_001395B8.bytes[0xD] = mode;
        if (!D_001395B8.bytes[9] && IsPointInCuboid(gHeroState.position,I(state,0x4C)) && PushRequestQueue(D_L03_001BFB80,0x34)) {
            LaunchQueuedRequest(D_L03_001BFB80);
            D_001395B8.bytes[9]=1;
            SetStoredValuePair(StartBossAreaObjects,entity);
        }
        if (!gHeroState.field22B4 && IsPointInCuboid(gHeroState.position,I(state,8))) {
            if (FastFloatHelperD(state+0x60)) {
                RequestSubtitleVoiceLine(0x9CB,0x22);
                I(state,0x60)=600;
            }
        } else if (IsPointInCuboid(gHeroState.position,I(state,0xC))) {
            if(gSubtitleHistory[34].count!=65535) {
                gSubtitleHistory[34].count=65535;
                if (D_L03_00282078.active || D_L03_00282078.key!=-1) {
                    if (D_L03_00282078.type==0x22) BeginSubtitleClose();
                }
            }
        }
        if(IsPointInCuboid(gHeroState.position,I(state,0x10)) && !D_L03_00282078.active && D_L03_00282078.key==-1) {
            u32 now = D_001A7390[0], prev = gSubtitleHistory[35].time;
            if (now - prev > 120) {
                RequestSubtitleVoiceLine(0x9CC,0x23);
                if (gSubtitleHistory[35].time < D_001A7390[0]) gSubtitleHistory[35].time = D_001A7390[0];
            } else {
                if (prev < now) gSubtitleHistory[35].time = now;
            }
        } else if(IsPointInCuboid(gHeroState.position,I(state,0x14))) {
            if(gSubtitleHistory[35].count!=65535) {
                gSubtitleHistory[35].count=65535;
                if(D_L03_00282078.active || D_L03_00282078.key!=-1) BeginSubtitleClose();
            }
        }
        if(IsPointInCuboid(gHeroState.position,I(state,0x18))) {
            if(D_001A7390[0]-gSubtitleHistory[36].time>2400) RequestSubtitleVoiceLine(0x9CD,0x24);
        } else if(IsPointInCuboid(gHeroState.position,I(state,0x1C))) {
            D_001395B8.bytes[0xA2]=1;
            gSubtitleHistory[36].count=65535;
            if(D_L03_00282078.active || D_L03_00282078.key!=-1) BeginSubtitleClose();
        }
        if(IsPointInCuboid(gHeroState.position,I(state,0x64)) && !gSubtitleHistory[123].count) {
            D_001395B8.bytes[0xA2]=1;
            RequestSubtitleVoiceLine(0xA24,0x7B);
        }
        TriggerSubtitleInCuboid(0x9D3,0x2A,0,I(state,0x20),-1);
        if(IsPointInCuboid(gHeroState.position,I(state,0x24)) && ((D_001395B8.bytes[0x78] ^ 1) & 1)) {
            u32 now=D_001A7390[0], prev=gSubtitleHistory[131].time;
            if(now-prev>1080 || !prev) RequestSubtitleVoiceLine(0xA2C,0x83);
            else if(prev<now) gSubtitleHistory[131].time=now;
        }
        TriggerSubtitleInCuboid(0x9D5,0x2C,0,I(state,0x40),-1);
        TriggerSubtitleInCuboid(0x9E5,0x3C,2,I(state,0x54),-1);
        if(IsPointInCuboid(gHeroState.position,I(state,0x2C))) gSubtitleHistory[43].count=65535;
        else if(IsPointInCuboid(gHeroState.position,I(state,0x28))) {
            if(gHeroState.field2294==0x23 && gHeroState.field1B8==1) ++I(state,0x30);
            if(I(state,0x30)>=3 && gHeroState.field2294==0x23) RequestSubtitleVoiceLine(0x9D4,0x2B);
        }
        if(gHeroState.position[2]<155.5f) {
            point.q = 0;
            point.f[0]=400.0f;
            point.f[1]=222.0f;
            point.f[2]=155.0f;
            if(fast_vec_dist(gHeroState.position,point.f)<24.0f) gSubtitleHistory[37].time=0;
        }
        TriggerSubtitleInCuboid(0x9CE,0x25,1,I(state,0x28),I(state,0x2C));
        TriggerSubtitleInCuboid(0x9CE,0x25,3,I(state,0x28),I(state,0x2C));
        if(IsPointInCuboid(gHeroState.position,I(state,0x7C))) {
            if(!gProgressStatistics.fieldF0 || D_001A7390[0]-gProgressStatistics.fieldF4>72000) {
                u32 seen = gSubtitleHistory[32].levels & (1 << gCurrentMapIndex);
                if (!seen) RequestSubtitleVoiceLine(0x9C9,0x20);
            }
        }
        if(!gPlayerBolts.field12 && gFrameCounter_L03>0 && !(gFrameCounter_L03&0x7F) && !D_001A7BED[0] && !CountActiveTypeOneEntries()) {
            u32 count = gSubtitleHistory[138].count;
            if (count < 3) {
                if (!count && IsPointInCuboid(gHeroState.position,I(state,0x78))) RequestSubtitleVoiceLine(0xA33,0x8A);
                else if (D_001A7390[0] - gSubtitleHistory[138].time > 36000) RequestSubtitleVoiceLine(0xA33,0x8A);
            }
        }
        if(D_001A7390[0]-gProgressStatistics.field70>108000 && IsPointInCuboid(gHeroState.position,I(state,0x78))) {
            u32 seen = gSubtitleHistory[12].levels & (1 << gCurrentMapIndex);
            if (!seen) RequestSubtitleVoiceLine(0x9B5,0xC);
        }
        break;
    }
    if(D_L03_001B0F20) AddDrawCallbackToList1(CallBlastHelperNoArgs,entity);
}
