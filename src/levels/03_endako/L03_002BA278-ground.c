/* Endako's copy of the hero's ground probe. Adapted from OpenRAC/rac1-decomp
 * src/overlays/l05_rilgar/hero_collision.c, HeroL05_GroundProbe (GPL-3.0), and retail.
 * Field names follow the matched copy in L04_002D38E8-probe.c. */
#include "common.h"

extern float func_00282DB0(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern int D_L03_001A8FF0 MACRO_ADDR;
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern int func_00278E78(void);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282D30(void *, void *, float);
typedef int GroundQuad __attribute__((mode(TI)));
typedef struct { char prefix[0x18]; unsigned char *object; int count; float position[4]; char gap[16]; float normal[4]; } GroundCollision;
extern int D_001A79F0 __attribute__((sda));
extern int D_L03_001A8FF4 __attribute__((sda));
extern GroundCollision D_L03_001BFDC0;
extern int func_L00_002ADF80(void);
extern void func_L00_002B47A8(void *, void *, int, float, float);
extern int func_L00_002E2048(void);
extern float func_002A90F8(float *, void *);
extern int func_002ABB78(char *);
extern int func_002AB1F0(unsigned char *);
extern int func_002AD0B0(unsigned char *);
extern float func_002B0360(char *);
extern float func_00282E48(void *, void *);
extern void func_001290E0(void *, void *);
extern float func_L00_002D3EA8(void *);
extern float func_00283248(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFF60(char *, char *, int);
extern void func_L00_002B8E48(void *, float *);
extern void func_L00_002D3638(float *, float, float, int, float);
extern float func_00282C48(float);

typedef struct ProbeHero {
    unsigned char pad0[128];
    struct {
        unsigned char pad80[8];
        float z;
        unsigned char tail[4];
    } position;
    unsigned char pad90[32];
    struct {
        unsigned char padb0[12];
        float w;
    } referencePoint;
    unsigned char padc0[420];
    float capsuleRadius;
    unsigned char pad268[56];
    struct {
        int x;
        int y;
        float z;
        unsigned char tail[4];
    } groundNormal;
    struct {
        unsigned char tail[16];
    } waterSurfaceNormal;
    struct {
        unsigned char pad2c0[8];
        float z;
        unsigned char tail[4];
    } gravityDir;
    struct {
        unsigned char tail[16];
    } groundPoint;
    struct {
        unsigned char tail[16];
    } lastGroundPoint;
    struct {
        unsigned char pad2f0[12];
        float w;
    } f2f0;
    float sideHeight[2];
    float sidePitch[2];
    float sideRoll[2];
    float groundZ;
    float groundDistance;
    float groundSlope;
    float groundPitch;
    float groundRoll;
    float downhillYaw;
    float waterSurfaceZ;
    float field_334;
    int inWaterFrames;
    int groundMoby;
    int groundedFrames;
    unsigned char pad344[6];
    short onFlaggedGroundMoby;
    short framesOffGround;
    short airFrames;
    unsigned char pad350[332];
    unsigned char f49c;
    unsigned char pad49d[1907];
    int lastLandedMoby;
    unsigned char padc14[2172];
    short groundType;
    unsigned char pad1492[11];
    unsigned char groundSoundClass;
    unsigned char pad149e[1058];
    int field_18c0;
    unsigned char pad18c4[2508];
    char * moby;
    int field_2294;
    unsigned char pad2298[4];
    int controlMode;
    unsigned char pad22a0[35];
    unsigned char gravityMode;
} ProbeHero;
extern ProbeHero D_00189E20;

/* Checks the ground under the hero each frame and records its height, slope, tilt and type. Also updates the gravity direction and water state. */
void func_L03_002BA278(void)
{
    float end[4];
    float start[4];
    float difference[4];
    float left[4];
    float right[4];
    float angles[2];
    float normal[4];
    float reach;
    float scale;
    int side;
    ++gHeroState.airFrames;
    gHeroState.groundNormal.z = 1.0f;
    ++gHeroState.framesOffGround;
    gHeroState.groundNormal.x = 0;
    gHeroState.groundNormal.y = 0;
    gHeroState.groundSlope = 0.0f;
    gHeroState.groundZ = 0.0f;
    ClearVector128((GroundQuad *)(&gHeroState.groundPoint));
    gHeroState.onFlaggedGroundMoby = 0;
    gHeroState.groundDistance = 32.0f;
    gHeroState.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (gHeroState.inWaterFrames)
        ++gHeroState.inWaterFrames;
    reach = gHeroState.capsuleRadius * scale;
    if (gHeroState.controlMode == 2)
        reach = gHeroState.capsuleRadius * 2.9f;
    if (IsHeroInSpecialKindOrMode())
        reach = 0.0f;
    BuildOffsetVectorPair(start, end, 1, reach, -48.0f);
    if (CollLine(start, end, 2, gHeroState.moby, 0)) {
        gHeroState.groundSoundClass = func_L00_002E2048();
        if (D_L03_001BFDC0.object)
            gHeroState.groundSoundClass = 0;
        if (gCurrentMapIndex == 7 && D_L03_001BFDC0.object)
            gHeroState.groundSoundClass = 1;
        gHeroState.groundType = GetCollHitMaterial();
        if (!gHeroState.groundType) {
            gHeroState.waterSurfaceZ = GetGroundHeightAtPosition(D_L03_001BFDC0.position, &gHeroState.waterSurfaceNormal);
            if (gHeroState.position.z < gHeroState.waterSurfaceZ && gHeroState.inWaterFrames < 1)
                gHeroState.inWaterFrames = 1;
            if (!CollLine(start, end, 0x24, gHeroState.moby, 0))
                goto contacts_done;
            gHeroState.groundSoundClass = func_L00_002E2048();
        }
        if (gHeroState.groundType != 1 || (unsigned int)(gHeroState.field_2294 - 0x79) > 1) {
            if (D_L03_001BFDC0.object) {
                unsigned char *record;
                if (IsMobyInSpecialClassRange((char *)D_L03_001BFDC0.object))
                    gHeroState.onFlaggedGroundMoby = 1;
                record = (unsigned char *)GetMobyPrivateValue0(D_L03_001BFDC0.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    gHeroState.onFlaggedGroundMoby = 1;
                record = (unsigned char *)GetMobyPrivateValue2(D_L03_001BFDC0.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    gHeroState.onFlaggedGroundMoby = 1;
            }
            if (D_L03_001BFDC0.count > 0) {
                qcopy(&gHeroState.groundPoint, D_L03_001BFDC0.position);
                gHeroState.groundZ = D_L03_001BFDC0.position[2];
                if (D_L03_001A8FF0)
                    gHeroState.groundZ = GetDistanceFromGravityCenter((char *)D_L03_001BFDC0.position);
                gHeroState.groundDistance = fast_vec_dist(&gHeroState.position, &gHeroState.groundPoint);
                gHeroState.groundMoby = (int)D_L03_001BFDC0.object;
                func_001290E0(&gHeroState.groundNormal, D_L03_001BFDC0.normal);
                gHeroState.groundSlope = GetViewSpaceAngle(D_L03_001BFDC0.normal);
                gHeroState.downhillYaw = FastMatrixHelperA(D_L03_001BFDC0.normal[0], D_L03_001BFDC0.normal[1]);
                FastVecSub(difference, &gHeroState.groundPoint, &gHeroState.position);
                if (FastVecDot(difference, &gHeroState.groundNormal) > 0.0f)
                    gHeroState.groundDistance = -gHeroState.groundDistance;
                if (gHeroState.groundDistance < 0.02f) {
                    gHeroState.framesOffGround = 0;
                    if (gHeroState.groundSlope <= 0.8726646900177002f || gHeroState.gravityMode) {
                        gHeroState.airFrames = 0;
                        gHeroState.lastLandedMoby = (int)D_L03_001BFDC0.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (gHeroState.position.z > gHeroState.waterSurfaceZ)
        gHeroState.inWaterFrames = 0;
    if (gHeroState.airFrames) {
        gHeroState.groundedFrames = 0;
    } else {
        ++gHeroState.groundedFrames;
        qcopy(&gHeroState.lastGroundPoint, &gHeroState.groundPoint);
    }
    ClearVector128((GroundQuad *)(&gHeroState.gravityDir));
    switch (gHeroState.gravityMode) {
    case 0:
        gHeroState.gravityDir.z = -1.0f;
        break;
    case 1:
        if (D_L03_001A8FF4) {
            ComputeFlatDirectionFromPoint((char *)&gHeroState.position, (char *)&gHeroState.gravityDir, 0);
        } else {
            if (gHeroState.f2f0.w != 0.0f) {
                ApproachValue(&gHeroState.f2f0.w, 0.0f, 1.0f);
                qcopy(&gHeroState.gravityDir, &gHeroState.f2f0);
            } else {
                qcopy(&gHeroState.gravityDir, &gHeroState.groundNormal);
                FastVecScale(&gHeroState.gravityDir, &gHeroState.gravityDir, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (gHeroState.referencePoint.w > 0.0f)
                sign = 1.0f;
            FastVecSub(&gHeroState.gravityDir, &gHeroState.referencePoint, &gHeroState.position);
            vec_scale_to_length(&gHeroState.gravityDir, &gHeroState.gravityDir, sign);
        }
        break;
    }
    gHeroState.groundPitch = 0.0f;
    gHeroState.groundRoll = 0.0f;
    gHeroState.sideRoll[0] = 0;
    gHeroState.sideRoll[1] = 0;
    gHeroState.sidePitch[0] = 0;
    gHeroState.sidePitch[1] = 0;
    gHeroState.sideHeight[0] = 0;
    gHeroState.sideHeight[1] = 0;
    if (gHeroState.groundDistance < 0.25f &&
        (gHeroState.controlMode == 0 || gHeroState.controlMode == 12 || gHeroState.controlMode == 9 || gHeroState.controlMode == 7 ||
         (gHeroState.controlMode == 4 && gHeroState.f49c) || gHeroState.controlMode == 1)) {
        ComputeAnglesToHeroLocalDirection(&gHeroState.groundNormal, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            gHeroState.groundPitch = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            gHeroState.groundRoll = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            BuildHeroRelativeOffset(left, 0.2f, angle, 1, 0.44999998807907104f);
            BuildHeroRelativeOffset(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (CollLine(left, right, 0x22, gHeroState.moby, 0)) {
                if (D_L03_001A8FF0) {
                    float firstHeight = GetDistanceFromGravityCenter((char *)D_L03_001BFDC0.position);
                    gHeroState.sideHeight[side] = firstHeight - GetDistanceFromGravityCenter((char *)&gHeroState.groundPoint);
                } else {
                    gHeroState.sideHeight[side] = D_L03_001BFDC0.position[2] - gHeroState.groundZ;
                }
                if (FloatAbs(gHeroState.sideHeight[side]) > 0.4f)
                    gHeroState.sideHeight[side] = 0.0f;
                func_001290E0(normal, D_L03_001BFDC0.normal);
                ComputeAnglesToHeroLocalDirection(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    gHeroState.sidePitch[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    gHeroState.sideRoll[side] = angles[0];
            } else {
                gHeroState.sideHeight[side] = 0.0f;
                gHeroState.sidePitch[side] = gHeroState.groundPitch;
                gHeroState.sideRoll[side] = gHeroState.groundRoll;
            }
        }
    }
}
