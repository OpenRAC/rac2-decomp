#include "include_asm.h"
#include "common.h"

extern s32 D_L08_001A9050 __attribute__((sda));
extern f32 D_L08_001A9054 __attribute__((sda));
extern f32 D_L08_001BE0B0 __attribute__((nosda));

extern void func_0027AB40();

/* Starts a saved-state hold: remembers a global float and returns 1, or returns 0 if one is already active. */
s32 func_L08_00300090(void) {
    if (D_L08_001A9050 != 0)
        return 0;
    D_L08_001A9050 = 1;
    D_L08_001A9054 = D_L08_001BE0B0;
    return 1;
}

/* Ends the saved-state hold: puts the remembered float back and returns 1, or returns 0 if none is active. */
s32 func_L08_003000C0(void) {
    if (D_L08_001A9050 == 0)
        return 0;
    D_L08_001BE0B0 = D_L08_001A9054;
    UpdateViewContext();
    D_L08_001A9050 = 0;
    return 1;
}

/* The level's shared scalars: the aim values the camera reads, and the object
   the level keeps at a fixed place (its flag at +0x86, its target at +0x70). */
extern f32 D_L08_001B00E0 __attribute__((sda));
extern f32 D_L08_001B00E4 __attribute__((sda));
extern f32 D_L08_001B00E8 __attribute__((sda));
extern f32 D_L08_001B00F0 __attribute__((sda));
extern s32 D_L08_001B00F4 __attribute__((sda));
extern f32 D_L08_001B00F8 __attribute__((sda));
extern u8 *D_L08_001B9B50 __attribute__((nosda));

/* The boot's own vector, the one the aim is measured against. */
extern char D_00189EA0[] __attribute__((nosda));

extern void func_L00_00424A08(s32, f32, f32);
extern void func_L00_00424A50(f32, f32);
/* The prototype's order is the one the call site uses: the first float, then the
   flag, then the second float. The registers are the same either way (the int
   in $a0, the floats in $f12 and $f13). */
extern void func_L00_00424A88(f32, s32, f32);
extern void func_L00_00424B20(f32);
extern void func_L00_00424B70(f32, f32);
extern void func_L00_00424BB8(f32, f32);
extern void func_L00_00424C00(void);
extern void func_L00_00424C28(void);
extern s32 func_002ACBC8(void *, s32);
extern f32 func_00283CE0(s32);

/* Flags the level's object, feeds the camera its aim values and advances the
   counter the aim is scaled by. */
void func_L08_003CD488(s32 *counter, u8 *moby) {
    u8 *owner;
    f32 fade, scaleA, scaleB, scaleC;

    owner = *(u8 **)((u8 *)moby + 0x68);
    if (*(s16 *)((u8 *)D_L08_001B9B50 + 0x86) == 0) {
        *(s32 *)((u8 *)*(u8 **)((u8 *)D_L08_001B9B50 + 0x70) + 0x250) = 2;
    }

    SetCameraAimOffsetTarget(D_L08_001B00F0, D_L08_001B00F4, D_L08_001B00F8);
    follow_camera_set_distance(0, D_L08_001B00E4, D_L08_001B00E0);

    if (*(s32 *)((u8 *)owner + 0xC8) >= 0 &&
        IsPointInCuboid(gHeroPosition, *(s32 *)((u8 *)owner + 0xC8)) != 0) {
        SetCameraTuningValue(0.52359885f);
    }

    follow_camera_set_height(D_L08_001B00E8, 0.003f);
    SetCameraLockFlag();

    fade = IntToFloat(*counter) / IntToFloat(0x5A);
    if (fade > 1.0f)
        fade = 1.0f;

    scaleA = fade * 0.985f + 0.015f;
    scaleB = fade * 0.8f + 0.2f;
    scaleC = fade * 0.044999998062849045f + 0.015f;

    SetCameraSpeedsIfNonZero(scaleA, scaleB);
    SetCameraTurnSpeedsIfNonZero(scaleC, 0.2f);
    SetCameraSnapFlag();

    if (*counter < 0x5A)
        *counter = *counter + 1;
}

extern f32 func_002A7798(f32);

/* Resident data: a pair of floats at 0x189E20 + 0x1FB0, the aim values at
   0x138180 + 0x124, and the mode word at 0x1A79F0. */
extern char D_00189E20[];
extern char D_00138180[];
extern s32 D_001A79F0;

/* Reads the player's aim and stick values and gives back six values clamped to the range -1 to 1. */
void func_L08_003C6528(f32 *outX, f32 *outY, f32 *outZ, f32 *outA, f32 *outB, f32 *outC) {
    char *playerData = (char *)gHeroState;
    f32 value;
    {
        char *settings = (char *)gPadState;
        *outX = -*(f32 *)(playerData + 0x1FB0);
        *outZ = -*(f32 *)(playerData + 0x1FB4);
        *outY = EaseOutQuad(*(f32 *)(settings + 0x128)) - EaseOutQuad(*(f32 *)(settings + 0x124));
    }
    if (gCurrentMapIndex == 8 || gCurrentMapIndex == 0x1E || gCurrentMapIndex == 0x15) {
        char *settings = (char *)gPadState;
        *outA = *(f32 *)(settings + 0x12C);
        *outC = 0;
    } else {
        char *settings = (char *)gPadState;
        *outC = *(f32 *)(settings + 0x12C);
        *outA = 0;
    }
    {
        char *settings = (char *)gPadState;
        *outB = EaseOutQuad(*(f32 *)(settings + 0x138)) - EaseOutQuad(*(f32 *)(settings + 0x13C));
    }

    value = *outX;
    if (value > 1.0f)
        *outX = 1.0f;
    else if (value < -1.0f)
        *outX = -1.0f;

    value = *outY;
    if (value > 1.0f)
        *outY = 1.0f;
    else if (value < -1.0f)
        *outY = -1.0f;

    value = *outB;
    if (value > 1.0f)
        *outB = 1.0f;
    else if (value < -1.0f)
        *outB = -1.0f;
}
