#include "common.h"

/* Measured partial layouts for the transition's objects and shared contexts. */
typedef struct {
    char pad0[0x20];
    unsigned char status;
    char pad21[0x13];
    unsigned short flags;
    char pad36[0x74];
    short type;
    char padAC[0x54];
} TransitionMoby;

typedef struct {
    TransitionMoby *object;
    char pad4[4];
    int field8;
    char padC[20];
    short mode;
    short slot;
    char pad24[6];
    short active;
    char pad2C[64];
    int field6C;
} TransitionContext;

typedef struct {
    char pad[12];
    int start;
    int end;
} TransitionArchive;

typedef struct {
    char pad[0x6C];
    int start;
    int end;
} TransitionScene;

typedef struct {
    char pad[0x24];
    int state;
    int next;
    char gap[0x40];
    short limit;
    char gap2[4];
    short phase;
} TransitionState;

typedef struct {
    char pad[0x22B5];
    char flag;
    char gap[0x246];
    short mode;
} TransitionGlobals;

extern TransitionContext D_00152C00;
extern TransitionScene D_001B8840;
extern TransitionArchive D_001BAEC0;
extern TransitionState D_001A63A8;
extern TransitionGlobals D_00189E20;
extern char D_001B1390[] MACRO_ADDR;
extern char D_001B2980[];
extern char D_001B13D0[] MACRO_ADDR;
extern int D_001B22B0;
extern float D_001B15A0;
extern int D_001B15A4 __attribute__((sda));
extern TransitionMoby *D_001B1B60;

extern void func_00282A60(void *, int, int);
extern void func_002FC138(void);
extern unsigned int func_0026F748(int, int);
extern void func_0026F720(void);
extern void func_00293F98(int, int);
extern void func_00294070(int);
extern int func_002E4AC8(void);
/* The callee ignores a0; retain the caller's explicit zero argument. */
extern int func_001261F0(int);
extern int func_002B6D28(void);

/* Sets up the scene for a screen transition: clears work areas, hides some objects, chooses the music and starting state, then waits until the scene is ready. */
void func_002E6D88(int mode)
{
    TransitionMoby *p;
    TransitionMoby *object;
    int offset;
    int state;
    int music;
    int channel;

    gHeroMoby_00152C00.field6C = 0;
    gHeroMoby_00152C00.mode = mode;
    gHeroMoby_00152C00.field8 = 0;
    gHeroMoby_00152C00.slot = -1;
    ClearMemory(&gScenePlaybackState, 0, 0x1D0);
    ClearMemory(&D_001B1390, 0, 0x40);
    ClearMemory(D_001B2980, 0, 0x40);
    ClearMemory(D_001B2980 + 0x40, 0, 0x40);
    ClearMemory(&D_001B13D0, 0, 0x40);
    SelectPacketBufferSetup();

    offset = D_001B22B0 - 0x60000;
    gScenePlaybackState.start = D_001BAEC0.start + offset;
    gScenePlaybackState.end = D_001BAEC0.end + offset;
    gScreenFade = 1.0f;
    D_001B22B0 = offset;
    D_001B15A4 = 0;
    EmptyStubF748(0x61, 2);
    gHeroState.flag = 1;
    EmptyStubF720();

    object = gHeroMoby_00152C00.object;
    p = D_001B1B60;
    object->flags |= 1;
    for (; p->status != 255; p++) {
        if (!(p->status & 0x80) && (p->type == 0x4A /* moby class 74 */ || p->type == 0xCB /* Decoy */))
            p->flags |= 0x80;
    }

    if (mode == 0) {
        state = gHeroState.mode ? 5 : 2;
        music = gHeroState.mode ? 3 : 1;
        LoadPartsSetFromDisc(music, 6);
    } else {
        state = gHeroState.mode ? 3 : 0;
        music = gHeroState.mode ? 2 : 0;
        if (!gHeroMoby_00152C00.active)
            state++;
        channel = gHeroMoby_00152C00.active ? 0 : 2;
        LoadPartsSetFromDisc(music, channel);
    }

    gMusicState.state = state + 5000;
    gMusicState.next = 0;
    SelectSegmentAndUpdateWorld(0);
    while (gMusicState.phase != 3 || gMusicState.limit >= 6000) {
        UpdateSoundVoices();
        GetGsCurrentField(0);
    }
    ResumeMusicStream();
}
