#include "common.h"

/* Adapted from public OpenRAC/rac1-decomp hero_collision.c (GPL-3.0), with the
 * Going Commando field offsets and its additional gravity modes. */
typedef union { float f; int i; } FloatBits;
typedef union { short s; unsigned short u; } ShortBits;
typedef union { float f[2]; int i[2]; } FloatPair;
typedef union { float f[4]; int i[4]; } Vec4;

/* The hero (D_00189E20) as the ground probe sees it. The union members are
 * written in one type and cleared or counted in the other. */
typedef struct {
    u8 pad0[0x80];
    Vec4 position;                  /* 0x80 */
    u8 pad90[0xB0 - 0x90];
    Vec4 gravityPoint;              /* 0xB0: w > 0 pulls towards the point */
    u8 padC0[0x264 - 0xC0];
    float capsuleRadius;            /* 0x264 */
    u8 pad268[0x2A0 - 0x268];
    Vec4 groundNormal;              /* 0x2A0 */
    Vec4 waterNormal;               /* 0x2B0 */
    Vec4 gravityDir;                /* 0x2C0 */
    Vec4 groundPoint;               /* 0x2D0 */
    Vec4 lastGroundPoint;           /* 0x2E0 */
    Vec4 gravityOverride;           /* 0x2F0: used while w is nonzero */
    FloatPair sideHeight;           /* 0x300: side probe heights above the ground point */
    FloatPair sideTiltY;            /* 0x308 */
    FloatPair sideTiltX;            /* 0x310 */
    FloatBits groundZ;              /* 0x318 */
    float groundDistance;           /* 0x31C */
    FloatBits groundSlope;          /* 0x320 */
    FloatBits groundTiltY;          /* 0x324 */
    FloatBits groundTiltX;          /* 0x328 */
    float downhillYaw;              /* 0x32C */
    float waterSurfaceZ;            /* 0x330 */
    float sinkSurfaceZ;             /* 0x334 */
    int inWaterFrames;              /* 0x338 */
    void *groundMoby;               /* 0x33C */
    int groundedFrames;             /* 0x340 */
    u8 pad344[0x34A - 0x344];
    short onFlaggedGroundMoby;      /* 0x34A */
    ShortBits framesOffGround;      /* 0x34C */
    ShortBits airFrames;            /* 0x34E */
    u8 pad350[0x49C - 0x350];
    u8 f49C;                        /* 0x49C */
    u8 pad49D[0xC10 - 0x49D];
    void *lastLandedMoby;           /* 0xC10 */
    u8 padC14[0x1490 - 0xC14];
    short groundType;               /* 0x1490 */
    u8 pad1492[0x149D - 0x1492];
    u8 groundSoundClass;            /* 0x149D */
    u8 pad149E[0x18C0 - 0x149E];
    int f18C0;                      /* 0x18C0 */
    u8 pad18C4[0x2290 - 0x18C4];
    void *moby;                     /* 0x2290 */
    int state;                      /* 0x2294 */
    u8 pad2298[0x229C - 0x2298];
    int controlMode;                /* 0x229C */
    u8 pad22A0[0x22C3 - 0x22A0];
    u8 gravityMode;                 /* 0x22C3 */
} HeroGround;
extern HeroGround D_00189E20;

/* The result of the last collision query. */
typedef struct {
    u8 pad0[0x18];
    void *moby;                     /* 0x18: 0 for level geometry */
    int count;                      /* 0x1C */
    Vec4 point;                     /* 0x20 */
    u8 pad30[0x40 - 0x30];
    Vec4 normal;                    /* 0x40 */
} CollisionHit;
extern CollisionHit D_L01_001BF900;

extern int D_001A79F0;
extern int D_L01_001A9030 MACRO_ADDR;
extern int D_L01_001A9034;

extern int func_L00_002ADF80(void);
extern void func_00282C88(void *);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_L00_002E2048(void);
extern int func_00278E78(void);
extern float func_002A90F8(void *, void *);
extern int func_002ABB78(void *);
extern u8 *func_002AB1F0(void *);
extern u8 *func_002AD0B0(void *);
extern float func_002B0360(void *);
extern void func_002AFF60(void *, void *, int);
extern void func_002AA2E8(float *, float, float);
extern float func_00282E48(void *, void *);
extern void func_001290E0(void *, void *);
extern float func_L00_002D3EA8(void *);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002B8E48(void *, void *);
/* The EE integer and FP argument banks keep their own order. */
extern void func_L00_002D3638(void *, float, float, float, int);
extern float func_00282C48(float);

/* Probe the ground under the hero: surface type and height, slope, gravity direction and side tilts. */
void func_L01_002B5218(void)
{
    Vec4 rayEnd;
    Vec4 rayStart;
    Vec4 work;                      /* hero-to-ground offset, then the ground normal's angles */
    Vec4 sideStart;
    Vec4 sideEnd;
    Vec4 sideAngles;
    Vec4 sideNormal;
    s32 side;
    f32 angle;
    f32 sign;
    u8 *info;
    s32 alongGravity;
    f32 height;

    D_00189E20.groundNormal.f[2] = 1.0f;
    D_00189E20.airFrames.u++;
    D_00189E20.framesOffGround.u++;
    D_00189E20.groundNormal.i[0] = 0;
    D_00189E20.groundNormal.i[1] = 0;
    D_00189E20.groundSlope.i = 0;
    D_00189E20.groundZ.i = 0;
    func_00282C88(&D_00189E20.groundPoint);
    D_00189E20.onFlaggedGroundMoby = 0;
    D_00189E20.groundDistance = 32.0f;
    D_00189E20.groundMoby = 0;
    if (D_00189E20.inWaterFrames != 0)
        D_00189E20.inWaterFrames++;

    /* Cast a ray down from above the hero. */
    alongGravity = 1;
    height = D_00189E20.capsuleRadius * 2.2f;
    if (D_00189E20.controlMode == 2)
        height = D_00189E20.capsuleRadius * 2.9f;
    if (func_L00_002ADF80())
        height = 0.0f;
    BuildOffsetVectorPair(&rayStart, &rayEnd, alongGravity, height, -48.0f);
    if (CollLine(&rayStart, &rayEnd, 2, D_00189E20.moby, 0) == 0)
        goto probed;
    D_00189E20.groundSoundClass = func_L00_002E2048();
    if (D_L01_001BF900.moby != 0)
        D_00189E20.groundSoundClass = 0;
    if (D_001A79F0 == 7 && D_L01_001BF900.moby != 0)
        D_00189E20.groundSoundClass = 1;
    D_00189E20.groundType = GetCollHitMaterial();
    if (D_00189E20.groundType == 0) {
        /* Water: note the surface, then look for the floor below it. */
        D_00189E20.waterSurfaceZ = func_002A90F8(&D_L01_001BF900.point, &D_00189E20.waterNormal);
        if (D_00189E20.position.f[2] < D_00189E20.waterSurfaceZ && D_00189E20.inWaterFrames <= 0)
            D_00189E20.inWaterFrames = 1;
        if (CollLine(&rayStart, &rayEnd, 0x24, D_00189E20.moby, 0) == 0)
            goto probed;
        D_00189E20.groundSoundClass = func_L00_002E2048();
    }
    if (D_00189E20.groundType == 3) {
        D_00189E20.sinkSurfaceZ = D_L01_001BF900.point.f[2];
        rayStart.f[2] = D_L01_001BF900.point.f[2] - 0.01f;
        if (CollLine(&rayStart, &rayEnd, 4, D_00189E20.moby, 0) == 0)
            goto probed;
    }
    if (D_00189E20.groundType == 0xB) {
        D_00189E20.sinkSurfaceZ = D_L01_001BF900.point.f[2];
        goto probed;
    }
    if (D_L01_001BF900.moby != 0) {
        if (func_002ABB78(D_L01_001BF900.moby))
            D_00189E20.onFlaggedGroundMoby = 1;
        info = func_002AB1F0(D_L01_001BF900.moby);
        if (info != 0 && (*(u16 *)(info + 0x1E) & 8))
            D_00189E20.onFlaggedGroundMoby = 1;
        info = func_002AD0B0(D_L01_001BF900.moby);
        if (info != 0 && (*(int *)(info + 0x3C) & 8))
            D_00189E20.onFlaggedGroundMoby = 1;
    }
    if (D_L01_001BF900.count > 0) {
        qcopy(&D_00189E20.groundPoint, &D_L01_001BF900.point);
        D_00189E20.groundZ.f = D_L01_001BF900.point.f[2];
        if (D_L01_001A9030)
            D_00189E20.groundZ.f = func_002B0360(&D_L01_001BF900.point);
        D_00189E20.groundDistance = fast_vec_dist(&D_00189E20.position, &D_00189E20.groundPoint);
        D_00189E20.groundMoby = D_L01_001BF900.moby;
        func_001290E0(&D_00189E20.groundNormal, &D_L01_001BF900.normal);
        D_00189E20.groundSlope.f = func_L00_002D3EA8(&D_L01_001BF900.normal);
        D_00189E20.downhillYaw = func_00283248(D_L01_001BF900.normal.f[0], D_L01_001BF900.normal.f[1]);
        FastVecSub(&work, &D_00189E20.groundPoint, &D_00189E20.position);
        if (0.0f < FastVecDot(&work, &D_00189E20.groundNormal))
            D_00189E20.groundDistance = -D_00189E20.groundDistance;
        if (D_00189E20.groundDistance < 0.02f) {
            D_00189E20.framesOffGround.s = 0;
            if (D_00189E20.groundSlope.f <= 0.87266469f || D_00189E20.gravityMode != 0) {
                D_00189E20.airFrames.s = 0;
                D_00189E20.lastLandedMoby = D_L01_001BF900.moby;
            }
        }
    }
probed:
    if (D_00189E20.position.f[2] > D_00189E20.waterSurfaceZ)
        D_00189E20.inWaterFrames = 0;
    if (D_00189E20.airFrames.s != 0) {
        D_00189E20.groundedFrames = 0;
    } else {
        D_00189E20.groundedFrames++;
        qcopy(&D_00189E20.lastGroundPoint, &D_00189E20.groundPoint);
        if (D_00189E20.state != 0x38)
            D_00189E20.f18C0 = 0;
    }

    /* Gravity direction. */
    func_00282C88(&D_00189E20.gravityDir);
    switch (D_00189E20.gravityMode) {
    case 0:
        D_00189E20.gravityDir.f[2] = -1.0f;
        break;
    case 1:
        if (D_L01_001A9034) {
            func_002AFF60(&D_00189E20.position, &D_00189E20.gravityDir, 0);
        } else if (D_00189E20.gravityOverride.f[3] != 0.0f) {
            ApproachValue(&D_00189E20.gravityOverride.f[3], 0.0f, 1.0f);
            qcopy(&D_00189E20.gravityDir, &D_00189E20.gravityOverride);
        } else {
            qcopy(&D_00189E20.gravityDir, &D_00189E20.groundNormal);
            FastVecScale(&D_00189E20.gravityDir, &D_00189E20.gravityDir, -1.0f);
        }
        break;
    case 2:
        sign = -1.0f;
        if (D_00189E20.gravityPoint.f[3] > 0.0f)
            sign = 1.0f;
        FastVecSub(&D_00189E20.gravityDir, &D_00189E20.gravityPoint, &D_00189E20.position);
        vec_scale_to_length(&D_00189E20.gravityDir, &D_00189E20.gravityDir, sign);
        break;
    }

    /* Ground and side tilts, only close to the ground in the listed control modes. */
    D_00189E20.groundTiltY.i = 0;
    D_00189E20.groundTiltX.i = 0;
    D_00189E20.sideTiltX.i[0] = 0;
    D_00189E20.sideTiltX.i[1] = 0;
    D_00189E20.sideTiltY.i[0] = 0;
    D_00189E20.sideTiltY.i[1] = 0;
    D_00189E20.sideHeight.i[0] = 0;
    D_00189E20.sideHeight.i[1] = 0;
    if (!(D_00189E20.groundDistance < 0.25f))
        return;
    if (!(D_00189E20.controlMode == 0 || D_00189E20.controlMode == 12 ||
          D_00189E20.controlMode == 9 || D_00189E20.controlMode == 7 ||
          (D_00189E20.controlMode == 4 && D_00189E20.f49C) ||
          D_00189E20.controlMode == 1))
        return;
    func_L00_002B8E48(&D_00189E20.groundNormal, &work);
    if (-0.785398244f < work.f[1] && work.f[1] < 0.785398244f)
        D_00189E20.groundTiltY.f = work.f[1];
    if (-0.785398244f < work.f[0] && work.f[0] < 0.785398244f)
        D_00189E20.groundTiltX.f = work.f[0];
    for (side = 0; side < 2; side++) {
        angle = 1.57079649f;
        if (side == 1)
            angle = -angle;
        func_L00_002D3638(&sideStart, 0.2f, angle, 0.45f, 1);
        func_L00_002D3638(&sideEnd, 0.2f, angle, -0.45f, 1);
        if (CollLine(&sideStart, &sideEnd, 0x22, D_00189E20.moby, 0)) {
            if (D_L01_001A9030)
                D_00189E20.sideHeight.f[side] = func_002B0360(&D_L01_001BF900.point) -
                                                func_002B0360(&D_00189E20.groundPoint);
            else
                D_00189E20.sideHeight.f[side] = D_L01_001BF900.point.f[2] - D_00189E20.groundZ.f;
            if (0.4f < func_00282C48(D_00189E20.sideHeight.f[side]))
                D_00189E20.sideHeight.f[side] = 0.0f;
            func_001290E0(&sideNormal, &D_L01_001BF900.normal);
            func_L00_002B8E48(&sideNormal, &sideAngles);
            if (-0.785398244f < sideAngles.f[1] && sideAngles.f[1] < 0.785398244f)
                D_00189E20.sideTiltY.f[side] = sideAngles.f[1];
            if (-0.785398244f < sideAngles.f[0] && sideAngles.f[0] < 0.785398244f)
                D_00189E20.sideTiltX.f[side] = sideAngles.f[0];
        } else {
            D_00189E20.sideHeight.i[side] = 0;
            D_00189E20.sideTiltY.f[side] = D_00189E20.groundTiltY.f;
            D_00189E20.sideTiltX.f[side] = D_00189E20.groundTiltX.f;
        }
    }
}
