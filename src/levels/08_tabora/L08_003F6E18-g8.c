#include "common.h"
typedef struct {
    u8 pad00[0x20]; u8 state; u8 pad21[0x68-0x21];
    void *data; u8 pad6c[0xB0-0x6c]; u8 id; u8 padB1;
    s16 index; u8 padB4[0x100-0xB4];
} TaboraMoby;
extern TaboraMoby *D_L08_001B29DC;
extern u8 D_001395B8[], D_00139568[];
typedef struct { u8 pad[0x50]; int flags[2]; } TaboraProgress;
extern TaboraProgress D_00139768;
typedef struct { int state; u8 pad[0x24]; float value; } FlareStatus;
extern FlareStatus D_L08_001CA080;
typedef struct { u8 pad[4]; u8 count; u8 rest[0xDB]; } StageStatus;
extern u8 D_L08_0026CCF0[];
typedef struct { u8 pad[0x464]; u8 flags[1]; } TaboraLevelFlags;
extern TaboraLevelFlags D_L08_0021EAF0, D_L08_0021DE80;
extern u8 D_0019B2E8[], D_0019B4A8[], D_0019B278[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern int D_001A79F0, D_0018CD20 NOT_SDA;
extern float D_00189EA8 NOT_SDA;
extern u8 D_001A7AF8[] __attribute__((sda));
extern int D_L08_0021F758 NOT_SDA, D_L08_001A8F00, D_L08_001B2514;
extern float D_L08_001B2420 __attribute__((sda));
extern float D_L08_001B9E08 NOT_SDA;
extern char D_L08_001BFD00[], D_00189EA0[];
extern char D_L08_002B53E0[], D_L08_001B0BE8[], D_L08_001B0C00[], D_L08_001B0C28[], D_L08_001B0C50[], D_L08_001B0C70[], D_L08_001B0C90[], D_L08_001B0CC0[], D_L08_001B0CF0[], D_L08_001B0D08[], D_L08_001B0D30[], D_L08_001B0D48[], D_L08_001B0D70[], D_L08_001B0DA8[];
extern void func_0026FEB8(char *, ...);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_L00_002E6CF0(void *,void *);
extern int func_00287FF8(int,int);
extern void func_00288508(int);
extern int func_00288AA0(void *,int);
extern int func_00288BE8(void *);
extern int func_00288D58(void);
extern int func_00288E18(int,int);
extern void func_L01_002EABA8(int,int,int,int,int);
extern void func_L08_0030A8F8(int);
extern void func_L00_00303530(int,int);
extern int func_0029B3E0(int,int);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_L00_00329520(void *,int);
extern void func_L08_0036EFC8(void);
extern void func_L00_003672F8(void);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L08_003F6D30(void *);
extern float func_L08_003F76C0(void *);
extern void func_L08_003F77C0(void *);
extern void func_L08_003F79E0(void *);
extern void func_L08_003F7A48(void *);

static __inline__ int TaboraStageComplete(void)
{
    int threshold;
    if (IsFlagByteSet()) threshold = 4;
    else threshold = 1;
    if (((StageStatus *)D_L08_0026CCF0)[gItemSlotToRecord[0xA]].count >= threshold) return 1;
    return 0;
}

/* Per-frame update of the level's progress controller moby (class 3114): checks which goals are done, plays the talk lines, moves between states and retires its helper mobys. */
void func_L08_003F6E18(u8 *moby)
{
    u8 *vars = *(u8 **)(moby+0x68);
    TaboraMoby *other;
    int mode;
    int bits;
    unsigned int seen;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30]=255;
        *(u16 *)(moby+0x96)=0;
        if (!D_001395B8[0x1C]) SetFlagToOne();
        if (*(int *)(vars+4)!=-1 && D_00189EA8 < D_L08_001CA080.value) {
            other=(D_L08_001B29DC+*(int *)(vars+4));
            if (other->state || (D_0019B2E8[other->id+(gCurrentMapIndex<<4)]&128) ||
                D_L08_0021EAF0.flags[other->index])
                goto relocate_child;
            bits = D_0019B4A8[(other->index>>1)+(gCurrentMapIndex<<10)];
            if (((u16)other->index & 1) ? ((bits >> 4) & 7) : (bits & 7)) {
relocate_child:
                STUB_printf(D_L08_002B53E0);
                ResetHeroPositionAndDirection((u8 *)other+0x10,(u8 *)other+0xF0,0,1);
                SetMobyState(moby,5,-1);
            }
        }
        if (TaboraStageComplete()) {
            if (*(int *)(vars+0x30)!=-1) {
                MarkMobySpawned((D_L08_001B29DC+*(int *)(vars+0x30)));
                *(int *)(vars+0x30)=-1;
            }
            if (D_00189EA8 < D_L08_001CA080.value) {
                mode=0;
                STUB_printf(D_L08_001B0BE8);
                D_L08_0021F758=0;
                SetFlagToOne();
                SetMobyState(moby,5,-1);
            } else {
                mode=1;
                STUB_printf(D_L08_001B0C00);
                D_L08_0021F758=mode;
                SetMobyState(moby,5,-1);
            }
            ReplaceTrackedMoby(moby);
        } else if (!(D_00139768.flags[0]&0x80000) || !(D_00139768.flags[1]&0x100000)) {
            mode=1;
            STUB_printf(D_L08_001B0C28);
            if (PushRequestQueue(D_L08_001BFD00,0x53)) {
                PushRequestQueue(D_L08_001BFD00,0x54);
                LaunchQueuedRequest(D_L08_001BFD00);
                SetSlowdownFactorAndLowFpsFade();
                SetFlagToOne();
                SetMobyState(moby,1,-1);
            }
        } else if (D_00139768.flags[1]&0x200000) {
            mode=0;
            STUB_printf(D_L08_001B0C50);
            D_L08_0021F758=0;
            SetFlagToOne();
            SetMobyState(moby,3,-1);
        } else {
            mode=0;
            STUB_printf(D_L08_001B0C70);
            SetFlagToOne();
            SetMobyState(moby,1,-1);
            *(u16 *)(moby+0x96)=6;
        }
        if (gItemOwnedFlags[0x15] && *(int *)(vars+0x20)!=-1 &&
            (D_L08_001B29DC+*(int *)(vars+0x20))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(vars+0x20))->state!=0xFD &&
            *(int *)(vars+0x24)!=-1 &&
            (D_L08_001B29DC+*(int *)(vars+0x24))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(vars+0x24))->state!=0xFD) {
            STUB_printf(D_L08_001B0C90);
            if (!D_0019B278[*(int *)D_L08_001B29DC[*(int *)(vars+0x24)].data+(gCurrentMapIndex<<2)]) {
                mode=1;
                D_L08_0021F758=mode;
                STUB_printf(D_L08_001B0CC0);
                {
                    TaboraMoby *replacement = D_L08_001B29DC + *(int *)(vars+0x20);
                    ResetHeroPositionAndDirection((u8 *)replacement+0x10,(u8 *)replacement+0xF0,0,1);
                }
                SetFlagToOne();
            }
            if (TaboraStageComplete()) {
                if (IsFlagByteSet()) SeekChainEntry(10,4);
                else SeekChainEntry(10,1);
                RunScreenUpdateSteps(1);
            }
            SetMobyState(moby,5,-1);
        }
        STUB_printf(D_L08_001B0CF0,mode);
        LoadSceneChunk(mode,0);
        SetFarTargetPoint(moby);
        StartSparkleBurst(moby);
        break;
    case 1:
        if (!IsEitherModeTwo() && *(u16 *)(moby+0x96)>=6) {
            D_001395B8[0x19]=1;
            if (PushRequestQueue(D_L08_001BFD00,0x55)) {
                LaunchQueuedRequest(D_L08_001BFD00);
                D_L08_0021F758=0;
                STUB_printf(D_L08_001B0D08);
                SetSlowdownFactorAndLowFpsFade();
                D_L08_001B2514=1;
                D_L08_001B2420=1.2f;
                DisableObjectListFlags();
                LoadSceneChunk(0,0);
                SetMobyState(moby,2,-1);
            }
        }
        break;
    case 2:
        if (!IsEitherModeTwo() && *(u16 *)(moby+0x96)>=6) {
            D_001395B8[0x1A]=1;
            STUB_printf(D_L08_001B0D30);
            MemcardSave(0,-1);
            SetMobyState(moby,3,-1);
        }
        break;
    case 3:
        if (IsPointInsideRegion(gHeroPosition,*(int *)vars)) {
            if (PushRequestQueue(D_L08_001BFD00,0x56)) {
                LaunchQueuedRequest(D_L08_001BFD00);
                STUB_printf(D_L08_001B0D48);
                SetMobyState(moby,4,-1);
            }
        }
        break;
    case 4:
        if (D_L08_001A8F00==2 && *(int *)(vars+0x30)!=-1) {
            MarkMobySpawned((D_L08_001B29DC+*(int *)(vars+0x30)));
            *(int *)(vars+0x30)=-1;
        }
        if (!IsEitherModeTwo() && *(u16 *)(moby+0x96)>=6) {
            if (IsFlagByteSet()) SeekChainEntry(10,4);
            else SeekChainEntry(10,1);
            RunScreenUpdateSteps(1);
            ShowHelpMessageForId(10);
            ReplaceTrackedMoby(moby);
            if (*(int *)(vars+8)!=-1) {
                other=D_L08_001B29DC + *(int *)(vars+8);
                STUB_printf(D_L08_001B0D70);
                D_L08_0021DE80.flags[other->index]=other->id+2;
                {
                    int id = other->id;
                    if (id == 255 || (!(D_L08_001B2840[(u8)id] & 128) &&
                        (D_0019B2E8[(u8)id + (gCurrentMapIndex << 4)] & 128)))
                        D_L08_0021EAF0.flags[other->index]=id+2;
                }
            }
            STUB_printf(D_L08_001B0DA8);
            MemcardSave(0,-1);
            SetMobyState(moby,5,-1);
        }
        break;
    }
    ++*(u16 *)(moby+0x96);
    if (D_001395B8[0x1C]) {
        seen = (unsigned)D_0018CD20 & (1 << gCurrentMapIndex);
        if (!seen) RequestSubtitleVoiceLine(0x9F9,0x50);
    }
    TriggerSubtitleInCuboid(0xA3A,0x91,0,*(int *)(vars+0xC),-1);
    if (D_L08_001CA080.state==1) {
        D_L08_001B9E08=GetHeightMapGroundHeight(moby);
        AddDrawCallbackToList1(DrawLensFlare_L08,moby);
    }
}
