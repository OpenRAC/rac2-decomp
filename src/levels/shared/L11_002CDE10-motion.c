#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L00_002D4140(u32, void *, void *);
extern float func_L00_002D3A58(char *);
extern void func_L00_002D3BD8(char *, int, float);
extern float func_L00_002D3B00(char *);
extern void func_L00_002D3B58(TI128 *, TI128 *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(TI128 *);
extern void func_L00_002B5A88(void);
extern void func_L09_002B7238(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_L00_002B5250(void);
extern float func_00282DB0(void *, void *);
extern void func_L00_002D3960(char *, char *);
extern float func_L00_002B5590(void *);
extern void func_00282D30(void *, void *, float);

/* Measured resident prefix; this view does not claim the full hero extent. */
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

extern HeroMotionPrefix D_00189E20;

/* Integrate hero motion, resolve contacts, and measure the resulting displacement. */
void func_L11_002CDE10(void)
{
    MotionVector initial, planar, vertical;
    MotionVector *resolved;
    float limit, magnitude, component, savedW;
    int state;

    qcopy(initial.f, (char *)&gHeroState.position);
    UpdateHeroAttachment(gHeroState.attachment, (char *)&gHeroState.impulse, (u8 *)&gHeroState + 0x90);
    state = gHeroState.state;
    if (state == 0x14 || state == 0x5B || state == 0x58 || state == 0x81) {
        if (gHeroState.collisionOffFrames == 0) {
            magnitude = GetViewSpaceVectorLength((char *)&gHeroState.velocity);
            limit = gHeroState.radius - 0.02f;
            if (limit < magnitude)
                SetViewSpaceVectorLength((char *)&gHeroState.velocity, (int)(char *)&gHeroState.velocity, limit);
        }
        component = GetViewSpaceHeight((char *)&gHeroState.velocity);
        if (component < -gHeroState.downLimit) {
            limit = -gHeroState.downLimit - 0.02f;
            if (limit > 0.0f)
                limit = 0.0f;
            SetViewSpaceHeight((TI128 *)(char *)&gHeroState.velocity, (TI128 *)(char *)&gHeroState.velocity, limit);
        }
    } else if (gHeroState.controlMode != 13) {
        if (gHeroState.controlMode != 14) {
            if (state != 0x44 && gHeroState.collisionOffFrames == 0) {
                magnitude = FastVecLength((char *)&gHeroState.velocity);
                limit = gHeroState.radius - 0.02f;
                if (limit < magnitude)
                    vec_scale_to_length((char *)&gHeroState.velocity, (char *)&gHeroState.velocity, limit);
            }
        }
    }
    FastVecAdd((char *)&gHeroState.position, (char *)&gHeroState.position, (char *)&gHeroState.velocity);
    FastVecAdd((char *)&gHeroState.position, (char *)&gHeroState.position, &gHeroState.extraStep);
    ClearVector128((TI128 *)&gHeroState.extraStep);
    gHeroState.collHit = 0;
    gHeroState.wallHit = 0;
    if (FastVecLength((char *)&gHeroState.impulse) <= 0.0001f) {
        ResolveHeroCollisionWithRewind();
        ProbeHeroGround();
        FastVecSub((char *)&gHeroState.displacement, (char *)&gHeroState.position, initial.f);
        EaseHeroPositionToGoal();
    } else {
        ProbeHeroGround();
    }

    resolved = &gHeroState.projected;
    FastVecSub((char *)resolved, (char *)&gHeroState.position, initial.f);
    qcopy((char *)&gHeroState.flat, (char *)resolved);
    qcopy((char *)&gHeroState.up, (char *)resolved);
    vec_scale_to_length((char *)resolved, (char *)resolved, 1.0f);
    magnitude = FastVecDot((char *)resolved, (char *)&gHeroState.velocity);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)resolved, (char *)&gHeroState.velocity, magnitude);
    qcopy(planar.f, (char *)&gHeroState.velocity);
    ProjectVectorOntoViewPlane((char *)planar.f, (char *)planar.f);
    ProjectVectorOntoViewPlane((char *)&gHeroState.flat, (char *)&gHeroState.flat);
    vec_scale_to_length((char *)&gHeroState.flat, (char *)&gHeroState.flat, 1.0f);
    magnitude = FastVecDot((char *)&gHeroState.flat, planar.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)&gHeroState.flat, planar.f, magnitude);
    qcopy(vertical.f, (char *)&gHeroState.velocity);
    SetViewSpaceVectorLength((char *)vertical.f, (int)vertical.f, 0.0f);
    SetViewSpaceVectorLength((char *)&gHeroState.up, (int)(char *)&gHeroState.up, 0.0f);
    vec_scale_to_length((char *)&gHeroState.up, (char *)&gHeroState.up, 1.0f);
    magnitude = FastVecDot((char *)&gHeroState.up, vertical.f);
    if (magnitude < 0.0f)
        magnitude = 0.0f;
    vec_scale_to_length((char *)&gHeroState.up, vertical.f, magnitude);
    gHeroState.speed = FastVecLength((char *)resolved);
    magnitude = GetViewSpaceVectorLength((char *)resolved);
    planar.q = resolved->q;
    gHeroState.flatSpeed = magnitude;
    gHeroState.forwardSpeed = GetSpeedAlongHeroForward(planar.f);
    gHeroState.verticalSpeed = GetViewSpaceHeight((char *)resolved);
    if (gHeroState.forwardSpeed < 0.0f)
        gHeroState.forwardSpeed = 0.0f;
    qcopy(planar.f, (char *)&gHeroState.position);
    if (FastVecLength((char *)&gHeroState.impulse) > 0.0001f) {
        FastVecAdd((char *)&gHeroState.position, (char *)&gHeroState.position, (char *)&gHeroState.impulse);
        savedW = gHeroState.impulse.f[3];
        ClearVector128((TI128 *)(char *)&gHeroState.impulse);
        gHeroState.impulse.f[3] = savedW;
        ResolveHeroCollisionWithRewind();
        ProbeHeroGround();
        FastVecSub((char *)&gHeroState.displacement, (char *)&gHeroState.position, initial.f);
        EaseHeroPositionToGoal();
    }
    FastVecSub((char *)&gHeroState.impulseMove, (char *)&gHeroState.position, planar.f);
    gHeroState.impulseSpeed = FastVecLength((char *)&gHeroState.impulseMove);
    gHeroState.impulseMove.f[3] = gHeroState.impulse.f[3];
    gHeroState.impulse.f[3] = 0.0f;
    FastVecSub((char *)&gHeroState.displacement, (char *)&gHeroState.position, initial.f);
    gHeroState.slope = 0.0f;
    if (gHeroState.flatSpeed > 0.004f) {
        gHeroState.slope = gHeroState.displacement.f[2] / gHeroState.flatSpeed;
        if (gHeroState.slope > 0.5f)
            gHeroState.slope = 0.5f;
        else if (gHeroState.slope < -0.5f)
            gHeroState.slope = -0.5f;
    }
    if (gHeroState.speed > 0.86666673f) {
        FastVecScale((char *)&gHeroState.displacement, (char *)&gHeroState.displacement, 0.86666673f / gHeroState.speed);
        gHeroState.speed = 0.86666673f;
    }
}
