#include "common.h"

/* the hero object, with the fields this function reads */
typedef struct {
    u8  pad00[0x20];
    f32 axis20[4];
    u8  pad30[0x50];
    f32 position[4];
    u8  pad90[0x156];
    s16 f1E6;
    u8  pad1E8[8];
    s16 air_frames;
    u8  pad1F2[0x26];
    s16 f218;
    u8  pad21A[0x16];
    f32 contact_a[4];
    f32 contact_b[4];
    f32 f250;
    f32 f254;
    u8  pad258[0xC];
    f32 radius;
    u8  pad268[4];
    s32 collision_id;
    u8  pad270[0x17];
    u8  collision_flag;
    u8  pad288[0x38];
    f32 axis2C0[4];
    u8  pad2D0[0x1FC0];
    s32 object;
    u8  pad2294[8];
    s32 control_mode;
    u8  pad22A0[0x14];
    u8  f22B4;
    u8  pad22B5[0xE];
    u8  f22C3;
    u8  pad22C4[0x23A];
    s16 f24FE;
} Hero;

/* -G8 is required for the movement-mode flag at D_001A8FF0. */
extern Hero g_hero_state;
extern char g_collision_quad[];
extern int g_hero_height_zone_active MACRO_ADDR;
extern void vec_clear_128(void *);
extern void hero_check_timed_condition(void);
extern float FastVecDot(void *, void *);
extern void cam_offset_point_in_view_space(void *, void *, float);
extern void hero_build_relative_point(void *, int, float, float, float);
extern void FastVecAdd(void *, void *, void *);
/* EE argument banks retain radius/height in F12/F13 and position/mask/object
   in A0/A1/A2. */
extern int coll_test_point(float, void *, int, int);
extern int func_L00_002E0200(float, float, void *, int, int);
extern int coll_process_triangles(float, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);

/* Moves the hero by a step derived from its control mode and pushes it out of
   anything it hits, up to eight times; returns 1 when the net move is small, -1
   when it exceeds the hero's radius (clamping it first when reason is 15). */
int ResolveHeroPositionCollisions(int reason)
{
    float old[4] __attribute__((aligned(16)));
    float move[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    int grounded;
    int n;
    int hit;

    if (g_hero_state.air_frames)
        return 1;

    qcopy(old, g_hero_state.position);
    vec_clear_128(move);
    if (g_hero_state.f24FE) {
        hero_check_timed_condition();
        g_hero_state.f24FE = 0;
    }

    grounded = 0;
    if (FastVecDot(g_hero_state.axis20, g_hero_state.axis2C0) > -0.92f)
        grounded = 1;

    if (g_hero_state.control_mode != 0x11) {
        if (g_hero_state.f22C3 || g_hero_state.f218 || grounded) {
            if (g_hero_state.f22B4 == 2) {
                cam_offset_point_in_view_space(move, move, 5.0f);
            } else if (g_hero_state.f22C3 == 1 || g_hero_state.f218) {
                hero_build_relative_point(move, 0, 0.0f, 0.0f, 0.6f);
            } else if (g_hero_height_zone_active) {
                cam_offset_point_in_view_space(move, move, 0.77f);
            } else {
                hero_build_relative_point(move, 0, 0.0f, 0.0f, g_hero_state.f254);
            }
        } else {
            move[2] = g_hero_state.f254;
        }
    }
    FastVecAdd(g_hero_state.position, g_hero_state.position, move);

    for (n = 0; n < 8; n++) {
        if (g_hero_state.control_mode == 0x11) {
            if (!coll_test_point(0.6f, g_hero_state.position, 0x24, g_hero_state.object))
                break;
        } else {
            if (g_hero_state.f22C3 || grounded) {
                hit = coll_test_point(g_hero_state.radius, g_hero_state.position, 0x24,
                                    g_hero_state.object) |
                      (g_hero_state.f1E6 ? 0 : coll_process_triangles(g_hero_state.radius,
                                                           g_hero_state.position));
            } else {
                float height = g_hero_state.f250 - g_hero_state.f254;

                if (height < 0.05f)
                    height = 0.05f;
                hit = func_L00_002E0200(g_hero_state.radius, height, g_hero_state.position, 0x24,
                                        g_hero_state.object) |
                      (g_hero_state.f1E6 ? 0 : coll_process_triangles(g_hero_state.radius,
                                                           g_hero_state.position));
            }
            if (!hit)
                break;
        }

        {
            char *collision = g_collision_quad;

            qcopy(g_hero_state.position, collision);
            qcopy(g_hero_state.contact_a, collision + 0x10);
            qcopy(g_hero_state.contact_b, collision - 0x10);
            g_hero_state.collision_flag = 1;
            g_hero_state.collision_id = *(s32 *)(collision - 0x18);
        }
    }

    FastVecSub(g_hero_state.position, g_hero_state.position, move);
    FastVecSub(delta, g_hero_state.position, old);
    if (FastVecLength(delta) > g_hero_state.radius * 1.5f) {
        if (reason == 15) {
            if (delta[0] > 512.0f)
                delta[0] = 512.0f;
            else if (delta[0] < -512.0f)
                delta[0] = -512.0f;
            if (delta[1] > 512.0f)
                delta[1] = 512.0f;
            else if (delta[1] < -512.0f)
                delta[1] = -512.0f;
            if (delta[2] > 512.0f)
                delta[2] = 512.0f;
            else if (delta[2] < -512.0f)
                delta[2] = -512.0f;
            vec_scale_to_length(delta, delta, g_hero_state.radius);
            FastVecAdd(g_hero_state.position, old, delta);
        }
        return -1;
    }
    return 1;
}
