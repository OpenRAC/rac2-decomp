/* Player frame update: the ordered resident-player steps while control is active.
   The player record is reached through pointer locals (one per stretch, sharing the
   %hi of D_00189E20) and the control mode is a macro-addressed word. */
#include "common.h"
/*
 * Retained handwritten near miss; historical evidence only.
 * No linked-image equality or complete retail semantics is established.
 * Compiler: game EE-GCC 2.9-ee-991111b (project profile).
 * Profile: -O2 -G0 -ffunction-sections.
 * Reported final C / retail: 552 / 556 bytes; size equality is not a match.
 * us: 0/13 placements; 552/556 bytes.
 * us2: absent from catalogue (not a match).
 * pal: absent from catalogue (not a match).
 * Residual: The 552/556-byte form hoists the repeated position address and saves an additional GPR. Disabling GCSE and using documented position/root views did not close the gap.
 * Reopening condition: Reopen only after independent source, data-layout, ABI or compiler evidence specifically explains the residual above; then test that single hypothesis. Do not repeat tied source forms or flag sweeps.
 * Where listed, tools/check.py measurements predate retention; no compilation was rerun for this copy.
 */

/* Readable manual reconstruction, measured 2026-10-23.
 * Retained profile: -O2 -G0 -ffunction-sections.
 * us: 0 of 13 places match; exit 1.
 * us2: absent from both catalogues (exit 1).
 * pal: absent from both catalogues (exit 1).
 * The 552/556-byte form hoists the repeated position address and saves an additional GPR. Disabling GCSE and using documented position/root views did not close the gap.
 * 4 bounded source/profile trials; no exact-C credit is claimed.
 * Live helper inputs and consumed return banks were checked against retail and
 * current definitions. Original scalar-return intent remains unqualified for
 * procedural ASM callees whose results this body does not consume.
 * Reopen with independent layout/lifetime, table-extent or scheduling evidence;
 * no source barriers, register pins, invented aliases or padding were used.
 */

extern unsigned char D_00189E20[];
extern unsigned char D_00189EA0[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern void func_L00_002A65D8(void);
extern void func_L00_002D24E8(void);
extern void func_L00_002B36E0(void);
extern void func_L00_002ACA08(void);
extern int func_L00_002ACF88(void *, void *, void *);
extern void func_L00_002ADB40(void);
extern void func_L00_002ADD30(void);
extern void func_L00_002CB3A8(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002D3068(void);
extern void func_L00_002AE0C8(void);
extern void func_L00_002B9CA8(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9460(void);
extern void func_L00_002AA178(int);
extern void func_L00_002B2120(void);
extern void func_L00_002B2318(void);
extern void func_L00_002B2200(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_L00_002A67F8(void);
extern void func_L00_002D5EB8(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *);
extern int func_002A677C(void *);
extern void func_L00_002A74A8(void);
extern void func_L00_002A9760(void);

/* Run the frame's ordered resident-player updates while its control mode is active. */
void func_L00_002A6DD0(void) {
    unsigned char *player = gHeroState;
    unsigned char *hero;
    *(short *)(player + 0x2162) = 0;
    *(short *)(player + 0x2160) = 0;
    if (player[0x22B4]) { UpdateHeroFrame_L00(); return; }
    AdvanceHeroAnimation();
    UpdateHeroInputAndHistory();
    ProcessHeroActionCommand();
    FindHeroLedgeGrab(player + 0x80, player + 0x90, player + 0x550);
    FindGrindRail();
    FindHeroLedgeCandidate();
    DecideHeroState_L00();
    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        if (player[0x22B5]) SetHeroObjectsFlagBit();
        else ClearHeroObjectsFlagBit();
        return;
    }
    RebuildRegionObjectMembership();
    if (player[0x22B4]) return;
    UpdateDelayedSounds();
    UpdateHeroEasingTargetsAndPointEffects();
    UpdateCameraBlendAngles();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    UpdateAllAttachmentRecords();
    update_hero_moby();
    SpawnEffectFromRecord(0);
    UpdateHeroItemsAndFlags();
    UpdateHeroLockOnWeaponFire();
    PlayHeroVoiceLineForProgress();
    UpdateHeroItemsFrame();
    if (player[0x22B5] || IsHeroActionAllowed()) SetHeroObjectsFlagBit();
    else ClearHeroObjectsFlagBit();
    FadeScreenEffect();
    ApplyHeroAxisScales();
    UpdateHeroStatTrackers();
    UpdateCollectionProgress();
    CheckHeroTargetingTriggers();
    UpdateHeroAimAndTransitions();
    hero = gHeroState;
    if ((*(int *)(hero + 0x229C) != 0x16 && *(int *)(hero + 0x229C) != 0x1F && *(int *)(hero + 0x2294) != 0x31) || IsHeroInSwingOrGrindMode())
        ClearMapBitsAroundPosition(gHeroPosition);
    { unsigned char *base = gHeroState; func_002A677C(*(void **)(base + 0x2290)); }
    UpdateHeroBlinkAndItemTint();
    UpdateHeroMobyProbedHeightBounds();
}
