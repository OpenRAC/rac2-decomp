#include "common.h"

typedef unsigned int LaunchQuad __attribute__((mode(TI)));
typedef union {
    LaunchQuad q;
    float f[4];
} LaunchVec;

/* A path: point count, then the points. */
typedef struct {
    int count;
    char pad04[12];
    LaunchVec points[0];
} AranosLaunchPath;

/* One entry of the pose table: position at 0x30, rotation at 0x70. */
typedef struct {
    char pad00[0x30];
    LaunchVec position;
    char pad40[0x30];
    LaunchVec rotation;
} AranosLaunchPose;

/* The object's context block (obj->ctx). */
typedef struct LaunchMoby LaunchMoby;
typedef struct {
    int flag;
    int pose;
    int cue;
    char pad0C[4];
    int target;
    int pathIndex;
    LaunchMoby *child;
    float speed;
    int pointIndex;
} AranosLaunchCtx;

/* The launch object and the child it drives. */
struct LaunchMoby {
    char pad00[0x10];
    LaunchVec position;
    unsigned char state;
    char pad21[0xF];
    unsigned char f30;
    char pad31;
    short f32;
    unsigned short flags;
    char pad36[0x32];
    AranosLaunchCtx *ctx;
    char pad6C[0x29];
    unsigned char f95;
    unsigned short timer;
    int f98;
    char pad9C[0x24];
    char matrix[0x30];
    LaunchVec rotation;
};

typedef struct {
    char pad00[0x80];
    char flagBits[0x2214];
    int state;
    char pad2298[0x234];
    int count;
} AranosLaunchHero;

extern AranosLaunchPose *D_L00_001B1F8C __attribute__((sda));
extern AranosLaunchPath *D_L00_001FDA80[];
extern LaunchMoby *D_L00_00220DA0[];
extern int D_L00_001B1A50 __attribute__((sda));
extern int D_L00_001B19C8 __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern int D_L00_001BF154;
/* Declared as arrays (a flags word and a 3-float vector) so struct-field accesses are not reordered around them. */
extern unsigned int D_00139788[];
extern unsigned int D_001A7424 __attribute__((sda));
extern float D_L00_001B18E0 __attribute__((sda));
extern float D_L00_001B24B0[4] __attribute__((sda));
extern char D_L00_001BEFC0[];
extern char D_L00_001AED10[];
extern AranosLaunchHero D_00189E20;

extern int func_002F5D10(void);
extern int func_00288D58(void);
extern int func_002B3868(void *);
extern int func_L00_00429048(int);
extern int func_L00_002D40F0(void);
extern int func_0029B3E0(int, int);
extern int func_002ACBC8(char *, unsigned int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_002E6178(void *);
extern void func_L00_00429020(int);
extern void func_002A7750(void *, int, int);
extern void func_002ED260(int);
extern void func_002AD7B8(int);
extern void func_L00_003672F8(void);
extern void func_002B37E8(void *, void *);
extern LaunchMoby *func_0029EFD0(int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern int func_L00_0035F5A0(int, int, int);
extern void func_0026FEB8(const char *, ...);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E80(void *, void *);
extern void func_002833F0(char *, char *);
extern void func_002F5CC8(void);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L00_003618D8(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002D40A0(void *, int, float);
extern void func_L00_0042A500(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_00383958(void *);

/* State machine for the launch object: drives its child along a path, then hands off to the next state. */
void func_L00_00383300(LaunchMoby *obj) {
    LaunchVec offset;
    AranosLaunchCtx *ctx = obj->ctx;
    AranosLaunchPath *path;
    int i;
    float angle;

    switch (obj->state) {
    case 0: {
        LaunchMoby *child;
        AranosLaunchPath *initialPath;

        if (IsFlagByteSet())
            MarkFlagAndAppendToList(0x18);
        SetFlagToOne();
        if (ctx->pose != -1)
            ResetHeroPositionAndDirection(&D_L00_001B1F8C[ctx->pose].position, &D_L00_001B1F8C[ctx->pose].rotation, 0, 1);
        InitChildObjectFromParent(ctx->child = CreateMoby(0xD54 /* moby class 3412 */), obj);
        initialPath = D_L00_001FDA80[ctx->pathIndex];
        /* The copies write only the child position, so the no-clobber form is enough. */
        qcopy_nc(&ctx->child->position, &initialPath->points[0]);
        SpawnEquipmentPieces(ctx->child);
        child = ctx->child;
        qcopy_nc(&child->position, &initialPath->points[0]);
        child->f32 = 0x28F;
        ctx->child->rotation.f[2] = FastMatrixHelperA(initialPath->points[1].f[0] - obj->position.f[0],
                                                  initialPath->points[1].f[1] - obj->position.f[1]);
        euler_rotation_basis(ctx->child->matrix, (char *)&ctx->child->rotation);
        ctx->pointIndex = 0;
        obj->f30 = 0xFF;
        if (!(D_00139788[0] & 2) && gHeroState.state != 0x1C && gHeroState.count > 0 && !D_L00_001A8F00 &&
            (ctx->flag == -1 || IsPointInCuboid(gHeroState.flagBits, ctx->flag))) {
            PushRequestQueue(D_L00_001BEFC0, 0x21);
            LaunchQueuedRequest(D_L00_001BEFC0);
            if (gFrameCounter_L00 < 5)
                SetSlowdownFactorAndLowFpsFade();
            SetMobyState(obj, 1, -1);
        } else {
            SetMobyState(obj, 4, -1);
        }
        break;
    }
    case 1:
        if (!IsEitherModeTwo()) {
            if (ctx->pose != -1)
                ResetHeroPositionAndDirection(&D_L00_001B1F8C[ctx->pose].position, &D_L00_001B1F8C[ctx->pose].rotation, 0, 1);
            SpawnEquipmentPieces(ctx->child);
            LockCameraEntry(ctx->cue);
            D_L00_001B1A50 = 0;
            D_L00_001B18E0 = 1.5f;
            SetMobyState(obj, 2, -1);
            InitEffectRecordTable(D_L00_001BF154 + 0xF0000);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(obj)) {
            StartEffectInSlot(0x17, 0, 0);
            D_L00_001B1A50 = 0;
        }
        angle = FastAddRotations(ctx->child->rotation.f[2], 3.1415927f);
        D_L00_001B24B0[0] = FastSinOrCosA(angle) * 0.6f;
        D_L00_001B24B0[1] = FastSinOrCosB(angle) * 0.6f;
        D_L00_001B24B0[2] = 0.0f;
        ctx->child->f95 = 0xFF;
        AddDrawCallbackToList1(DrawObjectMultiPass, ctx->child);
        ++obj->timer;
        if (obj->timer > 10 && IsCameraTriggerReady(ctx->cue)) {
            AranosLaunchPose *poses;

            STUB_printf(D_L00_001AED10);
            poses = D_L00_001B1F8C;
            ctx->child->flags |= 0x41;
            ctx->child->flags &= 0xEFFF;
            ctx->child->f98 = 0;
            offset.f[0] = FastSinOrCosA(poses[ctx->pose].rotation.f[2]);
            offset.f[0] += offset.f[0];
            offset.f[1] = FastSinOrCosB(D_L00_001B1F8C[ctx->pose].rotation.f[2]);
            offset.f[1] += offset.f[1];
            offset.f[2] = 0;
            FastVecAdd(&offset, &offset, &D_L00_001B1F8C[ctx->pose].position);
            StartHeroTargetState(&offset, 1, D_L00_001B1F8C[ctx->pose].rotation.f[2]);
            ResetCameraEntry(ctx->target);
            D_L00_001B1A50 = 2;
            SetMobyState(obj, 4, -1);
        }
        path = D_L00_001FDA80[ctx->pathIndex];
        if (vec_distance_xy(&ctx->child->position, &path->points[ctx->pointIndex]) < 0.75f)
            ++ctx->pointIndex;
        if (path->count - 1 < ctx->pointIndex)
            ctx->pointIndex = path->count - 1;
        FastVecSub(&offset, &path->points[ctx->pointIndex], &ctx->child->position);
        vec_scale_to_length(&offset, &offset, ctx->speed * 0.016666668f);
        FastVecAdd(&ctx->child->position, &ctx->child->position, &offset);
        break;
    case 4:
        if (SetFirstPendingFlag(obj)) {
            int target = ctx->target;

            D_L00_001B1A50 = 2;
            ResetCameraEntry(target);
        }
        if (!GetHeroTargetStateKind()) {
            if (MemcardSave(1, -1))
                gSaveMenuFlags |= 0x200;
            SetMobyState(obj, 5, -1);
        }
        break;
    }

    if (obj->state != 4 && obj->state != 5) {
        path = D_L00_001FDA80[ctx->pathIndex];
        SnapMobyListToParent(ctx->child);
        ctx->child->rotation.f[2] = FastMatrixHelperA(path->points[1].f[0] - ctx->child->position.f[0],
                                                  path->points[1].f[1] - ctx->child->position.f[1]);
        euler_rotation_basis(ctx->child->matrix, (char *)&ctx->child->rotation);
    } else {
        i = 0;
        while (D_L00_00220DA0[i]) {
            D_L00_00220DA0[i]->flags |= 0x41;
            D_L00_00220DA0[i]->flags &= 0xEFFF;
            D_L00_00220DA0[i]->f98 = 0;
            ++i;
        }
    }
}
