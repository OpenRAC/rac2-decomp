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
    ++D_00189E20.airFrames;
    D_00189E20.groundNormal.z = 1.0f;
    ++D_00189E20.framesOffGround;
    D_00189E20.groundNormal.x = 0;
    D_00189E20.groundNormal.y = 0;
    D_00189E20.groundSlope = 0.0f;
    D_00189E20.groundZ = 0.0f;
    func_00282C88((GroundQuad *)(&D_00189E20.groundPoint));
    D_00189E20.onFlaggedGroundMoby = 0;
    D_00189E20.groundDistance = 32.0f;
    D_00189E20.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (D_00189E20.inWaterFrames)
        ++D_00189E20.inWaterFrames;
    reach = D_00189E20.capsuleRadius * scale;
    if (D_00189E20.controlMode == 2)
        reach = D_00189E20.capsuleRadius * 2.9f;
    if (func_L00_002ADF80())
        reach = 0.0f;
    BuildOffsetVectorPair(start, end, 1, reach, -48.0f);
    if (CollLine(start, end, 2, D_00189E20.moby, 0)) {
        D_00189E20.groundSoundClass = func_L00_002E2048();
        if (D_L03_001BFDC0.object)
            D_00189E20.groundSoundClass = 0;
        if (D_001A79F0 == 7 && D_L03_001BFDC0.object)
            D_00189E20.groundSoundClass = 1;
        D_00189E20.groundType = GetCollHitMaterial();
        if (!D_00189E20.groundType) {
            D_00189E20.waterSurfaceZ = func_002A90F8(D_L03_001BFDC0.position, &D_00189E20.waterSurfaceNormal);
            if (D_00189E20.position.z < D_00189E20.waterSurfaceZ && D_00189E20.inWaterFrames < 1)
                D_00189E20.inWaterFrames = 1;
            if (!CollLine(start, end, 0x24, D_00189E20.moby, 0))
                goto contacts_done;
            D_00189E20.groundSoundClass = func_L00_002E2048();
        }
        if (D_00189E20.groundType != 1 || (unsigned int)(D_00189E20.field_2294 - 0x79) > 1) {
            if (D_L03_001BFDC0.object) {
                unsigned char *record;
                if (func_002ABB78((char *)D_L03_001BFDC0.object))
                    D_00189E20.onFlaggedGroundMoby = 1;
                record = (unsigned char *)func_002AB1F0(D_L03_001BFDC0.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    D_00189E20.onFlaggedGroundMoby = 1;
                record = (unsigned char *)func_002AD0B0(D_L03_001BFDC0.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    D_00189E20.onFlaggedGroundMoby = 1;
            }
            if (D_L03_001BFDC0.count > 0) {
                qcopy(&D_00189E20.groundPoint, D_L03_001BFDC0.position);
                D_00189E20.groundZ = D_L03_001BFDC0.position[2];
                if (D_L03_001A8FF0)
                    D_00189E20.groundZ = func_002B0360((char *)D_L03_001BFDC0.position);
                D_00189E20.groundDistance = fast_vec_dist(&D_00189E20.position, &D_00189E20.groundPoint);
                D_00189E20.groundMoby = (int)D_L03_001BFDC0.object;
                func_001290E0(&D_00189E20.groundNormal, D_L03_001BFDC0.normal);
                D_00189E20.groundSlope = func_L00_002D3EA8(D_L03_001BFDC0.normal);
                D_00189E20.downhillYaw = func_00283248(D_L03_001BFDC0.normal[0], D_L03_001BFDC0.normal[1]);
                FastVecSub(difference, &D_00189E20.groundPoint, &D_00189E20.position);
                if (FastVecDot(difference, &D_00189E20.groundNormal) > 0.0f)
                    D_00189E20.groundDistance = -D_00189E20.groundDistance;
                if (D_00189E20.groundDistance < 0.02f) {
                    D_00189E20.framesOffGround = 0;
                    if (D_00189E20.groundSlope <= 0.8726646900177002f || D_00189E20.gravityMode) {
                        D_00189E20.airFrames = 0;
                        D_00189E20.lastLandedMoby = (int)D_L03_001BFDC0.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (D_00189E20.position.z > D_00189E20.waterSurfaceZ)
        D_00189E20.inWaterFrames = 0;
    if (D_00189E20.airFrames) {
        D_00189E20.groundedFrames = 0;
    } else {
        ++D_00189E20.groundedFrames;
        qcopy(&D_00189E20.lastGroundPoint, &D_00189E20.groundPoint);
    }
    func_00282C88((GroundQuad *)(&D_00189E20.gravityDir));
    switch (D_00189E20.gravityMode) {
    case 0:
        D_00189E20.gravityDir.z = -1.0f;
        break;
    case 1:
        if (D_L03_001A8FF4) {
            func_002AFF60((char *)&D_00189E20.position, (char *)&D_00189E20.gravityDir, 0);
        } else {
            if (D_00189E20.f2f0.w != 0.0f) {
                ApproachValue(&D_00189E20.f2f0.w, 0.0f, 1.0f);
                qcopy(&D_00189E20.gravityDir, &D_00189E20.f2f0);
            } else {
                qcopy(&D_00189E20.gravityDir, &D_00189E20.groundNormal);
                FastVecScale(&D_00189E20.gravityDir, &D_00189E20.gravityDir, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (D_00189E20.referencePoint.w > 0.0f)
                sign = 1.0f;
            FastVecSub(&D_00189E20.gravityDir, &D_00189E20.referencePoint, &D_00189E20.position);
            vec_scale_to_length(&D_00189E20.gravityDir, &D_00189E20.gravityDir, sign);
        }
        break;
    }
    D_00189E20.groundPitch = 0.0f;
    D_00189E20.groundRoll = 0.0f;
    D_00189E20.sideRoll[0] = 0;
    D_00189E20.sideRoll[1] = 0;
    D_00189E20.sidePitch[0] = 0;
    D_00189E20.sidePitch[1] = 0;
    D_00189E20.sideHeight[0] = 0;
    D_00189E20.sideHeight[1] = 0;
    if (D_00189E20.groundDistance < 0.25f &&
        (D_00189E20.controlMode == 0 || D_00189E20.controlMode == 12 || D_00189E20.controlMode == 9 || D_00189E20.controlMode == 7 ||
         (D_00189E20.controlMode == 4 && D_00189E20.f49c) || D_00189E20.controlMode == 1)) {
        func_L00_002B8E48(&D_00189E20.groundNormal, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            D_00189E20.groundPitch = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            D_00189E20.groundRoll = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            func_L00_002D3638(left, 0.2f, angle, 1, 0.44999998807907104f);
            func_L00_002D3638(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (CollLine(left, right, 0x22, D_00189E20.moby, 0)) {
                if (D_L03_001A8FF0) {
                    float firstHeight = func_002B0360((char *)D_L03_001BFDC0.position);
                    D_00189E20.sideHeight[side] = firstHeight - func_002B0360((char *)&D_00189E20.groundPoint);
                } else {
                    D_00189E20.sideHeight[side] = D_L03_001BFDC0.position[2] - D_00189E20.groundZ;
                }
                if (func_00282C48(D_00189E20.sideHeight[side]) > 0.4f)
                    D_00189E20.sideHeight[side] = 0.0f;
                func_001290E0(normal, D_L03_001BFDC0.normal);
                func_L00_002B8E48(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    D_00189E20.sidePitch[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    D_00189E20.sideRoll[side] = angles[0];
            } else {
                D_00189E20.sideHeight[side] = 0.0f;
                D_00189E20.sidePitch[side] = D_00189E20.groundPitch;
                D_00189E20.sideRoll[side] = D_00189E20.groundRoll;
            }
        }
    }
}
