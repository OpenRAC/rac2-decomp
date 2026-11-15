/* func_L00_0038BF18 (27 places), in a unit of its own for its profile:
   -O2 -G8 -ffunction-sections -frac2-keep-block-order -frac2-hazard-labels.
   keep-block-order puts case 0 before the 10/11 body, as retail's `b` to it requires;
   hazard-labels keeps the threshold chain's join label on the mtc1 hazard nop.
   The two quadword clears are qzero_nc: retail recomputes the hero address and reloads
   1.0f right after each `sq $zero`, which is CSE forgetting its table at a volatile asm
   with no clobber. The stack is one vec[8][4] scratch array, since this compiler never
   shares stack slots between block-scope locals. The arm offset `pv + 0x40` is written
   out at each use: gcse then carries it in one register across both arms (retail's s5),
   which is what leaves %hi(D_00189E20) in s6. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* the level-class table entry, 0xE0 bytes */
typedef struct {
    u8 pad0[0x70];
    f32 f70;
    f32 f74;
    u8 pad78[0x68];
} LevelClass;

/* the camera-mode table entry, 0x2C bytes */
typedef struct {
    s32 i0;
    s32 i4;
    u8 pad8[0x14];
    s32 i1C;
    s32 i20;
    u8 pad24[8];
} CamMode;

/* the collision query's result */
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
} CollResult;

/* the query passed to the collision tests */
typedef struct {
    f32 v[4];
    char *moby;
    s32 mask;
    s8 b18;
    s8 b19;
    u16 h1A;
    f32 f1C;
    s32 i20;
} CollQuery;

extern char D_00189E20[];
extern u8 D_00139568[];
extern u8 D_00188660[];
extern LevelClass D_L00_00262570[];
extern CamMode D_L00_0025D990[];
extern CollResult D_L00_001BF200 __attribute__((aligned(16)));
extern char *D_L00_001C3280 __attribute__((nosda));
extern int D_001A72C0;

extern void func_00273318(void *, int, int, int, int, int, float, float, float);
/* The binder: func_L00_002E6EF8 in 23 programs, its twin func_L08_002F2D10 in levels 08, 09,
   19 and 30, so the call carries a name without an address. */
extern void ref_L00_0038BF18_00(void *, void *);
extern void func_L00_0038B208(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0038B6F8(char *);
extern void func_0029FCC0(void *, int, void *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_L00_0038BE70(char *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern int func_L00_0031F220(char *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_0038BA80(char *);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern int func_L00_002B3998(float);
extern void func_L00_002D3778(void *, void *, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002AFD88(void *, void *, float, float, float);
extern int func_L00_0031C3D0(char *, char *, char *, char *, void *, void *, int);
extern int func_L00_0038B848(void);
extern int func_L00_0038B7F8(void);
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_L00_00322BE0(void *, int);
extern void func_L00_00322A18(void *, float, float, float);
extern int func_00282948(void *);
extern float func_002A89A8(void *, int, float);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_0038BD00(char *);
extern void func_L00_002D24D0(int);
extern void func_002E59F8(int);
extern int func_L00_002B9B88(int, int);
extern void func_L00_00322EC8(void *);
extern int func_002ABB78(char *);
extern float *func_002AB1F0(char *);
extern void func_L00_0031D670(void *, void *, void *, float);
extern void func_L00_0038B888(void *, int);


/* Updates the hero's wrench object: checks what the swing hits, and handles the throw out and the return to the hero. */
void func_L00_0038BF18(char *moby)
{
    f32 vectors[8][4] __attribute__((aligned(16)));
    char *vars;
    float angle;
    char *heroMoby;
    char *heroMobyCheck;
    char *hitClass;
    char *mode;
    char *pos;
    char *sound;
    float *link;
    float yaw;
    float yawDiff;
    float lim;
    float range;
    float pull;
    float reachScale;
    float distanceToHero;
    float mobyZ;
    float checkRadius;
    float groundZ;
    LevelClass *levelClass;
    CamMode *camMode;
    int canHit;
    int swingAllowed;
    int didHit;
    int arrived;
    int tooFar;

    vars = *(char **)(moby + 0x68);
    ((Hero *)gHeroState)->b[0x123C] = 0;
    if (((Hero *)gHeroState)->i[0x1244 / 4] == 3) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(void **)(moby + 0xB8) = ((Hero *)gHeroState)->ptr[0x2290 / 4];
        if ((((Hero *)gHeroState)->i[0x2294 / 4] == 1 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x1D)
            && (*(u16 *)((char *)((Hero *)gHeroState)->ptr[0x2290 / 4] + 0x34) & 1)) {
            AddMobyMarker(moby, 0xFF917267, 0, 0x25, -1, 4, 1.0f, 0.0f, 90.0f);
        }
        if (vars != 0 && *(f32 *)(vars + 0x70) != 0.0f) {
            ref_L00_0038BF18_00(UpdateTrailStrips, moby);
        }
        if (D_001A72C0 == 0) {
            *(u16 *)(moby + 0x34) &= ~0x10;
        } else {
            *(u32 *)(moby + 0x78) = 0x80909090;
            *(u16 *)(moby + 0x34) |= 0x10;
        }
        if (*(u8 *)(moby + 0x43) != 0) {
            if (*(u8 *)(moby + 0x43) == 0xE) {
                if (*(u8 *)(moby + 0x60) & 2) {
                    StartAnimationBlended(moby, 1, 0, 5);
                }
                return;
            }
            if (((Hero *)gHeroState)->b[0x22BE] != 0) {
                if ((u8)(*(u8 *)(moby + 0x43) - 0xF) >= 2) {
                    StartAnimationBlended(moby, 0xF, 0, 4);
                } else if ((*(u8 *)(moby + 0x60) & 2) && *(u8 *)(moby + 0x43) == 0xF) {
                    StartAnimationBlended(moby, 0x10, 0, 5);
                }
                return;
            }
            if ((u8)(*(u8 *)(moby + 0x43) - 0xF) < 2) {
                StartAnimationBlended(moby, 0xE, 0, 2);
                return;
            }
        }
        if ((*(u8 *)(moby + 0x60) & 2) && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x37 && ((Hero *)gHeroState)->i[0x229C / 4] != 0x22
            && *(u8 *)(moby + 0x43) != 1) {
            StartAnimationBlended(moby, 1, 0, 5);
        }
        SyncWeaponAnimToHero(moby);
        if (((Hero *)gHeroState)->i[0x2294 / 4] != 0x13 && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x20 && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x2A
            && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x6D && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x14
            && *(u8 *)(moby + 0x43) >= 3 && *(u8 *)(moby + 0x43) < 6) {
            StartAnimationBlended(moby, 1, 0, 4);
        }
        heroMoby = ((Hero *)gHeroState)->ptr[0x2290 / 4];
        if (*(u8 *)(heroMoby + 0x43) != *(u8 *)(heroMoby + 0x42) || *(u8 *)(heroMoby + 0x41) - *(u8 *)(heroMoby + 0x40) >= 3) {
            *(u16 *)(vars + 0x74) += 1;
        }
        *(f32 *)(moby + 0x48) = ((Hero *)gHeroState)->f[0xC20 / 4];
        camMode = &D_L00_0025D990[((Hero *)gHeroState)->h[0xBFC / 2]];
        if (((Hero *)gHeroState)->i[0x229C / 4] != 6 && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x2A) {
            return;
        }
        canHit = 1;
        if (((Hero *)gHeroState)->i[0xC2C / 4] != 0 || ((Hero *)gHeroState)->f[0xC38 / 4] < (f32)camMode->i1C || (f32)camMode->i20 < ((Hero *)gHeroState)->f[0xC38 / 4]) {
            canHit = 0;
        }
        swingAllowed = 0;
        if (*(s16 *)(vars + 0x7C) != *(s16 *)(vars + 0x74)) {
            heroMobyCheck = ((Hero *)gHeroState)->ptr[0x2290 / 4];
            if (*(u8 *)(heroMobyCheck + 0x42) == *(u8 *)(heroMobyCheck + 0x43)) {
                if (*(u8 *)(heroMobyCheck + 0x42) == 0x17) {
                    swingAllowed = 1;
                    if (!(0.0f <= ((Hero *)gHeroState)->f[0xC38 / 4])) {
                        swingAllowed = 0;
                    }
                } else if (*(u8 *)(heroMobyCheck + 0x42) == 0x18) {
                    swingAllowed = 1;
                    if (!(0.0f <= ((Hero *)gHeroState)->f[0xC38 / 4])) {
                        swingAllowed = 0;
                    }
                } else if (*(u8 *)(heroMobyCheck + 0x42) == 0x19) {
                    swingAllowed = 1;
                    if (!(12.0f <= ((Hero *)gHeroState)->f[0xC38 / 4])) {
                        swingAllowed = 0;
                    }
                } else if (*(u8 *)(heroMobyCheck + 0x42) == 0x2B) {
                    swingAllowed = 1;
                    if (!(23.0f <= ((Hero *)gHeroState)->f[0xC38 / 4])) {
                        swingAllowed = 0;
                    }
                }
            }
        }
        if (swingAllowed != 0) {
            *(f32 *)(vars + 0x70) = 1.0f;
            *(s16 *)(vars + 0x7C) = *(s16 *)(vars + 0x74);
        }
        yawDiff = 0.0f;
        yaw = ((Hero *)gHeroState)->f[0x98 / 4];
        qcopy(&((Hero *)gHeroState)->b[0xB90], &((Hero *)gHeroState)->b[0xB70]);
        qcopy(&((Hero *)gHeroState)->b[0xB80], &((Hero *)gHeroState)->b[0xB60]);
        TransformMobyJointToWorld(moby, 1, &((Hero *)gHeroState)->b[0xB70]);
        TransformMobyJointToWorld(((Hero *)gHeroState)->ptr[0x2290 / 4], 0, &((Hero *)gHeroState)->b[0xB60]);
        if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x13 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x6D || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x2A) {
            yaw = FastMatrixHelperA(((Hero *)gHeroState)->f[0xB70 / 4] - ((Hero *)gHeroState)->f[0x80 / 4], ((Hero *)gHeroState)->f[0xB74 / 4] - ((Hero *)gHeroState)->f[0x84 / 4]);
            if (D_L00_0025D990[((Hero *)gHeroState)->h[0xBFC / 2]].i4 == 1) {
                yaw = FastAddRotations(yaw, -1.57079649f);
            } else {
                yaw = FastAddRotations(yaw, 1.57079649f);
            }
        }
        {
            FastVecSub(vectors[0], &((Hero *)gHeroState)->b[0xB70], &((Hero *)gHeroState)->b[0xB60]);
            vec_scale_to_length(vectors[0], vectors[0], FastVecLength(vectors[0]) + 0.17f);
            if (((Hero *)gHeroState)->i[0x229C / 4] != 0xF && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x6D && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x14) {
                yawDiff = FastDiffRots(((Hero *)gHeroState)->f[0x98 / 4],
                                     FastMatrixHelperA(((Hero *)gHeroState)->f[0xB70 / 4] - ((Hero *)gHeroState)->f[0x80 / 4],
                                                   ((Hero *)gHeroState)->f[0xB74 / 4] - ((Hero *)gHeroState)->f[0x84 / 4]));
                if (yawDiff > 1.57079649f) {
                    canHit = 0;
                }
                ScaleVectorByAngleLimit((char *)vectors[0]);
            }
            FastVecAdd(&((Hero *)gHeroState)->b[0xB70], &((Hero *)gHeroState)->b[0xB60], vectors[0]);
            if (((Hero *)gHeroState)->i[0x2294 / 4] != 0x2A && ((Hero *)gHeroState)->i[0x2294 / 4] != 0x6D && yawDiff < 1.22173059f
                && ((Hero *)gHeroState)->i[0x1B8 / 4] >= 11) {
                qcopy(vectors[0], &((Hero *)gHeroState)->b[0x80]);
                vectors[0][2] = vectors[0][2] + 0.5f;
                angle = FastMatrixHelperA(((Hero *)gHeroState)->f[0xB70 / 4] - ((Hero *)gHeroState)->f[0x80 / 4], ((Hero *)gHeroState)->f[0xB74 / 4] - ((Hero *)gHeroState)->f[0x84 / 4]);
                qcopy(vectors[1], &((Hero *)gHeroState)->b[0x80]);
                vectors[1][2] = vectors[1][2] + 0.5f;
                vectors[2][0] = FastSinOrCosA(angle) * 1.4f;
                vectors[2][1] = FastSinOrCosB(angle) * 1.4f;
                vectors[2][2] = 0.0f;
                ScaleVectorByAngleLimit((char *)vectors[2]);
                FastVecAdd(vectors[1], vectors[1], vectors[2]);
                if (((Hero *)gHeroState)->h[0xBFE / 2] == 0 && CollLine(vectors[0], vectors[1], 2, 0, 0) != 0 && GetCollHitMaterial() != 0
                    && (gCollisionResult.moby == 0 || IsMobyMissingOrClass502(gCollisionResult.moby) != 0)) {
                    ((Hero *)gHeroState)->h[0xBFE / 2] = 1;
                    PlayMobySound(2, 0, moby);
                    SpawnWeaponImpactSparks(moby);
                    if (gCollisionResult.moby != 0) {
                        if (((Hero *)gHeroState)->b[0x22C3] == 0) {
                            vectors[3][0] = FastSinOrCosA(yaw);
                            vectors[3][1] = FastSinOrCosB(yaw);
                            vectors[3][2] = 0.0f;
                        } else {
                            qcopy(vectors[3], &((Hero *)gHeroState)->b[0]);
                        }
                        QueueImpactEffect(gCollisionResult.moby, moby, 0x10000, gCollisionResult.pos, vectors[3], 1.0f);
                    }
                }
            }
            if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x14 && IsBelowPlaneWithinDepth(27.0f) != 0) {
                PlayMobySound(2, 0, moby);
                qcopy(vectors[0], &((Hero *)gHeroState)->b[0xB70]);
                qcopy(vectors[1], vectors[0]);
                ApplyHeroModeTransformReversed(vectors[0], vectors[0], 0.7f);
                ApplyHeroModeTransformReversed(vectors[1], vectors[1], -0.9f);
                if (CollLine(vectors[0], vectors[1], 2, 0, 0) != 0) {
                    SpawnWeaponImpactSparks(moby);
                }
            }
        }
        if (canHit != 0) {
            levelClass = &gWeaponTable_L00[gItemSlotToRecord[0xA]];
            reachScale = 1.0f;
            range = levelClass->f70;
            if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x14) {
                range = levelClass->f74;
                reachScale = 1.55f;
            }
            vectors[3][0] = FastSinOrCosA(yaw);
            vectors[3][1] = FastSinOrCosB(yaw);
            vectors[3][2] = 0.0f;
            make_hit_descriptor(vectors[0], moby, 0x10000, vectors[3], range);
            FastVectorNormalizeHelper(vectors[0], vectors[0], reachScale);
            vectors[0][2] = 1.0f;
            vectors[0][3] = 5627.9248f;
            ((CollQuery *)vectors[0])->b19 = 1;
            ((CollQuery *)vectors[0])->h1A = *(u16 *)(moby + 0xAA);
            ((CollQuery *)vectors[0])->b18 = 0;
            if (((Hero *)gHeroState)->b[0x22C3] != 0) {
                qzero_nc(vectors[3]);
                AddTransformedPointToVector(((Hero *)gHeroState)->ptr[0x2290 / 4], vectors[3], 1.0f, 0.0f, 1.0f);
            }
            if (SweepSegmentForHit(&((Hero *)gHeroState)->b[0xB60], &((Hero *)gHeroState)->b[0xB70], &((Hero *)gHeroState)->b[0xB80], &((Hero *)gHeroState)->b[0xB90],
                                  ((Hero *)gHeroState)->ptr[0x2290 / 4], (CollQuery *)vectors[0], 5) != 0
                && gCollisionResult.moby != 0 && IsCurrentRecordFlagSet() == 0 && ((Hero *)gHeroState)->h[0xBFE / 2] == 0
                && (gCollisionResult.moby == 0 || *(char **)(gCollisionResult.moby + 0x24) == 0
                    || *(s16 *)(*(char **)(gCollisionResult.moby + 0x24) + 0x46) != 0x14)) {
                ((Hero *)gHeroState)->h[0xBFE / 2] = 1;
                PlayMobySound(IsCurrentRecordByteOne(), 0, moby);
                SpawnWeaponImpactSparks(moby);
            }
            FastVecSub(vectors[5], &((Hero *)gHeroState)->b[0xB70], &((Hero *)gHeroState)->b[0xB60]);
            vec_scale_to_length(vectors[5], vectors[5], FastVecLength(vectors[5]) - 0.085f);
            FastVecAdd(vectors[4], vectors[5], &((Hero *)gHeroState)->b[0xB60]);
            checkRadius = 0.35f;
            if (((Hero *)gHeroState)->i[0x229C / 4] == 0xF) {
                checkRadius = 0.7f;
            }
            if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x14) {
                checkRadius = 0.47f;
            }
            if (ProcessCollisionHit(checkRadius, vectors[4], 0, ((Hero *)gHeroState)->ptr[0x2290 / 4], (CollQuery *)vectors[0]) == 0) {
                return;
            }
            if (gAreaHitTargets != 0 && *(char **)(gAreaHitTargets + 0x24) != 0
                && *(s16 *)(*(char **)(gAreaHitTargets + 0x24) + 0x46) == 0x12) {
                return;
            }
            if (IsCurrentRecordFlagSet() != 0) {
                return;
            }
            if (((Hero *)gHeroState)->h[0xBFE / 2] != 0) {
                return;
            }
            ((Hero *)gHeroState)->h[0xBFE / 2] = 1;
            PlayMobySound(IsCurrentRecordByteOne(), 0, moby);
            SpawnWeaponImpactSparks(moby);
        }
        break;
    case 10:
    case 11: {
        UpdateTransformHistoryFollowers(&((Hero *)gHeroState)->b[0x1A30], 0);
        *(void **)(moby + 0xB8) = ((Hero *)gHeroState)->ptr[0x2290 / 4];
        ((Hero *)gHeroState)->b[0x123C] = 2;
        if (*(u8 *)(moby + 0x20) == 10) {
            sound = (char *)gSoundState + ((Hero *)gHeroState)->i[0x2430 / 4] * 0x70;
            if (*(void **)(sound + 0x88) != ((Hero *)gHeroState)->ptr[0x2290 / 4] || *(u8 *)(sound + 0x74) == 0) {
                ((Hero *)gHeroState)->i[0x2430 / 4] = PlayMobySound(0xB, 4, ((Hero *)gHeroState)->ptr[0x2290 / 4]);
            }
        }
        ApplyOffsetToObjectMatrix(moby, 0.0f, 0.0f, 0.40724355f);
        if (((Hero *)gHeroState)->h[0xBFE / 2] != 0 && FastFloatHelperD(vars + 0x6C) != 0) {
            ((Hero *)gHeroState)->h[0xBFE / 2] = 0;
        }
        pos = moby + 0x10;
        if (((Hero *)gHeroState)->b[0x22C3] == 0) {
            groundZ = ProbeGroundHeightBelow(pos, 0, 0.5f);
            mobyZ = *(f32 *)(moby + 0x18);
            if (mobyZ - groundZ < 0.8f) {
                groundZ = groundZ + 0.55f;
                if (mobyZ < groundZ) {
                    ApproachValue((f32 *)(moby + 0x18), groundZ, 0.06666667f);
                } else {
                    ApproachValue((f32 *)(moby + 0x18), groundZ, 0.016666668f);
                }
            }
        }
        qcopy(vectors[0], pos);
        if (*(u8 *)(moby + 0x20) == 10) {
            qcopy(vectors[1], &((Hero *)gHeroState)->b[0x150]);
            FastVecScale(vectors[1], vectors[1], 0.98f);
            FastVecAdd(pos, pos, vectors[1]);
            vec_scale_to_length(vectors[1], vars + 0x40, *(f32 *)(vars + 0x60));
            FastVecAdd(pos, pos, vectors[1]);
            *(f32 *)(vars + 0x64) = *(f32 *)(vars + 0x64) + 0.000787037017f;
            ApproachValue((f32 *)(vars + 0x60), 0.0f, *(f32 *)(vars + 0x64));
            if (*(f32 *)(vars + 0x60) == 0.0f) {
                *(u8 *)(moby + 0x20) = 11;
            }
        } else {
            qcopy(vectors[1], &((Hero *)gHeroState)->b[0x150]);
            FastVecScale(vectors[1], vectors[1], 0.98f);
            arrived = 0;
            FastVecAdd(pos, pos, vectors[1]);
            TriggerNearbyObjectResponse(moby);
            FastVecSub(vectors[1], &((Hero *)gHeroState)->b[0x1200], pos);
            *(f32 *)(vars + 0x64) = *(f32 *)(vars + 0x64) + 0.00025f;
            *(f32 *)(vars + 0x60) = *(f32 *)(vars + 0x60) + *(f32 *)(vars + 0x64);
            distanceToHero = FastVecLength(vectors[1]);
            if (distanceToHero / *(f32 *)(vars + 0x60) < 5.0f && *(u8 *)(moby + 0x43) != 1) {
                StartAnimationBlended(moby, 1, 0, 5);
            }
            if (distanceToHero <= *(f32 *)(vars + 0x60)) {
                *(f32 *)(vars + 0x60) = distanceToHero;
                arrived = 1;
            }
            vec_scale_to_length(vectors[1], vectors[1], *(f32 *)(vars + 0x60));
            FastVecAdd(pos, pos, vectors[1]);
            if (distanceToHero / *(f32 *)(vars + 0x60) < 4.0f && ((Hero *)gHeroState)->i[0xC40 / 4] != -1) {
                SetHeroAnimationMode(2);
                ((Hero *)gHeroState)->i[0xC44 / 4] = 0x1A;
                if (((Hero *)gHeroState)->i[0x2430 / 4] != -1) {
                    sound = (char *)gSoundState + ((Hero *)gHeroState)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(sound + 0x88) == ((Hero *)gHeroState)->ptr[0x2290 / 4] && *(u8 *)(sound + 0x74) != 0) {
                        StopSoundVoice(((Hero *)gHeroState)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)gHeroState)->i[0x2430 / 4] = -1;
            }
            tooFar = 0;
            if (((Hero *)gHeroState)->i[0x2294 / 4] == 0x31 || ((Hero *)gHeroState)->i[0x2294 / 4] == 0x61 || distanceToHero > 32.0f) {
                tooFar = 1;
            }
            if (arrived != 0 || tooFar != 0) {
                if (tooFar == 0) {
                    PlayHeroSound(5, 0);
                }
                if (((Hero *)gHeroState)->i[0x2430 / 4] != -1) {
                    sound = (char *)gSoundState + ((Hero *)gHeroState)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(sound + 0x88) == ((Hero *)gHeroState)->ptr[0x2290 / 4] && *(u8 *)(sound + 0x74) != 0) {
                        StopSoundVoice(((Hero *)gHeroState)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)gHeroState)->i[0x2430 / 4] = -1;
                ReleaseSlotList(&((Hero *)gHeroState)->b[0x1A30]);
                ((Hero *)gHeroState)->b[0x123A] = 0;
                *(u8 *)(moby + 0x20) = 0;
            }
        }
        didHit = 0;
        if (CollLine(vectors[0], pos, 2, 0, 0) != 0 && GetCollHitMaterial() != 0
            && (gCollisionResult.moby == 0 || IsMobyInSpecialClassRange(gCollisionResult.moby) == 0)) {
            didHit = gCollisionResult.count != 0;
        }
        if (didHit != 0 || *(s16 *)(vars + 0x76) != 0) {
            *(s16 *)(vars + 0x76) = 0;
            if (((Hero *)gHeroState)->h[0xBFE / 2] == 0) {
                *(int *)(vars + 0x6C) = 0x1E;
                ((Hero *)gHeroState)->h[0xBFE / 2] = 1;
                PlayMobySound(2, 0, moby);
            }
            if (*(u8 *)(moby + 0x20) == 10) {
                SpawnWeaponImpactSparks(moby);
                *(f32 *)(vars + 0x60) = *(f32 *)(vars + 0x60) * 0.5f;
                *(u8 *)(moby + 0x20) = 11;
            }
        }
        pull = 1.2f;
        if (*(u8 *)(moby + 0x20) == 11) {
            pull = -0.37f;
        }
        vec_scale_to_length(vectors[4], vars + 0x40, pull);
        make_hit_descriptor(vectors[1], moby, 0x10000, vectors[4], (&gWeaponTable_L00[gItemSlotToRecord[0xA]])->f70);
        vectors[1][2] = 1.0f;
        if (((Hero *)gHeroState)->b[0x22C3] != 0) {
            qzero_nc(vectors[1]);
            AddTransformedPointToVector(((Hero *)gHeroState)->ptr[0x2290 / 4], vectors[1], pull, 0.0f, 1.0f);
        }
        vectors[1][3] = 5627.9248f;
        ((CollQuery *)vectors[1])->b19 = 1;
        ((CollQuery *)vectors[1])->h1A = ((Hero *)gHeroState)->uh[0xC0C / 2] + 1;
        ((CollQuery *)vectors[1])->b18 = 0;
        TransformMobyJointToWorld(moby, 1, vectors[5]);
        if ((ProcessCollisionHit(0.4f, vectors[5], 0, ((Hero *)gHeroState)->ptr[0x2290 / 4], (CollQuery *)vectors[1]) != 0
             || (TransformMobyJointToWorld(moby, 0, vectors[5]), ProcessCollisionHit(0.4f, vectors[5], 0, ((Hero *)gHeroState)->ptr[0x2290 / 4], (CollQuery *)vectors[1]) != 0))
            && ((Hero *)gHeroState)->h[0xBFE / 2] == 0 && gCollisionResult.moby != 0) {
            hitClass = *(char **)(gCollisionResult.moby + 0x24);
            if (hitClass == 0 || *(s16 *)(hitClass + 0x46) != 0x14) {
                link = GetMobyPrivateValue0(gCollisionResult.moby);
                if (link == 0 || *(s16 *)((char *)link + 0x1C) == 0 || *(char **)((char *)link + 0x18) != moby) {
                    *(TI128 *)vectors[7] = *(TI128 *)(gCollisionResult.moby + 0x10);
                    LerpVector4(vectors[6], vectors[5], vectors[7], 0.5f);
                    SpawnSparkBurst_L00_2(vectors[6], 5);
                    *(int *)(vars + 0x6C) = 0x1E;
                    ((Hero *)gHeroState)->h[0xBFE / 2] = 1;
                    PlayMobySound(IsCurrentRecordByteOne(), 0, moby);
                }
            }
        }
        break;
    }
    }
}
