#include "common.h"

extern float func_00282DB0(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern int D_L07_001A8FF0 MACRO_ADDR;
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern int func_00278E78(void);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282D30(void *, void *, float);
typedef int GroundQuad __attribute__((mode(TI)));
typedef struct { char prefix[0x18]; unsigned char *object; int count; float position[4]; char gap[16]; float normal[4]; } GroundCollision;
extern int D_001A79F0 __attribute__((sda));
extern int D_L07_001A8FF4 __attribute__((sda));
extern GroundCollision D_L07_001BF640;
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
/* This entry is +0x24 inside the catalogued ASM extent, not a new function identity. */

typedef struct GroundView {
    unsigned char pad0[128];
    struct {
        unsigned char pad80[8];
        float field_88;
        unsigned char tail[4];
    } vector_80;
    unsigned char pad90[32];
    struct {
        unsigned char padb0[12];
        float field_bc;
    } vector_b0;
    unsigned char padc0[420];
    float field_264;
    unsigned char pad268[56];
    struct {
        int field_2a0;
        int field_2a4;
        float field_2a8;
        unsigned char tail[4];
    } vector_2a0;
    struct {
        unsigned char tail[16];
    } vector_2b0;
    struct {
        unsigned char pad2c0[8];
        float field_2c8;
        unsigned char tail[4];
    } vector_2c0;
    struct {
        unsigned char tail[16];
    } vector_2d0;
    struct {
        unsigned char tail[16];
    } vector_2e0;
    struct {
        unsigned char pad2f0[12];
        float field_2fc;
    } vector_2f0;
    float footHeight[2];
    float footYaw[2];
    float footPitch[2];
    float groundHeight; /* 0x318 */
    float groundDistance; /* 0x31C */
    float slopeAngle; /* 0x320 */
    float field_324;
    float field_328;
    float slopeDirection; /* 0x32C */
    float field_330;
    float field_334;
    int field_338;
    int groundObject; /* 0x33C */
    int field_340;
    unsigned char pad344[6];
    short field_34a;
    short field_34c;
    short field_34e;
    unsigned char pad350[332];
    unsigned char field_49c;
    unsigned char pad49d[1907];
    int field_c10;
    unsigned char padc14[2172];
    short field_1490;
    unsigned char pad1492[11];
    unsigned char field_149d;
    unsigned char pad149e[1058];
    int field_18c0;
    unsigned char pad18c4[2508];
    char * field_2290;
    int field_2294;
    unsigned char pad2298[4];
    int field_229c;
    unsigned char pad22a0[35];
    unsigned char field_22c3;
} GroundView;
extern GroundView D_00189E20;

/* Checks the ground under the hero each frame: finds the floor height and slope, and works out how his feet should tilt. */
void func_L07_002B3580(void)
{
    float end[4];
    float start[4];
    float difference[4];
    float left[4];
    float right[4];
    float angles[2];
    float normal[4];
    float reach, scale;
    int side;
    ++gHeroState.field_34e;
    gHeroState.vector_2a0.field_2a8 = 1.0f;
    ++gHeroState.field_34c;
    gHeroState.vector_2a0.field_2a0 = 0;
    gHeroState.vector_2a0.field_2a4 = 0;
    gHeroState.slopeAngle = 0.0f;
    gHeroState.groundHeight = 0.0f;
    ClearVector128((GroundQuad *)(&gHeroState.vector_2d0));
    gHeroState.field_34a = 0;
    gHeroState.groundDistance = 32.0f;
    gHeroState.groundObject = 0;
    scale = 2.2f;
    if (gHeroState.field_338)
        ++gHeroState.field_338;
    reach = gHeroState.field_264 * scale;
    if (gHeroState.field_229c == 2)
        reach = gHeroState.field_264 * 2.9f;
    if (IsHeroInSpecialKindOrMode())
        reach = 0.0f;
    BuildOffsetVectorPair(start, end, 1, reach, -48.0f);
    if (CollLine(start, end, 2, gHeroState.field_2290, 0)) {
        gHeroState.field_149d = func_L00_002E2048();
        if (D_L07_001BF640.object)
            gHeroState.field_149d = 0;
        if (gCurrentMapIndex == 7 && D_L07_001BF640.object)
            gHeroState.field_149d = 1;
        gHeroState.field_1490 = GetCollHitMaterial();
        if (!gHeroState.field_1490) {
            gHeroState.field_330 = GetGroundHeightAtPosition(D_L07_001BF640.position, &gHeroState.vector_2b0);
            if (gHeroState.vector_80.field_88 < gHeroState.field_330 && gHeroState.field_338 < 1)
                gHeroState.field_338 = 1;
            if (!CollLine(start, end, 0x24, gHeroState.field_2290, 0))
                goto contacts_done;
            gHeroState.field_149d = func_L00_002E2048();
        }
        if (gHeroState.field_1490 == 13) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            gHeroState.field_330 = D_L07_001BF640.position[2];
            if (!CollLine(start, end, 4, gHeroState.field_2290, 0))
                goto contacts_done;
        }
        if (gHeroState.field_1490 == 3) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            gHeroState.field_334 = D_L07_001BF640.position[2];
            if (!CollLine(start, end, 4, gHeroState.field_2290, 0))
                goto contacts_done;
        }
        if (gHeroState.field_1490 == 11) {
            gHeroState.field_334 = D_L07_001BF640.position[2];
        } else {
            if (D_L07_001BF640.object) {
                unsigned char *record;
                if (IsMobyInSpecialClassRange((char *)D_L07_001BF640.object))
                    gHeroState.field_34a = 1;
                record = (unsigned char *)GetMobyPrivateValue0(D_L07_001BF640.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    gHeroState.field_34a = 1;
                record = (unsigned char *)GetMobyPrivateValue2(D_L07_001BF640.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    gHeroState.field_34a = 1;
            }
            if (D_L07_001BF640.count > 0) {
                qcopy(&gHeroState.vector_2d0, D_L07_001BF640.position);
                gHeroState.groundHeight = D_L07_001BF640.position[2];
                if (D_L07_001A8FF0)
                    gHeroState.groundHeight = GetDistanceFromGravityCenter((char *)D_L07_001BF640.position);
                gHeroState.groundDistance = fast_vec_dist(&gHeroState.vector_80, &gHeroState.vector_2d0);
                gHeroState.groundObject = (int)D_L07_001BF640.object;
                func_001290E0(&gHeroState.vector_2a0, D_L07_001BF640.normal);
                gHeroState.slopeAngle = GetViewSpaceAngle(D_L07_001BF640.normal);
                gHeroState.slopeDirection = FastMatrixHelperA(D_L07_001BF640.normal[0], D_L07_001BF640.normal[1]);
                FastVecSub(difference, &gHeroState.vector_2d0, &gHeroState.vector_80);
                if (FastVecDot(difference, &gHeroState.vector_2a0) > 0.0f)
                    gHeroState.groundDistance = -gHeroState.groundDistance;
                if (gHeroState.groundDistance < 0.02f) {
                    gHeroState.field_34c = 0;
                    if (gHeroState.slopeAngle <= 0.8726646900177002f || gHeroState.field_22c3) {
                        gHeroState.field_34e = 0;
                        gHeroState.field_c10 = (int)D_L07_001BF640.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (gHeroState.vector_80.field_88 > gHeroState.field_330)
        gHeroState.field_338 = 0;
    if (gHeroState.field_34e) {
        gHeroState.field_340 = 0;
    } else {
        ++gHeroState.field_340;
        qcopy(&gHeroState.vector_2e0, &gHeroState.vector_2d0);
        if (gHeroState.field_2294 != 56)
            gHeroState.field_18c0 = 0;
    }
    ClearVector128((GroundQuad *)(&gHeroState.vector_2c0));
    switch (gHeroState.field_22c3) {
    case 0:
        gHeroState.vector_2c0.field_2c8 = -1.0f;
        break;
    case 1:
        if (D_L07_001A8FF4) {
            ComputeFlatDirectionFromPoint((char *)&gHeroState.vector_80, (char *)&gHeroState.vector_2c0, 0);
        } else {
            if (gHeroState.vector_2f0.field_2fc != 0.0f) {
                ApproachValue(&gHeroState.vector_2f0.field_2fc, 0.0f, 1.0f);
                qcopy(&gHeroState.vector_2c0, &gHeroState.vector_2f0);
            } else {
                qcopy(&gHeroState.vector_2c0, &gHeroState.vector_2a0);
                FastVecScale(&gHeroState.vector_2c0, &gHeroState.vector_2c0, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (gHeroState.vector_b0.field_bc > 0.0f)
                sign = 1.0f;
            FastVecSub(&gHeroState.vector_2c0, &gHeroState.vector_b0, &gHeroState.vector_80);
            vec_scale_to_length(&gHeroState.vector_2c0, &gHeroState.vector_2c0, sign);
        }
        break;
    }
    gHeroState.field_324 = 0.0f;
    gHeroState.field_328 = 0.0f;
    gHeroState.footPitch[0] = 0;
    gHeroState.footPitch[1] = 0;
    gHeroState.footYaw[0] = 0;
    gHeroState.footYaw[1] = 0;
    gHeroState.footHeight[0] = 0;
    gHeroState.footHeight[1] = 0;
    if (gHeroState.groundDistance < 0.25f &&
        (gHeroState.field_229c == 0 || gHeroState.field_229c == 12 || gHeroState.field_229c == 9 || gHeroState.field_229c == 7 ||
         (gHeroState.field_229c == 4 && gHeroState.field_49c) || gHeroState.field_229c == 1)) {
        ComputeAnglesToHeroLocalDirection(&gHeroState.vector_2a0, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            gHeroState.field_324 = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            gHeroState.field_328 = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            BuildHeroRelativeOffset(left, 0.2f, angle, 1, 0.44999998807907104f);
            BuildHeroRelativeOffset(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (CollLine(left, right, 0x22, gHeroState.field_2290, 0)) {
                if (D_L07_001A8FF0) {
                    float firstHeight = GetDistanceFromGravityCenter((char *)D_L07_001BF640.position);
                    gHeroState.footHeight[side] = firstHeight - GetDistanceFromGravityCenter((char *)&gHeroState.vector_2d0);
                } else {
                    gHeroState.footHeight[side] = D_L07_001BF640.position[2] - gHeroState.groundHeight;
                }
                if (FloatAbs(gHeroState.footHeight[side]) > 0.4f)
                    gHeroState.footHeight[side] = 0.0f;
                func_001290E0(normal, D_L07_001BF640.normal);
                ComputeAnglesToHeroLocalDirection(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    gHeroState.footYaw[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    gHeroState.footPitch[side] = angles[0];
            } else {
                gHeroState.footHeight[side] = 0.0f;
                gHeroState.footYaw[side] = gHeroState.field_324;
                gHeroState.footPitch[side] = gHeroState.field_328;
            }
        }
    }
}
