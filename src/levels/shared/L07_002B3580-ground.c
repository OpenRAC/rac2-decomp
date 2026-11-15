#include "common.h"

extern float FastVecDot(void *, void *);
extern float ApproachValue(float *, float, float);
extern int D_L07_001A8FF0 MACRO_ADDR;
extern void vec_scale_to_length(void *, void *, float);
extern void vec_clear_128(void *);
extern int GetCollHitMaterial(void);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecScale(void *, void *, float);
typedef int GroundQuad __attribute__((mode(TI)));
typedef struct { char prefix[0x18]; unsigned char *object; int count; float position[4]; char gap[16]; float normal[4]; } GroundCollision;
extern int g_current_map_index __attribute__((sda));
extern int D_L07_001A8FF4 __attribute__((sda));
extern GroundCollision D_L07_001BF640;
extern int hero_is_in_special_kind_or_mode(void);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int func_L00_002E2048(void);
extern float coll_get_ground_height_at_position(float *, void *);
extern int moby_is_in_special_class_range(char *);
extern int moby_get_private_value_0(unsigned char *);
extern int moby_get_private_value_2(unsigned char *);
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
extern GroundView g_hero_state;

/* Checks the ground under the hero each frame: finds the floor height and slope, and works out how his feet should tilt. */
void hero_l07_update_ground_contact(void)
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
    ++g_hero_state.field_34e;
    g_hero_state.vector_2a0.field_2a8 = 1.0f;
    ++g_hero_state.field_34c;
    g_hero_state.vector_2a0.field_2a0 = 0;
    g_hero_state.vector_2a0.field_2a4 = 0;
    g_hero_state.slopeAngle = 0.0f;
    g_hero_state.groundHeight = 0.0f;
    vec_clear_128((GroundQuad *)(&g_hero_state.vector_2d0));
    g_hero_state.field_34a = 0;
    g_hero_state.groundDistance = 32.0f;
    g_hero_state.groundObject = 0;
    scale = 2.2f;
    if (g_hero_state.field_338)
        ++g_hero_state.field_338;
    reach = g_hero_state.field_264 * scale;
    if (g_hero_state.field_229c == 2)
        reach = g_hero_state.field_264 * 2.9f;
    if (hero_is_in_special_kind_or_mode())
        reach = 0.0f;
    BuildOffsetVectorPair(start, end, 1, reach, -48.0f);
    if (CollLine(start, end, 2, g_hero_state.field_2290, 0)) {
        g_hero_state.field_149d = func_L00_002E2048();
        if (D_L07_001BF640.object)
            g_hero_state.field_149d = 0;
        if (g_current_map_index == 7 && D_L07_001BF640.object)
            g_hero_state.field_149d = 1;
        g_hero_state.field_1490 = GetCollHitMaterial();
        if (!g_hero_state.field_1490) {
            g_hero_state.field_330 = coll_get_ground_height_at_position(D_L07_001BF640.position, &g_hero_state.vector_2b0);
            if (g_hero_state.vector_80.field_88 < g_hero_state.field_330 && g_hero_state.field_338 < 1)
                g_hero_state.field_338 = 1;
            if (!CollLine(start, end, 0x24, g_hero_state.field_2290, 0))
                goto contacts_done;
            g_hero_state.field_149d = func_L00_002E2048();
        }
        if (g_hero_state.field_1490 == 13) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            g_hero_state.field_330 = D_L07_001BF640.position[2];
            if (!CollLine(start, end, 4, g_hero_state.field_2290, 0))
                goto contacts_done;
        }
        if (g_hero_state.field_1490 == 3) {
            start[2] = D_L07_001BF640.position[2] - 0.01f;
            g_hero_state.field_334 = D_L07_001BF640.position[2];
            if (!CollLine(start, end, 4, g_hero_state.field_2290, 0))
                goto contacts_done;
        }
        if (g_hero_state.field_1490 == 11) {
            g_hero_state.field_334 = D_L07_001BF640.position[2];
        } else {
            if (D_L07_001BF640.object) {
                unsigned char *record;
                if (moby_is_in_special_class_range((char *)D_L07_001BF640.object))
                    g_hero_state.field_34a = 1;
                record = (unsigned char *)moby_get_private_value_0(D_L07_001BF640.object);
                if (record && (*(unsigned short *)(record + 0x1e) & 8))
                    g_hero_state.field_34a = 1;
                record = (unsigned char *)moby_get_private_value_2(D_L07_001BF640.object);
                if (record && (*(unsigned int *)(record + 0x3c) & 8))
                    g_hero_state.field_34a = 1;
            }
            if (D_L07_001BF640.count > 0) {
                qcopy(&g_hero_state.vector_2d0, D_L07_001BF640.position);
                g_hero_state.groundHeight = D_L07_001BF640.position[2];
                if (D_L07_001A8FF0)
                    g_hero_state.groundHeight = gravity_get_center_distance((char *)D_L07_001BF640.position);
                g_hero_state.groundDistance = fast_vec_dist(&g_hero_state.vector_80, &g_hero_state.vector_2d0);
                g_hero_state.groundObject = (int)D_L07_001BF640.object;
                func_001290E0(&g_hero_state.vector_2a0, D_L07_001BF640.normal);
                g_hero_state.slopeAngle = cam_get_view_space_angle(D_L07_001BF640.normal);
                g_hero_state.slopeDirection = mat_fast_helper_a(D_L07_001BF640.normal[0], D_L07_001BF640.normal[1]);
                FastVecSub(difference, &g_hero_state.vector_2d0, &g_hero_state.vector_80);
                if (FastVecDot(difference, &g_hero_state.vector_2a0) > 0.0f)
                    g_hero_state.groundDistance = -g_hero_state.groundDistance;
                if (g_hero_state.groundDistance < 0.02f) {
                    g_hero_state.field_34c = 0;
                    if (g_hero_state.slopeAngle <= 0.8726646900177002f || g_hero_state.field_22c3) {
                        g_hero_state.field_34e = 0;
                        g_hero_state.field_c10 = (int)D_L07_001BF640.object;
                    }
                }
            }
        }
    }
contacts_done:
    if (g_hero_state.vector_80.field_88 > g_hero_state.field_330)
        g_hero_state.field_338 = 0;
    if (g_hero_state.field_34e) {
        g_hero_state.field_340 = 0;
    } else {
        ++g_hero_state.field_340;
        qcopy(&g_hero_state.vector_2e0, &g_hero_state.vector_2d0);
        if (g_hero_state.field_2294 != 56)
            g_hero_state.field_18c0 = 0;
    }
    vec_clear_128((GroundQuad *)(&g_hero_state.vector_2c0));
    switch (g_hero_state.field_22c3) {
    case 0:
        g_hero_state.vector_2c0.field_2c8 = -1.0f;
        break;
    case 1:
        if (D_L07_001A8FF4) {
            vec_compute_flat_direction_from_point((char *)&g_hero_state.vector_80, (char *)&g_hero_state.vector_2c0, 0);
        } else {
            if (g_hero_state.vector_2f0.field_2fc != 0.0f) {
                ApproachValue(&g_hero_state.vector_2f0.field_2fc, 0.0f, 1.0f);
                qcopy(&g_hero_state.vector_2c0, &g_hero_state.vector_2f0);
            } else {
                qcopy(&g_hero_state.vector_2c0, &g_hero_state.vector_2a0);
                FastVecScale(&g_hero_state.vector_2c0, &g_hero_state.vector_2c0, -1.0f);
            }
        }
        break;
    case 2:
        {
            float sign = -1.0f;
            if (g_hero_state.vector_b0.field_bc > 0.0f)
                sign = 1.0f;
            FastVecSub(&g_hero_state.vector_2c0, &g_hero_state.vector_b0, &g_hero_state.vector_80);
            vec_scale_to_length(&g_hero_state.vector_2c0, &g_hero_state.vector_2c0, sign);
        }
        break;
    }
    g_hero_state.field_324 = 0.0f;
    g_hero_state.field_328 = 0.0f;
    g_hero_state.footPitch[0] = 0;
    g_hero_state.footPitch[1] = 0;
    g_hero_state.footYaw[0] = 0;
    g_hero_state.footYaw[1] = 0;
    g_hero_state.footHeight[0] = 0;
    g_hero_state.footHeight[1] = 0;
    if (g_hero_state.groundDistance < 0.25f &&
        (g_hero_state.field_229c == 0 || g_hero_state.field_229c == 12 || g_hero_state.field_229c == 9 || g_hero_state.field_229c == 7 ||
         (g_hero_state.field_229c == 4 && g_hero_state.field_49c) || g_hero_state.field_229c == 1)) {
        hero_compute_angles_to_local_dir(&g_hero_state.vector_2a0, difference);
        if (difference[1] > -0.7853982448577881f && difference[1] < 0.7853982448577881f)
            g_hero_state.field_324 = difference[1];
        if (difference[0] > -0.7853982448577881f && difference[0] < 0.7853982448577881f)
            g_hero_state.field_328 = difference[0];
        for (side = 0; side < 2; ++side) {
            float angle = 1.5707964897155762f;
            if (side == 1)
                angle = -angle;
            hero_build_relative_offset(left, 0.2f, angle, 1, 0.44999998807907104f);
            hero_build_relative_offset(right, 0.2f, angle, 1, -0.44999998807907104f);
            if (CollLine(left, right, 0x22, g_hero_state.field_2290, 0)) {
                if (D_L07_001A8FF0) {
                    float firstHeight = gravity_get_center_distance((char *)D_L07_001BF640.position);
                    g_hero_state.footHeight[side] = firstHeight - gravity_get_center_distance((char *)&g_hero_state.vector_2d0);
                } else {
                    g_hero_state.footHeight[side] = D_L07_001BF640.position[2] - g_hero_state.groundHeight;
                }
                if (math_fabs(g_hero_state.footHeight[side]) > 0.4f)
                    g_hero_state.footHeight[side] = 0.0f;
                func_001290E0(normal, D_L07_001BF640.normal);
                hero_compute_angles_to_local_dir(normal, angles);
                if (angles[1] > -0.7853982448577881f && angles[1] < 0.7853982448577881f)
                    g_hero_state.footYaw[side] = angles[1];
                if (angles[0] > -0.7853982448577881f && angles[0] < 0.7853982448577881f)
                    g_hero_state.footPitch[side] = angles[0];
            } else {
                g_hero_state.footHeight[side] = 0.0f;
                g_hero_state.footYaw[side] = g_hero_state.field_324;
                g_hero_state.footPitch[side] = g_hero_state.field_328;
            }
        }
    }
}
