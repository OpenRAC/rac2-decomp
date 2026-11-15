/* Shares the typed hero-motion layout with L04_002CC748-movement.c.
 * The dedicated -g profile retains retail padding before the slope division.
 */
#include "common.h"

extern unsigned char D_00189E20[];
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);

typedef int MovementQuadword __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} MovementVector;
typedef struct {
    unsigned char pad_0[0x80];
    float position[4];
    float rotation[4];
    unsigned char pad_a0[0x50];
    float velocity[4];
    MovementVector surface_motion;
    MovementVector displacement;
    float resolved_velocity[4];
    float resolved_velocity_xy[4];
    float resolved_velocity_planar[4];
    MovementVector surface_displacement;
    unsigned char pad_160[0x10];
    float speed;
    float planar_speed;
    float forward_speed;
    float slope;
    float vertical_speed;
    float surface_speed;
    unsigned char pad_188[0x68];
    short air_frames;
    unsigned char pad_1f2[0x72];
    float speed_limit;
    unsigned char pad_268[0x4];
    int collision_count;
    unsigned char pad_270[0x17];
    unsigned char collision_flag;
    unsigned char pad_288[0x94];
    float fall_speed_limit;
    unsigned char pad_320[0x268];
    int collision_mode;
    unsigned char pad_58c[0x4d4];
    float move_impulse[4];
    unsigned char pad_a70[0x1824];
    int state;
    unsigned char pad_2298[0x4];
    int control_mode;
} MovementHero;
#define MOVE_HERO (*(MovementHero *)&D_00189E20)
extern void func_L00_002D4140(int, void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3BD8(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern void func_00282C88(void *);
extern float func_00282E20(void *);
extern void func_00282F70(void *, void *, float);
extern void func_L00_002B5A88(void);
extern void func_L00_002B4900(void);
extern void func_L00_002B5250(void);
extern float func_L00_002B5590(void *);
/* Apply the hero's velocity and surface motion, then measure resolved displacement. */
void func_L00_002B5B60(void) {
    float old[4], horizontal[4], flat[4];

    qcopy(old, &MOVE_HERO.position);
    UpdateHeroAttachment(MOVE_HERO.collision_mode, &MOVE_HERO.surface_motion,
                      &MOVE_HERO.rotation);
    if (MOVE_HERO.state == 0x14 || MOVE_HERO.state == 0x5B ||
        MOVE_HERO.state == 0x58 || MOVE_HERO.state == 0x81) {
        if (MOVE_HERO.air_frames == 0) {
            if (func_L00_002D3A58(&MOVE_HERO.velocity) > MOVE_HERO.speed_limit - 0.02f) {
                func_L00_002D3BD8(&MOVE_HERO.velocity, &MOVE_HERO.velocity,
                                  MOVE_HERO.speed_limit - 0.02f);
            }
        }
        if (func_L00_002D3B00(&MOVE_HERO.velocity) < -MOVE_HERO.fall_speed_limit) {
            float x = -MOVE_HERO.fall_speed_limit - 0.02f;
            if (x > 0.0f) x = 0.0f;
            func_L00_002D3B58(&MOVE_HERO.velocity, &MOVE_HERO.velocity, x);
        }
    } else if (MOVE_HERO.control_mode == 15) {
        if (MOVE_HERO.air_frames == 0) {
            if (vec_length_xy(&MOVE_HERO.velocity) > MOVE_HERO.speed_limit - 0.02f) {
                func_00282F70(&MOVE_HERO.velocity, &MOVE_HERO.velocity,
                             MOVE_HERO.speed_limit - 0.02f);
            }
        }
    } else {
        if (MOVE_HERO.control_mode == 13) goto integrate;
        if (MOVE_HERO.control_mode == 14) goto integrate;
        if (MOVE_HERO.state == 68) goto integrate;
        if (MOVE_HERO.air_frames != 0) goto integrate;
        if (FastVecLength(&MOVE_HERO.velocity) > MOVE_HERO.speed_limit - 0.02f) {
            vec_scale_to_length((float *)&MOVE_HERO.velocity, (float *)&MOVE_HERO.velocity,
                          MOVE_HERO.speed_limit - 0.02f);
        }
    }
integrate:
    FastVecAdd(&MOVE_HERO.position, &MOVE_HERO.position, &MOVE_HERO.velocity);
    FastVecAdd(&MOVE_HERO.position, &MOVE_HERO.position, &MOVE_HERO.move_impulse);
    func_00282C88(&MOVE_HERO.move_impulse);
    MOVE_HERO.collision_flag = 0;
    MOVE_HERO.collision_count = 0;
    if (FastVecLength(&MOVE_HERO.surface_motion) <= 0.0001f) {
        func_L00_002B5A88();
        func_L00_002B4900();
        FastVecSub((float *)&MOVE_HERO.displacement, (float *)&MOVE_HERO.position, old);
        EaseHeroPositionToGoal();
    } else {
        func_L00_002B4900();
    }
    FastVecSub((float *)&MOVE_HERO.resolved_velocity, (float *)&MOVE_HERO.position, old);
    qcopy(&MOVE_HERO.resolved_velocity_planar, &MOVE_HERO.resolved_velocity);
    qcopy(&MOVE_HERO.resolved_velocity_xy, &MOVE_HERO.resolved_velocity);
    vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity,
                  (float *)&MOVE_HERO.resolved_velocity, 1.0f);
    {
        float x = FastVecDot(&MOVE_HERO.resolved_velocity, &MOVE_HERO.velocity);
        if (x < 0.0f) x = 0.0f;
        vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity, (float *)&MOVE_HERO.velocity, x);
    }
    qcopy(horizontal, &MOVE_HERO.velocity);
    func_L00_002D3960(horizontal, horizontal);
    func_L00_002D3960(&MOVE_HERO.resolved_velocity_planar, &MOVE_HERO.resolved_velocity_planar);
    vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity_planar,
                  (float *)&MOVE_HERO.resolved_velocity_planar, 1.0f);
    {
        float x = FastVecDot(&MOVE_HERO.resolved_velocity_planar, horizontal);
        if (x < 0.0f) x = 0.0f;
        vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity_planar, horizontal, x);
    }
    qcopy(flat, &MOVE_HERO.velocity);
    func_L00_002D3BD8(flat, flat, 0.0f);
    func_L00_002D3BD8(&MOVE_HERO.resolved_velocity_xy, &MOVE_HERO.resolved_velocity_xy, 0.0f);
    vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity_xy,
                  (float *)&MOVE_HERO.resolved_velocity_xy, 1.0f);
    {
        float x = FastVecDot(&MOVE_HERO.resolved_velocity_xy, flat);
        if (x < 0.0f) x = 0.0f;
        vec_scale_to_length((float *)&MOVE_HERO.resolved_velocity_xy, flat, x);
    }
    MOVE_HERO.speed = FastVecLength(&MOVE_HERO.resolved_velocity);
    MOVE_HERO.planar_speed = func_L00_002D3A58(&MOVE_HERO.resolved_velocity);
    *(MovementQuadword *)horizontal = *(MovementQuadword *)&MOVE_HERO.resolved_velocity;
    MOVE_HERO.forward_speed = func_L00_002B5590(horizontal);
    MOVE_HERO.vertical_speed = func_L00_002D3B00(&MOVE_HERO.resolved_velocity);
    if (MOVE_HERO.forward_speed < 0.0f) MOVE_HERO.forward_speed = 0.0f;
    qcopy(horizontal, &MOVE_HERO.position);
    if (FastVecLength(&MOVE_HERO.surface_motion) > 0.0001f) {
        float x;
        FastVecAdd(&MOVE_HERO.position, &MOVE_HERO.position, &MOVE_HERO.surface_motion);
        x = MOVE_HERO.surface_motion.w;
        func_00282C88(&MOVE_HERO.surface_motion);
        MOVE_HERO.surface_motion.w = x;
        func_L00_002B5A88();
        func_L00_002B4900();
        FastVecSub((float *)&MOVE_HERO.displacement, (float *)&MOVE_HERO.position, old);
        EaseHeroPositionToGoal();
    }
    FastVecSub((float *)&MOVE_HERO.surface_displacement, (float *)&MOVE_HERO.position,
                  horizontal);
    MOVE_HERO.surface_speed = FastVecLength(&MOVE_HERO.surface_displacement);
    MOVE_HERO.surface_displacement.w = MOVE_HERO.surface_motion.w;
    MOVE_HERO.surface_motion.w = 0.0f;
    FastVecSub((float *)&MOVE_HERO.displacement, (float *)&MOVE_HERO.position, old);
    MOVE_HERO.slope = 0.0f;
    if (MOVE_HERO.planar_speed > 0.004f) {
        MOVE_HERO.slope = MOVE_HERO.displacement.z / MOVE_HERO.planar_speed;
        if (MOVE_HERO.slope > 0.5f) MOVE_HERO.slope = 0.5f;
        else if (MOVE_HERO.slope < -0.5f) MOVE_HERO.slope = -0.5f;
    }
    if (MOVE_HERO.speed > 0.8666667342185974f) {
        FastVecScale(&MOVE_HERO.displacement, &MOVE_HERO.displacement,
                      0.8666667342185974f / MOVE_HERO.speed);
        MOVE_HERO.speed = 0.8666667342185974f;
    }
}
