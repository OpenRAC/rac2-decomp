/* Per-frame level update: the resident block through a pointer, the tail through fresh
   pointers (retail re-derives them from the kept %hi), the mode word as a macro load. */

#include "common.h"

extern char D_00189E20[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char D_00189EA0[];

extern void func_L01_002A84D8(void);
extern void func_2C7CA8(void);
extern void func_L00_002B36E0(void);
extern void func_L01_002ADDC8(void);
extern void func_L01_002AE128(char *a0, char *a1, char *a2);
extern void func_L01_002C37C8(void);
extern void func_2C8628(void);
extern void func_L00_002D3068(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void func_L00_002AA178(int a0);
extern void func_L00_002B2120(void);
extern void func_L00_002B2318(void);
extern void func_L00_002B2200(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void func_L00_002A67F8(void);
extern void func_L00_002D5EB8(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_30F444(int a0);
extern void func_L01_002A9298(void);
extern void func_2AB328(void);

/* Runs one frame of the main game update: reads input, moves the hero and camera, and updates effects and menus. A shorter path is used when the game is in a special mode. */
void func_L01_002A8C48(void) {
    char *hero;

    hero = gHeroState;
    *(short *)(hero + 0x2162) = 0;
    *(short *)(hero + 0x2160) = 0;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        UpdateHeroSubsystems();
        return;
    }
    func_2C7CA8();
    UpdateHeroInputAndHistory();
    ReadHeroInputCommandFlags();
    ProbeLedgeGrab(hero + 0x80, hero + 0x90, hero + 0x550);
    UpdateHeroStateTransitions_L01();
    if (D_L01_001A8F40 == 2 || D_L01_001A8F40 == 6) {
        if (*(unsigned char *)(hero + 0x22B5) != 0)
            func_2C8628();
        else
            ClearHeroObjectsFlagBit();
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(hero + 0x22B4) != 0)
        return;
    func_2B9878();
    UpdateHeroEasingTargetsAndPointEffects();
    UpdateCameraBlendAngles();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    func_2A7740();
    func_2AB028();
    SpawnEffectFromRecord(0);
    UpdateHeroItemsAndFlags();
    UpdateHeroLockOnWeaponFire();
    PlayHeroVoiceLineForProgress();
    UpdateHeroItemsFrame();
    if (*(unsigned char *)(hero + 0x22B5) != 0 || IsHeroActionAllowed() != 0)
        func_2C8628();
    else
        ClearHeroObjectsFlagBit();
    func_2A9520();
    func_2A9310();
    UpdateHeroStatTrackers();
    UpdateCollectionProgress();
    CheckHeroTargetingTriggers();
    UpdateHeroAimAndTransitions();
    {
        char *heroBlock = gHeroState;
        if ((*(int *)(heroBlock + 0x229C) != 0x16 && *(int *)(heroBlock + 0x229C) != 0x1F
             && *(int *)(heroBlock + 0x2294) != 0x31) || IsHeroInSwingOrGrindMode() != 0)
            ClearMapBitsAroundPosition(gHeroPosition);
    }
    {
        char *heroBlock = gHeroState;
        func_30F444(*(int *)(heroBlock + 0x2290));
    }
    UpdateEquippedWeaponEffect();
    func_2AB328();
}
