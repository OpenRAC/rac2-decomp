#include "include_asm.h"
#include "names.h"

extern int D_001AA100 __attribute__((sda));
extern int D_001B1D50[];

/* Returns the most recent entry of the mode stack, or -2 when it is empty. */
int func_002B4BE8(void) {
    int depth = D_001AA100;
    if (depth != 0)
        return D_001B1D50[depth - 1];
    return -2;
}

extern void *D_0026CBB0[];
extern void *D_0026CBE0[];
extern int D_001A8BB0;
extern int D_001A8BB4;
extern int D_001A8BB8;
extern int D_0018C2EC __attribute__((nosda));
extern int D_001AA0F4 __attribute__((sda));
extern int D_001AA0F8 __attribute__((sda));
extern int D_001AA0FC __attribute__((sda));
extern char *D_001AA104 __attribute__((sda));
extern float D_001A8C7C;
extern float D_001B15A0;
extern int D_001B1694;
extern float D_001B90F0 __attribute__((nosda));
extern int D_001ABD80;
extern void func_002CA790(void);
extern void func_00285860(void);
extern void func_002F5EF8(void);
extern void func_002F57A8(void);
extern void func_0026FF08(int, int, float, float, float, float);
extern void func_0027AB40(void);
extern void func_002E7248(void);
extern void func_002F8768(void);
extern void func_002DF380(void);
extern void func_002FF288(void);
extern void func_00291128(void);
extern void func_00282A28(void);
extern void func_002B49B0(int);
extern int func_002857B0(void);
extern void func_002C9CF8(int);
extern void func_002858C0(int, int);
extern void func_002F5D40(int);
extern float func_002AA2E8(float *, float, float);
extern void func_002F53C8(int);
extern void func_00288CB0(int, int);
extern void func_002E71B8(void);
extern void func_002E7090(int);
extern void func_002E7018(void);
extern void func_002F8178(int);
extern void func_002DF2E0(int, int);
extern void func_002FF0D8(void);
extern void func_00291108(void);

/* Applies a requested change of mode: D_001A8BB8 holds the requested mode (-2 when none) and
   D_001A8BB0 the current one. The first dispatch runs the handler of the mode being left and the
   second the handler of the mode being entered; unless that one holds the change (hold), the
   request becomes the current mode and is cleared. Both dispatches read the tables retail has in
   its data (ten code addresses each, one per mode, D_0026CBB0 and D_0026CBE0); `leaving` and
   `entering` only keep the labels alive. A handler reached through a table starts with no known
   values, so D_001A8BB8 is read again where retail reads it (the compare in the first handler of
   mode 3) without any qualifier on the global. */
/* Switches the game to a newly requested mode: shuts down the old mode, starts the new one and clears the request. */
void func_002B4C18(void)
{
    static void *leaving[12] = {&&L1_3, &&L1_4, &&L1_1, &&L1_2, &&L1_6, &&L1_5, &&L1_7, &&L1_8, &&L1_9, &&L1_0, &&L1_def, &&shared};
    static void *entering[11] = {&&L2_3, &&L2_0, &&L2_4, &&L2_1, &&L2_2, &&L2_6, &&L2_5, &&L2_7, &&L2_8, &&L2_9, &&L2_def};
    int oldMode = gCurrentGameMode;
    int newMode;
    int hold;
    gPreviousGameMode = oldMode;
    if (gRequestedGameMode == -2)
        return;
    if (D_001AA0F4 > 0) {
        D_001AA0F4--;
        return;
    }
    if (D_0018C2EC == 0)
        return;
    if ((unsigned)oldMode >= 10)
        goto L1_def;
    goto *D_0026CBB0[oldMode];
L1_3:
    if (gRequestedGameMode != 4 || D_001AA0F8 == 8)
        RestoreMenuDisplayState();
    goto E1;
L1_4:
    EndMenu();
    goto E1;
L1_1:
    ResumeAfterMovie();
    goto shared;
L1_2:
    EndCutscene();
shared:
    D_001B90F0 = 0.62f;
    SetCameraValueTarget(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    UpdateViewContext();
    goto E1;
L1_6:
    if (D_001AA0F8 != 4)
        EndPlaybackScene();
    goto E1;
L1_5:
    ResetShopMenuCamera();
    goto E1;
L1_7:
    ShowAllMobys();
    goto E1;
L1_8:
    NoOp_002FF288();
    goto E1;
L1_9:
    CallFunc00278F80Wrapper();
    goto E1;
L1_def:
    TrapAlways();
L1_0:
E1:
    SetRequestSettingA(10);
    hold = 0;
    newMode = gRequestedGameMode;
    if ((unsigned)newMode >= 10)
        goto L2_def;
    goto *D_0026CBE0[newMode];
L2_3:
    if (gPreviousGameMode != 4 || GetMenuMode() == 8)
        InitPauseMenuState(D_001AA0F8);
L2_0:
    hold = 0;
    goto E2;
L2_4:
    SetMenuMode(D_001AA0F8, D_001AA0FC);
    goto E2;
L2_1:
    StartMovieFromTocEntry(D_001AA0FC);
    hold = 0;
    goto E2;
L2_2:
    if ((unsigned)(gCurrentGameMode - 1) >= 2) {
        float f;
        ApproachValue(&D_001A8C7C, 1.2f, 0.10000001f);
        f = D_001A8C7C;
        gScreenFade = f;
        if (1.0f < f)
            gScreenFade = 1.0f;
        if (1.2f <= f) {
            hold = 0;
            D_001A8C7C = 1.0f;
            StartCutscene(D_001AA0F8);
        } else {
            hold = 1;
        }
    } else {
        StartCutscene(D_001AA0F8);
    }
    goto E2;
L2_6:
    if (D_001AA0F8 == 5) {
        SetSmallDataValueAndRefresh(D_001AA0FC, 1);
    } else if (D_001AA0F8 == 6) {
        InitPlaybackSceneState();
    } else {
        if (gPreviousGameMode == 3)
            InitSceneListForLevel(D_001AA0FC);
        else
            ResetSceneStateOnStart();
        D_001B1694 = 1;
    }
    goto E2;
L2_5:
    OpenVendorMenu(D_001AA0F8);
    goto E2;
L2_7:
    {
        int fallback = D_001ABD80;
        HideAllMobys(D_001AA0F8 ? D_001AA0F8 : fallback, D_001AA0FC);
    }
    goto E2;
L2_8:
    BeginPreviewTransition();
    goto E2;
L2_9:
    CallLightingInit();
    goto E2;
L2_def:
    TrapAlways();
E2:
    if (hold == 0) {
        int state;
        if (D_001AA104 != 0)
            *D_001AA104 = 1;
        state = gRequestedGameMode;
        gRequestedGameMode = -2;
        gCurrentGameMode = state;
        D_001AA104 = 0;
    }
}
