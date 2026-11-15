#include "names.h"
/* Endako's copy of the hero's ground probe. Adapted from OpenRAC/rac1-decomp
 * src/overlays/l05_rilgar/hero_collision.c, HeroL05_GroundProbe (GPL-3.0), and retail.
 * Field names follow the matched copy in L04_002D38E8-probe.c. */
#include "common.h"

extern float FastVecDot(void *, void *);
extern float ApproachValue(float *, float, float);
extern int D_L03_001A8FF0 MACRO_ADDR;
extern void vec_scale_to_length(void *, void *, float);
extern void vec_clear_128(void *);
extern int GetCollHitMaterial(void);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecScale(void *, void *, float);
typedef int GroundQuad __attribute__((mode(TI)));
typedef struct { char prefix[0x18]; unsigned char *object; int count; float position[4]; char gap[16]; float normal[4]; } GroundCollision;
extern int g_current_map_index __attribute__((sda));
extern int D_L03_001A8FF4 __attribute__((sda));
extern GroundCollision D_L03_001BFDC0;
extern int hero_is_in_special_kind_or_mode(void);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int func_L00_002E2048(void);
extern float coll_get_ground_height_at_position(float *, void *);
extern int moby_is_in_special_class_range(char *);
extern char *moby_get_private_value_0(unsigned char *);
extern char *moby_get_private_value_2(unsigned char *);
extern float gravity_get_center_distance(char *);
extern float fast_vec_dist(void *, void *);
extern void func_001290E0(void *, void *);
extern float cam_get_view_space_angle(void *);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_compute_flat_direction_from_point(char *, char *, int);
extern void hero_compute_angles_to_local_dir(void *, float *);
extern void hero_build_relative_offset(float *, float, float, int, float);
extern float math_fabs(float);

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
extern ProbeHero g_hero_state;

/* Checks the ground under the hero each frame and records its height, slope, tilt and type. Also updates the gravity direction and water state. */
void UpdateEndakoHeroGroundContacts(void)
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
    ++g_hero_state.airFrames;
    g_hero_state.groundNormal.z = 1.0f;
    ++g_hero_state.framesOffGround;
    g_hero_state.groundNormal.x = 0;
    g_hero_state.groundNormal.y = 0;
    g_hero_state.groundSlope = 0.0f;
    g_hero_state.groundZ = 0.0f;
    vec_clear_128((GroundQuad *)(&g_hero_state.groundPoint));
    g_hero_state.onFlaggedGroundMoby = 0;
    g_hero_state.groundDistance = 32.0f;
    g_hero_state.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (g_hero_state.inWaterFrames)
        ++g_hero_state.inWaterFrames;
    reach = g_hero_state.capsuleRadius * scale;
    if (g_hero_state.controlMode == 2)
        reach = g_hero_state.capsuleRadius * 2.9f;
    if (hero_is_in_special_kind_or_mode())
        reach = 0.0f;
    BuildOffsetVectorPair(start, end, 1, reach, -48.0f);
    if (CollLine(start, end, 2, g_hero_state.moby, 0)) {
        g_hero_state.groundSoundClass = func_L00_002E2048();
        if (D_L03_001BFDC0.object)
            g_hero_state.groundSoundClass = 0;
        if (g_current_map_index == 7 && D_L03_001BFDC0.object)
            g_hero_state.groundSoundClass = 1;
        g_hero_state.groundType = GetCollHitMaterial();
        if (!g_hero_state.groundType) {
            g_hero_state.waterSurfaceZ = coll_get_ground_height_at_position(D_L03_001BFDC0.position, &g_hero_state.waterSurfaceNormal);
            if (g_hero_state.position.z < g_hero_state.waterSurfaceZ && g_hero_state.inWaterFrames < 1)
                g_hero_state.inWaterFrames = 1;
            if (!CollLine(start, end, 0x24, g_hero_state.moby, 0))
                goto contacts_done;
            g_hero_state.groundSoundClass = func_L00_002E2048();
        }
        if (g_hero_state.groundType != 1 || (unsigned int)(g_hero_state.field_2294 - 0x79) > 1) {
            if (D_L03_001BFDC0.object) {
                unsigned char *record;
                if (moby_is_in_special_class_range((char *)D_L03_001BFDC0.object))
                    g_hero_state.onFlaggedGroundMoby = 1;
                record = (unsigned char *)moby_get_private_value_0(D_L03_001BFDC0.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    g_hero_state.onFlaggedGroundMoby = 1;
                record = (unsigned char *)moby_get_private_value_2(D_L03_001BFDC0.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    g_hero_state.onFlaggedGroundMoby = 1;
            }
            if (D_L03_001BFDC0.count > 0) {
                qcopy(&g_hero_state.groundPoint, D_L03_001BFDC0.position);
                g_hero_state.groundZ = D_L03_001BFDC0.position[2];
                if (D_L03_001A8FF0)
                    g_hero_state.groundZ = gravity_get_center_distance((char *)D_L03_001BFDC0.position);
                g_hero_state.groundDistance = fast_vec_dist(&g_hero_state.position, &g_hero_state.groundPoint);
                g_hero_state.groundMoby = (int)D_L03_001BFDC0.object;
                func_001290E0(&g_hero_state.groundNormal, D_L03_001BFDC0.normal);
                g_hero_state.groundSlope = cam_get_view_space_angle(D_L03_001BFDC0.normal);
                g_hero_state.downhillYaw = mat_fast_helper_a(D_L03_001BFDC0.normal[0], D_L03_001BFDC0.normal[1]);
                FastVecSub(difference, &g_hero_state.groundPoint, &g_hero_state.position);
                if (FastVecDot(difference, &g_hero_state.groundNormal) > 0.0f)
                    g_hero_state.groundDistance = -g_hero_state.groundDistance;
                if (g_hero_state.groundDistance < 0.02f) {
                    g_hero_state.framesOffGround = 0;
                    if (g_hero_state.groundSlope <= 0.8726646900177002f || g_hero_state.gravityMode) {
                        g_hero_state.airFrames = 0;
                        g_hero_state.lastLandedMoby = (int)D_L03_001BFDC0.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (g_hero_state.position.z > g_hero_state.waterSurfaceZ)
        g_hero_state.inWaterFrames = 0;
    if (g_hero_state.airFrames) {
        g_hero_state.groundedFrames = 0;
    } else {
        ++g_hero_state.groundedFrames;
        qcopy(&g_hero_state.lastGroundPoint, &g_hero_state.groundPoint);
    }
    vec_clear_128((GroundQuad *)(&g_hero_state.gravityDir));
    switch (g_hero_state.gravityMode) {
    case 0:
        g_hero_state.gravityDir.z = -1.0f;
        break;
    case 1:
        if (D_L03_001A8FF4) {
            vec_compute_flat_direction_from_point((char *)&g_hero_state.position, (char *)&g_hero_state.gravityDir, 0);
        } else {
            if (g_hero_state.f2f0.w != 0.0f) {
                ApproachValue(&g_hero_state.f2f0.w, 0.0f, 1.0f);
                qcopy(&g_hero_state.gravityDir, &g_hero_state.f2f0);
            } else {
                qcopy(&g_hero_state.gravityDir, &g_hero_state.groundNormal);
                FastVecScale(&g_hero_state.gravityDir, &g_hero_state.gravityDir, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (g_hero_state.referencePoint.w > 0.0f)
                sign = 1.0f;
            FastVecSub(&g_hero_state.gravityDir, &g_hero_state.referencePoint, &g_hero_state.position);
            vec_scale_to_length(&g_hero_state.gravityDir, &g_hero_state.gravityDir, sign);
        }
        break;
    }
    g_hero_state.groundPitch = 0.0f;
    g_hero_state.groundRoll = 0.0f;
    g_hero_state.sideRoll[0] = 0;
    g_hero_state.sideRoll[1] = 0;
    g_hero_state.sidePitch[0] = 0;
    g_hero_state.sidePitch[1] = 0;
    g_hero_state.sideHeight[0] = 0;
    g_hero_state.sideHeight[1] = 0;
    if (g_hero_state.groundDistance < 0.25f &&
        (g_hero_state.controlMode == 0 || g_hero_state.controlMode == 12 || g_hero_state.controlMode == 9 || g_hero_state.controlMode == 7 ||
         (g_hero_state.controlMode == 4 && g_hero_state.f49c) || g_hero_state.controlMode == 1)) {
        hero_compute_angles_to_local_dir(&g_hero_state.groundNormal, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            g_hero_state.groundPitch = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            g_hero_state.groundRoll = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            hero_build_relative_offset(left, 0.2f, angle, 1, 0.44999998807907104f);
            hero_build_relative_offset(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (CollLine(left, right, 0x22, g_hero_state.moby, 0)) {
                if (D_L03_001A8FF0) {
                    float firstHeight = gravity_get_center_distance((char *)D_L03_001BFDC0.position);
                    g_hero_state.sideHeight[side] = firstHeight - gravity_get_center_distance((char *)&g_hero_state.groundPoint);
                } else {
                    g_hero_state.sideHeight[side] = D_L03_001BFDC0.position[2] - g_hero_state.groundZ;
                }
                if (math_fabs(g_hero_state.sideHeight[side]) > 0.4f)
                    g_hero_state.sideHeight[side] = 0.0f;
                func_001290E0(normal, D_L03_001BFDC0.normal);
                hero_compute_angles_to_local_dir(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    g_hero_state.sidePitch[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    g_hero_state.sideRoll[side] = angles[0];
            } else {
                g_hero_state.sideHeight[side] = 0.0f;
                g_hero_state.sidePitch[side] = g_hero_state.groundPitch;
                g_hero_state.sideRoll[side] = g_hero_state.groundRoll;
            }
        }
    }
}
