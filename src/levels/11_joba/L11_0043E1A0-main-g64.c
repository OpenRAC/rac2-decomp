/* func_L11_0043E1A0 in its own unit (-G64 -Wa,-G64: the 56-byte class table is small data).
 * What decided the match:
 * - The state block and the object are real structs (JobaState, JobaObj), not byte views.
 * - Globals by retail form: lui/load in ordinary flow plus $gp in delay slots = a plain
 *   sized scalar; $gp everywhere = sda with its measured size; explicit %hi/%lo = an
 *   incomplete array. 0x001B3774 is element 1 of the sound pair D_L11_001B3770[2] (a
 *   symbol+offset access never fills a slot); the height band's bounds are two sda scalars.
 * - The clear loops count up; the marks and limits loops share one counter.
 * - Case 2's shared tail is written out per arm; case 9's 13-or-5 code per arm with the
 *   timer store in each arm (cross-jumping keeps retail's then-arm + b).
 * - The sound-slot blocks read st->sound before the slot test and pass the second slot's
 *   buffer as a pointer plus 0xE0; index-first sums where retail adds the index first.
 * - Case 8's wave end reads the class as (u16) into cls3 right after cls1.
 * - func_L00_0030DD70 is called for its effect only and declared void here: its ignored
 *   $v0 result otherwise takes v0 from the case-9 light/lamp chain in local-alloc.
 *   (Its definition in src/levels/shared/L00_002FC7A0.c returns its argument or the
 *   helper's value.)
 * - Case 9's start flags are set D_L11_001A8FF4 first, then D_L11_001A8FF0.
 */
#include "common.h"

/* func_L11_0043E1A0: the level's scripted-encounter driver, dispatched on the object's state
   byte 0x20.  Built -G8 in its own unit: the class tables and their constants sit in the level's
   small data and are reached through $gp, while the controls declared MACRO_ADDR are macro
   operands that the assembler expands to lui/low-half in ordinary flow and to one $gp access in
   a delay slot. */

/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

/* The object's own fields (state 0x20, timer 0x96, phase 0xBC) and the state block at 0x68. */
typedef struct JobaState {
    u8 pad000[0x90];
    f32 delay[4];        /* 0x90 */
    f32 phase[4];        /* 0xA0 */
    f32 speed[4];        /* 0xB0 */
    u8 pad0C0[0x20];
    s32 limits[6];       /* 0xE0 */
    u8 pad0F8[8];
    s32 counts[8];       /* 0x100 */
    u8 *slots[8];        /* 0x120 */
    s32 lost;            /* 0x140 */
    u8 pad144[0xC];
    s32 trigger1;        /* 0x150 */
    s32 trigger2;        /* 0x154 */
    u8 pad158[0x14];
    s32 camera;          /* 0x16C */
    u8 pad170[0x10];
    s32 sound;           /* 0x180 */
    s32 owner;           /* 0x184 */
    s32 frames;          /* 0x188 */
    s32 slot;            /* 0x18C */
    u8 pad190[0xC];
    f32 heading;         /* 0x19C */
    u8 pad1A0[0x18];
    s32 door;            /* 0x1B8 */
    u8 pad1BC[4];
    s32 light;           /* 0x1C0 */
    u8 pad1C4[0xC];
    s32 lamp;            /* 0x1D0 */
    s32 gate1;           /* 0x1D4 */
    s32 gate2;           /* 0x1D8 */
    s32 gate3;           /* 0x1DC */
    u8 pad1E0[4];
    s32 zone;            /* 0x1E4 */
    s16 result;          /* 0x1E8 */
    u8 pad1EA[6];
    s16 cls;             /* 0x1F0 */
    s16 wave;            /* 0x1F2 */
    s16 fade;            /* 0x1F4 */
    u8 pad1F6[4];
    s16 mode;            /* 0x1FA */
    u8 pad1FC[0xA4];
    s16 marks[0x28];     /* 0x2A0 */
    s32 music;           /* 0x2F0 */
    u8 pad2F4[4];
    s32 volume;          /* 0x2F8 */
    u8 pad2FC[4];
    s32 track;           /* 0x300 */
    s32 trackVolume;     /* 0x304 */
} JobaState;

typedef struct {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    JobaState *st;       /* 0x68 */
    u8 pad6C[0x96 - 0x6C];
    u16 timer;           /* 0x96 */
    u8 pad98[0xBC - 0x98];
    u8 phase;            /* 0xBC */
} JobaObj;

typedef int TI128 __attribute__((mode(TI)));

/* One 26-byte class record: the six target counts, then the flag bytes. */
typedef struct {
    s16 h[10];
    u8 b[6];
} JobaRecord;

typedef struct {
    s16 count;
    JobaRecord *records;
    s32 id;
} JobaClass;

typedef struct {
    u8 pad0[0x284];
    s32 owner;
    s32 timer;
} JobaFlags;

/* A moby record of the level's moby array (0x100 bytes). */
typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1[0x31 - 0x1C];
    u8 hidden;
    u8 pad2[2];
    u16 flags;
    u8 pad3[0x100 - 0x36];
} JobaMoby;

/* A 0x40-byte record of the level's light table. */
typedef struct {
    u8 pad0[0x30];
    f32 pos[2];
    f32 height;
    u8 pad1[0x40 - 0x3C];
} JobaLight;

extern char D_00189E20[];
extern u8 D_001395B8[];
extern u8 D_00139586[];
extern s32 D_00139700[];
extern s32 D_001A7904;
extern u16 D_001A65D2[];
extern s32 D_001A7A00;
extern s32 D_001A7BC0;
extern s32 D_001A7390;
extern u8 D_001A63A8[];

extern f32 D_L11_001A7CD8;
extern s32 D_L11_001A8F00;
extern s32 D_L11_001A8FF0;
extern s32 D_L11_001A8FF4;
extern s32 D_L11_001A9010;
extern u16 **D_L11_001A9014;
extern s32 D_L11_001AA170;
extern u8 D_L11_001B14B0[8] __attribute__((sda));
extern s32 D_L11_001B14B8[6] __attribute__((sda));
extern s32 D_L11_001B14D0[2] __attribute__((sda));
extern s32 D_L11_001B14D8[8] __attribute__((sda));
extern JobaClass *D_L11_001B14F8[14] __attribute__((sda));
extern f32 D_L11_001B1570[4] __attribute__((sda));
extern f32 D_L11_001B1580 __attribute__((sda));
extern f32 D_L11_001B1584 __attribute__((sda));
extern s32 D_L11_001B1588 __attribute__((sda));
extern f32 D_L11_001B1590[2];
extern f32 D_L11_001B1598[2];
extern char D_L11_001B15A0[];
extern f32 D_L11_001B2FE0;
extern s32 D_L11_001B30C8;
extern JobaMoby *D_L11_001B359C;
extern s32 D_L11_001B3680;
extern u8 *D_L11_001B368C;
extern s32 D_L11_001B3770[2];
extern JobaLight *D_L11_001B3C1C;
extern JobaFlags D_L11_001BA780;
extern s32 D_L11_001CAE40[];
extern u8 D_L11_001FFA78[];
/* One 0xE0-byte record of the level's selection table. */
typedef struct {
    u8 pad0[4];
    u8 enabled;
    u8 pad5[0xE0 - 5];
} JobaChoice;

extern JobaChoice D_L11_00279BA0[];

extern int func_00115DA8(char *, const char *, ...);
extern void func_00282A60(void *, int, int);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283CE0(s32);
extern s32 func_00288D58(void);
extern s32 func_00288FB8(s32);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002ACBC8(void *, s32);
extern void func_002AD860(s32);
extern void func_002B0C28(s32, s32, s32);
extern s32 func_002B3868(u8 *);
extern void func_002DF3F8(void *, void *);
extern void func_00335438(char *, char *, int, int, int);
extern void func_003355A8(int);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_L00_002C8BA8(s32);
extern void func_L00_002D40A0(void *, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_00303530(int, int);
/* Defined returning int (L00_002FC7A0.c), but retail compiled this caller as a void call, as
   the registers after the call show: the original header evidently declared it void. */
extern void func_L00_0030DD70(int, int);
extern int func_L00_003206B8(void *, int);
extern void func_L00_003294F0(u8 *, s32);
extern void func_L00_003672F8(void);
extern void func_L00_003DF6B0(int, int);
extern void func_L00_003E4948(void);
extern void func_L00_004028C0(char *, int);
extern void func_L01_00323310(s32, s32);
extern s32 func_L02_003D77B8(u8 *);
extern void func_L02_003FF698(void *);
extern s32 func_L11_002D8EF8(s32, s32);
extern int func_L11_0043E090(unsigned int);
extern int func_L11_0043E108(unsigned int);
extern void func_L11_00440160(u8 *);
extern void func_L11_004401C0(u8 *);
extern void func_L11_00440238(u8 *);
extern void func_L11_00440360(u8 *);
extern s32 func_L11_00440790(u8 *, s32, s32);
extern s32 func_L11_00440868(u8 *, s32, s32);
extern void func_L11_00440E18(u8 *);
extern void func_L11_00441090(u8 *);
extern void func_L11_00441108(u8 *);
extern void func_L11_004411C8(u8 *);
extern void func_L11_00441350(u8 *);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L11_00441A58(u8 *, s32);
extern void func_L11_00441D08(u8 *, s32);
extern void func_L11_00442170(u8 *);
extern void func_L11_004423F8(u8 *);
extern s32 func_L11_00442710(u8 *);
extern void func_L11_004427B8(char *, int);
extern void func_L11_00442C80(u8 *);
extern void func_L11_00442E38(u8 *);
extern void func_L11_00443380(u8 *);
extern void func_L11_004433D8(u8 *);
extern void func_L11_00443498(u8 *);
extern void func_L11_00444400(u8 *);
extern void func_L11_00445990(char *);
extern s32 func_L11_00445D28(u8 *, s32);
extern void func_L11_00445B30(u8 *);
extern void func_L11_00446020(u8 *);
extern void func_L11_004461E8(u8 *);
extern void func_L11_00446C78(u8 *);
extern void func_L11_00446EB8(u8 *);
extern void func_L11_00447018(u8 *, s32);
extern void func_L11_004471A8(u8 *, void *);
extern void func_L11_00447360(char *);

#define HERO ((Hero *)D_00189E20)
#define TABLE D_L11_001B14F8
#define OBJ ((JobaObj *)obj)

/* Runs the arena challenge from start to finish: waiting for the player, spawning each wave of fighters, the boss fights, and the win or fail screens. */
void func_L11_0043E1A0(u8 *obj) {
    JobaState *st;
    JobaRecord *firstRecord;
    JobaRecord *nextWaveRecord;
    JobaRecord *currentRecord;
    JobaRecord *bossSpawnRecord;
    JobaRecord *followRecord;
    JobaRecord *newWaveRecord;
    s32 spawnedAny;
    s32 spawnedAnyBoss;
    s32 killSum5;
    s32 killSum8;
    s32 killSum12;
    s32 savedWord1;
    s32 savedWord2;
    s32 bossA;
    s32 bossB;
    s32 bossC;
    s32 challengeA;
    s32 challengeB;
    u32 challengeU;
    JobaLight *lightRise;
    JobaLight *lightLower;
    JobaLight *lightReset;
    JobaLight *lightEnd;
    JobaMoby *lampReset;
    JobaMoby *lampEnd;
    JobaMoby *lampLower;
    u8 *slotEntity;
    u8 *slotEntityBoss;
    f32 raisedHeight;
    f32 loweredHeight;
    u8 *cameraEntry;
    u8 *lampBytes;
    s32 mobySlot;
    s32 clearIdx;
    s32 k2;
    s32 markIdx;
    s32 resetIdx;
    s32 sumIdx5;
    s32 sumIdx8;
    s32 spawnIdx;
    s32 orbIdx;
    s32 spawnIdxBoss;
    s32 hoverIdx;
    s32 resetIdx2;
    s32 clearIdx2;
    s32 followIdx;
    s32 sumIdx12;
    s32 resetIdx3;
    s32 selection;
    s32 code;
    JobaClass *classInfo;
    s32 waveIndex;
    JobaRecord *nextRecord;
    s32 soundHandleA;
    u8 *soundBufB;
    u8 *soundBufC;
    s32 soundHandleB;
    s32 soundHandleC;

    st = OBJ->st;
    CallBlastHelperNoArgs();
    D_L11_001A9010 = 1;
    switch (OBJ->state) {
    case 0:
        ResetArenaControllerState_L11(obj);
        RunHelperOnSpawnGroups(obj);
        D_L11_001A8FF0 = 0;
        D_L11_001A8FF4 = 0;
        gMobyTable_L11[st->door].flags |= 1;
        gMobyTable_L11[st->door].hidden = 0;
        if (D_001A7904 == 2) {
            D_001A7904 = 0;
            SetMobyState(obj, 2, -1);
            SetFlagToOne();
            st->fade = D_001A65D2[0];
            AddDrawCallbackToList1(DrawScreenFadeBar, obj);
            OBJ->timer = 0x1F;
        }
        break;
    case 1:
        if (IsPointInsideRecordVolume(&HERO->f[0x80 / 4], st->zone) != 0) {
            SetMobyState(obj, 4, -1);
        } else if (IsPointInCuboid(&HERO->f[0x80 / 4], st->trigger1) != 0) {
            TryClaimNotice(4, 0x2F3C, 1);
            TryAllocateAndEnterState2(obj);
        } else if (D_001395B8[GetChallengeFlagIndex(1)] != 0) {
            if (IsPointInCuboid(&HERO->f[0x80 / 4], st->trigger2) != 0) {
                TryClaimNotice(4, 0x2F3C, 1);
                TryAllocateAndEnterState2(obj);
            }
        }
        if (D_001A7904 == 2) {
            D_001A7904 = 0;
            SetMobyState(obj, 2, -1);
            SetFlagToOne();
            st->fade = D_001A65D2[0];
            AddDrawCallbackToList1(DrawScreenFadeBar, obj);
            OBJ->timer = 0x1F;
        }
        D_L11_001A9010 = 0;
        break;
    case 2:
        if (SetFirstPendingFlag(obj) != 0) {
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            OBJ->phase = 0;
            gMobyTable_L11[st->door].flags |= 1;
            gMobyTable_L11[st->door].hidden = 0;
            lightReset = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            lampReset = &gMobyTable_L11[st->lamp];
            lightReset->height = 419.766f;
            lampReset->y = 419.766f;
        } else if (OBJ->phase == 0) {
            if (OBJ->timer < 0x1F) {
                D_L11_001B2FE0 = IntToFloat(OBJ->timer) * 0.05f < 1.0f
                                     ? IntToFloat(OBJ->timer) * 0.05f
                                     : 1.0f;
            } else {
                f32 cameraPos[4] __attribute__((aligned(16)));

                st->fade = D_001A65D2[0];
                AddDrawCallbackToList1(DrawScreenFadeBar, obj);
                if (D_L11_001CAE40[0] != 1) {
                    LoadSceneChunk(1, st->music);
                }
                cameraEntry = D_L11_001B368C + (st->camera << 7);
                ResetHeroPositionAndDirection(cameraEntry + 0x30, cameraEntry + 0x70, 0x6F, 1);
                CaptureCheckpointState(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
                QueueKeyedRequest(st->music, st->volume);
                *(TI128 *)cameraPos = *(TI128 *)(D_L11_001B368C + ((st->camera << 7) + 0x30));
                cameraPos[2] += 2.0f;
                SetCamera5Pose((char *)cameraPos, (char *)(D_L11_001B368C + (st->camera << 7) + 0x70), 1, 0, 0);
                OBJ->phase = 2;
            }
        } else if (OBJ->phase == 2) {
            AddDrawCallbackToList3(DrawScreenFadeBar, obj);
            D_L11_001B2FE0 = 0.0f;
            if (st->fade <= 0) {
                OBJ->phase = 3;
                StartHeroLoaderState(0);
                StartHeroTargetState(GetArenaCenterPoint(obj), 0, 0.0f);
            }
        } else if (OBJ->phase == 3) {
            if (vec_distance_xy(&HERO->f[0x80 / 4], GetArenaCenterPoint(obj)) < 10.0f) {
                if (D_001395B8[0x4A] == 0) {
                    D_001395B8[0x4A] = 1;
                    OBJ->phase = 1;
                    SetObjectFlagBit((u8 *)&gMobyTable_L11[st->gate1], 1);
                    OBJ->timer = 0;
                } else if (D_001395B8[GetChallengeFlagIndex(0)] != 0) {
                    SetMobyState(obj, 4, -1);
                } else {
                    ResetHeroPositionAndDirection(GetArenaCenterPoint(obj), D_L11_001B1570, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    SetMobyState(obj, 8, -1);
                    SetCameraModeState(2);
                }
            }
        } else if (OBJ->phase == 1) {
            if (OBJ->timer >= 0x3D && D_L11_001A8F00 != 2) {
                if (D_001395B8[GetChallengeFlagIndex(0)] == 0) {
                    ResetHeroPositionAndDirection(GetArenaCenterPoint(obj), D_L11_001B1570, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    SetMobyState(obj, 8, -1);
                    SetCameraModeState(2);
                } else {
                    SetMobyState(obj, 4, -1);
                }
            }
        }
        break;
    case 5:
        if (OBJ->timer < 0xB4) {
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            HERO->f[0x24A4 / 4] = 300.0f;
            UpdateFightersInsideArena(obj);
            break;
        }
    case 4:
        if (SetFirstPendingFlag(obj) != 0) {
            if (OBJ->state == 5) {
                StartChallengeResultScene((char *)obj, st->cls);
            }
            gMobyTable_L11[st->door].flags |= 1;
            gMobyTable_L11[st->door].hidden = 0;
            RunHelperOnSpawnGroups(obj);
            RunAllArenaMemberHandlers(obj);
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            ResetHeroPositionAndDirection(GetArenaCenterPoint(obj), D_L11_001B1570, 0x6F, 1);
            CaptureCheckpointState(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
            StartArenaIntroScript(obj);
            st->mode = 5;
            UpdateJobaRibbonScale(obj);
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
        }
        UpdateArenaIntroScript(obj);
        break;
    case 11:
        if (OBJ->timer < 0x168) {
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            if (OBJ->timer >= 0xB5) {
                HERO->f[0x24A4 / 4] = 200.0f;
            }
            UpdateFightersInsideArena(obj);
        } else {
            SetMobyState(obj, 4, -1);
        }
        break;
    case 12:
    case 13:
        if (SetFirstPendingFlag(obj) != 0) {
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            OBJ->phase = 0;
        }
        if (OBJ->phase == 0) {
            if (OBJ->timer < 0xB4) {
                HERO->f[0x24A4 / 4] = 200.0f;
                UpdateFightersInsideArena(obj);
                break;
            }
            if (OBJ->state == 12) {
                SetObjectFlagBit((u8 *)&gMobyTable_L11[st->gate2], 1);
            } else if (OBJ->state == 13) {
                SetObjectFlagBit((u8 *)&gMobyTable_L11[st->gate3], 1);
            }
            OBJ->timer = 0;
            OBJ->phase = 1;
        } else if (HERO->i[0x24CC / 4] > 0 && D_L11_001A8F00 != 2 && OBJ->timer >= 0xF1) {
            StartChallengeResultScene((char *)obj, st->cls);
            OBJ->state = 5;
            gMobyTable_L11[st->door].flags |= 1;
            gMobyTable_L11[st->door].hidden = 0;
            RunHelperOnSpawnGroups(obj);
            RunAllArenaMemberHandlers(obj);
            SetGroupAActiveCount(obj, 0);
            SetGroupBActiveCount(obj, 0);
            ResetHeroPositionAndDirection(GetArenaCenterPoint(obj), D_L11_001B1570, 0x6F, 1);
            CaptureCheckpointState(&HERO->f[0x80 / 4], &HERO->f[0x90 / 4]);
            StartArenaIntroScript(obj);
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
        }
        break;
    case 6:
        MoveJobaMenuSelectionToNext((char *)obj);
        break;
    case 7:
        if (SetFirstPendingFlag(obj) != 0) {
            selection = D_001395B8[0x49];
            if (selection != 0 && (D_001395B8[GetChallengeFlagIndex(TABLE[selection]->id)] == 0 ||
                             (selection >= 11 && IsFlagByteSet() == 0) ||
                             (selection == 8 && D_00139586[0][D_L11_00279BA0].enabled == 0))) {
                selection = 0;
            }
            st->result = selection;
        }
        UpdateJobaClassSelectionMenu(obj);
        break;
    case 8:
        GetChallengeFlagIndex(1);
        if (SetFirstPendingFlag(obj) != 0) {
            st->wave = 0;
            for (clearIdx = 0; clearIdx < 8; clearIdx++) {
                st->counts[clearIdx] = 0;
            }
            st->frames = 0;
            st->lost = 0;
            RunHelperOnSpawnGroups(obj);
            CountArenaFighters(obj);
            AssignFightersToSpawnPoints(obj);
            firstRecord = &TABLE[st->cls]->records[st->wave];
            SetGroupAActiveCount(obj, firstRecord->h[7]);
            SetGroupBActiveCount(obj, firstRecord->h[6]);
            for (markIdx = 0; markIdx < 40; markIdx++) {
                st->marks[markIdx] = 0;
            }
            for (markIdx = 0; markIdx < 6; markIdx++) {
                st->limits[markIdx] = D_L11_001B14B0[markIdx];
            }
            HERO->i[0x24CC / 4] = D_001A7A00;
            UpdateMobyClassSpecials((char *)obj);
            gMobyTable_L11[st->door].flags |= 1;
            gMobyTable_L11[st->door].hidden = 0;
            if (st->cls == 7) {
                savedWord1 = HERO->i[0x18D4 / 4];
                HERO->i[0x18D4 / 4] = 0;
                D_L11_001B1588 = savedWord1;
            } else if (st->cls == 8) {
                savedWord2 = HERO->i[0x18D4 / 4];
                HERO->i[0x18D4 / 4] = 0;
                D_00139700[0] = 300;
                D_L11_001B1588 = savedWord2;
            }
        }
        currentRecord = &TABLE[st->cls]->records[st->wave];
        if (currentRecord->b[3] != 0) {
            SetMobyState(obj, 9, -1);
            return;
        }
        UpdateArenaLossHistory(obj);
        if (IsWaveComplete_L11(obj) != 0) {
            st->wave++;
            for (resetIdx = 0; resetIdx < 7; resetIdx++) {
                st->counts[resetIdx] = 0;
            }
            st->lost = 0;
            if (D_L11_001BA780.owner == st->owner) {
                D_L11_001BA780.owner = 0;
            }
            challengeA = st->cls;
            challengeU = (u16)st->cls;
            st->sound = 0;
            st->owner = 0;
            if (st->wave >= TABLE[challengeA]->count) {
                if (challengeU - 7U < 2) {
                    HERO->i[0x18D4 / 4] = D_L11_001B1588;
                }
                st->result = st->cls;
                if (st->result == 0 && D_001395B8[GetChallengeFlagIndex(0)] == 0) {
                    SetMobyState(obj, 12, -1);
                    return;
                }
                SetMobyState(obj, 5, -1);
                SetTrackedObjectState(1, -1);
                StartGlobalObject((char *)1, -1);
                return;
            }
            if (challengeA >= 13) {
                st->cls = 0;
            }
            AssignFightersToSpawnPoints(obj);
            nextWaveRecord = &TABLE[st->cls]->records[st->wave];
            SetGroupAActiveCount(obj, nextWaveRecord->h[7]);
            SetGroupBActiveCount(obj, nextWaveRecord->h[6]);
        }
        st->frames++;
        if (st->cls == 5) {
            if (st->frames >= 0x1519) {
                char message[0x70];

                killSum5 = 0;
                for (sumIdx5 = 0; sumIdx5 < 6; sumIdx5++) {
                    killSum5 += st->counts[sumIdx5];
                }
                Sprintf(message, D_L11_001B15A0, GetLocalizedString(0x3269), D_L11_001B14B8[st->wave] + killSum5 - st->lost,
                              GetLocalizedString(0x2F61));
                CallLoadedModuleHandlerWithArg_003387A0_1((int)message, -1);
                SetMobyState(obj, 11, -1);
                SetTrackedObjectState(1, -1);
                StartGlobalObject((char *)1, -1);
                return;
            }
        }
        if (st->cls == 9 && st->frames >= 0x2A31) {
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x3269), -1);
            SetMobyState(obj, 11, -1);
            SetTrackedObjectState(1, -1);
            StartGlobalObject((char *)1, -1);
            return;
        }
        if (st->cls == 8) {
            if (st->frames >= 0xE11) {
                char message[0x70];

                killSum8 = 0;
                for (sumIdx8 = 0; sumIdx8 < 6; sumIdx8++) {
                    killSum8 += st->counts[sumIdx8];
                }
                Sprintf(message, D_L11_001B15A0, GetLocalizedString(0x3269), D_L11_001B14D0[st->wave] + killSum8 - st->lost,
                              GetLocalizedString(0x2F61));
                CallLoadedModuleHandlerWithArg_003387A0_1((int)message, -1);
                SetMobyState(obj, 11, -1);
                SetTrackedObjectState(1, -1);
                StartGlobalObject((char *)1, -1);
                return;
            }
        }
        if ((st->cls == 3 || st->cls == 11) && HERO->i[0x24CC / 4] < D_001A7A00) {
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x326A), -1);
            SetMobyState(obj, 11, -1);
            SetTrackedObjectState(1, -1);
            StartGlobalObject((char *)1, -1);
            return;
        }
        currentRecord = &TABLE[st->cls]->records[st->wave];
        if (OBJ->timer >= 0x3D || currentRecord->b[0] != 0) {
            spawnedAny = 0;
            ClearSquadSlotsWhenDone(obj);
            ChooseNextSquadMember(obj);
            slotEntity = st->slots[st->slot];
            if (slotEntity != 0 && HasFreeChildSlotInState2(slotEntity) != 0) {
                for (spawnIdx = st->counts[3]; spawnIdx < currentRecord->h[3]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xDF7 /* moby class 3575 */, 0);
                }
                for (spawnIdx = st->counts[1]; spawnIdx < currentRecord->h[1]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xDCF /* Joba smasher robot */, 0);
                }
                for (spawnIdx = st->counts[2]; spawnIdx < currentRecord->h[2]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xDF4 /* moby class 3572 */, 0);
                }
                for (spawnIdx = st->counts[0]; spawnIdx < currentRecord->h[0]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xD98 /* Joba security robot */, 0);
                }
                for (spawnIdx = st->counts[4]; spawnIdx < currentRecord->h[4]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xDF9 /* Joba fighter */, 0);
                }
                for (spawnIdx = st->counts[5]; spawnIdx < currentRecord->h[5]; spawnIdx++) {
                    spawnedAny |= ActivateArenaFighterOfClass(obj, 0xD37 /* moby class 3383 */, 0);
                }
            }
            if (st->counts[6] == 0 && currentRecord->b[0] != 0) {
                bossA = ActivateArenaBossOfClass(obj, 0xD4A /* moby class 3402 */, 0);
                st->sound = bossA;
                st->owner = bossA;
                if (D_L11_001BA780.owner == 0) {
                    D_L11_001BA780.owner = bossA;
                    D_L11_001BA780.timer = 0;
                }
                soundHandleA = st->sound;
                if (D_L11_001B3770[0] == 0) {
                    D_L11_001B3770[0] = soundHandleA;
                    ClearMemory(D_L11_001FFA78, 0, 0xE0);
                }
                QueueArenaVoiceLine(obj, 10);
                QueueKeyedRequest(st->track, st->trackVolume);
            }
            if (currentRecord->b[0] == 0) {
                if (gMusicState[0x48] != st->music && gMusicState[0x3C] != st->music) {
                    QueueKeyedRequest(st->music, st->volume);
                }
            }
            if (spawnedAny != 0) {
                RefreshSquadSlots(obj);
            }
        }
        if (st->cls == 7) {
            HandleRequestSlotState(10);
            HERO->b[0x22B7] = 1;
        }
        if (st->cls == 8) {
            HandleRequestSlotState(30);
        }
        AddDrawCallbackToList1(DrawJobaChallengeHud, obj);
        UpdateArenaCameraGuide(obj);
        PickJobaBossActionByTarget(obj);
        if ((D_001A7BC0 & 3) == 0) {
            MarkNearestFightersToAttack(obj);
        }
        UpdateFightersInsideArena(obj);
        if (GetChallengeDisplayId(st->cls) != -1) {
            D_L11_001AA170 = GetChallengeDisplayId(st->cls);
            D_L11_001B3680 = D_001A7390;
        }
        break;
    case 9:
        GetChallengeFlagIndex(1);
        if (SetFirstPendingFlag(obj) != 0) {
            if (st->counts[7] == 0) {
                if (TABLE[st->cls]->records[st->wave].b[1] != 0) {
                    bossB = ActivateArenaBossOfClass(obj, 0xB3A /* Arachnoid */, 0);
                    st->sound = bossB;
                    st->owner = bossB;
                    if (D_L11_001BA780.owner == 0) {
                        D_L11_001BA780.owner = bossB;
                        D_L11_001BA780.timer = 0;
                    }
                    soundHandleB = st->sound;
                    if (D_L11_001B3770[1] == 0) {
                        D_L11_001B3770[1] = soundHandleB;
                        soundBufB = D_L11_001FFA78;
                        ClearMemory(soundBufB + 0xE0, 0, 0xE0);
                    }
                    QueueArenaVoiceLine(obj, 4);
                    QueueKeyedRequest(st->track, st->trackVolume);
                }
            }
            st->mode = 1;
            OBJ->phase = 0;
            QueueArenaVoiceLine(obj, RandomIntBelow(2) + 0x1B);
            for (orbIdx = 0; orbIdx < 4; orbIdx++) {
                st->phase[orbIdx] = (f32)orbIdx * 0.25f;
                st->speed[orbIdx] = RandomFloatRange(D_L11_001B1590[0], D_L11_001B1590[1]) * 0.016666668f;
                st->delay[orbIdx] = RandomFloatRange(D_L11_001B1598[0], D_L11_001B1598[1]);
            }
        } else if (OBJ->phase == 0) {
            UpdateJobaRibbonScale(obj);
            UpdateArenaLossHistory(obj);
            lightRise = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            lampBytes = (u8 *)&gMobyTable_L11[st->lamp];
            if (lightRise->height < 421.266f) {
                raisedHeight = lightRise->height + 0.008333334f;
                lightRise->height = raisedHeight;
                *(f32 *)(lampBytes + 0x18) = raisedHeight;
            }
            if (HERO->ptr[0x33C / 4] == (void *)lampBytes && HERO->i[0x340 / 4] != 0 &&
                (HERO->i[0x2294 / 4] == 7 || OBJ->timer >= 0x12D)) {
                HERO->i[0xF0 / 4] = 0;
                D_L11_001A7CD8 = 80.0f;
                HERO->i[0xF4 / 4] = 0;
                if (HERO->i[0x2294 / 4] != 7) {
                    if (HERO->i[0x2294 / 4] != 0x81) {
                        EnterHeroState_L11(7, 1);
                    }
                } else {
                    EnterHeroState_L11(0x81, 1);
                }
                if (vec_distance_xy(&HERO->f[0x80 / 4], lightRise->pos) < 0.01f) {
                    HERO->f[0x84 / 4] += 0.01f;
                }
            }
            spawnedAnyBoss = 0;
            ClearSquadSlotsWhenDone(obj);
            ChooseNextSquadMember(obj);
            slotEntityBoss = st->slots[st->slot];
            if (slotEntityBoss != 0 && HasFreeChildSlotInState2(slotEntityBoss) != 0) {
                for (spawnIdxBoss = st->counts[1]; spawnIdxBoss < 4; spawnIdxBoss++) {
                    spawnedAnyBoss |= ActivateArenaFighterOfClass(obj, 0xDCF /* Joba smasher robot */, 0);
                }
                for (spawnIdxBoss = st->counts[2]; spawnIdxBoss < 4; spawnIdxBoss++) {
                    spawnedAnyBoss |= ActivateArenaFighterOfClass(obj, 0xDF4 /* moby class 3572 */, 0);
                }
                for (spawnIdxBoss = st->counts[0]; spawnIdxBoss < 4; spawnIdxBoss++) {
                    spawnedAnyBoss |= ActivateArenaFighterOfClass(obj, 0xD98 /* Joba security robot */, 0);
                }
            }
            EmitRobotLaserParticles(obj);
            AddDrawCallbackToList1(SpawnChannelBeamEffects, obj);
            if (spawnedAnyBoss != 0) {
                RefreshSquadSlots(obj);
            }
            if (D_L11_001A8FF4 == 0) {
                if (HERO->f[0x88 / 4] > 480.0f && HERO->f[0x180 / 4] < 0.033333335f) {
                    D_L11_001A8FF4 = 1;
                    D_L11_001A8FF0 = 1;
                    UpdateMobyClassSpecials((char *)obj);
                    EmitObjectSparks(obj, 5);
                }
                if (D_L11_001A8FF4 == 0) {
                    if (HERO->f[0x88 / 4] < D_L11_001B1580 && D_L11_001B1584 < HERO->f[0x88 / 4]) {
                        HERO->h[0x1F0 / 2] = 1;
                    }
                    if (D_L11_001A8FF4 == 0) {
                        goto tail9;
                    }
                }
            }
            EmitObjectSparks(obj, 0);
            if (D_L11_001A8FF4 != 0 && st->mode == 3) {
                OBJ->timer = 0;
                OBJ->phase = 1;
                bossSpawnRecord = &TABLE[st->cls]->records[st->wave];
                for (resetIdx2 = 0; resetIdx2 < 6; resetIdx2++) {
                    st->counts[resetIdx2] = 0;
                }
                st->heading = FastMatrixHelperA(HERO->f[0x80 / 4] - ((f32 *)GetArenaCenterPoint(obj))[0],
                                           HERO->f[0x84 / 4] - ((f32 *)GetArenaCenterPoint(obj))[1]);
                st->heading = FastAddRotations(st->heading, -1.5707965f);
                for (hoverIdx = st->counts[3]; hoverIdx < bossSpawnRecord->h[3]; hoverIdx++) {
                    ActivateArenaFighterOfClass(obj, 0xDF7 /* moby class 3575 */, 1);
                }
                for (hoverIdx = st->counts[5]; hoverIdx < bossSpawnRecord->h[5]; hoverIdx++) {
                    ActivateArenaFighterOfClass(obj, 0xD37 /* moby class 3383 */, 1);
                }
                for (hoverIdx = st->counts[1]; hoverIdx < bossSpawnRecord->h[1]; hoverIdx++) {
                    ActivateArenaFighterOfClass(obj, 0xDCF /* Joba smasher robot */, 1);
                }
                for (hoverIdx = st->counts[2]; hoverIdx < bossSpawnRecord->h[2]; hoverIdx++) {
                    ActivateArenaFighterOfClass(obj, 0xDF4 /* moby class 3572 */, 1);
                }
                for (hoverIdx = st->counts[0]; hoverIdx < bossSpawnRecord->h[0]; hoverIdx++) {
                    ActivateArenaFighterOfClass(obj, 0xD98 /* Joba security robot */, 1);
                }
            }
        } else if (OBJ->phase == 1) {
            UpdateArenaLossHistory(obj);
            UpdateJobaRibbonScale(obj);
            if (TABLE[st->cls]->records[st->wave].b[4] != 0) {
                SpawnTimedEffectNearAnchor(obj, &TABLE[st->cls]->records[st->wave]);
            }
            EmitObjectSparks(obj, 0);
            if (IsWaveComplete_L11(obj) != 0) {
                for (clearIdx2 = 0; clearIdx2 < 8; clearIdx2++) {
                    st->counts[clearIdx2] = 0;
                }
                st->lost = 0;
                classInfo = TABLE[st->cls];
                waveIndex = st->wave;
                nextRecord = &classInfo->records[waveIndex + 1];
                if (waveIndex + 1 < classInfo->count && nextRecord->b[3] != 0) {
                    st->heading = FastMatrixHelperA(HERO->f[0x80 / 4] - ((f32 *)GetArenaCenterPoint(obj))[0],
                                               HERO->f[0x84 / 4] - ((f32 *)GetArenaCenterPoint(obj))[1]);
                    st->heading = FastAddRotations(st->heading, -1.5707965f);
                    st->wave++;
                    followRecord = &TABLE[st->cls]->records[st->wave];
                    for (followIdx = st->counts[3]; followIdx < followRecord->h[3]; followIdx++) {
                        ActivateArenaFighterOfClass(obj, 0xDF7 /* moby class 3575 */, 1);
                    }
                    for (followIdx = st->counts[5]; followIdx < followRecord->h[5]; followIdx++) {
                        ActivateArenaFighterOfClass(obj, 0xD37 /* moby class 3383 */, 1);
                    }
                    for (followIdx = st->counts[1]; followIdx < followRecord->h[1]; followIdx++) {
                        ActivateArenaFighterOfClass(obj, 0xDCF /* Joba smasher robot */, 1);
                    }
                    for (followIdx = st->counts[2]; followIdx < followRecord->h[2]; followIdx++) {
                        ActivateArenaFighterOfClass(obj, 0xDF4 /* moby class 3572 */, 1);
                    }
                    for (followIdx = st->counts[0]; followIdx < followRecord->h[0]; followIdx++) {
                        ActivateArenaFighterOfClass(obj, 0xD98 /* Joba security robot */, 1);
                    }
                    if (st->counts[7] == 0 && followRecord->b[1] != 0) {
                        bossC = ActivateArenaBossOfClass(obj, 0xB3A /* Arachnoid */, 0);
                        st->sound = bossC;
                        st->owner = bossC;
                        if (D_L11_001BA780.owner == 0) {
                            D_L11_001BA780.owner = bossC;
                            D_L11_001BA780.timer = 0;
                        }
                        soundHandleC = st->sound;
                        if (D_L11_001B3770[1] == 0) {
                            D_L11_001B3770[1] = soundHandleC;
                            soundBufC = D_L11_001FFA78;
                            ClearMemory(soundBufC + 0xE0, 0, 0xE0);
                        }
                        QueueArenaVoiceLine(obj, 4);
                    }
                } else {
                    EnterHeroState_L11(0x6F, 1);
                    OBJ->phase = 2;
                    st->mode = 4;
                    OBJ->timer = 0;
                    SetTrackedObjectState(1, -1);
                    StartGlobalObject((char *)1, -1);
                }
            }
            st->frames++;
            if (st->cls == 12) {
                if (st->frames >= 0x1771) {
                    char message[0x70];

                    killSum12 = 0;
                    for (sumIdx12 = 0; sumIdx12 < 6; sumIdx12++) {
                        killSum12 += st->counts[sumIdx12];
                    }
                    Sprintf(message, D_L11_001B15A0, GetLocalizedString(0x3269), D_L11_001B14D8[st->wave] + killSum12 - st->lost,
                                  GetLocalizedString(0x2F61));
                    CallLoadedModuleHandlerWithArg_003387A0_1((int)message, -1);
                    lightEnd = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
                    lampEnd = &gMobyTable_L11[st->lamp];
                    lightEnd->height = 419.766f;
                    lampEnd->y = 419.766f;
                    SetMobyState(obj, 11, -1);
                    SetTrackedObjectState(1, -1);
                    StartGlobalObject((char *)1, -1);
                    return;
                }
            }
        } else if (OBJ->phase == 2) {
            UpdateJobaRibbonScale(obj);
            if (OBJ->timer >= 0xB5) {
                HERO->h[0x348 / 2] = 0;
                D_L11_001A7CD8 = 5.0f;
                EnterHeroState_L11(0x81, 1);
                OBJ->phase = 3;
            }
        } else if (OBJ->phase == 3) {
            D_L11_001A8FF4 = 0;
            D_L11_001A8FF0 = 0;
            if (HERO->f[0x88 / 4] < D_L11_001B1580 && D_L11_001B1584 < HERO->f[0x88 / 4]) {
                HERO->h[0x1F0 / 2] = 1;
            }
            UpdateJobaRibbonScale(obj);
            lightLower = &D_L11_001B3C1C[*D_L11_001A9014[st->light] & 0x7FFF];
            lampLower = &gMobyTable_L11[st->lamp];
            if (lightLower->height > 419.766f) {
                loweredHeight = lightLower->height - 0.008333334f;
                lightLower->height = loweredHeight;
                lampLower->y = loweredHeight;
            }
            if (st->mode == 0) {
                st->wave++;
                for (resetIdx3 = 0; resetIdx3 < 7; resetIdx3++) {
                    st->counts[resetIdx3] = 0;
                }
                st->lost = 0;
                if (D_L11_001BA780.owner == st->owner) {
                    D_L11_001BA780.owner = 0;
                }
                challengeB = st->cls;
                st->sound = 0;
                st->owner = 0;
                if (st->wave >= TABLE[challengeB]->count) {
                    if (challengeB == 1 && D_001395B8[GetChallengeFlagIndex(1)] == 0) {
                        SetMobyState(obj, 13, -1);
                        OBJ->timer = 0xB4;
                    } else {
                        SetMobyState(obj, 5, -1);
                        OBJ->timer = 0xB4;
                    }
                    SetTrackedObjectState(1, -1);
                    StartGlobalObject((char *)1, -1);
                    st->result = st->cls;
                    return;
                }
                if (challengeB >= 13) {
                    st->cls = 0;
                }
                AssignFightersToSpawnPoints(obj);
                newWaveRecord = &TABLE[st->cls]->records[st->wave];
                SetGroupAActiveCount(obj, newWaveRecord->h[7]);
                SetGroupBActiveCount(obj, newWaveRecord->h[6]);
                OBJ->state = 8;
            }
        }
    tail9:
        mobySlot = (s32)obj >> 8;
        AddDrawCallbackToList1(DrawJobaChallengeHud, obj);
        UpdateArenaCameraGuide(obj);
        PickJobaBossActionByTarget(obj);
        if ((D_L11_001B30C8 & 7) == (mobySlot & 7)) {
            UpdateFightersInsideArena(obj);
        }
        if ((D_L11_001B30C8 & 0x3F) == (mobySlot & 0x3F)) {
            MarkNearestFightersToAttack(obj);
        }
        if (GetChallengeDisplayId(st->cls) != -1) {
            D_L11_001AA170 = GetChallengeDisplayId(st->cls);
            D_L11_001B3680 = D_001A7390;
        }
        break;
    }
    EndArenaControllerFrame(obj);
}

