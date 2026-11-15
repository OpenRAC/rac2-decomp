#include "common.h"

extern char D_001BAD40[];
extern int D_001A7478 __attribute__((sda));
extern short D_00152C28[];
extern int D_0013955C[];
extern void func_00288AA0(char *, int);
extern void func_00288BE8(char *);
extern void func_002F5CB8(void (*)(void), int);
extern void func_002F6458(void);

/* Loads a data file into the shared buffer and sets up a callback and two flags for the next screen. */
void func_002F64A8(void)
{
    char *buffer = D_001BAD40;
    D_001A7478 = 1;
    PushRequestQueue(buffer, 21);
    LaunchQueuedRequest(buffer);
    SetStoredValuePair(FlagCurrentMenuEntry, 0);
    D_00152C28[0] = 1;
    D_0013955C[0] = 0;
}

/* Cutscene state: cleared whole when a cutscene starts. */
typedef struct { char pad[0xC]; unsigned char n; char padD[0x3B]; int slots[1]; } CutsceneParts;
typedef struct { char pad[0x24]; CutsceneParts *parts; } CutsceneMoby;
typedef struct {
    char pad0[0x10];
    float pos[4];             /* 0x10 */
    float rot[4];             /* 0x20 */
    int id;                   /* 0x30 */
    int unk34;                /* 0x34 */
    int index;                /* 0x38 */
    int unk3C;                /* 0x3C */
    char pad40[4];
    short count;              /* 0x44 */
    short restore;            /* 0x46 */
    short wait;               /* 0x48 */
    char pad4A[0x22];
    int base6C;               /* 0x6C */
    int base70;               /* 0x70 */
    char pad74[0x118];
    CutsceneMoby *mobys[1];   /* 0x18C */
} CutsceneState;
typedef struct { char pad[0xB0]; float fov; } CutsceneCamVars;
typedef struct {
    char pad0[4];
    short active;             /* 0x04 */
    char pad6[0x1E];
    int id;                   /* 0x24 */
    int flag;                 /* 0x28 */
    char pad2C[0x40];
    short timer;              /* 0x6C */
    char pad6E[4];
    short state;              /* 0x72 */
} CutsceneHelp;
typedef struct {
    char pad0[0x80];
    float pos[4];             /* 0x80 */
    char pad90[0x2200];
    int active;               /* 0x2290 */
    char pad2294[0x21];
    char flag;                /* 0x22B5 */
} CutsceneHero;
typedef struct { char pad[0xFC]; char *moby; } CutsceneMenu;
/* Retail never puts the moby or data load in a delay slot: both are read at an
   offset from an earlier small-data name, taken here as the word before them. */
typedef struct { int unk0; char *moby; void *data; } CutsceneTalk;
typedef struct { char pad[0xC]; int baseC, base10; } CutsceneResources;

extern CutsceneState D_001B8840;
extern CutsceneCamVars D_001B9040;
extern CutsceneHelp D_001A63A8;
extern CutsceneHero D_00189E20;
extern CutsceneMenu D_001F2840;
extern CutsceneTalk D_001B178C MACRO_ADDR;
extern CutsceneResources D_001BAEC0;
extern float D_001A8C74, D_001A8C78, D_001A8C7C, D_001B15A0;
extern int D_001A79F0, D_001A8BB0, D_001B15A4, D_001B15A8, D_001B15AC;
extern int D_001B22B0[] __attribute__((sda));
extern char *D_001B1B60;
extern int D_00139768[];
extern char D_001B1450[] MACRO_ADDR, D_001B1390[] MACRO_ADDR, D_001B13D0[] MACRO_ADDR, D_001B1410[] MACRO_ADDR;
extern char D_001B2980[], D_0021F080[];
extern void (*D_001A8C80)(int);
extern int D_001A8C84, D_001A8BB8;
extern int D_001BAD78[];
extern void func_00288B38(void *);
extern int func_002EF010(int);
extern void func_002B72E8(int);
extern void func_002B7CE0(int);
extern void func_00282A60(void *, int, int);
extern void func_00288EA0(void);
extern unsigned int func_0026F748(int, int);
extern void func_0026F720(void);
extern int func_00293CA8(int);
extern void func_00293D30(void);
extern void func_002912F0(void);
extern void func_002E4AC8(void);
extern int func_001261F0(int);
extern int func_002B6D28(void);
extern void func_002FC138(void);
extern void func_0027D330(int);
extern void func_00272198(float);
extern void func_002F5220(void);
extern void func_0027AB40(void);
extern void func_0029F338(void *);
extern void func_0026F750(int);
extern float func_002A89A8(void *, int, float);
extern float func_00282C48(float);
extern void func_0026F728(void);
extern void func_0026F778(void *, void *, int, int);
extern void func_002B8108(void *, void *, int);
extern void func_002B7340(int);
extern void func_002E6120(void);

/* Starts cutscene n: marks it seen, clears the cutscene state and buffers, sets
   up the resource bases and hero, then waits for the dialog stream and three
   frames. */
/* Starts a cutscene by its number. */
void func_002F53C8(int cutsceneId)
{
    int index, i, memTop;
    char *bufferPtr, *moby;

    if ((unsigned)cutsceneId < 0xB1)
        *(D_00139768 + ((unsigned)cutsceneId >> 2)) |= 1 << (cutsceneId & 31);
    MarkQueuedRequestsInFlagTable(D_001BAD40);
    index = MapCutsceneIdToIndex(cutsceneId);
    if (index < 0)
        return;
    music_Pause(0);
    PumpMusicAndDiscRead(0);
    ClearMemory(&gScenePlaybackState, 0, 0x1D0);
    ClearMemory(D_001B1450, 0, 0x40);
    ClearMemory(D_001B1390, 0, 0x40);
    ClearMemory(D_001B2980, 0, 0x40);
    ClearMemory(D_001B2980 + 0x40, 0, 0x40);
    ClearMemory(D_001B13D0, 0, 0x40);
    ClearMemory(D_001B1410, 0, 0x40);
    bufferPtr = D_0021F080;
    for (i = 0; i < 7; i++) {
        char *entry = bufferPtr;
        bufferPtr += 0x40;
        ClearMemory(entry, 0, 0x40);
    }
    D_001A8C74 = 1.0f;
    gScenePlaybackState.id = index;
    D_001A8C78 = 0;
    gScenePlaybackState.unk34 = 0;
    gScenePlaybackState.unk3C = 0;
    if (gCurrentMapIndex == 20)
        memTop = D_001B22B0[0] - 0x60000;
    else
        memTop = D_001B22B0[0] - 0x40000;
    D_001B22B0[0] = memTop;
    gScenePlaybackState.base6C = D_001BAEC0.baseC + memTop;
    gScenePlaybackState.base70 = D_001BAEC0.base10 + memTop;
    ClearSubtitleState();
    gScreenFade = 1.0f;
    gCurrentGameMode = 2;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    if (gHeroState.active) {
        EmptyStubF748(0x61, 2);
        gHeroState.flag = 1;
        EmptyStubF720();
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) |= 1;
    if (gPauseMenuState.moby)
        *(unsigned short *)(gPauseMenuState.moby + 0x34) |= 1;
    D_001B15A8 = 1;
    D_001B15AC = 52;
    if (gMusicState.active) {
        PumpMusicAndDiscRead(1);
        LoadChunkPartFromDisc(0);
    } else
        LoadChunkPartFromDisc(0);
    if (gMusicState.active)
        PumpMusicAndDiscRead(1);
    RelocateWorldObjectParts();
    EmptyStub_002912F0();
    for (moby = D_001B1B60; (unsigned char)moby[0x20] != 255; moby += 0x100) {
        if (!((unsigned char)moby[0x20] & 0x80) && *(short *)(moby + 0xAA) == 0xCB /* Decoy */)
            *(unsigned short *)(moby + 0x34) |= 0x80;
    }
    gMusicState.id = gScenePlaybackState.id;
    gMusicState.flag = 0;
    while (gMusicState.state != 3 || gMusicState.timer >= 6000) {
        UpdateSoundVoices();
        GetGsCurrentField(0);
    }
    {
        int ticks = 0;
        CutsceneState *state = &gScenePlaybackState;

        state->wait = -3;
        ResumeMusicStream();
        LoadChunkPartFromDisc(1);
        for (; state->wait < ticks; ticks--)
            GetGsCurrentField(0);
    }
}

/* Ends the cutscene: restores the frame rate, camera field of view and the
   cutscene mobys, drops the hero and camera back to the ground, clears the
   talk and menu mobys and runs the pending end callback. */
void func_002F57A8(void)
{
    char *moby;
    CutsceneHero *hero;
    CutsceneState *cutscene;
    float heroGroundZ, cutsceneGroundZ;
    int i;

    if ((unsigned short)(gMusicState.state - 6) >= 2)
        gMusicState.state = 5;
    SelectPacketBufferSetup();
    FadeToBlack(6);
    D_001B15A8 = 0;
    D_001B15AC = 0;
    D_001B15A4 = 0;
    D_001A8C7C = 0;
    SetCameraTransitionFrames(6.0f);
    ResetFrameCounters();
    D_001B9040.fov = 0.62f;
    UpdateViewContext();
    for (i = 0; i < gScenePlaybackState.count; i++) {
        CutsceneMoby *m = gScenePlaybackState.mobys[i];
        if (m) {
            m->parts->n--;
            m->parts->slots[m->parts->n] = 0;
            MarkMobySpawned(m);
        }
    }
    for (moby = D_001B1B60; (unsigned char)moby[0x20] != 255; moby += 0x100) {
        if (!((unsigned char)moby[0x20] & 0x80) && *(short *)(moby + 0xAA) == 0xCB /* Decoy */)
            *(unsigned short *)(moby + 0x34) &= 0xFF7F;
    }
    hero = &gHeroState;
    if (hero->active) {
        EmptyStubF750(1);
        heroGroundZ = ProbeGroundHeightBelow(hero->pos, 0, 0.5f);
        if (2.0f < heroGroundZ) {
            if (FloatAbs(hero->pos[2] - heroGroundZ) < 4.5f)
                hero->pos[2] = heroGroundZ;
        }
        gHeroState.flag = 0;
        EmptyStubF728();
        cutscene = &gScenePlaybackState;
        if (cutscene->restore) {
            cutsceneGroundZ = ProbeGroundHeightBelow(cutscene->pos, 0, 0.5f);
            if (2.0f < cutsceneGroundZ && FloatAbs(cutscene->pos[2] - cutsceneGroundZ) < 2.0f)
                cutscene->pos[2] = cutsceneGroundZ;
            EmptyStubF778(gScenePlaybackState.pos, gScenePlaybackState.rot, 0, 1);
        }
    }
    if (D_001B178C.moby)
        *(unsigned short *)(D_001B178C.moby + 0x34) &= 0xFFFE;
    if (gPauseMenuState.moby) {
        *(unsigned short *)(gPauseMenuState.moby + 0x34) &= 0xFFFE;
        gPauseMenuState.moby = 0;
    }
    if (D_001B178C.moby) {
        char *moby = D_001B178C.moby;
        void *data = D_001B178C.data;
        D_001B178C.moby = 0;
        D_001B178C.data = 0;
        RunDialogueNode(moby, data, 1);
    }
    music_set_active_track_value(30);
    if (D_001A8C80 && !D_001BAD78[0] && gRequestedGameMode != 2 && gRequestedGameMode != 1) {
        D_001A8C80(D_001A8C84);
        D_001A8C80 = 0;
        D_001A8C84 = 0;
    }
    DestroyEquipmentPieces();
}
