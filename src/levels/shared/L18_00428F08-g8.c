/* EE argument banks are independent; the interleaved call declaration agrees
 * with the matched motion callers and preserves each bank's argument order. */
#include "common.h"

typedef struct { int q __attribute__((mode(TI))); } Vec4;

extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0013965E[];
extern u8 D_00188660[];
typedef union { u8 b[0x1000]; s16 h[0x800]; u16 uh[0x800]; s32 i[0x400]; u32 ui[0x400]; f32 f[0x400]; u8 *p[0x400]; } View;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *p[0x980]; } Hero;
extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_0018C958[];
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern float D_L18_001B1230 __attribute__((sda));
extern float D_L18_001B1238 __attribute__((sda));
extern s32 D_L18_001B1258 __attribute__((sda));
extern s32 D_L18_001B125C __attribute__((sda));
extern u16 D_L18_001B1260 __attribute__((sda));
extern s32 D_L18_001B1274 __attribute__((sda));
extern s32 D_L18_001B1278 __attribute__((sda));
extern s32 D_L18_001B127C __attribute__((sda));
extern s32 D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B1298 __attribute__((sda));
extern float D_L18_001B129C __attribute__((sda));
extern s32 D_L18_001B2564[] __attribute__((sda));
extern u8 D_L18_001B2660[] MACRO_ADDR;
extern s32 D_L18_001B281C MACRO_ADDR;
extern Vec4 D_L18_001B97C0[];
extern u8 D_L18_0021DB40[][0x464];
extern u8 D_L18_0021E7B0[][0x464];
extern u8 D_L18_002571A0[];

extern s32 func_00282978(void *);
extern void func_00282A60(void *, u32, s32);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283CE0(s32);
extern s32 func_00288E18(s32, s32);
extern void func_0029B758(s32, void *);
extern void func_0029F338(void *);
extern void func_002A6C58(void *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern float func_002AAA00(void *out, float, void *in, s32, float, float, float);
extern void func_002AB8C0(void *, void *);
extern float func_002ABB18(float);
extern void func_002ABBB8(void *, void *, void *, float, float, s32, s32, s32, float, float,
                          float, float, s32, float, s32, s32, s32, s32, s32);
extern s32 func_002ACD38(void *);
extern void func_002B0C28(s32, s32, s32);
extern s32 func_002B1C20(void *, void *);
extern s32 func_002B3890(void *);
extern s32 func_002B5258(void *);
extern void func_002B5278(void *, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002E59F8(s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_003355A8(s32);
extern s32 func_001163B0(void);
extern s32 func_L00_00329520(void *, s32);
extern s32 func_L02_002EF388(void *, void *, void *, void *, s32);
extern void func_L02_003329C8(void *, void *, float, float);
extern s32 func_L07_00323038(void *, float, float, float);
extern void func_L18_002CFD68(s32, s32, void *);
extern void func_L18_002CFF48(s32);
extern s32 func_L18_0033B628(void *, s32, s32);
extern float func_L18_0035D5A8(void *, void *, void *, s32, float);
extern void func_L18_00426AB0(void);
extern void func_L18_00426D98(void *);
extern s32 func_L18_00426E00(void *);
extern s32 func_L18_00426E48(void *, void *);
extern void func_L18_00426F28(void *, s32, s32, float);
extern void func_L18_00427010(void *);
extern void func_L18_00427058(void *);
extern s32 func_L18_00427130(void *, s32, s32);
extern void func_L18_00427208(void *);
extern void func_L18_00427B48(void *, s32);
extern void func_L18_00427BE0(void *);
extern void func_L18_00428048(void *);
extern s32 func_L18_004283F0(void *);
extern void func_L18_00428738(void *);
extern void func_L18_00428AE8(void *);

/* Runs every frame for the Receiver Bot style enemy. It watches the player, picks its next move, handles being grabbed and carried, and finally hands over to the shared per-frame tick. */
void func_L18_00428F08(u8 *moby) {
    float cameraPos[4] __attribute__((aligned(16)));
    float dirVec[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float offsetVec[4] __attribute__((aligned(16)));
    float tempVec[4] __attribute__((aligned(16)));
    u8 *vars;
    s32 enemyKind;

    if (IsObjectInSelectedZone(moby + 0x10) == 0)
        return;
    vars = ((View *)moby)->p[0x68 / 4];
    UpdateReceiverBotTargetingAndHits(moby);
    switch (((View *)moby)->b[0x95]) {
    case 1:
        if (((View *)moby)->b[0x42] == 0xD)
            ((View *)moby)->i[0x48 / 4] = 0;
        break;
    case 2:
        if (!(((View *)vars)->b[0x399] & 1) && (((View *)vars)->i[0x234 / 4] == 1 || ((View *)vars)->h[0x390 / 2] != 0)
            && (IsShooterEnemyAlive(*(void **)(vars + 0x230)) == 0
                || IsTargetInSight(moby, *(void **)(vars + 0x230)) != 0)) {
            FlagShootersInGroup(moby, ((View *)moby)->b[0x21]);
            ((View *)vars)->i[0x37C / 4] = ((View *)vars)->i[0x364 / 4];
            ((View *)vars)->i[0x13C / 4] = ((View *)vars)->i[0x384 / 4];
            ((View *)vars)->h[0x392 / 2] = ((View *)vars)->b[0x398];
            if (((View *)vars)->i[0x368 / 4] != -1
                && (((View *)vars)->i[0x3A4 / 4] == -1 || IsPointInsideRegion(vars + 0x220, ((View *)vars)->i[0x3A4 / 4]) == 0)) {
                if (**(s32 **)(vars + 0x3A8) == 0 && **(s32 **)(vars + 0x3AC) < D_L18_001B127C) {
                    **(s32 **)(vars + 0x3A8) = RandomIntRange(D_L18_001B1274, D_L18_001B1278);
                    AcquireSharedResource(moby);
                    SetMobyState(moby, 1, 4);
                }
            } else {
                SetObjectAnimation(moby, ((View *)vars)->i[0x370 / 4], -1);
                SetMobyState(moby, 1, 3);
            }
        }
        break;
    case 3:
        if (((View *)vars)->h[0x392 / 2] == 0) {
            StartOrForwardAnimation(moby, 3, 0, 5.0f);
            if (((View *)vars)->i[0x370 / 4] != -1) {
                SetMobyState(moby, 3, 5);
            } else {
                SetObjectAnimation(moby, ((View *)vars)->i[0x374 / 4], -1);
                ((View *)vars)->h[0x390 / 2] = RandomIntRange(D_L18_001B1258, D_L18_001B125C);
                SetMobyState(moby, 3, 6);
            }
        }
        break;
    case 4:
        if (((View *)vars)->h[0x392 / 2] == 0) {
            ((View *)moby)->b[0x31] = 1;
            ((View *)moby)->uh[0x34 / 2] &= ~1;
            FindBestPointOnPathById(cameraPos, moby + 0x10, gHeroPosition, ((View *)vars)->i[0x368 / 4], 0.0f);
            StartOrForwardAnimation(moby, 6, 0, 5.0f);
            AimMoveRecordAtTarget(moby, cameraPos, D_L18_001B1238 * 0.0166666675f, D_L18_001B1230 * 0.000277777785f);
            SetMobyState(moby, 5, 10);
        }
        break;
    case 5:
        if (((View *)vars)->i[0x234 / 4] == 1 && ((View *)vars)->h[0x390 / 2] == 0)
            ((View *)vars)->h[0x390 / 2] = RandomIntRange(D_L18_001B1258, D_L18_001B125C);
        break;
    case 6:
        if ((((View *)vars)->i[0x234 / 4] != 1 && ((View *)vars)->h[0x390 / 2] == 0)
            || (((View *)vars)->b[0x3B2] != 0 && ((View *)vars)->b[0x3B3] == 0)
            || (((View *)vars)->b[0x3B3] != 0 && (((View *)vars)->p[0x230 / 4])[0xBC] == 0)) {
            ((View *)vars)->h[0x390 / 2] = 0;
            StartOrForwardAnimation(moby, (Rand() & 1) | 4, 0, 10.0f);
            SetMobyState(moby, 2, 2);
        } else if (((View *)vars)->b[0x3B0] == 0 && ((View *)vars)->i[0x368 / 4] != -1 && ((View *)vars)->i[0x3A4 / 4] != -1
                   && IsPointInsideRegion(vars + 0x220, ((View *)vars)->i[0x3A4 / 4]) == 0
                   && **(s32 **)(vars + 0x3A8) == 0 && **(s32 **)(vars + 0x3AC) < D_L18_001B127C) {
            **(s32 **)(vars + 0x3A8) = RandomIntRange(D_L18_001B1274, D_L18_001B1278);
            AcquireSharedResource(moby);
            SetMobyState(moby, 0, 4);
        }
        break;
    case 9: {
        s32 hitFlags = DispatchActionByKind(moby, vars + 0x50);

        if (hitFlags & 1) {
            SetDeathBits(moby, 0, 3);
            SetMobyState(moby, 12, -1);
        } else if (hitFlags & 2) {
            ((View *)vars)->h[0x390 / 2] = RandomIntRange(D_L18_001B1258, D_L18_001B125C);
            FlagShootersInGroup(moby, ((View *)moby)->b[0x21]);
            if (((View *)moby)->b[0xBC] == 1) {
                StartOrForwardAnimation(moby, 13, 0, 10.0f);
                SetMobyState(moby, 7, 8);
            } else {
                StartOrForwardAnimation(moby, (Rand() & 1) | 4, 0, 10.0f);
                SetMobyState(moby, 4, 6);
            }
        }
        break;
    }
    case 11: {
        s32 linkIndex;
        u8 *linked;

        ((View *)vars)->f[0x100 / 4] = 0.699999988f;
        linkIndex = ((View *)vars)->i[0x3B4 / 4];
        if (linkIndex != -1 && (linked = (u8 *)((linkIndex << 8) + gMobyTable_L18), *(s16 *)(linked + 0xAA) == 0x114D /* moby class 4429 */)
            && linked[0x20] != 0xFE && linked[0x20] != 0xFD) {
            if (linked[0xBC] == 0) {
                ((View *)moby)->b[0x23] = 0x80;
                ((View *)moby)->f[0x2C / 4] = *(float *)(((View *)moby)->p[0x24 / 4] + 0x24);
                ((View *)moby)->b[0x31] = 1;
                ((View *)moby)->uh[0x34 / 2] &= ~1;
                SetMobyState(moby, 0, 12);
            }
        } else {
            ((View *)moby)->b[0x31] = 1;
            ((View *)moby)->uh[0x34 / 2] &= ~1;
            FuseObjectWithLinkedObjects(moby, moby + 0x10, moby + 0xF0, 0, 0);
            SetMobyState(moby, 0, 14);
        }
        break;
    }
    case 12: {
        u8 *linked;

        *(Vec4 *)(moby + 0x10) = *(Vec4 *)((u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + gMobyTable_L18) + 0x10);
        linked = (u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + gMobyTable_L18);
        if (linked[0xBC] == 2) {
            if (((View *)moby)->b[0x43] != 2)
                StartAnimationBlended(moby, 2, 0, 10);
            SetMobyState(moby, 4, 13);
        }
        break;
    }
    case 13:
        if (((u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + gMobyTable_L18))[0xBC] == 3) {
            u8 *link = ((View *)moby)->p[0x24 / 4];

            ((View *)moby)->b[0x30] = ((View *)vars)->b[0x3E0];
            ((View *)moby)->i[0x98 / 4] = *(s32 *)(link + 0x10);
            ((View *)moby)->uh[0x34 / 2] |= 0x1000;
            ((View *)moby)->f[0x2C / 4] = *(float *)(link + 0x24);
            ((View *)vars)->h[0x392 / 2] = 0;
            if (((View *)moby)->h[0xAA / 2] == 0xED4 /* moby class 3796 */)
                ((View *)vars)->f[0x100 / 4] = 1.0f;
            if (((View *)moby)->h[0xAA / 2] == 0xEE1 /* Receiver Bot */)
                ((View *)vars)->f[0x100 / 4] = 1.10000002f;
            SetMobyState(moby, 2, 2);
        }
        break;
    case 14: {
        u8 *link = ((View *)moby)->p[0x24 / 4];

        ((View *)moby)->b[0x23] = 0x80;
        if (*(float *)(link + 0x24) <= ((View *)moby)->f[0x2C / 4]) {
            ((View *)moby)->b[0x30] = ((View *)vars)->b[0x3E0];
            ((View *)moby)->i[0x98 / 4] = *(s32 *)(link + 0x10);
            ((View *)moby)->uh[0x34 / 2] |= 0x1000;
            ((View *)moby)->f[0x2C / 4] = *(float *)(link + 0x24);
            if (((View *)moby)->h[0xAA / 2] == 0xED4 /* moby class 3796 */)
                ((View *)vars)->f[0x100 / 4] = 1.0f;
            if (((View *)moby)->h[0xAA / 2] == 0xEE1 /* Receiver Bot */)
                ((View *)vars)->f[0x100 / 4] = 1.10000002f;
            if (((View *)vars)->b[0x3E8] != 0) {
                if (((View *)moby)->b[0x43] != 13)
                    StartAnimationBlended(moby, 13, 0, 10);
                SetMobyState(moby, 0, 1);
            } else {
                ((View *)vars)->h[0x392 / 2] = 0;
                SetMobyState(moby, 2, 2);
            }
        }
        break;
    }
    case 7: {
        s32 effectIndex;
        float savedRot;
        float blend;

        TryClaimNotice(6, 0, 20);
        if (SetSecondPendingFlag(moby) != 0)
            PlaySoundFromClassBank(6, 0, moby, 0xEE1 /* Receiver Bot */);
        if (((View *)vars)->i[0x3F0 / 4] != -1) {
            u8 *effect = gSoundState + ((View *)vars)->i[0x3F0 / 4] * 0x70;
            if (*(u8 **)(effect + 0x88) == moby && effect[0x74] != 0)
                goto have;
        }
        ((View *)vars)->i[0x3F0 / 4] = PlaySoundFromClassBank(9, 4, moby, 0xEE1 /* Receiver Bot */);
    have:
        UpdateColorFade(moby, vars + 0x50);
        ApproachTargetWithDirectionMode(moby + 0xF8,
                      FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - ((View *)moby)->f[0x10 / 4],
                                    ((Hero *)gHeroState)->f[0x84 / 4] - ((View *)moby)->f[0x14 / 4]),
                      vars + 0x1B4, 0, ((View *)vars)->f[0x114 / 4], ((View *)vars)->f[0x118 / 4], ((View *)vars)->f[0x11C / 4]);
        D_L18_001B2564[1] = 1;
        qcopy(cameraPos, gCameraPosition_L18);
        ((Hero *)gHeroState)->h[0x1DC / 2] = 5;
        ((Hero *)gHeroState)->h[0x1E0 / 2] = 10;
        if (FastDecTimer(vars + 0x396) != 0) {
            StoreLevelObjectValuePair(0, DrawTimerBarHud);
            ((View *)vars)->uh[0x3BC / 2] = ((View *)vars)->uh[0x3BE / 2];
            savedRot = ((View *)moby)->f[0xF8 / 4];
            if (((Hero *)gHeroState)->b[0x22B4] == 4) {
                if (gCurrentMapIndex == 0x14)
                    D_0013965E[0] = 1;
                DetachHeroFromObject(1);
            }
            ResetObjectColorGrey(moby);
            ((View *)moby)->b[0xBC] = 1;
            ((View *)vars)->i[0x13C / 4] = -1;
            ((View *)vars)->h[0x392 / 2] = 30;
            ClearMemory(D_L18_002571A0, 0, 0x50);
            AttachHeroToObject(4, 0x8D, moby);
            ((Hero *)gHeroState)->f[0x98 / 4] = savedRot;
            ((View *)moby)->f[0xF8 / 4] = savedRot;
            D_L18_001B2564[1] = 0;
            if (gCurrentMapIndex == 0x13) {
                if (((View *)gSubtitleHistory)->uh[0x504 / 2] == 0)
                    RequestSubtitleVoiceLine(0xA14, 0x6B);
                else
                    ((View *)gSubtitleHistory)->uh[0x504 / 2] = 0xFFFF;
            }
            D_L18_001AFBB0 = 0;
            SetMobyState(moby, 7, 8);
            effectIndex = ((View *)vars)->i[0x3F0 / 4];
            if (effectIndex != -1) {
                u8 *effect = gSoundState + effectIndex * 0x70;
                if (*(u8 **)(effect + 0x88) == moby && effect[0x74] != 0)
                    StopSoundVoice(effectIndex);
            }
            ((View *)vars)->i[0x3F0 / 4] = -1;
        }
        blend = 1.0f - IntToFloat(((View *)vars)->h[0x396 / 2]) / (float)D_L18_001B1290;
        if (blend > 1.0f)
            blend = 1.0f;
        else if (blend < 0.0f)
            blend = 0.0f;
        FastVecSub(tempVec, gHeroPosition, moby + 0x10);
        *(Vec4 *)offsetVec = *(Vec4 *)tempVec;
        offsetVec[2] = 0.0f;
        vec_scale_to_length(offsetVec, offsetVec, D_L18_001B1294);
        add_vectors(tempVec, offsetVec, moby + 0x10);
        offsetVec[2] += D_L18_001B1298;
        FastVecSub(tempVec, cameraPos, offsetVec);
        *(Vec4 *)dirVec = *(Vec4 *)tempVec;
        vec_scale_to_length(dirVec, dirVec, ((View *)vars)->f[0x3B8 / 4] * IntToFloat(((View *)vars)->h[0x396 / 2]));
        add_vectors(tempVec, dirVec, offsetVec);
        angles[2] = FastMatrixHelperA(((View *)moby)->f[0x10 / 4] - dirVec[0], ((View *)moby)->f[0x14 / 4] - dirVec[1]);
        angles[1] = -FastMatrixHelperA(vec_distance_xy(dirVec, moby + 0x10), ((View *)moby)->f[0x18 / 4] - dirVec[2]);
        angles[0] = D_L18_001B129C * (FastSinOrCosB(WrapAngleToPi(blend * 6.28318548f)) * 0.0174532942f);
        CopyVectorToSelectedObject(dirVec);
        SetCameraStateRotation(angles);
        if (((View *)moby)->b[0x95] == 8)
            SetCameraModeState(1);
        break;
    }
    case 8:
        TryClaimNotice(6, 0, 20);
        if ((((Hero *)gHeroState)->b[0x22B4] != 4 || ((Hero *)gHeroState)->p[0x2290 / 4] != moby) && ((View *)vars)->h[0x392 / 2] == 0) {
            if (((Hero *)gHeroState)->b[0x22B4] != 4)
                StoreLevelObjectValuePair(0, 0);
            D_L18_001AFBB0 = 0;
            ((View *)vars)->i[0x13C / 4] = ((View *)vars)->i[0x384 / 4];
            ((View *)vars)->i[0x37C / 4] = ((View *)vars)->i[0x360 / 4];
            ((View *)vars)->i[0x38C / 4] = -1;
            ((View *)moby)->b[0xBC] = 0;
            SetControllerSpeedLimits(moby, ((View *)vars)->f[0x3C4 / 4] * 0.000277777785f, ((View *)vars)->f[0x3C0 / 4] * 0.0166666675f,
                          ((View *)vars)->f[0x3D4 / 4] * 4.84813745e-06f, ((View *)vars)->f[0x3D0 / 4] * 0.000290888245f);
            ((View *)moby)->uh[0x34 / 2] &= 0xFFBE;
            enemyKind = GetEnemyKindIndex(moby);
            SpawnExplosionEffects(moby, D_L18_001A8F20, 0, 2.0f, (float)((View *)vars)->b[0x35], 5, 2, 9, 6.0f, 4.0f, 9.0f, 1.10000002f,
                          enemyKind, 0.0f, 1, 1, -2, 0, 0x850001);
            SetMobyState(moby, 11, -1);
        }
        break;
    }

    switch (((View *)moby)->b[0x20]) {
    case 1:
        StepMovementAtOwnPositionWithFactor(moby, FastMatrixHelperA(((View *)vars)->f[0x220 / 4] - ((View *)moby)->f[0x10 / 4],
                                        ((View *)vars)->f[0x224 / 4] - ((View *)moby)->f[0x14 / 4]));
        break;
    case 2:
        StepMovementAtOwnPosition(moby);
        if (((View *)vars)->h[0x392 / 2] == 0) {
            ((View *)vars)->h[0x392 / 2] = D_L18_001B1260;
            StartOrForwardAnimation(moby, 2, 0, 10.0f);
            SetMobyState(moby, 4, -1);
        }
        break;
    case 3:
        ApproachTargetWithDirectionMode(moby + 0xF8,
                      FastMatrixHelperA(((Hero *)gHeroState)->f[0x80 / 4] - ((View *)moby)->f[0x10 / 4],
                                    ((Hero *)gHeroState)->f[0x84 / 4] - ((View *)moby)->f[0x14 / 4]),
                      vars + 0x1B4, 0, ((View *)vars)->f[0x114 / 4], ((View *)vars)->f[0x118 / 4], ((View *)vars)->f[0x11C / 4]);
        if (((View *)moby)->b[0x60] & 2) {
            StartOrForwardAnimation(moby, 2, 0, 10.0f);
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        MoveReceiverBotTowardTarget(moby);
        break;
    case 5:
        if (AdjustJumpSpeedToTarget(moby, 7.0f, 32.0f, 37.0f) != 0) {
            if (RunSlotHandler(moby + 0x10, ((View *)vars)->i[0x380 / 4], 0) != 0) {
                ((View *)vars)->h[0x392 / 2] = 0;
                SetMobyState(moby, 0, 4);
            } else {
                s32 pathIndex;

                StartOrForwardAnimation(moby, 2, 0, 10.0f);
                pathIndex = ((View *)vars)->i[0x370 / 4];
                if (pathIndex != -1) {
                    SetObjectAnimation(moby, pathIndex, -1);
                    SetMobyState(moby, 4, 5);
                } else {
                    if (((View *)vars)->i[0x374 / 4] != -1)
                        SetObjectAnimation(moby, ((View *)vars)->i[0x374 / 4], -1);
                    else
                        ((View *)vars)->i[0x38C / 4] = -1;
                    SetMobyState(moby, 4, 6);
                }
            }
        }
        break;
    case 6:
        UpdateShooterRangedAttack(moby);
        break;
    case 12:
        enemyKind = GetEnemyKindIndex(moby);
        SpawnExplosionEffects(moby, D_L18_001A8F20, 0, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f,
                      enemyKind, 15.0f, 1, 1, -1, 0, 0x810001);
    case 11: {
        u16 slotBits;
        u8 *unusedPtr;
        u8 stateFlags;

        ReleaseSharedResource(moby);
        slotBits = ((View *)moby)->uh[0xB2 / 2];
        if (slotBits & 1) {
            u8 *slotFlags = D_0019B4A8 + (((s16)slotBits >> 1) + (gCurrentMapIndex << 10));
            if (((*slotFlags >> 4) & 7) != 7)
                *slotFlags += 0x10;
        } else {
            u8 *slotFlags = D_0019B4A8 + (((s16)slotBits >> 1) + (gCurrentMapIndex << 10));
            if ((*slotFlags & 7) != 7)
                *slotFlags += 1;
        }
        D_L18_0021DB40[1][((View *)moby)->h[0xB2 / 2]] = ((View *)moby)->b[0xB0] + 2;
        if (((View *)moby)->b[0xB0] == 0xFF || (!(D_L18_001B2660[((View *)moby)->b[0xB0]] & 0x80) && (D_0019B2E8[((View *)moby)->b[0xB0] + (gCurrentMapIndex << 4)] & 0x80)))
            D_L18_0021E7B0[1][((View *)moby)->h[0xB2 / 2]] = ((View *)moby)->b[0xB0] + 2;
        stateFlags = ((View *)vars)->b[0x3B1];
        if (stateFlags != 0 && stateFlags != 0xFE
            && (((View *)moby)->b[0xB0] == 0xFF || !(D_0019B2E8[((View *)moby)->b[0xB0] + (gCurrentMapIndex << 4)] & 0x80))) {
            WakeLinkedEnemy(moby);
        } else {
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    }
    TickEnemyTimers_L18(moby);
}
