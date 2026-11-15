#include "common.h"

typedef struct MotionVector {
    float x, y, z, w;
} MotionVector;
typedef int VectorBits __attribute__((mode(TI)));

/* The hero (D_00189E20) fields the motion step uses. */
typedef struct PlayerMotionView {
    u8 pad0[0x80];
    MotionVector position;              /* 0x80 */
    MotionVector rotation;              /* 0x90 */
    u8 padA0[0xF0 - 0xA0];
    MotionVector velocity;              /* 0xF0 */
    MotionVector platformDelta;         /* 0x100: movement of the attached platform this frame */
    MotionVector displacement;          /* 0x110 */
    MotionVector resolvedVelocity;      /* 0x120 */
    MotionVector resolvedVertical;      /* 0x130 */
    MotionVector resolvedHorizontal;    /* 0x140 */
    MotionVector platformCarry;         /* 0x150 */
    u8 pad160[0x170 - 0x160];
    float speed;                        /* 0x170 */
    float flatSpeed;                    /* 0x174 */
    float forwardSpeed;                 /* 0x178 */
    float slope;                        /* 0x17C */
    float verticalSpeed;                /* 0x180 */
    float platformDistance;             /* 0x184 */
    u8 pad188[0x1F0 - 0x188];
    short collisionOffFrames;           /* 0x1F0 */
    u8 pad1F2[0x264 - 0x1F2];
    float capsuleRadius;                /* 0x264 */
    u8 pad268[0x26C - 0x268];
    void *hitMoby;                      /* 0x26C */
    u8 pad270[0x287 - 0x270];
    u8 wallHit;                         /* 0x287 */
    u8 pad288[0x31C - 0x288];
    float groundDistance;               /* 0x31C */
    u8 pad320[0x588 - 0x320];
    void *ledgeMoby;                    /* 0x588 */
    u8 pad58C[0xA60 - 0x58C];
    MotionVector moveImpulse;           /* 0xA60: added to the position once, then cleared */
    u8 padA70[0x2294 - 0xA70];
    int state;                          /* 0x2294 */
} PlayerMotionView;
extern PlayerMotionView D_00189E20;

extern void func_L00_002D4140(void *, void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3BD8(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern float func_L00_002B5590(MotionVector *);
extern void func_L00_002B5A88(void);
extern void func_L00_002B5250(void);
extern void func_L01_002B5218(void);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);

/* Apply the hero's velocity, resolve contacts, then measure the movement that resulted. */
void func_L01_002B6390(void)
{
    MotionVector start __attribute__((aligned(16)));
    /* The horizontal velocity, then the resolved velocity, then the position before the platform move. */
    MotionVector work __attribute__((aligned(16)));
    MotionVector vertical __attribute__((aligned(16)));
    float amount;
    float zero;

    qcopy(&start, &gHeroState.position);
    UpdateHeroAttachment(gHeroState.ledgeMoby, &gHeroState.platformDelta, &gHeroState.rotation);

    /* Keep a step within the collision radius, and a fall within the ground distance. */
    if (gHeroState.state == 20 || gHeroState.state == 91 ||
        gHeroState.state == 88 || gHeroState.state == 129) {
        if (gHeroState.collisionOffFrames == 0) {
            amount = GetViewSpaceVectorLength(&gHeroState.velocity);
            if (gHeroState.capsuleRadius - 0.02f < amount)
                SetViewSpaceVectorLength(&gHeroState.velocity, &gHeroState.velocity, gHeroState.capsuleRadius - 0.02f);
        }
        amount = GetViewSpaceHeight(&gHeroState.velocity);
        if (amount < -gHeroState.groundDistance) {
            amount = -gHeroState.groundDistance - 0.02f;
            if (0.0f < amount)
                amount = 0.0f;
            SetViewSpaceHeight(&gHeroState.velocity, &gHeroState.velocity, amount);
        }
    } else if (gHeroState.collisionOffFrames == 0) {
        amount = FastVecLength(&gHeroState.velocity);
        if (gHeroState.capsuleRadius - 0.02f < amount)
            vec_scale_to_length(&gHeroState.velocity, &gHeroState.velocity, gHeroState.capsuleRadius - 0.02f);
    }

    /* Move, then resolve the collisions. */
    FastVecAdd(&gHeroState.position, &gHeroState.position, &gHeroState.velocity);
    FastVecAdd(&gHeroState.position, &gHeroState.position, &gHeroState.moveImpulse);
    ClearVector128(&gHeroState.moveImpulse);
    gHeroState.wallHit = 0;
    gHeroState.hitMoby = 0;
    if (FastVecLength(&gHeroState.platformDelta) <= 0.0001f) {
        ResolveHeroCollisionWithRewind();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&gHeroState.displacement, &gHeroState.position, &start);
        EaseHeroPositionToGoal();
    } else {
        UpdateOozlaHeroGroundContacts();
    }

    /* The part of the movement along the velocity, in full and split horizontally and vertically. */
    FastVecSub(&gHeroState.resolvedVelocity, &gHeroState.position, &start);
    qcopy(&gHeroState.resolvedHorizontal, &gHeroState.resolvedVelocity);
    qcopy(&gHeroState.resolvedVertical, &gHeroState.resolvedVelocity);
    zero = 0.0f;
    vec_scale_to_length(&gHeroState.resolvedVelocity, &gHeroState.resolvedVelocity, 1.0f);
    {
        float projection = FastVecDot(&gHeroState.resolvedVelocity, &gHeroState.velocity);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&gHeroState.resolvedVelocity, &gHeroState.velocity, projection);
    }
    qcopy(&work, &gHeroState.velocity);
    ProjectVectorOntoViewPlane(&work, &work);
    ProjectVectorOntoViewPlane(&gHeroState.resolvedHorizontal, &gHeroState.resolvedHorizontal);
    vec_scale_to_length(&gHeroState.resolvedHorizontal, &gHeroState.resolvedHorizontal, 1.0f);
    {
        float projection = FastVecDot(&gHeroState.resolvedHorizontal, &work);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&gHeroState.resolvedHorizontal, &work, projection);
    }
    qcopy(&vertical, &gHeroState.velocity);
    SetViewSpaceVectorLength(&vertical, &vertical, zero);
    SetViewSpaceVectorLength(&gHeroState.resolvedVertical, &gHeroState.resolvedVertical, zero);
    vec_scale_to_length(&gHeroState.resolvedVertical, &gHeroState.resolvedVertical, 1.0f);
    {
        float projection = FastVecDot(&gHeroState.resolvedVertical, &vertical);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&gHeroState.resolvedVertical, &vertical, projection);
    }
    gHeroState.speed = FastVecLength(&gHeroState.resolvedVelocity);
    gHeroState.flatSpeed = GetViewSpaceVectorLength(&gHeroState.resolvedVelocity);
    /* A plain value copy here; the other transfers go through qcopy. */
    *(VectorBits *)&work = *(VectorBits *)&gHeroState.resolvedVelocity;
    gHeroState.forwardSpeed = GetSpeedAlongHeroForward(&work);
    gHeroState.verticalSpeed = GetViewSpaceHeight(&gHeroState.resolvedVelocity);
    if (gHeroState.forwardSpeed < zero)
        gHeroState.forwardSpeed = zero;

    /* Then follow the platform, keeping the w of its delta. */
    qcopy(&work, &gHeroState.position);
    if (0.0001f < FastVecLength(&gHeroState.platformDelta)) {
        float saved;

        FastVecAdd(&gHeroState.position, &gHeroState.position, &gHeroState.platformDelta);
        saved = gHeroState.platformDelta.w;
        ClearVector128(&gHeroState.platformDelta);
        gHeroState.platformDelta.w = saved;
        ResolveHeroCollisionWithRewind();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&gHeroState.displacement, &gHeroState.position, &start);
        EaseHeroPositionToGoal();
    }
    FastVecSub(&gHeroState.platformCarry, &gHeroState.position, &work);
    gHeroState.platformDistance = FastVecLength(&gHeroState.platformCarry);
    gHeroState.platformCarry.w = gHeroState.platformDelta.w;
    gHeroState.platformDelta.w = zero;

    /* Total displacement, its slope and a cap on its length. */
    FastVecSub(&gHeroState.displacement, &gHeroState.position, &start);
    gHeroState.slope = zero;
    if (0.004f < gHeroState.flatSpeed) {
        gHeroState.slope = gHeroState.displacement.z / gHeroState.flatSpeed;
        if (0.5f < gHeroState.slope)
            gHeroState.slope = 0.5f;
        else if (gHeroState.slope < -0.5f)
            gHeroState.slope = -0.5f;
    }
    if (0.86666673f < gHeroState.speed) {
        FastVecScale(&gHeroState.displacement, &gHeroState.displacement, 0.86666673f / gHeroState.speed);
        gHeroState.speed = 0.86666673f;
    }
}
