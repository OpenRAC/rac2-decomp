/* func_PAL_L00_002B3210, the PAL copy of func_L00_002B32F8: the same C, where lit 0.024f becomes 0.0288f. */
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
void func_PAL_L00_002B3210(void)
{
    switch (D_00189E20.vehicle_mode) {
    case 0:
        D_00189E20.top_target = 0.8f;
        D_00189E20.bottom_target = 0.7f;
        D_00189E20.radius_target = 0.44999998807907104f;
        break;
    case 1:
        D_00189E20.top_target = 0.5999999642372131f;
        D_00189E20.bottom_target = 0.45000001788139343f;
        D_00189E20.radius_target = 0.3f;
        break;
    }
    if (D_00189E20.control_mode == 4) {
        if (D_00189E20.takeoff_frame < D_00189E20.state_timer && !D_00189E20.past_jump_apex)
            D_00189E20.bottom_target = D_00189E20.field4b8;
    } else if (D_00189E20.move_state == 6) {
        D_00189E20.bottom_target = 0.5f;
    } else if (D_00189E20.move_state == 4) {
        D_00189E20.top_target = 0.3500000238418579f;
    } else if ((unsigned)(D_00189E20.control_mode - 17) < 2) {
        D_00189E20.top_target = 0.0f;
        D_00189E20.bottom_target = 0.0f;
    } else if (D_00189E20.field1492 && D_00189E20.field340) {
        D_00189E20.top_target = 0.8f;
        D_00189E20.bottom_target = 0.9f;
    } else if (D_00189E20.move_state == 124) {
        D_00189E20.radius_target = 0.8f;
    }
    if (!D_00189E20.wall_hit || D_00189E20.previous_control_mode == 18 ||
        D_00189E20.field22b0 == 18 ||
        (D_00189E20.vehicle_mode == 0 && D_00189E20.capsule_bottom < 0.53f) ||
        D_00189E20.control_mode == 17 || D_00189E20.base_condition ||
        func_00282E80((char *)&D_00189E20 + 0x240, (char *)&D_00189E20 + 0x80) >
            D_00189E20.radius * 0.5f) {
        func_002AA2E8(&D_00189E20.capsule_top, D_00189E20.top_target, 0.024f);
        func_002AA2E8(&D_00189E20.capsule_bottom, D_00189E20.bottom_target, 0.024f);
        func_002AA3A8(&D_00189E20.radius, &D_00189E20.radius_velocity,
                     D_00189E20.radius_target, 0.028800001f, 0.43200004f, 0.080000006f);
    }
}
