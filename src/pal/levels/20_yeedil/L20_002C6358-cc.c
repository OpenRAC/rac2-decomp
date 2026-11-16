#include "names.h"
/* func_PAL_L20_002C6358, the PAL copy of func_L20_002C63F0: the same C, where lit 0.024f becomes 0.0288f. */
#include "common.h"

extern char g_hero_state[];

/* EE integer and FP argument banks retain their original order. */
extern void UpdateYeedilHeroCollisionCapsule_pal(void);

typedef struct {
    unsigned char pad0[440];
    int state_timer;
    unsigned char pad1bc[148];
    float capsule_top;
    float capsule_bottom;
    float top_target;
    float bottom_target;
    float radius_target;
    float radius;
    float radius_velocity;
    unsigned char pad26c[27];
    unsigned char wall_hit;
    unsigned char pad288[184];
    int field340;
    unsigned char pad344[346];
    unsigned char past_jump_apex;
    unsigned char pad49f[13];
    short takeoff_frame;
    unsigned char pad4ae[10];
    float field4b8;
    unsigned char pad4bc[4054];
    unsigned char field1492;
    unsigned char pad1493[1];
    unsigned char base_condition;
    unsigned char pad1495[3583];
    int move_state;
    unsigned char pad2298[4];
    int control_mode;
    unsigned char pad22a0[4];
    int previous_control_mode;
    unsigned char pad22a8[8];
    int field22b0;
    unsigned char vehicle_mode;
} HeroCapsuleState;
extern float ApproachValue(float *, float, float);
extern float vec_distance_xy(char *, char *);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* func_L20_002C5A48 is defined in L20_002C5A48-qcopy.c (its copies need the grouped-copy profile). */

/* func_L20_002C5D00 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* Grows or shrinks the hero collision capsule toward the size its current pose needs. (PAL: faster approach rate) */
void UpdateYeedilHeroCollisionCapsule_pal(void)
{
    HeroCapsuleState *hero = (HeroCapsuleState *)g_hero_state;
    switch (hero->vehicle_mode) {
    case 1:
        hero->top_target = 0.5999999642372131f;
        hero->bottom_target = 0.45000001788139343f;
        hero->radius_target = 0.3f;
        break;
    case 0:
    case 4:
        hero->top_target = 0.8f;
        hero->bottom_target = 0.7f;
        hero->radius_target = 0.44999998807907104f;
        break;
    }
    if ((*(HeroCapsuleState *)g_hero_state).control_mode == 4) {
        if ((*(HeroCapsuleState *)g_hero_state).takeoff_frame < (*(HeroCapsuleState *)g_hero_state).state_timer && !(*(HeroCapsuleState *)g_hero_state).past_jump_apex)
            (*(HeroCapsuleState *)g_hero_state).bottom_target = (*(HeroCapsuleState *)g_hero_state).field4b8;
    } else if ((*(HeroCapsuleState *)g_hero_state).move_state == 6) {
        (*(HeroCapsuleState *)g_hero_state).bottom_target = 0.5f;
    } else if ((*(HeroCapsuleState *)g_hero_state).move_state == 4) {
        (*(HeroCapsuleState *)g_hero_state).top_target = 0.3500000238418579f;
    } else if ((unsigned)((*(HeroCapsuleState *)g_hero_state).control_mode - 17) < 2) {
        (*(HeroCapsuleState *)g_hero_state).top_target = 0.0f;
        (*(HeroCapsuleState *)g_hero_state).bottom_target = 0.0f;
    } else if ((*(HeroCapsuleState *)g_hero_state).field1492 && (*(HeroCapsuleState *)g_hero_state).field340) {
        (*(HeroCapsuleState *)g_hero_state).top_target = 0.8f;
        (*(HeroCapsuleState *)g_hero_state).bottom_target = 0.9f;
    } else if ((*(HeroCapsuleState *)g_hero_state).move_state == 124) {
        (*(HeroCapsuleState *)g_hero_state).radius_target = 0.8f;
    }
    if (!(*(HeroCapsuleState *)g_hero_state).wall_hit || (*(HeroCapsuleState *)g_hero_state).previous_control_mode == 18 ||
        (*(HeroCapsuleState *)g_hero_state).field22b0 == 18 ||
        ((*(HeroCapsuleState *)g_hero_state).vehicle_mode == 0 && (*(HeroCapsuleState *)g_hero_state).capsule_bottom < 0.53f) ||
        (*(HeroCapsuleState *)g_hero_state).control_mode == 17 || (*(HeroCapsuleState *)g_hero_state).base_condition ||
        vec_distance_xy((char *)&(*(HeroCapsuleState *)g_hero_state) + 0x240, (char *)&(*(HeroCapsuleState *)g_hero_state) + 0x80) >
            (*(HeroCapsuleState *)g_hero_state).radius * 0.5f) {
        ApproachValue(&(*(HeroCapsuleState *)g_hero_state).capsule_top, (*(HeroCapsuleState *)g_hero_state).top_target, 0.024f);
        ApproachValue(&(*(HeroCapsuleState *)g_hero_state).capsule_bottom, (*(HeroCapsuleState *)g_hero_state).bottom_target, 0.024f);
        math_spring_float_to_goal(&(*(HeroCapsuleState *)g_hero_state).radius, &(*(HeroCapsuleState *)g_hero_state).radius_velocity,
                     (*(HeroCapsuleState *)g_hero_state).radius_target, 0.028800001f, 0.43200004f, 0.080000006f);
    }
}

