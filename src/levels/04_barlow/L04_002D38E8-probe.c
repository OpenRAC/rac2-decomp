#include "common.h"

/* Barlow's copy of the hero's ground probe. Adapted from OpenRAC/rac1-decomp
 * src/overlays/l12_hoven/hero_movement.c, Hero_ProbeGround (GPL-3.0), and retail. */

typedef struct {
    unsigned char pad0[0x80];
    float position[4];
    unsigned char pad90[0x20];
    float referencePoint[4];
    unsigned char padc0[0x1A4];
    float capsuleRadius;
    unsigned char pad268[0x38];
    float groundNormal[4];
    float waterSurfaceNormal[4];
    float gravityDir[4];
    float groundPoint[4];
    float lastGroundPoint[4];
    float f2f0[3];
    float f2fc;
    union { float f[2]; int i[2]; } sideHeight;
    union { float f[2]; int i[2]; } sidePitch;
    union { float f[2]; int i[2]; } sideRoll;
    float groundZ;
    float groundDistance;
    float groundSlope;
    float groundPitch;
    float groundRoll;
    float downhillYaw;
    float waterSurfaceZ;
    unsigned char pad334[4];
    int inWaterFrames;
    int groundMoby;
    int groundedFrames;
    unsigned char pad344[6];
    short onFlaggedGroundMoby;
    short framesOffGround;
    short airFrames;
    unsigned char pad350[0x14C];
    unsigned char f49c;
    unsigned char pad49d[0x773];
    int lastLandedMoby;
    unsigned char padc14[0x87C];
    short groundType;
    unsigned char pad1492[11];
    unsigned char groundSoundClass;
    unsigned char pad149e[0xDF2];
    int moby;
    unsigned char pad2294[8];
    int controlMode;
    unsigned char pad22a0[0x23];
    unsigned char gravityMode;
} ProbeHero;

typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    int count;
    float point[4];
    unsigned char pad30[0x10];
    float normal[4];
} ProbeHit;

extern ProbeHero D_00189E20;
extern unsigned char D_L04_001BFAC0[];
#define hit ((ProbeHit *)D_L04_001BFAC0)
extern int D_001A79F0 __attribute__((sda));
extern int D_L04_001A8FF0 __attribute__((sda));
extern int D_L04_001A8FF4 __attribute__((sda));
extern int D_L04_001A8FF0_gp SDATA(D_L04_001A8FF0);

extern float func_00282C48(float);
extern void func_00282C88(void *);
extern int func_L00_002ADF80(void);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_002761F8(void *, void *, int, int, int);
extern int func_L00_002E2048(void);
extern short func_00278E78(void);
extern float func_002A90F8(void *, void *);
extern int func_002ABB78(void *);
extern unsigned char *func_002AB1F0(void *);
extern unsigned char *func_002AD0B0(void *);
extern float func_002B0360(void *);
extern float func_00282E48(void *, void *);
extern void func_001290E0(void *, void *);
extern float func_L00_002D3EA8(void *);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_002AFF60(void *, void *, int);
extern void func_002AA2E8(void *, float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002B8E48(void *, void *);
extern void func_L00_002D3638(void *, float, float, float, int);

/* Looks for the ground under the hero each frame, records its slope and type, and sets the gravity direction. */
void func_L04_002DAD10(void)
{
    float end[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float geom[4] __attribute__((aligned(16)));
    float probe1[4] __attribute__((aligned(16)));
    float probe2[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float distance, angle, sign, scale;
    int i;
    unsigned char *flags;

    gHeroState.groundNormal[2] = 1.0f;
    gHeroState.airFrames++;
    gHeroState.framesOffGround++;
    gHeroState.groundNormal[0] = 0;
    gHeroState.groundNormal[1] = 0;
    gHeroState.groundSlope = 0;
    gHeroState.groundZ = 0;
    ClearVector128(gHeroState.groundPoint);
    gHeroState.onFlaggedGroundMoby = 0;
    gHeroState.groundDistance = 32.0f;
    gHeroState.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (gHeroState.inWaterFrames) {
        gHeroState.inWaterFrames++;
    }
    distance = gHeroState.capsuleRadius * scale;
    if (2 == gHeroState.controlMode) {
        distance = gHeroState.capsuleRadius * 2.9f;
    }
    if (IsHeroInSpecialKindOrMode()) {
        distance = 0;
    }
    BuildOffsetVectorPair(start, end, 1, distance, -48.0f);
    if (!CollLine(start, end, 2, gHeroState.moby, 0)) {
        goto tail;
    }
    gHeroState.groundSoundClass = func_L00_002E2048();
    if (hit->moby) {
        gHeroState.groundSoundClass = 0;
    }
    if (gCurrentMapIndex == 7 && hit->moby) {
        gHeroState.groundSoundClass = 1;
    }
    gHeroState.groundType = GetCollHitMaterial();
    if (gHeroState.groundType == 0) {
        gHeroState.waterSurfaceZ = GetGroundHeightAtPosition(hit->point, gHeroState.waterSurfaceNormal);
        if (gHeroState.position[2] < gHeroState.waterSurfaceZ && gHeroState.inWaterFrames <= 0) {
            gHeroState.inWaterFrames = 1;
        }
        if (!CollLine(start, end, 0x24, gHeroState.moby, 0)) {
            goto tail;
        }
        gHeroState.groundSoundClass = func_L00_002E2048();
    }
    if (gHeroState.groundType == 13) {
        gHeroState.waterSurfaceZ = hit->point[2];
        start[2] = hit->point[2] - 0.01f;
        if (!CollLine(start, end, 4, gHeroState.moby, 0)) {
            goto tail;
        }
    }
    if (hit->moby) {
        if (IsMobyInSpecialClassRange(hit->moby)) {
            gHeroState.onFlaggedGroundMoby = 1;
        }
        flags = GetMobyPrivateValue0(hit->moby);
        if (flags && (*(unsigned short *)(flags + 0x1E) & 8)) {
            gHeroState.onFlaggedGroundMoby = 1;
        }
        flags = GetMobyPrivateValue2(hit->moby);
        if (flags && (*(int *)(flags + 0x3C) & 8)) {
            gHeroState.onFlaggedGroundMoby = 1;
        }
    }
    if (hit->count > 0) {
        qcopy(gHeroState.groundPoint, hit->point);
        gHeroState.groundZ = hit->point[2];
        if (D_L04_001A8FF0) {
            gHeroState.groundZ = GetDistanceFromGravityCenter(hit->point);
        }
        gHeroState.groundDistance = fast_vec_dist(gHeroState.position, gHeroState.groundPoint);
        gHeroState.groundMoby = (int)hit->moby;
        func_001290E0(gHeroState.groundNormal, hit->normal);
        gHeroState.groundSlope = GetViewSpaceAngle(hit->normal);
        gHeroState.downhillYaw = FastMatrixHelperA(hit->normal[0], hit->normal[1]);
        FastVecSub(geom, gHeroState.groundPoint, gHeroState.position);
        if (FastVecDot(geom, gHeroState.groundNormal) > 0.0f) {
            gHeroState.groundDistance = -gHeroState.groundDistance;
        }
        if (gHeroState.groundDistance < 0.02f) {
            gHeroState.framesOffGround = 0;
            if (gHeroState.groundSlope <= 0.87266469f || gHeroState.gravityMode) {
                gHeroState.airFrames = 0;
                gHeroState.lastLandedMoby = (int)hit->moby;
            }
        }
    }
tail:
    if (gHeroState.position[2] > gHeroState.waterSurfaceZ) {
        gHeroState.inWaterFrames = 0;
    }
    if (gHeroState.airFrames) {
        gHeroState.groundedFrames = 0;
    } else {
        gHeroState.groundedFrames++;
        qcopy(gHeroState.lastGroundPoint, gHeroState.groundPoint);
    }
    ClearVector128(gHeroState.gravityDir);
    switch (gHeroState.gravityMode) {
    case 0:
        gHeroState.gravityDir[2] = -1;
        break;
    case 1:
        if (D_L04_001A8FF4) {
            ComputeFlatDirectionFromPoint(gHeroState.position, gHeroState.gravityDir, 0);
        } else if (gHeroState.f2fc != 0.0f) {
            ApproachValue(&gHeroState.f2fc, 0.0f, 1.0f);
            qcopy(gHeroState.gravityDir, gHeroState.f2f0);
        } else {
            qcopy(gHeroState.gravityDir, gHeroState.groundNormal);
            FastVecScale(gHeroState.gravityDir, gHeroState.gravityDir, -1.0f);
        }
        break;
    case 2:
        sign = -1.0f;
        if (gHeroState.referencePoint[3] > 0) {
            sign = 1.0f;
        }
        FastVecSub(gHeroState.gravityDir, gHeroState.referencePoint, gHeroState.position);
        vec_scale_to_length(gHeroState.gravityDir, gHeroState.gravityDir, sign);
        break;
    }
    gHeroState.groundPitch = 0;
    gHeroState.groundRoll = 0;
    gHeroState.sideRoll.i[0] = 0;
    gHeroState.sideRoll.i[1] = 0;
    gHeroState.sidePitch.i[0] = 0;
    gHeroState.sidePitch.i[1] = 0;
    gHeroState.sideHeight.i[0] = 0;
    gHeroState.sideHeight.i[1] = 0;
    if (!(gHeroState.groundDistance < 0.25f)) {
        return;
    }
    if (gHeroState.controlMode != 0 && gHeroState.controlMode != 12 && gHeroState.controlMode != 9 &&
        gHeroState.controlMode != 7 && !(gHeroState.controlMode == 4 && gHeroState.f49c) &&
        gHeroState.controlMode != 1) {
        return;
    }
    ComputeAnglesToHeroLocalDirection(gHeroState.groundNormal, geom);
    if (-0.78539824f < geom[1] && geom[1] < 0.78539824f) {
        gHeroState.groundPitch = geom[1];
    }
    if (-0.78539824f < geom[0] && geom[0] < 0.78539824f) {
        gHeroState.groundRoll = geom[0];
    }
    for (i = 0; i < 2; i++) {
        angle = 1.57079649f;
        if (i == 1) {
            angle = -angle;
        }
        BuildHeroRelativeOffset(probe1, 0.2f, angle, 0.45f, 1);
        BuildHeroRelativeOffset(probe2, 0.2f, angle, -0.45f, 1);
        if (CollLine(probe1, probe2, 0x22, gHeroState.moby, 0)) {
            if (D_L04_001A8FF0_gp) {
                gHeroState.sideHeight.f[i] = GetDistanceFromGravityCenter(hit->point) - GetDistanceFromGravityCenter(gHeroState.groundPoint);
            } else {
                gHeroState.sideHeight.f[i] = hit->point[2] - gHeroState.groundZ;
            }
            if (FloatAbs(gHeroState.sideHeight.f[i]) > 0.4f) {
                gHeroState.sideHeight.i[i] = 0;
            }
            func_001290E0(normal, hit->normal);
            ComputeAnglesToHeroLocalDirection(normal, angles);
            if (-0.78539824f < angles[1] && angles[1] < 0.78539824f) {
                gHeroState.sidePitch.f[i] = angles[1];
            }
            if (-0.78539824f < angles[0] && angles[0] < 0.78539824f) {
                gHeroState.sideRoll.f[i] = angles[0];
            }
        } else {
            gHeroState.sideHeight.i[i] = 0;
            gHeroState.sidePitch.f[i] = gHeroState.groundPitch;
            gHeroState.sideRoll.f[i] = gHeroState.groundRoll;
        }
    }
}
