/* func_L00_002A3B88 (RunLevelLoop): clears level state, restores its settings and services frames
 * until loading ends. A -G8 unit of its own. In the loop header the plain `sd` of D_001A7200 and
 * then the volatile T1_COUNT (0x10000800) clear come just before the first jal; the compiler's
 * default set-side volatile rule (GCC 2.95's) leaves that slot empty, as retail does, where the
 * EE tree's rule fills it with the clear of the frame accumulator (docs/build/compiler-notes.md).
 * T1_COUNT (include/common.h) is the EE timer 1 count register, 0x10000800. */
#include "common.h"

/* Partial views of the resident settings, weapon table and per-level statistics. */
typedef struct {
    char reserved00[0x18];
    int mode;
    char reserved1c[10];
    short pending, reset, ready, announce, reserved2e;
    int output;
} SoundSettings;
typedef struct {
    int active;
    unsigned char channel;
    char reserved05[15];
    int sound;
    char reserved18[200];
} WeaponResource __attribute__((aligned(16)));
typedef struct {
    unsigned short visits, reserved;
    unsigned int maximum, visited;
} LevelStatistics;

extern unsigned char D_L00_0025BBA0[];
extern const char D_L00_001A7C88[];
extern int D_L00_001A8F00[] __attribute__((sda));
extern int D_L00_001A8F04, D_L00_001A8F08;
extern int D_L00_001A8ED4, D_L00_001A8FE0;
extern int D_L00_001B19C4[] __attribute__((sda));
extern int D_L00_001B19D4[] __attribute__((sda));
extern int D_L00_001B18D8[] __attribute__((sda));
extern int D_L00_001B1680[] __attribute__((sda));
extern int D_L00_001B1680_1 NOT_SDA;
extern int D_L00_001B19C0;
extern float D_L00_001B19CC;
extern short D_L00_001BCB24 NOT_SDA;
extern int D_001A7290, D_001A72C0;
extern short D_001A7A18;
extern unsigned int D_001A7AF0;
extern unsigned char D_00139568[];
typedef struct {
    unsigned char reserved0000[0x1248];
    int weapon;
    unsigned char reserved124c[0x22c1 - 0x124c];
    unsigned char flush;
} LevelLoopHero;
extern LevelLoopHero D_00189E20;
extern WeaponResource D_L00_00262570[];
extern SoundSettings D_00152C00;
extern int D_001A7904, D_001A79F0, D_001A7398, D_001A7A04;
extern unsigned char D_001A7B1F;
extern unsigned char D_001A7BE8[] __attribute__((sda));
extern unsigned char D_0019B3D2 NOT_SDA;
extern unsigned char D_001395CA NOT_SDA, D_001395E5 NOT_SDA, D_00139629 NOT_SDA;
extern unsigned int D_001A7390;
extern LevelStatistics D_0018C360[];
extern unsigned char D_001A7248[] __attribute__((sda));
extern long D_001A7200 MACRO_ADDR;
typedef struct {
    unsigned char reserved00[0x10];
    int held;
    unsigned char reserved14[0x15c-0x14];
    int pressed;
    int reserved160;
    int alternate;
    int reserved168;
    int transition;
    unsigned char reserved170[0x17c-0x170];
    int counter;
} LevelLoopInput;
extern LevelLoopInput D_001393E0;
extern unsigned short D_0018C9DC NOT_SDA;
extern struct { char reserved00[0x84]; unsigned short resume; } D_0018C958;
extern int D_001A7420, D_001A7424, D_001A7B90;
extern int D_L00_001A7C80 __attribute__((sda));
extern int D_L00_001A7C84 __attribute__((sda));
extern unsigned char D_L00_0021DDB0[];
extern short D_001A63F0 NOT_SDA;
extern unsigned char D_0018D278[];

/* The callees' prototypes, as their definitions in src/ declare them. */
extern void func_00282A88(void *, int);
extern void func_0026FEB8(const char *, ...);
extern void func_002EED08(void), func_00290758(void);
extern void func_00292078(int), func_00292408(int), func_002926B8(int), func_002925F0(int);
extern int func_002AD860(int);
extern int func_L00_00303990(int, int);
extern void func_00294F10(void), func_0028AB70(void), func_0029CD48(void);
extern void func_002C9C20(void);
extern int func_002B49E0(int, int, int, int, unsigned char *);
extern void func_0027D330(int), func_002B6E78(int, int, int), func_002B72E8(int);
extern void func_00133220(void);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, void *);
extern void func_002B4C18(void), func_002B7320(void);
extern short func_002B7CE0(int);
extern void func_00294420(int);
extern void func_00280710(void), func_002FC280(void), func_002FC220(void);
extern void func_00284FC0(void), func_L00_002F0930(void), func_00284EA8(void);
extern int func_00132028(void);
extern void func_002B9000(void), func_L00_0036F488(void), func_L00_002E6348(void);
extern void func_L00_0037F7E8(void), func_L00_0037F790(void);
extern void func_L00_0036FA68(void), func_L00_002E6400(void);
extern void func_002F5FB8(void), func_L00_00370408(void), func_0027C480(void), func_0027D900(void);
extern void func_002CA8A8(void), func_L00_002E6448(void), func_00286738(void), func_0027C4A8(void);
extern void func_L00_00374C18(void), func_L00_0037A610(void), func_002EA8E8(void);
extern int func_002E9268(void);
extern int func_L00_002FC5C8(void), func_L00_002FC5E8(void);
extern void func_00282A28(void), func_L00_0032B288(void), func_L00_002D6FD8(void);
extern void func_00298F00(void), func_00298178(void), func_0027C540(int);
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_0028E588(int, int);
/* Retail returns the full 64-bit texture descriptor in v0. */
extern unsigned long long func_0028E640(int);
extern void func_0028E868(int, int, int, int, int, int);
extern void func_0028F410(int, int, long long, float, float, float, float, float);
extern void func_0027C660(void), func_002FC3C0(unsigned long);
extern float func_00283CE0(int);
extern int func_001261F0(int);
extern void func_L00_003584B0(void), func_0027B948(void), func_002FC1D8(void);
extern void func_00133230(void), func_002E5FE0(void), func_002B7170(void), func_00288EA0(void);
extern void func_L00_0032B500(int), func_00297670(void *), func_002EC408(void);

/* Clears level state, restores its settings and services frames until loading ends. */
void func_L00_002A3B88(void)
{
    int i, allowed, oldMode, flush, extra, limit, ticks, sound, period;
    float spriteSize;
    float elapsed, angle;
    if (!(((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1) & 15) && !((unsigned int)&D_L00_001B1680_1 & 15)) {
        FastMemoryHelperB(&D_L00_001B1680_1, (unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1);
    } else {
        STUB_printf(D_L00_001A7C88);
        for (i = 0; i < (int)((unsigned int)D_L00_0025BBA0 - (unsigned int)&D_L00_001B1680_1); i++) ((unsigned char *)&D_L00_001B1680_1)[i] = 0;
    }
    ResetBufferSlotTable();
    D_L00_001A8F00[0] = 0;
    D_L00_001A8F08 = -2;
    D_L00_001A8F04 = 0;
    D_L00_001B19C4[0] = 0;
    InitLevelSystems();
    if (D_001A7290 != D_001A7A18) LoadTexturePackToVram(D_001A7A18);
    {
        int weapon = gItemSlotToRecord[10];
        if (D_001A72C0 != gWeaponTable_L00[weapon].channel)
            LoadPackSingleTexture(gWeaponTable_L00[weapon].channel);
    }
    {
        int output = (gEquipmentBits >> 16) & 31;
        if (gHeroMoby_00152C00.output != output) LoadDiscTableTexture(output);
    }
    if (gHeroMoby_00152C00.mode != (gEquipmentBits & 3)) LoadDiscTableEntryForDraw(gEquipmentBits & 3);
    if (!gWeaponTable_L00[gItemSlotToRecord[gHeroState.weapon]].active) HandleRequestSlotState(10);
    LoadLevelArchiveResources(1, 0);
    SetupMapScreen();
    InitializeHudSlotsAndBuffers();
    InitLevelObjectCallbacks();
    ResetMenuSlots();
    gHeroMoby_00152C00.ready = 1;
    if (gHeroMoby_00152C00.reset) gHeroMoby_00152C00.reset = 0;
    allowed = 1;
    if (gHeroMoby_00152C00.pending || D_001A7904
        || gCurrentMapIndex == 0 || gCurrentMapIndex == 5 || gCurrentMapIndex == 10 || gCurrentMapIndex == 15
        || (gCurrentMapIndex > 20 && gCurrentMapIndex != 24)
        || (gCurrentMapIndex == 4 && D_001A7B1F && !D_001395CA)
        || (gCurrentMapIndex == 9 && D_001395E5)
        || (gCurrentMapIndex == 14 && !D_0019B3D2))
        allowed = 0;
    if (allowed && gHeroMoby_00152C00.announce) BeginSlotRequest(6, 1, 6, 0, 0);
    gHeroMoby_00152C00.pending = 0;
    D_001A7904 = 0;
    FadeToBlack(4);
    D_L00_001B18D8[0] = 0;
    StartMusicStreamNoLoop(0, 1, 1024);
    music_Pause(0);
    if (gCurrentMapIndex < 28 && !D_001A7BE8[gCurrentMapIndex]) D_001A7BE8[gCurrentMapIndex] = 1;
    if (D_0018C360[gCurrentMapIndex].visits < 65535) D_0018C360[gCurrentMapIndex].visits++;
    if (D_0018C360[gCurrentMapIndex].maximum < D_001A7390) D_0018C360[gCurrentMapIndex].maximum = D_001A7390;
    D_0018C360[gCurrentMapIndex].visited = D_0018C360[gCurrentMapIndex].visited | (1u << gCurrentMapIndex) | 0x80000000u;
    SetSoundCurrentBufferFlag();
    CallRpcServer(D_001A7248, 3, 0, 0, 0, 0, 0, 0, 0);
    ApplyPendingGameModeChange();
    if (!D_L00_001A8F00[0]) music_Unpause();
    PumpMusicAndDiscRead(1);
    LoadClassIntoFreeCacheSlot(gWeaponTable_L00[gItemSlotToRecord[D_001A7398]].sound);
    PumpMusicAndDiscRead(1);
    LoadClassIntoFreeCacheSlot(gWeaponTable_L00[gItemSlotToRecord[D_001A7A04]].sound);
    PumpMusicAndDiscRead(1);
    while (!D_L00_001A8ED4) {
        D_L00_001B19D4[0] = 0;
        flush = 0;
        extra = 0;
        D_001A7200 += T1_COUNT;
        T1_COUNT = 0;
        ProcessScreenCopyRegions();
        SubmitBufferedDmaChain();
        SwapPacketBuffer();
        PutDrawBufferSmall();
        AppendGsPacketTagB();
        AppendDrawListHeader();
        snd_Pump();
        oldMode = D_L00_001A8F00[0];
        switch (oldMode) {
        case -1: case 0:
            PollPadPorts();
            UpdateGameFrameInput();
            if (D_L00_001A7C80 == 1) {
                T1_COUNT = 0;
                PollPadPorts();
                UpdateGameFrameInput();
            }
            SetDrawModeAndRender();
            break;
        case 8:
            PollPadPorts();
            UpdateLevelObjectsPerFrame();
            ResetScreenOverlay();
            break;
        case 7:
            PollPadPorts();
            RunFrameUpdateChain();
            ClearScreenAndRender();
            break;
        case 1:
            PlayMovie_002F5FB8();
            break;
        case 2:
            PollPadPorts();
            UpdateCutsceneFrame();
            RenderFrameAllLayers();
            DrawLetterboxBars();
            break;
        case 3:
            PollPadPorts();
            UpdatePauseMenu();
            CallEngineRoutineWithZero();
            break;
        case 4:
            PollPadPorts();
            UpdateModalState();
            RenderFrameWithExtraLayers();
            break;
        case 5:
            PollPadPorts();
            UpdatePurchaseMenuAndPreview();
            DrawPurchaseMenuScene();
            break;
        case 6:
            PollPadPorts();
            UpdatePlaybackScene();
            DrawTransitionBackground();
            break;
        case 9:
            PollPadPorts();
            CallRac1HelperD();
            CallRac1HelperE();
            break;
        case -2: case 10: default:
            TrapAlways();
            break;
        }
        D_L00_001B19C4[0]++;
        DecrementCounterClamped();
        if (!D_L00_001A8F00[0]) AddToWrappingCounter();
        UpdateMemoryCardState();
        UpdateMapStateMachine();
        if ((unsigned)(gMemcardState.pressed - 15) < 2 || gMemcardState.alternate == 15 || D_L00_001B1680[0]) {
            if (gMemcardState.transition || gMemcardState.held) {
                gMemcardState.counter = 0;
                gSaveMenuScreen = 21;
                gSaveMenuFlags = 64;
                D_L00_001B1680[0] = 0;
                if (!D_L00_001A8F00[0])
                    BeginSlotRequest(4, 1, 1, 0, 0);
                else
                    BeginSlotRequest(4, 2, 1, 0, 0);
            } else if (D_L00_001B1680[0] == -1) {
                if (!D_L00_001A8F00[0]) {
                    if (!gSubtitleHistory.resume) gSubtitleHistory.resume = 1;
                    D_L00_001B1680[0] = 0;
                }
            } else if (!D_L00_001A8F00[0] && !D_0018C9DC) {
                BeginSlotRequest(4, 1, 2, 0, 0);
                D_L00_001B1680[0] = -1;
            } else {
                if ((unsigned)(gMemcardState.pressed - 15) < 2 || gMemcardState.alternate == 15)
                    D_L00_001B1680[0] = 30;
                else
                    D_L00_001B1680[0] = D_L00_001B1680[0] - 1;
                period = 55;
                SetupGifPaging(0);
                spriteSize = 272.0f;
                VU1_addGSregister(71, 0x2004bULL);
                DrawHudSprite(GetIconFrame(0x755d, 0), 425, 250, 64, 64, 128);
                angle = ((float)(D_L00_001B18D8[0] % period) * -6.2831854820251465f) / (float)period;
                DrawRotatedSprite(64, 64, GetFrameTexture(GetIconFrame(0x755d, 1)), 7312.0f, 4512.0f, spriteSize, spriteSize, angle);
                DoGifPaging();
                if (gSaveMenuScreen == 2) D_L00_001B1680[0] = 0;
            }
        }
        WaitForDmaStatusBits(1);
        elapsed = IntToFloat(T1_COUNT);
        D_L00_001B19CC = elapsed * (gIsPalVideo ? 0.00008680556f : 0.00010416667f);
        if (!gHeroState.flush && !D_L00_001B19D4[0]) {
            if (!D_L00_001A8F00[0]) {
                ticks = T1_COUNT;
                limit = gIsPalVideo ? 11520 : 9600;
                if (D_L00_001A7C80 == 0) {
                    if (limit < ticks) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 1;
                    }
                } else if (D_L00_001A7C80 == 1) {
                    if (D_L00_001A7C84 >= 2) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 2;
                    }
                } else if (D_L00_001A7C80 == 2) {
                    if (D_L00_001A7C84 >= 4 && ticks <= limit) {
                        D_L00_001A7C84 = 0;
                        D_L00_001A7C80 = 3;
                    }
                } else if (D_L00_001A7C80 == 3) {
                    D_L00_001A7C80 = 0;
                    D_L00_001A7C84 = 0;
                }
                D_L00_001A7C84++;
                if (D_L00_001A7C80 == 0) {
                    GetGsCurrentField(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 1) {
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 2) {
                    if (limit < ticks) D_L00_001A7C84 = 0;
                    if (!D_L00_001A8F00[0]) {
                        PollPadPorts();
                        UpdateGameFrameInput();
                    } else if (D_L00_001A8F00[0] == 2 && !D_L00_001BCB24) {
                        PollPadPorts();
                        UpdateCutsceneFrame();
                    }
                    AddToWrappingCounter();
                    GetGsCurrentField(0);
                    D_L00_001B18D8[0]++;
                } else if (D_L00_001A7C80 == 3) {
                    GetGsCurrentField(0);
                    GetGsCurrentField(0);
                    D_L00_001B18D8[0]++;
                }
                CountCallsAndBump();
            } else if (D_L00_001A8F00[0] == 2) {
                int now = T1_COUNT;
                int budget = gIsPalVideo ? 11520 : 9600;
                if (budget < now && !D_L00_001BCB24) {
                    PollPadPorts();
                    UpdateCutsceneFrame();
                }
                AddToWrappingCounter();
                CountCallsAndBump();
                GetGsCurrentField(0);
                D_L00_001B18D8[0]++;
            } else {
                GetGsCurrentField(0);
                D_L00_001A7C80 = 0;
                D_L00_001A7C84 = 0;
                D_L00_001B18D8[0]++;
                CountCallsAndBump();
            }
            D_L00_001A8FE0 = 0;
        }
        ResetGsRegistersPr();
        if (!D_L00_001A8F00[0] && gHeroState.flush) { flush = 1; extra = 1; }
        if (flush) {
            ResetPacketBuffer();
            ClearSoundFlagAndUpdate();
            snd_Pump();
            ClearAllSoundVoices();
            WaitForMusicIdle();
            sound = D_001A63F0;
            if (*(int *)D_L00_0021DDB0) sound = *(int *)(D_L00_0021DDB0 + 0xc64);
            ClearSubtitleState();
            LoadLevelArchiveResources(0, extra);
            ResetInputState(0);
            StartMusicStreamNoLoop(sound, 1, 1024);
            InitializeHudSlotsAndBuffers();
        } else {
            ApplyPendingGameModeChange();
            if (D_L00_001A8F00[0] != oldMode) D_L00_001B19C4[0] = 0;
            if (D_L00_001B19D4[0]) ResetPacketBuffer();
        }
        if (D_0018C360[gCurrentMapIndex].maximum < D_001A7390) D_0018C360[gCurrentMapIndex].maximum = D_001A7390;
    }
    FillMapBuffer(D_0018D278 + gCurrentMapIndex * 2048);
    if (D_L00_001B19C0 != gCurrentMapIndex) D_00139629 = gCurrentMapIndex;
    RunLevelTransition();
}
