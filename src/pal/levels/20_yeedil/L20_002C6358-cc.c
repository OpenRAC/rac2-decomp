/* func_PAL_L20_002C6358, the PAL copy of func_L20_002C63F0: the same C, where lit 0.024f becomes 0.0288f. */
#include "common.h"

extern char D_00189E20[];

/* EE integer and FP argument banks retain their original order. */
extern void func_PAL_L20_002C6358(void);

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
#define CAPSULE (*(HeroCapsuleState *)D_00189E20)
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(char *, char *);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* func_L20_002C5A48 is defined in L20_002C5A48-qcopy.c (its copies need the grouped-copy profile). */

/* func_L20_002C5D00 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

void func_PAL_L20_002C6358(void)
{
    HeroCapsuleState *initial = (HeroCapsuleState *)D_00189E20;
    switch (initial->vehicle_mode) {
    case 1:
        initial->top_target = 0.5999999642372131f;
        initial->bottom_target = 0.45000001788139343f;
        initial->radius_target = 0.3f;
        break;
    case 0:
    case 4:
        initial->top_target = 0.8f;
        initial->bottom_target = 0.7f;
        initial->radius_target = 0.44999998807907104f;
        break;
    }
    if (CAPSULE.control_mode == 4) {
        if (CAPSULE.takeoff_frame < CAPSULE.state_timer && !CAPSULE.past_jump_apex)
            CAPSULE.bottom_target = CAPSULE.field4b8;
    } else if (CAPSULE.move_state == 6) {
        CAPSULE.bottom_target = 0.5f;
    } else if (CAPSULE.move_state == 4) {
        CAPSULE.top_target = 0.3500000238418579f;
    } else if ((unsigned)(CAPSULE.control_mode - 17) < 2) {
        CAPSULE.top_target = 0.0f;
        CAPSULE.bottom_target = 0.0f;
    } else if (CAPSULE.field1492 && CAPSULE.field340) {
        CAPSULE.top_target = 0.8f;
        CAPSULE.bottom_target = 0.9f;
    } else if (CAPSULE.move_state == 124) {
        CAPSULE.radius_target = 0.8f;
    }
    if (!CAPSULE.wall_hit || CAPSULE.previous_control_mode == 18 ||
        CAPSULE.field22b0 == 18 ||
        (CAPSULE.vehicle_mode == 0 && CAPSULE.capsule_bottom < 0.53f) ||
        CAPSULE.control_mode == 17 || CAPSULE.base_condition ||
        func_00282E80((char *)&CAPSULE + 0x240, (char *)&CAPSULE + 0x80) >
            CAPSULE.radius * 0.5f) {
        func_002AA2E8(&CAPSULE.capsule_top, CAPSULE.top_target, 0.024f);
        func_002AA2E8(&CAPSULE.capsule_bottom, CAPSULE.bottom_target, 0.024f);
        func_002AA3A8(&CAPSULE.radius, &CAPSULE.radius_velocity,
                     CAPSULE.radius_target, 0.028800001f, 0.43200004f, 0.080000006f);
    }
}

