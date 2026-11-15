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

    D_00189E20.groundNormal[2] = 1.0f;
    D_00189E20.airFrames++;
    D_00189E20.framesOffGround++;
    D_00189E20.groundNormal[0] = 0;
    D_00189E20.groundNormal[1] = 0;
    D_00189E20.groundSlope = 0;
    D_00189E20.groundZ = 0;
    func_00282C88(D_00189E20.groundPoint);
    D_00189E20.onFlaggedGroundMoby = 0;
    D_00189E20.groundDistance = 32.0f;
    D_00189E20.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (D_00189E20.inWaterFrames) {
        D_00189E20.inWaterFrames++;
    }
    distance = D_00189E20.capsuleRadius * scale;
    if (2 == D_00189E20.controlMode) {
        distance = D_00189E20.capsuleRadius * 2.9f;
    }
    if (func_L00_002ADF80()) {
        distance = 0;
    }
    BuildOffsetVectorPair(start, end, 1, distance, -48.0f);
    if (!CollLine(start, end, 2, D_00189E20.moby, 0)) {
        goto tail;
    }
    D_00189E20.groundSoundClass = func_L00_002E2048();
    if (hit->moby) {
        D_00189E20.groundSoundClass = 0;
    }
    if (D_001A79F0 == 7 && hit->moby) {
        D_00189E20.groundSoundClass = 1;
    }
    D_00189E20.groundType = GetCollHitMaterial();
    if (D_00189E20.groundType == 0) {
        D_00189E20.waterSurfaceZ = func_002A90F8(hit->point, D_00189E20.waterSurfaceNormal);
        if (D_00189E20.position[2] < D_00189E20.waterSurfaceZ && D_00189E20.inWaterFrames <= 0) {
            D_00189E20.inWaterFrames = 1;
        }
        if (!CollLine(start, end, 0x24, D_00189E20.moby, 0)) {
            goto tail;
        }
        D_00189E20.groundSoundClass = func_L00_002E2048();
    }
    if (D_00189E20.groundType == 13) {
        D_00189E20.waterSurfaceZ = hit->point[2];
        start[2] = hit->point[2] - 0.01f;
        if (!CollLine(start, end, 4, D_00189E20.moby, 0)) {
            goto tail;
        }
    }
    if (hit->moby) {
        if (func_002ABB78(hit->moby)) {
            D_00189E20.onFlaggedGroundMoby = 1;
        }
        flags = func_002AB1F0(hit->moby);
        if (flags && (*(unsigned short *)(flags + 0x1E) & 8)) {
            D_00189E20.onFlaggedGroundMoby = 1;
        }
        flags = func_002AD0B0(hit->moby);
        if (flags && (*(int *)(flags + 0x3C) & 8)) {
            D_00189E20.onFlaggedGroundMoby = 1;
        }
    }
    if (hit->count > 0) {
        qcopy(D_00189E20.groundPoint, hit->point);
        D_00189E20.groundZ = hit->point[2];
        if (D_L04_001A8FF0) {
            D_00189E20.groundZ = func_002B0360(hit->point);
        }
        D_00189E20.groundDistance = fast_vec_dist(D_00189E20.position, D_00189E20.groundPoint);
        D_00189E20.groundMoby = (int)hit->moby;
        func_001290E0(D_00189E20.groundNormal, hit->normal);
        D_00189E20.groundSlope = func_L00_002D3EA8(hit->normal);
        D_00189E20.downhillYaw = func_00283248(hit->normal[0], hit->normal[1]);
        FastVecSub(geom, D_00189E20.groundPoint, D_00189E20.position);
        if (FastVecDot(geom, D_00189E20.groundNormal) > 0.0f) {
            D_00189E20.groundDistance = -D_00189E20.groundDistance;
        }
        if (D_00189E20.groundDistance < 0.02f) {
            D_00189E20.framesOffGround = 0;
            if (D_00189E20.groundSlope <= 0.87266469f || D_00189E20.gravityMode) {
                D_00189E20.airFrames = 0;
                D_00189E20.lastLandedMoby = (int)hit->moby;
            }
        }
    }
tail:
    if (D_00189E20.position[2] > D_00189E20.waterSurfaceZ) {
        D_00189E20.inWaterFrames = 0;
    }
    if (D_00189E20.airFrames) {
        D_00189E20.groundedFrames = 0;
    } else {
        D_00189E20.groundedFrames++;
        qcopy(D_00189E20.lastGroundPoint, D_00189E20.groundPoint);
    }
    func_00282C88(D_00189E20.gravityDir);
    switch (D_00189E20.gravityMode) {
    case 0:
        D_00189E20.gravityDir[2] = -1;
        break;
    case 1:
        if (D_L04_001A8FF4) {
            func_002AFF60(D_00189E20.position, D_00189E20.gravityDir, 0);
        } else if (D_00189E20.f2fc != 0.0f) {
            ApproachValue(&D_00189E20.f2fc, 0.0f, 1.0f);
            qcopy(D_00189E20.gravityDir, D_00189E20.f2f0);
        } else {
            qcopy(D_00189E20.gravityDir, D_00189E20.groundNormal);
            FastVecScale(D_00189E20.gravityDir, D_00189E20.gravityDir, -1.0f);
        }
        break;
    case 2:
        sign = -1.0f;
        if (D_00189E20.referencePoint[3] > 0) {
            sign = 1.0f;
        }
        FastVecSub(D_00189E20.gravityDir, D_00189E20.referencePoint, D_00189E20.position);
        vec_scale_to_length(D_00189E20.gravityDir, D_00189E20.gravityDir, sign);
        break;
    }
    D_00189E20.groundPitch = 0;
    D_00189E20.groundRoll = 0;
    D_00189E20.sideRoll.i[0] = 0;
    D_00189E20.sideRoll.i[1] = 0;
    D_00189E20.sidePitch.i[0] = 0;
    D_00189E20.sidePitch.i[1] = 0;
    D_00189E20.sideHeight.i[0] = 0;
    D_00189E20.sideHeight.i[1] = 0;
    if (!(D_00189E20.groundDistance < 0.25f)) {
        return;
    }
    if (D_00189E20.controlMode != 0 && D_00189E20.controlMode != 12 && D_00189E20.controlMode != 9 &&
        D_00189E20.controlMode != 7 && !(D_00189E20.controlMode == 4 && D_00189E20.f49c) &&
        D_00189E20.controlMode != 1) {
        return;
    }
    func_L00_002B8E48(D_00189E20.groundNormal, geom);
    if (-0.78539824f < geom[1] && geom[1] < 0.78539824f) {
        D_00189E20.groundPitch = geom[1];
    }
    if (-0.78539824f < geom[0] && geom[0] < 0.78539824f) {
        D_00189E20.groundRoll = geom[0];
    }
    for (i = 0; i < 2; i++) {
        angle = 1.57079649f;
        if (i == 1) {
            angle = -angle;
        }
        func_L00_002D3638(probe1, 0.2f, angle, 0.45f, 1);
        func_L00_002D3638(probe2, 0.2f, angle, -0.45f, 1);
        if (CollLine(probe1, probe2, 0x22, D_00189E20.moby, 0)) {
            if (D_L04_001A8FF0_gp) {
                D_00189E20.sideHeight.f[i] = func_002B0360(hit->point) - func_002B0360(D_00189E20.groundPoint);
            } else {
                D_00189E20.sideHeight.f[i] = hit->point[2] - D_00189E20.groundZ;
            }
            if (func_00282C48(D_00189E20.sideHeight.f[i]) > 0.4f) {
                D_00189E20.sideHeight.i[i] = 0;
            }
            func_001290E0(normal, hit->normal);
            func_L00_002B8E48(normal, angles);
            if (-0.78539824f < angles[1] && angles[1] < 0.78539824f) {
                D_00189E20.sidePitch.f[i] = angles[1];
            }
            if (-0.78539824f < angles[0] && angles[0] < 0.78539824f) {
                D_00189E20.sideRoll.f[i] = angles[0];
            }
        } else {
            D_00189E20.sideHeight.i[i] = 0;
            D_00189E20.sidePitch.f[i] = D_00189E20.groundPitch;
            D_00189E20.sideRoll.f[i] = D_00189E20.groundRoll;
        }
    }
}
