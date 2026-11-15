#include "common.h"

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
extern HeroCapsuleState D_00189E20;
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(char *, char *);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* Selects and eases the hero collision capsule dimensions for the movement mode. */
void func_L00_002B32F8(void)
{
    switch (gHeroState.vehicle_mode) {
    case 0:
        gHeroState.top_target = 0.8f;
        gHeroState.bottom_target = 0.7f;
        gHeroState.radius_target = 0.44999998807907104f;
        break;
    case 1:
        gHeroState.top_target = 0.5999999642372131f;
        gHeroState.bottom_target = 0.45000001788139343f;
        gHeroState.radius_target = 0.3f;
        break;
    }
    if (gHeroState.control_mode == 4) {
        if (gHeroState.takeoff_frame < gHeroState.state_timer && !gHeroState.past_jump_apex)
            gHeroState.bottom_target = gHeroState.field4b8;
    } else if (gHeroState.move_state == 6) {
        gHeroState.bottom_target = 0.5f;
    } else if (gHeroState.move_state == 4) {
        gHeroState.top_target = 0.3500000238418579f;
    } else if ((unsigned)(gHeroState.control_mode - 17) < 2) {
        gHeroState.top_target = 0.0f;
        gHeroState.bottom_target = 0.0f;
    } else if (gHeroState.field1492 && gHeroState.field340) {
        gHeroState.top_target = 0.8f;
        gHeroState.bottom_target = 0.9f;
    } else if (gHeroState.move_state == 124) {
        gHeroState.radius_target = 0.8f;
    }
    if (!gHeroState.wall_hit || gHeroState.previous_control_mode == 18 ||
        gHeroState.field22b0 == 18 ||
        (gHeroState.vehicle_mode == 0 && gHeroState.capsule_bottom < 0.53f) ||
        gHeroState.control_mode == 17 || gHeroState.base_condition ||
        vec_distance_xy((char *)&gHeroState + 0x240, (char *)&gHeroState + 0x80) >
            gHeroState.radius * 0.5f) {
        ApproachValue(&gHeroState.capsule_top, gHeroState.top_target, 0.02f);
        ApproachValue(&gHeroState.capsule_bottom, gHeroState.bottom_target, 0.02f);
        SpringFloatToGoal(&gHeroState.radius, &gHeroState.radius_velocity,
                     gHeroState.radius_target, 0.02f, 0.3f, 0.0666666701f);
    }
}
