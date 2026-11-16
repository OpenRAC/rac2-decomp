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
extern PlayerMotionView g_hero_state;
extern void UpdateHeroAttachment_pal(void *, void *, void *);
extern float cam_get_view_space_vector_length(void *);
extern float cam_get_view_space_height(void *);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern void cam_project_vector_onto_view_plane(void *, void *);
extern float hero_get_speed_along_forward(MotionVector *);
extern void hero_resolve_collision_with_rewind(void);
extern void EaseHeroPositionToGoal_pal(void);
extern void UpdateOozlaHeroGroundContacts(void);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_clear_128(void *);
extern float FastVecLength(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Apply the hero's velocity, resolve contacts, then measure the movement that resulted. */
void ApplyHeroMovementAndResolveDisplacement_pal(void)
{
    MotionVector start __attribute__((aligned(16)));
    /* The horizontal velocity, then the resolved velocity, then the position before the platform move. */
    MotionVector work __attribute__((aligned(16)));
    MotionVector vertical __attribute__((aligned(16)));
    float amount;
    float zero;

    qcopy(&start, &g_hero_state.position);
    UpdateHeroAttachment_pal(g_hero_state.ledgeMoby, &g_hero_state.platformDelta, &g_hero_state.rotation);

    /* Keep a step within the collision radius, and a fall within the ground distance. */
    if (g_hero_state.state == 20 || g_hero_state.state == 91 ||
        g_hero_state.state == 88 || g_hero_state.state == 129) {
        if (g_hero_state.collisionOffFrames == 0) {
            amount = cam_get_view_space_vector_length(&g_hero_state.velocity);
            if (g_hero_state.capsuleRadius - 0.02f < amount)
                cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, g_hero_state.capsuleRadius - 0.02f);
        }
        amount = cam_get_view_space_height(&g_hero_state.velocity);
        if (amount < -g_hero_state.groundDistance) {
            amount = -g_hero_state.groundDistance - 0.02f;
            if (0.0f < amount)
                amount = 0.0f;
            cam_set_view_space_height(&g_hero_state.velocity, &g_hero_state.velocity, amount);
        }
    } else if (g_hero_state.collisionOffFrames == 0) {
        amount = FastVecLength(&g_hero_state.velocity);
        if (g_hero_state.capsuleRadius - 0.02f < amount)
            vec_scale_to_length(&g_hero_state.velocity, &g_hero_state.velocity, g_hero_state.capsuleRadius - 0.02f);
    }

    /* Move, then resolve the collisions. */
    FastVecAdd(&g_hero_state.position, &g_hero_state.position, &g_hero_state.velocity);
    FastVecAdd(&g_hero_state.position, &g_hero_state.position, &g_hero_state.moveImpulse);
    vec_clear_128(&g_hero_state.moveImpulse);
    g_hero_state.wallHit = 0;
    g_hero_state.hitMoby = 0;
    if (FastVecLength(&g_hero_state.platformDelta) <= 0.0001f) {
        hero_resolve_collision_with_rewind();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&g_hero_state.displacement, &g_hero_state.position, &start);
        EaseHeroPositionToGoal_pal();
    } else {
        UpdateOozlaHeroGroundContacts();
    }

    /* The part of the movement along the velocity, in full and split horizontally and vertically. */
    FastVecSub(&g_hero_state.resolvedVelocity, &g_hero_state.position, &start);
    qcopy(&g_hero_state.resolvedHorizontal, &g_hero_state.resolvedVelocity);
    qcopy(&g_hero_state.resolvedVertical, &g_hero_state.resolvedVelocity);
    zero = 0.0f;
    vec_scale_to_length(&g_hero_state.resolvedVelocity, &g_hero_state.resolvedVelocity, 1.0f);
    {
        float projection = FastVecDot(&g_hero_state.resolvedVelocity, &g_hero_state.velocity);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&g_hero_state.resolvedVelocity, &g_hero_state.velocity, projection);
    }
    qcopy(&work, &g_hero_state.velocity);
    cam_project_vector_onto_view_plane(&work, &work);
    cam_project_vector_onto_view_plane(&g_hero_state.resolvedHorizontal, &g_hero_state.resolvedHorizontal);
    vec_scale_to_length(&g_hero_state.resolvedHorizontal, &g_hero_state.resolvedHorizontal, 1.0f);
    {
        float projection = FastVecDot(&g_hero_state.resolvedHorizontal, &work);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&g_hero_state.resolvedHorizontal, &work, projection);
    }
    qcopy(&vertical, &g_hero_state.velocity);
    cam_set_view_space_vector_length(&vertical, &vertical, zero);
    cam_set_view_space_vector_length(&g_hero_state.resolvedVertical, &g_hero_state.resolvedVertical, zero);
    vec_scale_to_length(&g_hero_state.resolvedVertical, &g_hero_state.resolvedVertical, 1.0f);
    {
        float projection = FastVecDot(&g_hero_state.resolvedVertical, &vertical);
        if (projection < zero)
            projection = zero;
        vec_scale_to_length(&g_hero_state.resolvedVertical, &vertical, projection);
    }
    g_hero_state.speed = FastVecLength(&g_hero_state.resolvedVelocity);
    g_hero_state.flatSpeed = cam_get_view_space_vector_length(&g_hero_state.resolvedVelocity);
    /* A plain value copy here; the other transfers go through qcopy. */
    *(VectorBits *)&work = *(VectorBits *)&g_hero_state.resolvedVelocity;
    g_hero_state.forwardSpeed = hero_get_speed_along_forward(&work);
    g_hero_state.verticalSpeed = cam_get_view_space_height(&g_hero_state.resolvedVelocity);
    if (g_hero_state.forwardSpeed < zero)
        g_hero_state.forwardSpeed = zero;

    /* Then follow the platform, keeping the w of its delta. */
    qcopy(&work, &g_hero_state.position);
    if (0.0001f < FastVecLength(&g_hero_state.platformDelta)) {
        float saved;

        FastVecAdd(&g_hero_state.position, &g_hero_state.position, &g_hero_state.platformDelta);
        saved = g_hero_state.platformDelta.w;
        vec_clear_128(&g_hero_state.platformDelta);
        g_hero_state.platformDelta.w = saved;
        hero_resolve_collision_with_rewind();
        UpdateOozlaHeroGroundContacts();
        FastVecSub(&g_hero_state.displacement, &g_hero_state.position, &start);
        EaseHeroPositionToGoal_pal();
    }
    FastVecSub(&g_hero_state.platformCarry, &g_hero_state.position, &work);
    g_hero_state.platformDistance = FastVecLength(&g_hero_state.platformCarry);
    g_hero_state.platformCarry.w = g_hero_state.platformDelta.w;
    g_hero_state.platformDelta.w = zero;

    /* Total displacement, its slope and a cap on its length. */
    FastVecSub(&g_hero_state.displacement, &g_hero_state.position, &start);
    g_hero_state.slope = zero;
    if (0.004f < g_hero_state.flatSpeed) {
        g_hero_state.slope = g_hero_state.displacement.z / g_hero_state.flatSpeed;
        if (0.5f < g_hero_state.slope)
            g_hero_state.slope = 0.5f;
        else if (g_hero_state.slope < -0.5f)
            g_hero_state.slope = -0.5f;
    }
    if (1.0400001f < g_hero_state.speed) {
        FastVecScale(&g_hero_state.displacement, &g_hero_state.displacement, 1.0400001f / g_hero_state.speed);
        g_hero_state.speed = 1.0400001f;
    }
}
