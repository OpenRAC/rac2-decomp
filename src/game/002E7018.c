#include "common.h"

extern char D_00189E20_9[];

extern char D_001A63A8_3[];

extern short D_00152C2A;

extern void func_002B72E8_1();

extern void func_002E4AC8();

extern void func_00288EA0();

extern void func_002E6D88();


typedef struct {
 u8 prefix[0x30];s32 state;u8 gap0[0x1c];u8 *current;u8 gap1[0x138];s32 bank[2];
} NativeContext;

extern NativeContext D_L24_001BC3C0;

extern u8 D_L24_0028AAC0[];

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
/* Resets the scene state when a scene starts. */
void func_002E7018(void)
{
    char *gameData = D_00189E20_9;
    char *transitionData;
    unsigned short stateValue;

    if (*(int *)(gameData + 9420) <= 0) {
        *(int *)(gameData + 9420) = 1;
    }
    func_002B72E8_1(0);

    transitionData = D_001A63A8_3;
    stateValue = *(unsigned short *)(transitionData + 114);
    if ((unsigned short)(stateValue - 6) >= 2) {
        *(unsigned short *)(transitionData + 114) = 5;
    }
    UpdateSoundVoices();
    ClearSubtitleState();
    StartTransitionScene(0);
    D_00152C2A = 0;
}

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef struct { char pad[0x20]; short active; short slot; } Menu2E7090;
typedef struct { char pad[0xC]; int start; int end; } Range2E7090;
typedef struct { char pad[0x30]; int selected; int base; int page; int row; char pad40[0x6C - 0x40]; int start; int destination; } List2E7090;

extern float D_001B15A0 MACRO_ADDR;
extern int D_001B15A4 MACRO_ADDR;
extern Menu2E7090 D_00152C00;
extern int D_001B22B0 MACRO_ADDR;
extern Range2E7090 D_001BAEC0;
extern List2E7090 D_001B8840;
extern int D_001A79F0 MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001B1680 MACRO_ADDR;
extern void func_002FC138(void);
extern void func_00294070(int);
extern int func_0029B3E0(int, int);

/* Opens the list: rebases its range on the loaded block and, for the current program, lays
   out the first page (80 or 96 rows a page). */
/* Starts the scene list: sets up its memory block and loads the first page of data. */
void func_002E7090(int level)
{
    Menu2E7090 *menu = &gHeroMoby_00152C00;
    short none = -1;
    int base;

    gScreenFade = 1.0f;
    D_001B15A4 = 0;
    menu->active = 0;
    menu->slot = none;
    SelectPacketBufferSetup();
    base = D_001B22B0 - 0x60000;
    gScenePlaybackState.start = D_001BAEC0.start + base;
    gScenePlaybackState.destination = D_001BAEC0.end + base;
    D_001B22B0 = base;
    if (gCurrentMapIndex == level) {
        StartTransitionScene(3);
        level = gIsPalVideo ? 0x50 : 0x60;
        gScenePlaybackState.base = 0;
        gScenePlaybackState.row = gScenePlaybackState.base / level;
        SelectSegmentAndUpdateWorld(gScenePlaybackState.row);
        gScenePlaybackState.page = gScenePlaybackState.base % level;
    } else {
        MemcardSave(0, level);
        D_001B1680 = level;
        menu->active = 1;
        menu->slot = none;
    }
}


/* func_002E7248 is matched in its own unit, 002E7248-qcopy.c. */


/* func_002E7570 is in 002E7018-qcopy.c (grouped lq/sq copies). */

/* func_002E76C0 is in 002E76C0-g8.c. */

extern unsigned int D_001A7AF0 __attribute__((sda));
extern void func_002E76C0(void *, int, int);

/* Draws the ship engine flames, three of them or just one depending on a game setting. */
void func_002E7B48(void *object)
{
    int count = ((gEquipmentBits >> 4) & 1) ? 3 : 1;
    int index;
    for (index = 0; index < count; index++)
        SpawnShipEngineFlame(object, index, 0);
}


/* func_002E7BC8 is in 002E7BC8-g8.c. */


/* func_002E8190 is matched in 002E7018-g8.c (-G8 small data). */

extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027E018(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern char *D_001A7344 __attribute__((sda));
extern unsigned long long D_001B2168 __attribute__((sda));

/* Draws a fading overlay strip across the screen with the given see-through amount. */
void func_002E82C8(int alpha)
{
    unsigned long long color;
    unsigned long long packet;
    char *dst;

    VU1_addGSregister(0x47, 0x31801ULL);
    VU1_addGSregister(0x42, 0x8000000044ULL);
    color = (alpha << 24) | 0x00808080;
    packet = D_001B2168;
    dst = gScreenHeight;
    DrawTexturedQuad(0x20, dst - 0x58, 0x100, 0x20, 0, 0, 0x100, 0x20, color, packet);
    VU1_addGSregister(0x47, 0x5360BULL);
}


/* func_002E8368 is matched in 002E7018-transition-g8.c. */

/* func_002E8BA8 is matched in 002E8BA8-g8.c. */



/* func_002E9268 is in 002E9268.c. */

extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void func_0027C480(void);
extern void func_0027BD70(void);
extern void func_002E8BA8(void);

/* Draws the background of the transition screen for the current transition type. */
void func_002EA8E8(void)
{
    switch (D_00152C20) {
    case 0:
    case 3:
        RenderFrameAllLayers();
        break;
    case 1:
        D_001B1594 = 127;
        RenderFrame();
        break;
    case 2:
        RenderTransitionScene();
        break;
    }
}


extern void func_001325E8(void *, void (*)(int, long), long long);
extern void func_0011AEA0(int);
extern int func_001261F0(int);
extern int func_00132028(void);
extern void func_002E6088(int, long);

/* Starts a background load and waits until it reports back. */
void func_002EAAA8(void *arg, int *status) {
    *status = -1;
    func_001325E8(arg, StoreSoundResult, (unsigned long long)(unsigned int)status);
    {
        int sentinel = -1;
        do {
            FlushCache(0);
            GetGsCurrentField(0);
            snd_Pump();
        } while (*status == sentinel);
    }
}

/* func_002EAB18 is in 002E7018-load.c (its views of D_00152C00 and D_001BAEC0 differ from this file's). */


/* D_001B8840 is declared above func_002E7090 (List2E7090). */
extern char D_0014B540[];
extern int func_002B7B18(int, int, int);
extern void func_002B7CE0(int);

/* Loads the data for one chunk of the current scene. */
int func_002EB158(int index)
{
    char *table = gCopySetupData;
    int row = gScenePlaybackState.selected * 0x14C;
    int destination = gScenePlaybackState.destination;
    int base = (int)(table + 0x3EA8);
    int first = *(int *)((index << 2) + row + base);
    int count = *(int *)(((index + 1) << 2) + row + base) - first;
    if (count > 0) {
        StartDiscRead(destination, first + *(int *)(table + 0x3E24), count);
        PumpMusicAndDiscRead(0);
    }
    return 1;
}

/* func_002EB1E0 is matched in its own unit, 002EB1E0.c (-frac2-gcse-unsplit-edges). */


/* func_002EB7E8 is in 002EB7E8-g8.c (-G8 small data). */

/* func_002EBAA8 is in 002EBAA8-g8.c (-G8 small data). */


/* func_002EBC70 is in 002EBC70-g8.c (-G8 small data). */

/* func_002EBDF0 is matched in 002EBDF0-g8.c. */

/* func_002EC1C0 is matched in 002E7018-g8.c (-G8 small data). */

/* func_002EC408 is in 002EC408-g8.c (-G8 small data). */

/* func_002ECB70 is matched in 002ECB70-g8.c (-G8 small data, -fno-gcse). */


/* selects the level data bank when the resident context is in state 9 */
void func_002ED058(void) {
 s32 index=-1;
 if(D_L24_001BC3C0.state==9) index=1;
 if(index!=-1) {
  D_L24_001BC3C0.current=D_L24_0028AAC0;
  *(s32 *)(D_L24_0028AAC0+0x68)=D_L24_001BC3C0.bank[index];
 }
}

