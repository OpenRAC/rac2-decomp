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

extern ProbeHero g_hero_state;
extern unsigned char D_L04_001BFAC0[];
#define hit ((ProbeHit *)D_L04_001BFAC0)
extern int g_current_map_index __attribute__((sda));
extern int D_L04_001A8FF0 __attribute__((sda));
extern int D_L04_001A8FF4 __attribute__((sda));
extern int D_L04_001A8FF0_gp SDATA(D_L04_001A8FF0);

extern float math_fabs(float);
extern void vec_clear_128(void *);
extern int hero_is_in_special_kind_or_mode(void);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int CollLine(void *, void *, int, int, int);
extern int func_L00_002E2048(void);
extern short GetCollHitMaterial(void);
extern float coll_get_ground_height_at_position(void *, void *);
extern int moby_is_in_special_class_range(void *);
extern unsigned char *moby_get_private_value_0(void *);
extern unsigned char *moby_get_private_value_2(void *);
extern float gravity_get_center_distance(void *);
extern float fast_vec_dist(void *, void *);
extern void func_001290E0(void *, void *);
extern float cam_get_view_space_angle(void *);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void vec_compute_flat_direction_from_point(void *, void *, int);
extern void ApproachValue(void *, float, float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void hero_compute_angles_to_local_dir(void *, void *);
extern void hero_build_relative_offset(void *, float, float, float, int);

/* Looks for the ground under the hero each frame, records its slope and type, and sets the gravity direction. */
void Hero_ProbeGround(void)
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

    g_hero_state.groundNormal[2] = 1.0f;
    g_hero_state.airFrames++;
    g_hero_state.framesOffGround++;
    g_hero_state.groundNormal[0] = 0;
    g_hero_state.groundNormal[1] = 0;
    g_hero_state.groundSlope = 0;
    g_hero_state.groundZ = 0;
    vec_clear_128(g_hero_state.groundPoint);
    g_hero_state.onFlaggedGroundMoby = 0;
    g_hero_state.groundDistance = 32.0f;
    g_hero_state.groundMoby = 0;
    /* A constant set once and used once in a later block: update_equiv_regs
     * sinks it after sched1, which gives the mode test's constant and load
     * retail's registers (local-alloc's three-qty sort). */
    scale = 2.2f;
    if (g_hero_state.inWaterFrames) {
        g_hero_state.inWaterFrames++;
    }
    distance = g_hero_state.capsuleRadius * scale;
    if (2 == g_hero_state.controlMode) {
        distance = g_hero_state.capsuleRadius * 2.9f;
    }
    if (hero_is_in_special_kind_or_mode()) {
        distance = 0;
    }
    BuildOffsetVectorPair(start, end, 1, distance, -48.0f);
    if (!CollLine(start, end, 2, g_hero_state.moby, 0)) {
        goto tail;
    }
    g_hero_state.groundSoundClass = func_L00_002E2048();
    if (hit->moby) {
        g_hero_state.groundSoundClass = 0;
    }
    if (g_current_map_index == 7 && hit->moby) {
        g_hero_state.groundSoundClass = 1;
    }
    g_hero_state.groundType = GetCollHitMaterial();
    if (g_hero_state.groundType == 0) {
        g_hero_state.waterSurfaceZ = coll_get_ground_height_at_position(hit->point, g_hero_state.waterSurfaceNormal);
        if (g_hero_state.position[2] < g_hero_state.waterSurfaceZ && g_hero_state.inWaterFrames <= 0) {
            g_hero_state.inWaterFrames = 1;
        }
        if (!CollLine(start, end, 0x24, g_hero_state.moby, 0)) {
            goto tail;
        }
        g_hero_state.groundSoundClass = func_L00_002E2048();
    }
    if (g_hero_state.groundType == 13) {
        g_hero_state.waterSurfaceZ = hit->point[2];
        start[2] = hit->point[2] - 0.01f;
        if (!CollLine(start, end, 4, g_hero_state.moby, 0)) {
            goto tail;
        }
    }
    if (hit->moby) {
        if (moby_is_in_special_class_range(hit->moby)) {
            g_hero_state.onFlaggedGroundMoby = 1;
        }
        flags = moby_get_private_value_0(hit->moby);
        if (flags && (*(unsigned short *)(flags + 0x1E) & 8)) {
            g_hero_state.onFlaggedGroundMoby = 1;
        }
        flags = moby_get_private_value_2(hit->moby);
        if (flags && (*(int *)(flags + 0x3C) & 8)) {
            g_hero_state.onFlaggedGroundMoby = 1;
        }
    }
    if (hit->count > 0) {
        qcopy(g_hero_state.groundPoint, hit->point);
        g_hero_state.groundZ = hit->point[2];
        if (D_L04_001A8FF0) {
            g_hero_state.groundZ = gravity_get_center_distance(hit->point);
        }
        g_hero_state.groundDistance = fast_vec_dist(g_hero_state.position, g_hero_state.groundPoint);
        g_hero_state.groundMoby = (int)hit->moby;
        func_001290E0(g_hero_state.groundNormal, hit->normal);
        g_hero_state.groundSlope = cam_get_view_space_angle(hit->normal);
        g_hero_state.downhillYaw = mat_fast_helper_a(hit->normal[0], hit->normal[1]);
        FastVecSub(geom, g_hero_state.groundPoint, g_hero_state.position);
        if (FastVecDot(geom, g_hero_state.groundNormal) > 0.0f) {
            g_hero_state.groundDistance = -g_hero_state.groundDistance;
        }
        if (g_hero_state.groundDistance < 0.02f) {
            g_hero_state.framesOffGround = 0;
            if (g_hero_state.groundSlope <= 0.87266469f || g_hero_state.gravityMode) {
                g_hero_state.airFrames = 0;
                g_hero_state.lastLandedMoby = (int)hit->moby;
            }
        }
    }
tail:
    if (g_hero_state.position[2] > g_hero_state.waterSurfaceZ) {
        g_hero_state.inWaterFrames = 0;
    }
    if (g_hero_state.airFrames) {
        g_hero_state.groundedFrames = 0;
    } else {
        g_hero_state.groundedFrames++;
        qcopy(g_hero_state.lastGroundPoint, g_hero_state.groundPoint);
    }
    vec_clear_128(g_hero_state.gravityDir);
    switch (g_hero_state.gravityMode) {
    case 0:
        g_hero_state.gravityDir[2] = -1;
        break;
    case 1:
        if (D_L04_001A8FF4) {
            vec_compute_flat_direction_from_point(g_hero_state.position, g_hero_state.gravityDir, 0);
        } else if (g_hero_state.f2fc != 0.0f) {
            ApproachValue(&g_hero_state.f2fc, 0.0f, 1.0f);
            qcopy(g_hero_state.gravityDir, g_hero_state.f2f0);
        } else {
            qcopy(g_hero_state.gravityDir, g_hero_state.groundNormal);
            FastVecScale(g_hero_state.gravityDir, g_hero_state.gravityDir, -1.0f);
        }
        break;
    case 2:
        sign = -1.0f;
        if (g_hero_state.referencePoint[3] > 0) {
            sign = 1.0f;
        }
        FastVecSub(g_hero_state.gravityDir, g_hero_state.referencePoint, g_hero_state.position);
        vec_scale_to_length(g_hero_state.gravityDir, g_hero_state.gravityDir, sign);
        break;
    }
    g_hero_state.groundPitch = 0;
    g_hero_state.groundRoll = 0;
    g_hero_state.sideRoll.i[0] = 0;
    g_hero_state.sideRoll.i[1] = 0;
    g_hero_state.sidePitch.i[0] = 0;
    g_hero_state.sidePitch.i[1] = 0;
    g_hero_state.sideHeight.i[0] = 0;
    g_hero_state.sideHeight.i[1] = 0;
    if (!(g_hero_state.groundDistance < 0.25f)) {
        return;
    }
    if (g_hero_state.controlMode != 0 && g_hero_state.controlMode != 12 && g_hero_state.controlMode != 9 &&
        g_hero_state.controlMode != 7 && !(g_hero_state.controlMode == 4 && g_hero_state.f49c) &&
        g_hero_state.controlMode != 1) {
        return;
    }
    hero_compute_angles_to_local_dir(g_hero_state.groundNormal, geom);
    if (-0.78539824f < geom[1] && geom[1] < 0.78539824f) {
        g_hero_state.groundPitch = geom[1];
    }
    if (-0.78539824f < geom[0] && geom[0] < 0.78539824f) {
        g_hero_state.groundRoll = geom[0];
    }
    for (i = 0; i < 2; i++) {
        angle = 1.57079649f;
        if (i == 1) {
            angle = -angle;
        }
        hero_build_relative_offset(probe1, 0.2f, angle, 0.45f, 1);
        hero_build_relative_offset(probe2, 0.2f, angle, -0.45f, 1);
        if (CollLine(probe1, probe2, 0x22, g_hero_state.moby, 0)) {
            if (D_L04_001A8FF0_gp) {
                g_hero_state.sideHeight.f[i] = gravity_get_center_distance(hit->point) - gravity_get_center_distance(g_hero_state.groundPoint);
            } else {
                g_hero_state.sideHeight.f[i] = hit->point[2] - g_hero_state.groundZ;
            }
            if (math_fabs(g_hero_state.sideHeight.f[i]) > 0.4f) {
                g_hero_state.sideHeight.i[i] = 0;
            }
            func_001290E0(normal, hit->normal);
            hero_compute_angles_to_local_dir(normal, angles);
            if (-0.78539824f < angles[1] && angles[1] < 0.78539824f) {
                g_hero_state.sidePitch.f[i] = angles[1];
            }
            if (-0.78539824f < angles[0] && angles[0] < 0.78539824f) {
                g_hero_state.sideRoll.f[i] = angles[0];
            }
        } else {
            g_hero_state.sideHeight.i[i] = 0;
            g_hero_state.sidePitch.f[i] = g_hero_state.groundPitch;
            g_hero_state.sideRoll.f[i] = g_hero_state.groundRoll;
        }
    }
}
