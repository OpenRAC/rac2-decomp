#include "common.h"
extern int D_L03_001A8F00, D_001A79F0, D_001A7390;
extern int D_00138324 __attribute__((nosda));
extern u8 D_0018C958[], D_00188660[];
extern u16 D_0018D090[];
extern u8 *D_L03_001AC040 MACRO_ADDR;
extern float D_001B2464;
extern int D_L03_001B2768;
extern int D_L03_001B0B50 __attribute__((sda)), D_L03_001B0B58 __attribute__((sda));
extern u16 D_L03_001B0B5C __attribute__((sda));
extern u16 D_L03_001B0B60 __attribute__((sda));
extern float D_L03_001B0B74 __attribute__((sda));
extern void func_002A7750(u8 *, int, int);
extern float func_002AA2E8(float *, float, float);
extern void func_002E59F8(int);
extern void func_L03_003E26C8(u8 *), func_L03_003E3018(u8 *),func_L03_003E2EC8(u8 *),func_L03_003E3678(u8 *),func_L03_003E3430(u8 *),func_L03_003E4588(u8 *),func_L03_003E5218(u8 *);
extern int func_L03_003E3800(u8 *);
extern int func_00288E18(int,int);
extern int func_002E5CF8(int,int,u8 *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002E5F40(int,int);
extern int func_002B3868(u8 *);
extern int func_002B4B70(int,int),func_00282978(short *);
extern void func_0029F338(u8 *);
extern void func_L03_003E3A00(u8 *);
extern void func_L00_002E6CF0(void (*)(u8 *),u8 *);

/* The signed halfword members preserve the record/global alias information
 * needed by the timer increment and clamp. */
typedef struct {
    u8 pad00[0x40];
    u8 choices[0x10];
    short current, next, f54, f56;
    float f58;
    short last, length, maximumLength, cursor, depth, pending, timer, active;
    u8 pad6C[0x10];
    int sound;
} PathRecord;

/* Updates the Infiltrator Ball (moby class 2856): runs the timed path puzzle through its states. */
void func_L03_003E21B0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    PathRecord *path = (PathRecord *)vars;
    int i, soundHandle;
    float ratio;
    u8 *timeRecord;

    if (D_L03_001A8F00 != 7) {
        if (moby[0x20])
            SetMobyState(moby, 0, -1);
        return;
    }
    ApproachValue(&D_001B2464, 0.0f, 0.16666667f);
    D_L03_001B2768 = 1;
    switch (moby[0x20]) {
    case 0:
        for (i = 0; i < 52; i++)
            StopSoundVoice(i);
        InitializePathPuzzle(moby);
        *(u16 *)(moby + 0x34) |= 0x100;
        ComputePathPuzzleTurn(moby);
        SetMobyState(moby, gCurrentMapIndex == 11 ? 1 : 3, -1);
        break;
    case 1:
        timeRecord = gSubtitleHistory;
        if ((u32)(D_001A7390 - *(u32 *)(timeRecord + 0x73C)) > 1080 ||
            !*(u32 *)(timeRecord + 0x73C))
            RequestSubtitleVoiceLine(0xA43, 0x9A);
        else if (*(u32 *)(timeRecord + 0x73C) < (u32)D_001A7390)
            *(u32 *)(timeRecord + 0x73C) = D_001A7390;
        SetMobyState(moby, 3, -1);
        break;
    case 2:
        if (!path->timer) {
            SetMobyState(moby, 4, -1);
            break;
        }
        if (SelectPathPuzzleNodeFromStick(moby)) {
            path->active = 1;
            UpdateChoicePath(moby);
            PlayMobySound(4, 0, moby);
            SetMobyState(moby, 3, -1);
        }
        break;
    case 3:
        AnimatePathPuzzleTurn(moby);
        if (!path->f56)
            break;
        if (path->pending != -1) {
            *(u16 *)(vars + 0x52) = *(u16 *)(vars + 0x66);
            path->pending = -1;
        } else {
            ChoosePathPuzzleNextNode(moby);
        }
        /* 255 terminates the available-neighbor list. */
        {
            int choice = path->choices[0];
            choice ^= 255;
            if (choice == 0) {
                PlayMobySound(0, 0, moby);
            } else {
                soundHandle = PlayMobySound(1, 0, moby);
                if (soundHandle != -1) {
                    ratio = IntToFloat(path->length);
                    ratio /= IntToFloat(D_L03_001B0B50);
                    SetVoicePitchBend(soundHandle, FloatToInt(ratio * 1024.0f) + 1024);
                }
            }
        }
        if (path->length > path->maximumLength) {
            path->maximumLength = *(u16 *)(vars + 0x5E);
            path->timer += D_L03_001B0B60;
            if (path->timer > D_L03_001B0B58)
                path->timer = D_L03_001B0B58;
        }
        if (path->length == D_L03_001B0B50) {
            PlayMobySound(5, 0, moby);
            SetMobyState(moby, 5, -1);
        } else {
            SetMobyState(moby, 2, -1);
        }
        break;
    case 4:
        if (path->f56) {
            if (path->last != path->current) {
                *(u16 *)(vars + 0x52) = *(u16 *)(vars + 0x5C);
                UpdateChoicePath(moby);
                PlayMobySound(2, 0, moby);
            } else {
                path->active = 0;
                path->maximumLength = 0;
                path->timer = D_L03_001B0B5C;
                SetMobyState(moby, 2, -1);
            }
        } else {
            AnimatePathPuzzleTurn(moby);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(moby))
            *(u16 *)(moby + 0x96) = 120;
        if (!*(u16 *)(moby + 0x96)) {
            D_0018D090[0] = 65535;
            SetMobyFlagOn(D_L03_001AC040);
            goto exit;
        } else {
            --*(u16 *)(moby + 0x96);
        }
        break;
    }
    if (D_00138324 & 16) {
        if (moby[0x20] == 5)
            SetMobyFlagOn(D_L03_001AC040);
    exit:
        EndSlotRequest(0, 0);
        MarkMobySpawned(moby);
        return;
    }
    if (moby[0x20] != 5 && path->active)
        FastDecTimer(&path->timer);
    if (path->active && path->timer) {
        u8 *soundSlot = gSoundState + *(int *)(vars + 0x7C) * 112;
        if (*(u8 **)(soundSlot + 0x88) != moby || !soundSlot[0x74])
            *(int *)(vars + 0x7C) = PlayMobySound(3, 4, moby);
    } else {
        int handle = *(int *)(vars + 0x7C);
        if (handle != -1) {
            int offset = handle * 112;
            u8 *soundSlot = gSoundState + offset;
            if (*(u8 **)(soundSlot + 0x88) == moby && soundSlot[0x74])
                StopSoundVoice(handle);
        }
        *(int *)(vars + 0x7C) = -1;
    }
    UpdatePathPuzzleGlowColor(moby);
    *(float *)(vars + 0x58) -= D_L03_001B0B74 * 0.016666667f;
    if (*(float *)(vars + 0x58) < -1.0f)
        *(float *)(vars + 0x58) += 1.0f;
    AddDrawCallbackToList1(DrawPathPuzzleHud, moby);
}
