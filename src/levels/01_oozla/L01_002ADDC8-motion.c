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

    qcopy(&start, &D_00189E20.position);
    UpdateHeroAttachment(D_00189E20.ledgeMoby, &D_00189E20.platformDelta, &D_00189E20.rotation);

    /* Keep a step within the collision radius, and a fall within the ground distance. */
    if (D_00189E20.state == 20 || D_00189E20.state == 91 ||
        D_00189E20.state == 88 || D_00189E20.state == 129) {
        if (D_00189E20.collisionOffFrames == 0) {
            amount = func_L00_002D3A58(&D_00189E20.velocity);
            if (D_00189E20.capsuleRadius - 0.02f < amount)
                func_L00_002D3BD8(&D_00189E20.velocity, &D_00189E20.velocity, D_00189E20.capsuleRadius - 0.02f);
        }
        amount = func_L00_002D3B00(&D_00189E20.velocity);
        if (amount < -D_00189E20.groundDistance) {
            amount = -D_00189E20.groundDistance - 0.02f;
            if (0.0f < amount)
                amount = 0.0f;
            func_L00_002D3B58(&D_00189E20.velocity, &D_00189E20.velocity, amount);
        }
    } else if (D_00189E20.collisionOffFrames == 0) {
        amount = FastVecLength(&D_00189E20.velocity);
        if (D_00189E20.capsuleRadius - 0.02f < amount)
            vec_scale_to_length(&D_00189E20.velocity, &D_00189E20.velocity, D_00189E20.capsuleRadius - 0.02f);
    }

    /* Move, then resolve the collisions. */
    FastVecAdd(&D_00189E20.position, &D_00189E20.position, &D_00189E20.velocity);
    FastVecAdd(&D_00189E20.position, &D_00189E20.position, &D_00189E20.moveImpulse);
    func_00282C88(&D_00189E20.moveImpulse);
    D_00189E20.wallHit = 0;
    D_00189E20.hitMoby = 0;
    if (FastVecLength(&D_00189E20.platformDelta) <= 0.0001f) {
        func_L00_002B5A88();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&D_00189E20.displacement, &D_00189E20.position, &start);
        EaseHeroPositionToGoal();
    } else {
        UpdateOozlaHeroGroundContacts();
    }

    /* The part of the movement along the velocity, in full and split horizontally and vertically. */
    FastVecSub(&D_00189E20.resolvedVelocity, &D_00189E20.position, &start);
    qcopy(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedVelocity);
    qcopy(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVelocity);
    zero = 0.0f;
    vec_scale_to_length(&D_00189E20.resolvedVelocity, &D_00189E20.resolvedVelocity, 1.0f);
    {
        float projection = FastVecDot(&D_00189E20.resolvedVelocity, &D_00189E20.velocity);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&D_00189E20.resolvedVelocity, &D_00189E20.velocity, projection);
    }
    qcopy(&work, &D_00189E20.velocity);
    func_L00_002D3960(&work, &work);
    func_L00_002D3960(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedHorizontal);
    vec_scale_to_length(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedHorizontal, 1.0f);
    {
        float projection = FastVecDot(&D_00189E20.resolvedHorizontal, &work);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&D_00189E20.resolvedHorizontal, &work, projection);
    }
    qcopy(&vertical, &D_00189E20.velocity);
    func_L00_002D3BD8(&vertical, &vertical, zero);
    func_L00_002D3BD8(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVertical, zero);
    vec_scale_to_length(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVertical, 1.0f);
    {
        float projection = FastVecDot(&D_00189E20.resolvedVertical, &vertical);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&D_00189E20.resolvedVertical, &vertical, projection);
    }
    D_00189E20.speed = FastVecLength(&D_00189E20.resolvedVelocity);
    D_00189E20.flatSpeed = func_L00_002D3A58(&D_00189E20.resolvedVelocity);
    /* A plain value copy here; the other transfers go through qcopy. */
    *(VectorBits *)&work = *(VectorBits *)&D_00189E20.resolvedVelocity;
    D_00189E20.forwardSpeed = func_L00_002B5590(&work);
    D_00189E20.verticalSpeed = func_L00_002D3B00(&D_00189E20.resolvedVelocity);
    if (D_00189E20.forwardSpeed < zero)
        D_00189E20.forwardSpeed = zero;

    /* Then follow the platform, keeping the w of its delta. */
    qcopy(&work, &D_00189E20.position);
    if (0.0001f < FastVecLength(&D_00189E20.platformDelta)) {
        float saved;

        FastVecAdd(&D_00189E20.position, &D_00189E20.position, &D_00189E20.platformDelta);
        saved = D_00189E20.platformDelta.w;
        func_00282C88(&D_00189E20.platformDelta);
        D_00189E20.platformDelta.w = saved;
        func_L00_002B5A88();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&D_00189E20.displacement, &D_00189E20.position, &start);
        EaseHeroPositionToGoal();
    }
    FastVecSub(&D_00189E20.platformCarry, &D_00189E20.position, &work);
    D_00189E20.platformDistance = FastVecLength(&D_00189E20.platformCarry);
    D_00189E20.platformCarry.w = D_00189E20.platformDelta.w;
    D_00189E20.platformDelta.w = zero;

    /* Total displacement, its slope and a cap on its length. */
    FastVecSub(&D_00189E20.displacement, &D_00189E20.position, &start);
    D_00189E20.slope = zero;
    if (0.004f < D_00189E20.flatSpeed) {
        D_00189E20.slope = D_00189E20.displacement.z / D_00189E20.flatSpeed;
        if (0.5f < D_00189E20.slope)
            D_00189E20.slope = 0.5f;
        else if (D_00189E20.slope < -0.5f)
            D_00189E20.slope = -0.5f;
    }
    if (0.86666673f < D_00189E20.speed) {
        FastVecScale(&D_00189E20.displacement, &D_00189E20.displacement, 0.86666673f / D_00189E20.speed);
        D_00189E20.speed = 0.86666673f;
    }
}
