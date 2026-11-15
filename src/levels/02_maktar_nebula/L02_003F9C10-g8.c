/* func_L02_003F9C10 in its own unit (-G8 -Wa,-G64 with the qcopy profile: the class table
 * and the loadout bytes are small data reached through $gp).
 * The Maktar arena's encounter driver, the counterpart of Joba's func_L11_0043E1A0
 * (src/levels/11_joba/L11_0043E1A0-main-g64.c), and matched with the same idioms:
 * - The state block and the object are real structs (MaktarState, MaktarObj): struct
 *   accesses let the scheduler move global stores past them as retail does.
 * - The 0x284/0x288 owner record is a struct view, owner stored before timer.
 * - The sound-slot blocks read st->owner before the slot test; 0x001B3774 is element 1 of
 *   the slot pair at D_L02_001B3770 (an incomplete sda array: symbol+offset never fills a
 *   slot; a sized one goes to $gp everywhere) and the second slot's buffer is passed as a
 *   pointer plus 0xE0.
 * - 0x1A7A00 is the word at +0x10 of the player-progress block D_001A79F0, read as an
 *   element of it: retail never puts it in a delay slot (symbol+offset is length 2).
 * - The hero's 0x24A4 float is stored through the Hero view of D_00189E20, as in Joba; the
 *   early bare %hi(D_00189E20) orders gcse's insertions in the case 8 setup as retail has them.
 * - Case 8's clear loops count up; the counts loop has a counter of its own, the marks and
 *   loadout loops share one. Its wave end reads the class into cls1 and (u16) cls3 first.
 * - Case 7 clears the choice only when it is non-zero, and indexes the selection table
 *   index-first (D_00139586[D_L02_00264A70]), as retail adds the index first.
 */
#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI128 __attribute__((mode(TI)));
extern int func_00115DA8(char *, const char *, ...);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_002C8BA8(int);
extern void func_L00_002D40A0(char *, int, float);
extern void func_L00_002E6CF0(void (*)(char *), char *);
extern void func_00282A60(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283CE0(int);
extern int func_00288D58(void);
extern char * func_00288FB8(int);
extern void func_L00_00303530(int, int);
extern void func_L00_0030DD70(char *, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int func_002ACBC8(char *, int);
extern int func_L00_003206B8(char *, int);
extern void func_002AD860(int);
extern void func_002B0C28(int, int, int);
extern int func_002B3868(char *);
extern void func_L00_003294F0(char *, int);
extern void func_L01_00323310(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_L00_003672F8(void);
extern void func_L02_003D4900(char *);
extern void func_L02_003D4980(char *, char *);
extern void func_L02_003D4990(char *);
extern int func_L02_003D77B8(char *);
extern void func_L02_003DB870(char *, char *);
extern void func_L00_003DF6B0(int, int);
extern int func_L02_003F9AF0(int);
extern int func_L02_003F9B70(int);
extern void func_L00_003E4948(char *);
extern void func_L02_003FAF28(char *);
extern void func_L02_003FAF90(char *);
extern void func_L02_003FB000(char *);
extern void func_L02_003FB120(char *);
extern int func_L02_003FB4D8(char *, int);
extern char * func_L02_003FB5A0(char *, int, int);
extern void func_L02_003FB7E0(char *);
extern void func_L02_003FBA58(char *);
extern void func_L02_003FBAD0(char *);
extern void func_L02_003FBB90(char *);
extern void func_L02_003FBCF8(char *);
extern char * func_L02_003FC098(char *);
extern void func_L02_003FC268(char *, int);
extern void func_L02_003FC518(char *, int);
extern void func_L02_003FC7C8(char *);
extern void func_L02_003FC9C0(char *);
extern int func_L02_003FCBF0(char *);
extern void func_L02_003FCCA0(char *, int);
extern void func_L02_003FD070(char *);
extern void func_L02_003FD228(char *);
extern void func_L02_003FD770(char *);
extern void func_L02_003FD7C8(char *);
extern void func_L02_003FD8B8(char *);
extern void func_L02_003FE8B8(char *);
extern void func_L02_003FF698(char *);
extern void func_L02_003FF9A0(char *);
extern void func_L02_003FFDB0(char *);
extern void func_L02_004002E0(char *);
extern int func_L02_00400650(char *, int);
extern void func_L02_00400948(char *);
extern void func_L02_00400B10(void);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_L00_004028C0(int, int);
extern void func_00335438(void *, void *, int, int, int);
extern void func_003355A8(int);
extern unsigned char D_00139586 __attribute__((section(".data")));
extern unsigned char D_00139592 __attribute__((section(".data")));
extern unsigned char D_001395B8[] __attribute__((section(".data")));
extern int D_00139700 __attribute__((section(".data")));
extern int D_00139730 __attribute__((section(".data")));
extern char D_00189E20[] __attribute__((section(".data")));
extern char D_00189EA0[] __attribute__((section(".data")));
extern int D_0018B068 __attribute__((section(".data")));
extern int D_0018B6F4 __attribute__((section(".data")));
extern unsigned char D_0018C0D7 __attribute__((section(".data")));
extern int D_0018C2EC __attribute__((section(".data")));
extern char D_001A63A8[] __attribute__((section(".data")));
extern unsigned short D_001A65D2 __attribute__((section(".data")));
extern int D_001A7390[] __attribute__((sda));
extern int D_001A7904[] __attribute__((sda));
extern int D_001A7BC0[] __attribute__((sda));
extern int D_L02_001A8F00[] __attribute__((sda));
extern float D_L02_001A8F20[4] __attribute__((section(".sdata")));
extern int D_L02_001A9010 __attribute__((sda));
extern int D_L02_001AA1B0[] __attribute__((sda));
extern char *D_L02_001B1190[14] __attribute__((sda));
extern unsigned char D_L02_001B11C8[4] __attribute__((sda));
extern int D_L02_001B1224 __attribute__((sda));
extern char D_L02_001B1228[] __attribute__((section(".data")));
extern float D_L02_001B2FE0 __attribute__((sda));
extern char * D_L02_001B359C[] __attribute__((sda));
extern char * D_L02_001B35A8[] __attribute__((sda));
extern int D_L02_001B3680[] __attribute__((sda));
extern char * D_L02_001B368C[] __attribute__((sda));
extern char * D_L02_001B3770[] __attribute__((sda));
extern char D_L02_001BA3C0[] __attribute__((section(".data")));
extern int D_L02_001CAA80 __attribute__((section(".data")));
extern char D_L02_001FF6B8[] __attribute__((section(".data")));

/* The controller's state block (the object's 0x68 pointer). */
typedef struct MaktarState {
    u8 pad000[0x50];
    s32 loadout[4];      /* 0x50 */
    s32 lost;            /* 0x60 */
    u8 pad064[0xC];
    s32 trigger1;        /* 0x70 */
    s32 trigger2;        /* 0x74 */
    u8 pad078[4];
    s32 zone;            /* 0x7C */
    u8 pad080[0xC];
    s32 camera;          /* 0x8C */
    s32 counts[6];       /* 0x90 */
    char *slots[10];     /* 0xA8 */
    char *owner;         /* 0xD0 */
    s32 frames;          /* 0xD4 */
    s32 slot;            /* 0xD8 */
    u8 pad0DC[0x108 - 0xDC];
    s32 gate1;           /* 0x108 */
    s32 gate2;           /* 0x10C */
    u8 pad110[8];
    s16 result;          /* 0x118 */
    u8 pad11A[6];
    s16 cls;             /* 0x120 */
    s16 wave;            /* 0x122 */
    s16 fade;            /* 0x124 */
    u8 pad126[0x1D0 - 0x126];
    s16 marks[40];       /* 0x1D0 */
    s32 music;           /* 0x220 */
    u8 pad224[4];
    s32 volume;          /* 0x228 */
    u8 pad22C[4];
    s32 track;           /* 0x230 */
    s32 trackVolume;     /* 0x234 */
} MaktarState;

/* The object's own fields: state 0x20, the state block 0x68, timer 0x96, phase 0xBC. */
typedef struct MaktarObj {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    MaktarState *st;     /* 0x68 */
    u8 pad6C[0x96 - 0x6C];
    u16 timer;           /* 0x96 */
    u8 pad98[0xBC - 0x98];
    u8 phase;            /* 0xBC */
    u8 padBD;
    u8 flags;            /* 0xBE */
} MaktarObj;

typedef struct { u8 pad0[0x284]; char *owner; s32 timer; } MaktarFlags;

/* The persistent player-progress block starts at D_001A79F0 (the level index); its word at
   +0x10 (0x1A7A00) is read here as an element of it. */
extern int D_001A79F0[] __attribute__((sda));

/* One 0xE0-byte record of the level's selection table. */
typedef struct {
    u8 pad0[4];
    u8 enabled;          /* 0x04 */
    u8 pad5[0xE0 - 5];
} MaktarChoice;
extern MaktarChoice D_L02_00264A70[] __attribute__((section(".data")));

/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; void *ptr[0x980]; } Hero;
#define HERO ((Hero *)D_00189E20)

#define W(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
#define OBJ ((MaktarObj *)actor)
/* Per-frame update of the Maktar arena controller (moby class 2905). It runs the challenge menu, starts each wave of enemies, and ends the challenge. */
void func_L02_003F9C10(char *actor) {
    MaktarState *st = OBJ->st;
    float fadeLevel;
    float pos[4];
    char text[112];
    CallBlastHelperNoArgs(actor);
    D_L02_001A9010 = 1;
    D_001395B8[2] = D_001395B8[GetChallengeSaveIndex(0)] != 0;
    switch (OBJ->state) {
    case 0:
        ResetArenaControllerState_L02(actor);
        RunSceneryGroupSetup(actor);
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            SetMobyState(actor,2,-1);
            SetFlagToOne();
            st->fade = D_001A65D2;
            AddDrawCallbackToList1(DrawScreenWipeTransition,actor);
            OBJ->timer = 31;
        }
        break;
    case 1:
        if (IsPointInsideRecordVolume(gHeroPosition,st->zone)) SetMobyState(actor,4,-1);
        else if (IsPointInCuboid(gHeroPosition,st->trigger1)) {
            TryClaimNotice(4,0x2f3c,1);
            TryAllocateAndEnterState2(actor);
        } else if (D_001395B8[GetChallengeSaveIndex(0)] && IsPointInsideRecordVolume(gHeroPosition,st->trigger2)) {
            TryClaimNotice(4,0x2f3c,1);
            TryAllocateAndEnterState2(actor);
        }
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            SetMobyState(actor,2,-1);
            SetFlagToOne();
            st->fade = D_001A65D2;
            AddDrawCallbackToList1(DrawScreenWipeTransition,actor);
            OBJ->timer = 31;
        }
        D_L02_001A9010 = 0;
        break;
    case 2: {
        char *a;
        if (SetFirstPendingFlag(actor)) {
            MatchActiveCountGroupA(actor,0); MatchActiveCountGroupB(actor,0); OBJ->phase=0;
            break;
        }
        if (OBJ->phase==0) {
            if (OBJ->timer<31) {
                fadeLevel=IntToFloat(OBJ->timer)*0.05f;
                if (fadeLevel<1.0f) fadeLevel=IntToFloat(OBJ->timer)*0.05f;
                else fadeLevel=1.0f;
                D_L02_001B2FE0=fadeLevel;
                break;
            }
            st->fade=D_001A65D2;
            AddDrawCallbackToList1(DrawScreenWipeTransition,actor);
            if (D_L02_001CAA80!=1) LoadSceneChunk(1,st->music);
            a=D_L02_001B368C[0]+st->camera*128;
            ResetHeroPositionAndDirection(a+0x30,a+0x70,0x6f,1);
            CaptureCheckpointState(gHeroPosition,gHeroPosition+0x10);
            QueueKeyedRequest(st->music,st->volume);
            *(TI128 *)pos=*(TI128 *)(D_L02_001B368C[0]+st->camera*128+0x30);
            pos[2]+=2.0f;
            SetCamera5Pose(pos,D_L02_001B368C[0]+st->camera*128+0x70,1,0,0);
            OBJ->phase=2;
        } else if (OBJ->phase==2) {
            AddDrawCallbackToList1(DrawScreenWipeTransition,actor);
            D_L02_001B2FE0=0;
            if (st->fade>0) break;
            if (!D_001395B8[5]) {
                D_001395B8[5]=1; OBJ->phase=1;
                SetObjectFlagBit(gMobyPool_L02[0]+st->gate1*256,1);
                OBJ->timer=0;
                break;
            }
            goto beginApproach;
        } else if (OBJ->phase==1 && OBJ->timer>=61 && D_L02_001A8F00[0]!=2) {
        beginApproach:
            OBJ->phase=3;
            StartHeroLoaderState(0);
            StartHeroTargetState(GetArenaCameraPoint(actor),0,0.0f);
        } else if (OBJ->phase==3) {
            if (D_001395B8[GetChallengeSaveIndex(0)]) {
                if (vec_distance_xy(gHeroPosition,GetArenaCameraPoint(actor))<10.0f) SetMobyState(actor,4,-1);
                else if (OBJ->timer>=61) SetCameraModeState(2);
            } else {
                st->cls=0; st->wave=0;
                D_001395B8[0x3c]=st->result;
                SetMobyState(actor,8,-1);
                SetCameraModeState(2); StartHeroLoaderState(0);
            }
        }
        break;
    }
    case 5:
        if (OBJ->timer<180) {
            MatchActiveCountGroupA(actor,0); MatchActiveCountGroupB(actor,0);
            HERO->f[0x24A4/4]=200.0f;
            UpdateArenaGroupEnemies(actor); AddDrawCallbackToList1(DrawRadialQuadEffect,actor);
            break;
        }
    case 4:
        if (SetFirstPendingFlag(actor)) {
            if (OBJ->state==5) StartSceneAndCountViews(actor,st->cls);
            RunSceneryGroupSetup(actor); ResetGroupEnemies(actor);
            MatchActiveCountGroupA(actor,0); MatchActiveCountGroupB(actor,0);
            ResetHeroPositionAndDirection(GetArenaCameraPoint(actor),D_L02_001A8F20,0x6f,1);
            CaptureCheckpointState(gHeroPosition,gHeroPosition+0x10);
            SetupSceneCamera(actor);
        }
        CheckHeroAtArenaConsole(actor); HERO->f[0x24A4/4]=200.0f;
        break;
    case 10:
        if (OBJ->timer<360) {
            MatchActiveCountGroupA(actor,0); MatchActiveCountGroupB(actor,0);
            if (OBJ->timer>180) HERO->f[0x24A4/4]=200.0f;
            UpdateArenaGroupEnemies(actor); AddDrawCallbackToList1(DrawRadialQuadEffect,actor);
            break;
        }
        SetMobyState(actor,4,-1);
        break;
    case 11:
        if (SetFirstPendingFlag(actor)) { MatchActiveCountGroupA(actor,0); MatchActiveCountGroupB(actor,0); OBJ->phase=0; }
        if (!OBJ->phase) {
            if (OBJ->timer<180) {
                HERO->f[0x24A4/4]=200.0f;
                UpdateArenaGroupEnemies(actor); AddDrawCallbackToList1(DrawRadialQuadEffect,actor);
            } else { SetObjectFlagBit(gMobyPool_L02[0]+st->gate2*256,1); OBJ->phase=1; }
        } else if (D_0018C2EC>0 && D_L02_001A8F00[0]!=2 && OBJ->timer>=241) {
            OBJ->state=5; OBJ->flags&=0xfe;
        }
        break;
    case 6:
        if (SetFirstPendingFlag(actor) && !D_001395B8[GetChallengeSaveIndex(st->cls)]) {
            switch(st->cls) {
            case 0: StartAnnouncerMessage(actor,10); break;
            case 3: StartAnnouncerMessage(actor,13); break;
            case 1: case 2: case 4: case 5: case 6: case 10: StartAnnouncerMessage(actor,RandomIntBelow(2)+11); break;
            }
        }
        SelectNextUsableMenuEntry(actor);
        break;
    case 7: {
        int choice;
        if (SetFirstPendingFlag(actor)) {
            choice=D_001395B8[0x3c];
            if (choice && (!D_001395B8[GetChallengeSaveIndex(W(D_L02_001B1190[choice],8))] ||
                           (choice>=12 && !IsFlagByteSet()) ||
                           (choice==7 && !D_00139586[D_L02_00264A70].enabled) ||
                           (choice==8 && !D_00139592[D_L02_00264A70].enabled))) choice=0;
            st->result=choice;
            StartAnnouncerMessage(actor,RandomIntBelow(2));
        }
        UpdateChallengeMenu(actor);
        break;
    }
    case 8: {
        char *row, *entity;
        int frames, spawned, allowed;
        GetChallengeSaveIndex(0);
        if (SetFirstPendingFlag(actor)) {
            int i, k;
            char *row;
            st->wave=0;
            for(k=0;k<6;k++) st->counts[k]=0;
            st->frames=0; st->lost=0;
            RunSceneryGroupSetup(actor); StartArenaEnemyTally(actor); CommandEnemyGroupAttacks(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            MatchActiveCountGroupA(actor,H(row,10)); MatchActiveCountGroupB(actor,H(row,8));
            for(i=39;i>=0;i--) st->marks[i]=0;
            for(i=0;i<4;i++) st->loadout[i]=D_L02_001B11C8[i];
            if (st->cls==7) { char *g=gHeroState; D_00139700=300; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            else if(st->cls==8) { char *g=gHeroState; D_00139730=8; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            if(st->cls==13) { char *g=gHeroState; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            { char *g=gHeroState; W(g,0x24cc)=gCurrentMapIndex[4]; }
            NotifyMobysOfChallengeStart();
        }
        UpdateArenaEnemyTally(actor);
        if (IsWaveComplete_L02(actor)) {
            int i, cls1;
            unsigned int cls3;
            char *row;
            st->wave++;
            for(i=5;i>=0;i--) st->counts[i]=0;
            st->lost=0;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
            cls1=st->cls;
            cls3=(u16)st->cls;
            st->owner=0;
            if(st->wave>=H(D_L02_001B1190[cls1],0)) {
                if(cls3-7U<2 || cls1==13) D_0018B6F4=D_L02_001B1224;
                SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
                if(!st->cls && !D_001395B8[GetChallengeSaveIndex(0)]) SetMobyState(actor,11,-1);
                else SetMobyState(actor,5,-1);
                st->result=st->cls;
                return;
            }
            if(cls1>=14) st->cls=13;
            CommandEnemyGroupAttacks(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            MatchActiveCountGroupA(actor,H(row,10)); MatchActiveCountGroupB(actor,H(row,8));
        }
        frames=++st->frames;
        if((st->cls==3 && frames>=1801) || (st->cls==5 && frames>=3601)) {
            char *format, *buffer, *a, *b;
            int sum=0, j, count;
            buffer=text;
            for(j=0;j<6;j++) sum+=st->counts[j];
            format=D_L02_001B1228;
            a=GetLocalizedString(0x3269);
            count=st->wave*15+sum-st->lost;
            b=GetLocalizedString(0x2f61);
            Sprintf(buffer,format,a,count,b);
            CallLoadedModuleHandlerWithArg_003387A0_1(buffer,-1);
            SetMobyState(actor,10,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
            return;
        }
        if(st->cls==7 && D_0018B068==30 && D_00139700<=0) {
            allowed=1;
            for(entity=D_L02_001B35A8[0];entity;entity=P(entity,0x28)) {
                if(B(entity,0x20)==0xfe) continue;
                if(B(entity,0x20)==0xfd) continue;
                if(H(entity,0xaa)==0xc89 /* moby class 3209 */ || H(entity,0xaa)==0xbfe /* moby class 3070 */) allowed=0;
            }
            if(allowed) {
                CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x326b),-1);
                SetMobyState(actor,10,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
                return;
            }
        } else if(st->cls==8 && D_0018B068==42 && D_00139730<=0) {
            allowed=1;
            for(entity=D_L02_001B35A8[0];entity;entity=P(entity,0x28)) {
                if(B(entity,0x20)==0xfe) continue;
                if(B(entity,0x20)==0xfd) continue;
                if((unsigned short)(U(entity,0xaa)-0xc06)<=1) allowed=0;
            }
            if(allowed) {
                CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x326c),-1);
                SetMobyState(actor,10,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
                return;
            }
        } else if(st->cls==12) {
            if(D_0018C2EC<gCurrentMapIndex[4]) {
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x326a),-1);
                SetMobyState(actor,10,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
                return;
            }
            if(st->frames>=7201) {
                QueueMobyForGlowEffect(st->owner,0,ResetChainbladeToIdle);
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                SetMobyState(actor,5,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
                return;
            }
        } else if(st->cls==13 && D_0018C2EC<gCurrentMapIndex[4]) {
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x326a),-1);
            SetMobyState(actor,10,-1); SetTrackedObjectState(1,-1); StartGlobalObject(1,-1);
            return;
        }
        AddDrawCallbackToList1(DrawMaktarChallengeHud,actor);
        row=P(D_L02_001B1190[st->cls],4)+st->wave*20;
        if(OBJ->timer<61 && !U(row,16)) goto spawn;
        ClearSpawnSlotsWhenReady(actor); spawned=0; PickWatchedEntityForSlot(actor);
        if(st->slots[st->slot] && HasFreeChildSlotInState2(st->slots[st->slot])) {
            int i;
            for(i=st->counts[3];i<H(row,6);i++) spawned|=ClaimEnemyOfClass(actor,0xc3e /* PX6 BladeBall */);
            for(i=st->counts[1];i<H(row,2);i++) spawned|=ClaimEnemyOfClass(actor,0xb22 /* moby class 2850 */);
            for(i=st->counts[2];i<H(row,4);i++) spawned|=ClaimEnemyOfClass(actor,0xc3b /* Megacorp Security Robot - Flamethrower */);
            for(i=st->counts[0];i<H(row,0);i++) spawned|=ClaimEnemyOfClass(actor,0x9ca /* moby class 2506 */);
        }
        if(!st->counts[4] && B(row,16) && !st->counts[5] && B(row,17)) {
            char *a, *b;
            a=ClaimBossOfClass(actor,0x9f8 /* Chainblade */,0); b=ClaimBossOfClass(actor,0xa44 /* B2 Brawler Legs */,1);
            SetChainbladeHelper(a,b); SetWatchedEntity(b,a); AdvanceChainbladeHealthPhase(a); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=a; ClearMemory(D_L02_001FF6B8,0,224); }
            if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=b; ClearMemory(buf+224,0,224); }
            StartAnnouncerMessage(actor,15); QueueKeyedRequest(st->track,st->trackVolume);
        } else if(!st->counts[4] && B(row,16)) {
            char *a;
            a=ClaimBossOfClass(actor,0x9f8 /* Chainblade */,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=snd; ClearMemory(D_L02_001FF6B8,0,224); } }
            StartAnnouncerMessage(actor,14); QueueKeyedRequest(st->track,st->trackVolume);
        } else if(!st->counts[5] && B(row,17)) {
            char *a;
            a=ClaimBossOfClass(actor,0xa44 /* B2 Brawler Legs */,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=snd; ClearMemory(buf+224,0,224); } }
            StartAnnouncerMessage(actor,20); QueueKeyedRequest(st->track,st->trackVolume);
        }
        if(!U(row,16)) { char *g=gMusicState; if(B(g,0x48)!=st->music && B(g,0x3c)!=st->music) QueueKeyedRequest(st->music,st->volume); }
        if(spawned) ActivateSpawnSlots(actor);
    spawn:
        if(st->cls==7) HandleRequestSlotState(30);
        else if(st->cls==8) HandleRequestSlotState(42);
        else if(st->cls==13) { HandleRequestSlotState(10); D_0018C0D7=1; }
        UpdateHelperObjectOffsets(actor); PickMessageForWatchedEntity(actor);
        if(!(D_001A7BC0[0]&3)) PickNearestAttackers(actor);
        UpdateArenaGroupEnemies(actor); AddDrawCallbackToList1(DrawRadialQuadEffect,actor);
        if(GetChallengeProgressIndex(st->cls)!=-1) {
            D_L02_001AA1B0[0]=GetChallengeProgressIndex(st->cls); D_L02_001B3680[0]=D_001A7390[0];
        }
        break;
    }
    }
    TickArenaController(actor);
}
