#include "common.h"

typedef struct {
    float x, y, z, w;
} UpdateVec;
typedef struct {
    UpdateVec start, end, velocity;
    void *object;
    void *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} UpdateQuery;
typedef union {
    UpdateQuery query;
    struct {
        UpdateVec angles, adjusted, transform[4];
    } attachment;
} UpdateWorkspace;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    UpdateVec point, extra, normal;
} UpdateCollision;

extern char D_L00_001B2C00[] MACRO_ADDR;
extern UpdateCollision D_L00_001BF200;
extern char D_L00_001BF240[];

extern char D_00189E20[];
extern char *D_L00_001B8E10 __attribute__((nosda));
extern int D_L00_001A904C[] MACRO_ADDR;
extern int D_0018C0B4 __attribute__((nosda));
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001A8F00 __attribute__((sda));
extern float D_L00_001B0C98 __attribute__((sda));
extern char *D_L00_001B0CA0 __attribute__((sda));
extern int D_L00_001B0CA4 __attribute__((sda));
extern float D_L00_001B0CAC __attribute__((sda));
extern float D_L00_001B0CB0 __attribute__((sda));
extern int D_L00_001B2C10[] MACRO_ADDR;
extern int update_timer SDATA(D_L00_001B2C10);
extern int D_L00_001B2C14[] MACRO_ADDR;
extern int update_collision SDATA(D_L00_001B2C14);
extern int D_L00_001B2C18[] MACRO_ADDR;
extern int update_water SDATA(D_L00_001B2C18);
extern int D_L00_001B2C28[] MACRO_ADDR;
extern int update_handle SDATA(D_L00_001B2C28);

extern char *D_L00_001ADB2C[] MACRO_ADDR;
extern float D_L00_00254650[][2];
extern void func_L00_003252A8(void *, void *, int);
extern void func_002FE8D8(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern void func_00282F20(void *, void *, float);
extern void func_002B0CE0(int, int, int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_0029B758(int, void (*)(void *));
extern void func_L00_004003F0(void *);
extern void ref_L00_003FFBA0_00(void);
extern void func_L00_00402DB8(void);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_002C42E0(int, int);
extern void func_00335798(void *, void *, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_0032FDD0(void *), func_003309A0(void *), func_0032FEA8(void *);
extern void func_L00_00401D50(void *), func_00331718(void);
extern int func_00282948(void *);
extern int func_002FE9D0(UpdateQuery *);
extern int func_00300540(int);
extern void func_00282C88(void *);
extern float func_00282DF0(void *);
extern char *func_0032DA58(void *, void *, void *, float);
extern void func_00330CA0(void *);
extern void func_002FEE50(int), func_002FED28(int), func_0029F338(void *);
extern void func_00283658(void *, void *), func_002AB6D8(void *, void *);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002833F0(void *, void *), func_0032F598(void *);
extern void func_0027D098(void (*)(void *), void *);
extern void func_L00_00401FF0(void *);
extern void func_002A9288(void *, float);

#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define P(p, n) (*(char **)((char *)(p) + (n)))
#define STATE(p) (*(unsigned char *)((p) + 0x20))

/* Advances launch, grounded movement, falling and teardown states of a timed actor. */
/* Updates the Turret Spider Bot (moby class 3705): it is launched, moves along the ground, falls, and is removed when its time runs out. */
void func_L00_003FFBA0(char *obj)
{
    /* The query and attachment transform use the same workspace in separate phases. */
    struct {
        UpdateVec previous, ahead, behind;
        UpdateWorkspace workspace;
        UpdateVec rotation;
    } scratch;
    char *vars = P(obj, 0x68);
    int i, hit, action;
    float (*particles)[2];
    char *hero;

    if (STATE(obj) >= 2)
    ForwardObjectPositionCall(obj, D_L00_001B2C00, 1);
    else
    GetObjectFacingDirection(obj + 0x10, D_L00_001B2C00);
    FastVecScale(D_L00_001B2C00, D_L00_001B2C00, -1.0f);
    FastVecScale(&scratch.ahead, obj + 0xE0, D_L00_001B0CAC);
    FastVecAdd(&scratch.ahead, obj + 0x10, &scratch.ahead);
    FastVecScale(&scratch.behind, obj + 0xE0, -1.0f);
    FastVecAdd(&scratch.behind, obj + 0x10, &scratch.behind);
    if (CollLine(&scratch.ahead, &scratch.behind, 2, obj, 0)) {
        if (GetCollHitMaterial() == 2) {
            FastVecScale(D_L00_001B2C00, D_L00_001BF240, 0.0009765625f);
            vec_scale_to_length(D_L00_001B2C00, D_L00_001B2C00, -1.0f);
            D_L00_001B2C14[0] = 1;
        } else {
            update_collision = 0;
        }
        if (GetCollHitMaterial() == 6)
        update_water = 1;
        else
        update_water = 0;
    } else {
        update_collision = 0;
        D_L00_001B2C18[0] = 0;
    }
    ForceClaimNotice(6, 0, 1);
    switch (STATE(obj)) {
    case 0:
        STATE(obj) = 1;
        I(vars, 0x58) = 0;
        F(obj, 0x2C) = 0.00025f;
        I(obj, 0x98) = 0;
        particles = D_L00_00254650;
        for (i = 97; i >= 0; i--) {
            (*particles)[0] = RandomAngle();
            (*particles)[1] = RandomSignedFloatRange(720.0f, 2160.0f) * 0.00029088825f;
            particles++;
        }
        update_timer = 1800;
        if (D_L00_001A904C[0])
            StoreLevelObjectValuePair(0, DrawTurretSpiderBotTimer);
        /* fall through */
    case 1:
        hero = gHeroState;
        action = I(hero, 0x2294);
        if (action == 98 || D_L00_001A8F00 == 2 || action == 111 || action == 100 ||
            action == 99 || action == 23 || action == 24 || action == 129 || action == 39) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 7;
            ActivateLinkedObjectData();
            I(vars, 0x60) = 0;
            break;
        }
        F(obj, 0x2C) += 0.01f;
        if (F(obj, 0x2C) > 0.023f)
            F(obj, 0x2C) = 0.023f;
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        SteerEffectDirection(D_L00_001B2C28[0], vars, 0);
        TransformVectorOrCopy(obj + 0x10, obj + 0x10);
        TriggerCurrentStateEffect(vars, vars);
        AddObjectDirectionScaled(obj + 0x10, vars, 0.0030555557f);
        if (CollLine(&scratch.previous, obj + 0x10, 0, obj, 0)) {
            UpdateCollision *collision = &gCollisionResult;
            char *other = collision->hit;
            if (other && (other == P(hero, 0x2290) || *(short *)(other + 0xAA) == 0x907 /* Spiderbot Glove */))
                break;
            qcopy(obj + 0x10, &collision->point);
            ForceClaimNotice(6, 0, 1);
            SetHeroAction_L00(28, 1);
            SetupObjectEffectEntry(obj + 0x10, obj + 0xF0, obj);
            STATE(obj) = 2;
            StartAnimationBlended(obj, 1, 0, 10);
            I(obj, 0x48) = 0;
        }
        break;
    case 2:
        STATE(obj) = 3;
        PlayMobySound(2, 0, obj);
        if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 3:
        ReadClampedStickInput(obj);
        SteerHeadingTowardAim(obj);
        UpdateVehicleSpeedAndMove(obj);
        NotifyNearbyTypedObjects(obj);
        PlaySoundsOnThresholdCrossing();
        if (FastFloatHelperD(D_L00_001B2C10)) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (D_00138324 & 32) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 4:
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        AddObjectDirectionScaled(obj + 0x10, vars, 0.0061111115f);
        TransformVectorOrCopy(obj + 0x10, obj + 0x10);
        TriggerCurrentStateEffect(vars, vars);
        qcopy(&scratch.workspace.query.start, &scratch.previous);
        qcopy(&scratch.workspace.query.end, obj + 0x10);
        qcopy(&scratch.workspace.query.velocity, vars);
        scratch.workspace.query.radius = 0.2f;
        scratch.workspace.query.friction = 0.85f;
        scratch.workspace.query.bounce = 0.75f;
        scratch.workspace.query.response = 1;
        scratch.workspace.query.object = obj;
        scratch.workspace.query.ignore = 0;
        scratch.workspace.query.ignoreCount = 0;
        scratch.workspace.query.flags = 0;
        scratch.workspace.query.mask = 0;
        scratch.workspace.query.gravity = 0;
        hit = CollideSweptSphere(&scratch.workspace.query);
        qcopy(obj + 0x10, &scratch.workspace.query.end);
        qcopy(vars, &scratch.workspace.query.velocity);
        if (hit == 2) {
            if (GetWeaponGroup(scratch.workspace.query.surface) || scratch.workspace.query.surface == 12) {
                STATE(obj) = 9;
                I(vars, 0x60) = 10;
            } else {
                STATE(obj) = 2;
                ClearVector128(vars);
            }
        } else if (FastVecLength(vars) > 0.4f) {
            STATE(obj) = 9;
            I(vars, 0x60) = 10;
        }
        break;
    case 9:
        STATE(obj) = 5;
        ActivateLinkedObjectData();
        /* fall through */
    case 5:
        if (FastFloatHelperD(vars + 0x60)) {
            PlayMobySound(1, 0, obj);
            vec_scale_to_length(&scratch.rotation, obj + 0xC0, 1.0f);
            SpawnBlastEffectMoby(obj, obj + 0x10, &scratch.rotation, F(obj, 0x18));
            STATE(obj) = 6;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
                ref_L00_003FFBA0_00();
                I(vars, 0x60) = 0;
            } else
                I(vars, 0x60) = D_L00_001B0CA4;
            I(vars, 0x64) = 0;
        }
        break;
    case 6:
        QueueRadialMobyImpacts(obj);
        F(vars, 0x64) += D_L00_001B0C98 * 0.016666668f;
        if (FastFloatHelperD(vars + 0x60) && !I(vars, 0x68))
            STATE(obj) = 8;
        break;
    case 7:
        if (FastFloatHelperD(vars + 0x60))
            STATE(obj) = 8;
        break;
    case 8:
        if (D_0018C0B4 == 28)
            SetHeroAction_L00(0, 1);
        if (*(short *)(gFollowCameraObject + 0x86) == 27)
            ref_L00_003FFBA0_00();
        ClearEntryFlag(update_handle);
        FreeSlot(I(vars, 0x6C));
        FreeSlot(I(vars, 0x70));
        FreeSlot(I(vars, 0x74));
        D_L00_001B0CA0 = 0;
        StoreLevelObjectValuePair(0, 0);
        MarkMobySpawned(obj);
        return;
    }
    if (STATE(obj) >= 2 && D_L00_001ADB2C[0]) {
        copy_matrix_rotation(scratch.workspace.attachment.transform, obj + 0xC0);
        GetEulerAnglesFromMatrix(scratch.workspace.attachment.transform, &scratch.workspace.attachment.angles);
        TransformPointAndRotationByParent(obj, D_L00_001ADB2C[0], obj + 0x10,
                     &scratch.workspace.attachment.angles, obj + 0x10,
                     &scratch.workspace.attachment.adjusted);
        euler_rotation_basis(obj + 0xC0, &scratch.workspace.attachment.adjusted);
    }
    if ((unsigned int)(STATE(obj) - 2) < 2)
        UpdateVehicleGunAiming(obj);
    RegisterFinalDrawCallback(func_L00_00401FF0, obj);
    QueueGroundShadow(obj, D_L00_001B0CB0);
}
