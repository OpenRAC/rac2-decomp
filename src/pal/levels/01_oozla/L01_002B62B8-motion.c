#include "include_asm.h"

#include "common.h"
typedef struct MotionVector {
    float x, y, z, w;
} MotionVector;
typedef int VectorBits __attribute__((mode(TI)));
typedef struct PlayerMotionView {
    u8 pad0[0x80];
    MotionVector position;               
    MotionVector rotation;               
    u8 padA0[0xF0 - 0xA0];
    MotionVector velocity;               
    MotionVector platformDelta;          
    MotionVector displacement;           
    MotionVector resolvedVelocity;       
    MotionVector resolvedVertical;       
    MotionVector resolvedHorizontal;     
    MotionVector platformCarry;          
    u8 pad160[0x170 - 0x160];
    float speed;                         
    float flatSpeed;                     
    float forwardSpeed;                  
    float slope;                         
    float verticalSpeed;                 
    float platformDistance;              
    u8 pad188[0x1F0 - 0x188];
    short collisionOffFrames;            
    u8 pad1F2[0x264 - 0x1F2];
    float capsuleRadius;                 
    u8 pad268[0x26C - 0x268];
    void *hitMoby;                       
    u8 pad270[0x287 - 0x270];
    u8 wallHit;                          
    u8 pad288[0x31C - 0x288];
    float groundDistance;                
    u8 pad320[0x588 - 0x320];
    void *ledgeMoby;                     
    u8 pad58C[0xA60 - 0x58C];
    MotionVector moveImpulse;            
    u8 padA70[0x2294 - 0xA70];
    int state;                           
} PlayerMotionView;
extern PlayerMotionView D_00189E20;
extern void func_PAL_L00_002D4668(void *, void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3BD8(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern float func_L00_002B5590(MotionVector *);
extern void func_L00_002B5A88(void);
extern void func_PAL_L00_002B5178(void);
extern void func_L01_002B5218(void);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);

/* Apply the hero's velocity, resolve contacts, then measure the movement that resulted. */
void func_PAL_L01_002B62B8(void)
{
    MotionVector start __attribute__((aligned(16)));
    /* The horizontal velocity, then the resolved velocity, then the position before the platform move. */
    MotionVector work __attribute__((aligned(16)));
    MotionVector vertical __attribute__((aligned(16)));
    float amount;
    float zero;

    qcopy(&start, &D_00189E20.position);
    func_PAL_L00_002D4668(D_00189E20.ledgeMoby, &D_00189E20.platformDelta, &D_00189E20.rotation);

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
        amount = func_00282DF0(&D_00189E20.velocity);
        if (D_00189E20.capsuleRadius - 0.02f < amount)
            func_00282F20(&D_00189E20.velocity, &D_00189E20.velocity, D_00189E20.capsuleRadius - 0.02f);
    }

    /* Move, then resolve the collisions. */
    func_00282CC0(&D_00189E20.position, &D_00189E20.position, &D_00189E20.velocity);
    func_00282CC0(&D_00189E20.position, &D_00189E20.position, &D_00189E20.moveImpulse);
    func_00282C88(&D_00189E20.moveImpulse);
    D_00189E20.wallHit = 0;
    D_00189E20.hitMoby = 0;
    if (func_00282DF0(&D_00189E20.platformDelta) <= 0.0001f) {
        func_L00_002B5A88();
        func_L01_002B5218();
        func_00282CF0(&D_00189E20.displacement, &D_00189E20.position, &start);
        func_PAL_L00_002B5178();
    } else {
        func_L01_002B5218();
    }

    /* The part of the movement along the velocity, in full and split horizontally and vertically. */
    func_00282CF0(&D_00189E20.resolvedVelocity, &D_00189E20.position, &start);
    qcopy(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedVelocity);
    qcopy(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVelocity);
    zero = 0.0f;
    func_00282F20(&D_00189E20.resolvedVelocity, &D_00189E20.resolvedVelocity, 1.0f);
    {
        float projection = func_00282DB0(&D_00189E20.resolvedVelocity, &D_00189E20.velocity);
        if (projection < zero)
            projection = zero;
        func_00282F20(&D_00189E20.resolvedVelocity, &D_00189E20.velocity, projection);
    }
    qcopy(&work, &D_00189E20.velocity);
    func_L00_002D3960(&work, &work);
    func_L00_002D3960(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedHorizontal);
    func_00282F20(&D_00189E20.resolvedHorizontal, &D_00189E20.resolvedHorizontal, 1.0f);
    {
        float projection = func_00282DB0(&D_00189E20.resolvedHorizontal, &work);
        if (projection < zero)
            projection = zero;
        func_00282F20(&D_00189E20.resolvedHorizontal, &work, projection);
    }
    qcopy(&vertical, &D_00189E20.velocity);
    func_L00_002D3BD8(&vertical, &vertical, zero);
    func_L00_002D3BD8(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVertical, zero);
    func_00282F20(&D_00189E20.resolvedVertical, &D_00189E20.resolvedVertical, 1.0f);
    {
        float projection = func_00282DB0(&D_00189E20.resolvedVertical, &vertical);
        if (projection < zero)
            projection = zero;
        func_00282F20(&D_00189E20.resolvedVertical, &vertical, projection);
    }
    D_00189E20.speed = func_00282DF0(&D_00189E20.resolvedVelocity);
    D_00189E20.flatSpeed = func_L00_002D3A58(&D_00189E20.resolvedVelocity);
    /* A plain value copy here; the other transfers go through qcopy. */
    *(VectorBits *)&work = *(VectorBits *)&D_00189E20.resolvedVelocity;
    D_00189E20.forwardSpeed = func_L00_002B5590(&work);
    D_00189E20.verticalSpeed = func_L00_002D3B00(&D_00189E20.resolvedVelocity);
    if (D_00189E20.forwardSpeed < zero)
        D_00189E20.forwardSpeed = zero;

    /* Then follow the platform, keeping the w of its delta. */
    qcopy(&work, &D_00189E20.position);
    if (0.0001f < func_00282DF0(&D_00189E20.platformDelta)) {
        float saved;

        func_00282CC0(&D_00189E20.position, &D_00189E20.position, &D_00189E20.platformDelta);
        saved = D_00189E20.platformDelta.w;
        func_00282C88(&D_00189E20.platformDelta);
        D_00189E20.platformDelta.w = saved;
        func_L00_002B5A88();
        func_L01_002B5218();
        func_00282CF0(&D_00189E20.displacement, &D_00189E20.position, &start);
        func_PAL_L00_002B5178();
    }
    func_00282CF0(&D_00189E20.platformCarry, &D_00189E20.position, &work);
    D_00189E20.platformDistance = func_00282DF0(&D_00189E20.platformCarry);
    D_00189E20.platformCarry.w = D_00189E20.platformDelta.w;
    D_00189E20.platformDelta.w = zero;

    /* Total displacement, its slope and a cap on its length. */
    func_00282CF0(&D_00189E20.displacement, &D_00189E20.position, &start);
    D_00189E20.slope = zero;
    if (0.004f < D_00189E20.flatSpeed) {
        D_00189E20.slope = D_00189E20.displacement.z / D_00189E20.flatSpeed;
        if (0.5f < D_00189E20.slope)
            D_00189E20.slope = 0.5f;
        else if (D_00189E20.slope < -0.5f)
            D_00189E20.slope = -0.5f;
    }
    if (1.0400001f < D_00189E20.speed) {
        func_00282D30(&D_00189E20.displacement, &D_00189E20.displacement, 1.0400001f / D_00189E20.speed);
        D_00189E20.speed = 1.0400001f;
    }
}
