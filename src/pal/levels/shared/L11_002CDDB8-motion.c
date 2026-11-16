#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void UpdateHeroAttachment_pal(u32, void *, void *);
extern float cam_get_view_space_vector_length(char *);
extern void cam_set_view_space_vector_length(char *, int, float);
extern float cam_get_view_space_height(char *);
extern void cam_set_view_space_height(TI128 *, TI128 *, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(TI128 *);
extern void hero_resolve_collision_with_rewind(void);
extern void hero_probe_ground(void);
extern void FastVecSub(void *, void *, void *);
extern void EaseHeroPositionToGoal_pal(void);
extern float FastVecDot(void *, void *);
extern void cam_project_vector_onto_view_plane(char *, char *);
extern float hero_get_speed_along_forward(void *);
extern void FastVecScale(void *, void *, float);
typedef union MotionVector {
    TI128 q;
    float f[4];
} MotionVector;
typedef struct HeroMotionPrefix {
    u8 unknown00[0x80];
    MotionVector position;
    u8 unknown90[0x60];
    MotionVector velocity, impulse, displacement, projected, up, flat, impulseMove;
    u8 unknown160[0x10];
    float speed, flatSpeed, forwardSpeed, slope, verticalSpeed, impulseSpeed;
    u8 unknown188[0x68];
    short collisionOffFrames;
    u8 unknown1F2[0x72];
    float radius;
    u8 unknown268[4];
    u32 wallHit;
    u8 unknown270[0x17];
    u8 collHit;
    u8 unknown288[0x94];
    float downLimit;
    u8 unknown320[0x268];
    u32 attachment;
    u8 unknown58C[0x4D4];
    MotionVector extraStep;
    u8 unknownA70[0x1824];
    int state;
    u8 unknown2298[4];
    int controlMode;
} HeroMotionPrefix;
extern HeroMotionPrefix g_hero_state;

/* Integrate hero motion, resolve contacts, and measure the resulting displacement. */
void HeroApplyMotionCollision_pal(void)
{
    MotionVector initial, planar, vertical;
    MotionVector *resolved;
    float limit, magnitude, component, saved_w;
    int state;

    qcopy(initial.f, (char *)&g_hero_state.position);
    UpdateHeroAttachment_pal(g_hero_state.attachment, (char *)&g_hero_state.impulse, (u8 *)&g_hero_state + 0x90);
    state = g_hero_state.state;
    if (state == 0x14 || state == 0x5B || state == 0x58 || state == 0x81) {
        if (g_hero_state.collisionOffFrames == 0) {
            magnitude = cam_get_view_space_vector_length((char *)&g_hero_state.velocity);
            limit = g_hero_state.radius - 0.02f;
            if (limit < magnitude)
                cam_set_view_space_vector_length((char *)&g_hero_state.velocity, (int)(char *)&g_hero_state.velocity, limit);
        }
        component = cam_get_view_space_height((char *)&g_hero_state.velocity);
        if (component < -g_hero_state.downLimit) {
            limit = -g_hero_state.downLimit - 0.02f;
            if (limit > 0.0f)
                limit = 0.0f;
            cam_set_view_space_height((TI128 *)(char *)&g_hero_state.velocity, (TI128 *)(char *)&g_hero_state.velocity, limit);
        }
    } else if (g_hero_state.controlMode != 13) {
        if (g_hero_state.controlMode != 14) {
            if (state != 0x44 && g_hero_state.collisionOffFrames == 0) {
                magnitude = FastVecLength((char *)&g_hero_state.velocity);
                limit = g_hero_state.radius - 0.02f;
                if (limit < magnitude)
                    vec_scale_to_length((char *)&g_hero_state.velocity, (char *)&g_hero_state.velocity, limit);
            }
        }
    }
    FastVecAdd((char *)&g_hero_state.position, (char *)&g_hero_state.position, (char *)&g_hero_state.velocity);
    FastVecAdd((char *)&g_hero_state.position, (char *)&g_hero_state.position, &g_hero_state.extraStep);
    vec_clear_128((TI128 *)&g_hero_state.extraStep);
    g_hero_state.collHit = 0;
    g_hero_state.wallHit = 0;
    if (FastVecLength((char *)&g_hero_state.impulse) <= 0.0001f) {
        hero_resolve_collision_with_rewind();
        hero_probe_ground();
        FastVecSub((char *)&g_hero_state.displacement, (char *)&g_hero_state.position, initial.f);
        EaseHeroPositionToGoal_pal();
    } else {
        hero_probe_ground();
    }

    resolved = &g_hero_state.projected;
    FastVecSub((char *)resolved, (char *)&g_hero_state.position, initial.f);
    qcopy((char *)&g_hero_state.flat, (char *)resolved);
    qcopy((char *)&g_hero_state.up, (char *)resolved);
    vec_scale_to_length((char *)resolved, (char *)resolved, 1.0f);
    magnitude = FastVecDot((char *)resolved, (char *)&g_hero_state.velocity);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)resolved, (char *)&g_hero_state.velocity, magnitude);
    qcopy(planar.f, (char *)&g_hero_state.velocity);
    cam_project_vector_onto_view_plane((char *)planar.f, (char *)planar.f);
    cam_project_vector_onto_view_plane((char *)&g_hero_state.flat, (char *)&g_hero_state.flat);
    vec_scale_to_length((char *)&g_hero_state.flat, (char *)&g_hero_state.flat, 1.0f);
    magnitude = FastVecDot((char *)&g_hero_state.flat, planar.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)&g_hero_state.flat, planar.f, magnitude);
    qcopy(vertical.f, (char *)&g_hero_state.velocity);
    cam_set_view_space_vector_length((char *)vertical.f, (int)vertical.f, 0.0f);
    cam_set_view_space_vector_length((char *)&g_hero_state.up, (int)(char *)&g_hero_state.up, 0.0f);
    vec_scale_to_length((char *)&g_hero_state.up, (char *)&g_hero_state.up, 1.0f);
    magnitude = FastVecDot((char *)&g_hero_state.up, vertical.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)&g_hero_state.up, vertical.f, magnitude);
    g_hero_state.speed = FastVecLength((char *)resolved);
    magnitude = cam_get_view_space_vector_length((char *)resolved);
    planar.q = resolved->q;
    g_hero_state.flatSpeed = magnitude;
    g_hero_state.forwardSpeed = hero_get_speed_along_forward(planar.f);
    g_hero_state.verticalSpeed = cam_get_view_space_height((char *)resolved);
    if (g_hero_state.forwardSpeed < 0.0f)
        g_hero_state.forwardSpeed = 0.0f;
    qcopy(planar.f, (char *)&g_hero_state.position);
    if (FastVecLength((char *)&g_hero_state.impulse) > 0.0001f) {
        FastVecAdd((char *)&g_hero_state.position, (char *)&g_hero_state.position, (char *)&g_hero_state.impulse);
        saved_w = g_hero_state.impulse.f[3];
        vec_clear_128((TI128 *)(char *)&g_hero_state.impulse);
        g_hero_state.impulse.f[3] = saved_w;
        hero_resolve_collision_with_rewind();
        hero_probe_ground();
        FastVecSub((char *)&g_hero_state.displacement, (char *)&g_hero_state.position, initial.f);
        EaseHeroPositionToGoal_pal();
    }
    FastVecSub((char *)&g_hero_state.impulseMove, (char *)&g_hero_state.position, planar.f);
    g_hero_state.impulseSpeed = FastVecLength((char *)&g_hero_state.impulseMove);
    g_hero_state.impulseMove.f[3] = g_hero_state.impulse.f[3];
    g_hero_state.impulse.f[3] = 0.0f;
    FastVecSub((char *)&g_hero_state.displacement, (char *)&g_hero_state.position, initial.f);
    g_hero_state.slope = 0.0f;
    if (g_hero_state.flatSpeed > 0.004f) {
        g_hero_state.slope = g_hero_state.displacement.f[2] / g_hero_state.flatSpeed;
        if (g_hero_state.slope > 0.5f)
            g_hero_state.slope = 0.5f;
        else if (g_hero_state.slope < -0.5f)
            g_hero_state.slope = -0.5f;
    }
    if (g_hero_state.speed > 1.0400001f) {
        FastVecScale((char *)&g_hero_state.displacement, (char *)&g_hero_state.displacement, 1.0400001f / g_hero_state.speed);
        g_hero_state.speed = 1.0400001f;
    }
}
