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
extern HeroCapsuleState g_hero_state;
extern float ApproachValue(float *, float, float);
extern float vec_distance_xy(char *, char *);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Selects and eases the hero collision capsule dimensions for the movement mode. */
void hero_update_collision_capsule(void)
{
    switch (g_hero_state.vehicle_mode) {
    case 0:
        g_hero_state.top_target = 0.8f;
        g_hero_state.bottom_target = 0.7f;
        g_hero_state.radius_target = 0.44999998807907104f;
        break;
    case 1:
        g_hero_state.top_target = 0.5999999642372131f;
        g_hero_state.bottom_target = 0.45000001788139343f;
        g_hero_state.radius_target = 0.3f;
        break;
    }
    if (g_hero_state.control_mode == 4) {
        if (g_hero_state.takeoff_frame < g_hero_state.state_timer && !g_hero_state.past_jump_apex)
            g_hero_state.bottom_target = g_hero_state.field4b8;
    } else if (g_hero_state.move_state == 6) {
        g_hero_state.bottom_target = 0.5f;
    } else if (g_hero_state.move_state == 4) {
        g_hero_state.top_target = 0.3500000238418579f;
    } else if ((unsigned)(g_hero_state.control_mode - 17) < 2) {
        g_hero_state.top_target = 0.0f;
        g_hero_state.bottom_target = 0.0f;
    } else if (g_hero_state.field1492 && g_hero_state.field340) {
        g_hero_state.top_target = 0.8f;
        g_hero_state.bottom_target = 0.9f;
    } else if (g_hero_state.move_state == 124) {
        g_hero_state.radius_target = 0.8f;
    }
    if (!g_hero_state.wall_hit || g_hero_state.previous_control_mode == 18 ||
        g_hero_state.field22b0 == 18 ||
        (g_hero_state.vehicle_mode == 0 && g_hero_state.capsule_bottom < 0.53f) ||
        g_hero_state.control_mode == 17 || g_hero_state.base_condition ||
        vec_distance_xy((char *)&g_hero_state + 0x240, (char *)&g_hero_state + 0x80) >
            g_hero_state.radius * 0.5f) {
        ApproachValue(&g_hero_state.capsule_top, g_hero_state.top_target, 0.02f);
        ApproachValue(&g_hero_state.capsule_bottom, g_hero_state.bottom_target, 0.02f);
        math_spring_float_to_goal(&g_hero_state.radius, &g_hero_state.radius_velocity,
                     g_hero_state.radius_target, 0.02f, 0.3f, 0.0666666701f);
    }
}
