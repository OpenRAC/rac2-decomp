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
extern HeroGround g_hero_state;

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

extern int g_current_map_index;
extern int D_L01_001A9030 MACRO_ADDR;
extern int D_L01_001A9034;

extern int hero_is_in_special_kind_or_mode(void);
extern void vec_clear_128(void *);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern int func_L00_002E2048(void);
extern int GetCollHitMaterial(void);
extern float coll_get_ground_height_at_position(void *, void *);
extern int moby_is_in_special_class_range(void *);
extern u8 *moby_get_private_value_0(void *);
extern u8 *moby_get_private_value_2(void *);
extern float gravity_get_center_distance(void *);
extern void vec_compute_flat_direction_from_point(void *, void *, int);
extern f32 ApproachValue(float *, float, float);
extern float fast_vec_dist(void *, void *);
extern void func_001290E0(void *, void *);
extern float cam_get_view_space_angle(void *);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void hero_compute_angles_to_local_dir(void *, void *);
/* The EE integer and FP argument banks keep their own order. */
extern void hero_build_relative_offset(void *, float, float, float, int);
extern float math_fabs(float);

/* Probe the ground under the hero: surface type and height, slope, gravity direction and side tilts. */
void UpdateOozlaHeroGroundContacts(void)
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

    g_hero_state.groundNormal.f[2] = 1.0f;
    g_hero_state.airFrames.u++;
    g_hero_state.framesOffGround.u++;
    g_hero_state.groundNormal.i[0] = 0;
    g_hero_state.groundNormal.i[1] = 0;
    g_hero_state.groundSlope.i = 0;
    g_hero_state.groundZ.i = 0;
    vec_clear_128(&g_hero_state.groundPoint);
    g_hero_state.onFlaggedGroundMoby = 0;
    g_hero_state.groundDistance = 32.0f;
    g_hero_state.groundMoby = 0;
    if (g_hero_state.inWaterFrames != 0)
        g_hero_state.inWaterFrames++;

    /* Cast a ray down from above the hero. */
    alongGravity = 1;
    height = g_hero_state.capsuleRadius * 2.2f;
    if (g_hero_state.controlMode == 2)
        height = g_hero_state.capsuleRadius * 2.9f;
    if (hero_is_in_special_kind_or_mode())
        height = 0.0f;
    BuildOffsetVectorPair(&rayStart, &rayEnd, alongGravity, height, -48.0f);
    if (CollLine(&rayStart, &rayEnd, 2, g_hero_state.moby, 0) == 0)
        goto probed;
    g_hero_state.groundSoundClass = func_L00_002E2048();
    if (D_L01_001BF900.moby != 0)
        g_hero_state.groundSoundClass = 0;
    if (g_current_map_index == 7 && D_L01_001BF900.moby != 0)
        g_hero_state.groundSoundClass = 1;
    g_hero_state.groundType = GetCollHitMaterial();
    if (g_hero_state.groundType == 0) {
        /* Water: note the surface, then look for the floor below it. */
        g_hero_state.waterSurfaceZ = coll_get_ground_height_at_position(&D_L01_001BF900.point, &g_hero_state.waterNormal);
        if (g_hero_state.position.f[2] < g_hero_state.waterSurfaceZ && g_hero_state.inWaterFrames <= 0)
            g_hero_state.inWaterFrames = 1;
        if (CollLine(&rayStart, &rayEnd, 0x24, g_hero_state.moby, 0) == 0)
            goto probed;
        g_hero_state.groundSoundClass = func_L00_002E2048();
    }
    if (g_hero_state.groundType == 3) {
        g_hero_state.sinkSurfaceZ = D_L01_001BF900.point.f[2];
        rayStart.f[2] = D_L01_001BF900.point.f[2] - 0.01f;
        if (CollLine(&rayStart, &rayEnd, 4, g_hero_state.moby, 0) == 0)
            goto probed;
    }
    if (g_hero_state.groundType == 0xB) {
        g_hero_state.sinkSurfaceZ = D_L01_001BF900.point.f[2];
        goto probed;
    }
    if (D_L01_001BF900.moby != 0) {
        if (moby_is_in_special_class_range(D_L01_001BF900.moby))
            g_hero_state.onFlaggedGroundMoby = 1;
        info = moby_get_private_value_0(D_L01_001BF900.moby);
        if (info != 0 && (*(u16 *)(info + 0x1E) & 8))
            g_hero_state.onFlaggedGroundMoby = 1;
        info = moby_get_private_value_2(D_L01_001BF900.moby);
        if (info != 0 && (*(int *)(info + 0x3C) & 8))
            g_hero_state.onFlaggedGroundMoby = 1;
    }
    if (D_L01_001BF900.count > 0) {
        qcopy(&g_hero_state.groundPoint, &D_L01_001BF900.point);
        g_hero_state.groundZ.f = D_L01_001BF900.point.f[2];
        if (D_L01_001A9030)
            g_hero_state.groundZ.f = gravity_get_center_distance(&D_L01_001BF900.point);
        g_hero_state.groundDistance = fast_vec_dist(&g_hero_state.position, &g_hero_state.groundPoint);
        g_hero_state.groundMoby = D_L01_001BF900.moby;
        func_001290E0(&g_hero_state.groundNormal, &D_L01_001BF900.normal);
        g_hero_state.groundSlope.f = cam_get_view_space_angle(&D_L01_001BF900.normal);
        g_hero_state.downhillYaw = mat_fast_helper_a(D_L01_001BF900.normal.f[0], D_L01_001BF900.normal.f[1]);
        FastVecSub(&work, &g_hero_state.groundPoint, &g_hero_state.position);
        if (0.0f < FastVecDot(&work, &g_hero_state.groundNormal))
            g_hero_state.groundDistance = -g_hero_state.groundDistance;
        if (g_hero_state.groundDistance < 0.02f) {
            g_hero_state.framesOffGround.s = 0;
            if (g_hero_state.groundSlope.f <= 0.87266469f || g_hero_state.gravityMode != 0) {
                g_hero_state.airFrames.s = 0;
                g_hero_state.lastLandedMoby = D_L01_001BF900.moby;
            }
        }
    }
probed:
    if (g_hero_state.position.f[2] > g_hero_state.waterSurfaceZ)
        g_hero_state.inWaterFrames = 0;
    if (g_hero_state.airFrames.s != 0) {
        g_hero_state.groundedFrames = 0;
    } else {
        g_hero_state.groundedFrames++;
        qcopy(&g_hero_state.lastGroundPoint, &g_hero_state.groundPoint);
        if (g_hero_state.state != 0x38)
            g_hero_state.f18C0 = 0;
    }

    /* Gravity direction. */
    vec_clear_128(&g_hero_state.gravityDir);
    switch (g_hero_state.gravityMode) {
    case 0:
        g_hero_state.gravityDir.f[2] = -1.0f;
        break;
    case 1:
        if (D_L01_001A9034) {
            vec_compute_flat_direction_from_point(&g_hero_state.position, &g_hero_state.gravityDir, 0);
        } else if (g_hero_state.gravityOverride.f[3] != 0.0f) {
            ApproachValue(&g_hero_state.gravityOverride.f[3], 0.0f, 1.0f);
            qcopy(&g_hero_state.gravityDir, &g_hero_state.gravityOverride);
        } else {
            qcopy(&g_hero_state.gravityDir, &g_hero_state.groundNormal);
            FastVecScale(&g_hero_state.gravityDir, &g_hero_state.gravityDir, -1.0f);
        }
        break;
    case 2:
        sign = -1.0f;
        if (g_hero_state.gravityPoint.f[3] > 0.0f)
            sign = 1.0f;
        FastVecSub(&g_hero_state.gravityDir, &g_hero_state.gravityPoint, &g_hero_state.position);
        vec_scale_to_length(&g_hero_state.gravityDir, &g_hero_state.gravityDir, sign);
        break;
    }

    /* Ground and side tilts, only close to the ground in the listed control modes. */
    g_hero_state.groundTiltY.i = 0;
    g_hero_state.groundTiltX.i = 0;
    g_hero_state.sideTiltX.i[0] = 0;
    g_hero_state.sideTiltX.i[1] = 0;
    g_hero_state.sideTiltY.i[0] = 0;
    g_hero_state.sideTiltY.i[1] = 0;
    g_hero_state.sideHeight.i[0] = 0;
    g_hero_state.sideHeight.i[1] = 0;
    if (!(g_hero_state.groundDistance < 0.25f))
        return;
    if (!(g_hero_state.controlMode == 0 || g_hero_state.controlMode == 12 ||
          g_hero_state.controlMode == 9 || g_hero_state.controlMode == 7 ||
          (g_hero_state.controlMode == 4 && g_hero_state.f49C) ||
          g_hero_state.controlMode == 1))
        return;
    hero_compute_angles_to_local_dir(&g_hero_state.groundNormal, &work);
    if (-0.785398244f < work.f[1] && work.f[1] < 0.785398244f)
        g_hero_state.groundTiltY.f = work.f[1];
    if (-0.785398244f < work.f[0] && work.f[0] < 0.785398244f)
        g_hero_state.groundTiltX.f = work.f[0];
    for (side = 0; side < 2; side++) {
        angle = 1.57079649f;
        if (side == 1)
            angle = -angle;
        hero_build_relative_offset(&sideStart, 0.2f, angle, 0.45f, 1);
        hero_build_relative_offset(&sideEnd, 0.2f, angle, -0.45f, 1);
        if (CollLine(&sideStart, &sideEnd, 0x22, g_hero_state.moby, 0)) {
            if (D_L01_001A9030)
                g_hero_state.sideHeight.f[side] = gravity_get_center_distance(&D_L01_001BF900.point) -
                                                gravity_get_center_distance(&g_hero_state.groundPoint);
            else
                g_hero_state.sideHeight.f[side] = D_L01_001BF900.point.f[2] - g_hero_state.groundZ.f;
            if (0.4f < math_fabs(g_hero_state.sideHeight.f[side]))
                g_hero_state.sideHeight.f[side] = 0.0f;
            func_001290E0(&sideNormal, &D_L01_001BF900.normal);
            hero_compute_angles_to_local_dir(&sideNormal, &sideAngles);
            if (-0.785398244f < sideAngles.f[1] && sideAngles.f[1] < 0.785398244f)
                g_hero_state.sideTiltY.f[side] = sideAngles.f[1];
            if (-0.785398244f < sideAngles.f[0] && sideAngles.f[0] < 0.785398244f)
                g_hero_state.sideTiltX.f[side] = sideAngles.f[0];
        } else {
            g_hero_state.sideHeight.i[side] = 0;
            g_hero_state.sideTiltY.f[side] = g_hero_state.groundTiltY.f;
            g_hero_state.sideTiltX.f[side] = g_hero_state.groundTiltX.f;
        }
    }
}
