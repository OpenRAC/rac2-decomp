#include "include_asm.h"

#include "common.h"
typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0xF0 - 0x60]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    unsigned char pad1A4[0x1B0 - 0x1A4]; float speed, targetSpeed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recoverySpeed;
    unsigned char pad458[0x470 - 0x458]; DriveVector localDirection, targetDirection;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allowAction;
    unsigned char pad49F[0x4AE - 0x49F]; short actionFrame;
    unsigned char pad4B0[12]; float lateralSpeed, inputHeading, targetHeading;
    unsigned char pad4C8[12]; int transition; float inputSpeed, strafeSpeed;
    unsigned char pad4E0[16]; DriveVector jumpDirection;
    unsigned char pad500[0x20]; float recoveryRate; short special;
    unsigned char pad526[7]; unsigned char useCurrentSpeed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pendingDamping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector savedDirection;
    unsigned char pad1450[4]; short overrideDirection;
    unsigned char pad1456[2]; float savedHeading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axisMode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animationSpeed;
} PlayerDriveView;
extern PlayerDriveView g_hero_state;
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView g_drive_velocity_view;
extern int g_hero_input_lock MACRO_ADDR;
extern float g_hero_l01_speed_threshold MACRO_ADDR;
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings g_drive_settings;
extern void hero_build_move_impulse(float, float);
extern void hero_approach_speed(float, float);
extern void hero_steer_heading(int, float, float, float);
extern void func_PAL_L01_002B6870(float);
extern void cam_offset_point_by_side_direction(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_height(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_vector_length(void *, const void *, float);
extern float cam_get_view_space_vector_length(char *);
extern float ApproachValue(float *, float, float);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastDiffRots(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Update directional movement for the active player locomotion state. */
void func_PAL_L01_002B72D0(void)
{
    union { DriveVector q; float f[3]; } local;
    float smoothed;
    float oldHeading;
    int state = g_hero_state.state;

    if (state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
        g_hero_state.targetSpeed = g_hero_state.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &g_hero_state;
        if (g_hero_state.frame > 45) {
            ApproachValue((float *)(&g_hero_state.recoveryRate), 0.010000001f, 0.0028000001f);
        }
        if (g_hero_state.frame <= 45) speed = g_hero_state.recoverySpeed;
        else speed = 0.07000001f;
        hero->speed = speed;
        hero_approach_speed(0.0176f, 0.018000001f);
        cam_set_view_space_vector_length(&g_drive_velocity_view.velocity, &g_drive_velocity_view.velocity, 0.0f);
        cam_offset_point_by_side_direction((DriveVector *)(&g_drive_velocity_view.velocity), (DriveVector *)(&g_drive_velocity_view.velocity), g_drive_velocity_view.targetSpeed);
    } else if (state == 27) {
        if (g_hero_state.frame > 33) {
            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.30019668f);
            func_PAL_L01_002B6870(0.008f);
        }
        if (13.0f <= g_hero_state.plane && g_hero_state.plane <= 3e+01f) {
            if (27.0f < g_hero_state.plane)
                ApproachValue((float *)(&g_hero_state.lateralSpeed), 0.0f, 0.0032000002f);
            else ApproachValue((float *)(&g_hero_state.lateralSpeed), 0.040000003f, 0.0032000002f);
        }
        local.f[0] = g_hero_state.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&g_hero_state.velocity, &g_hero_state.basis);
        matrix_mul_vec3(&g_hero_state.velocity, &local, &g_hero_state);
    } else if (state == 11) {
        g_hero_state.heading = g_hero_state.targetHeading;
        qcopy(&g_hero_state.direction, &g_hero_state.targetDirection);
        hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.13962635f);
        if (g_hero_state.transition != 3) g_hero_state.targetSpeed = g_hero_state.inputSpeed;
        else g_hero_state.targetSpeed = 0.0f;
        if (g_hero_state.useCurrentSpeed != 0) {
            float rate = g_hero_state.animationSpeed * 0.10000001f;
            if (rate < 0.040000003f) rate = 0.040000003f;
            ApproachValue((float *)(&g_hero_state.strafeSpeed), rate, 0.014800001f);
            g_hero_state.targetSpeed = g_hero_state.planarDistance;
        } else {
            if (g_hero_state.allowAction != 0 && g_hero_state.actionFrame <= 9)
                ApproachValue((float *)(&g_hero_state.strafeSpeed), 0.0f, 0.0032000002f);
            else ApproachValue((float *)(&g_hero_state.strafeSpeed), 0.084f, 0.0032000002f);
        }
        if (g_hero_state.axisMode == 0) {
            ((float *)&g_hero_state.velocity)[0] = math_fast_sin_or_cos_a(g_hero_state.inputHeading);
            ((float *)&g_hero_state.velocity)[0] *= g_hero_state.strafeSpeed;
            ((float *)&g_hero_state.velocity)[1] = math_fast_sin_or_cos_b(g_hero_state.inputHeading);
            ((float *)&g_hero_state.velocity)[1] *= g_hero_state.strafeSpeed;
        } else {
            cam_set_view_space_vector_length(&local, &g_hero_state.localDirection, g_hero_state.strafeSpeed);
            cam_set_view_space_height(&local.q, &local.q, 0.0f);
            cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, 0.0f);
            FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &local);
        }
        if (g_hero_state.axisMode == 0 && g_hero_state.useCurrentSpeed == 0) {
            float angle = FastDiffRots(g_hero_state.targetHeading, g_hero_state.inputHeading);
            float cosine = math_fast_sin_or_cos_b(angle);
            float amount = g_hero_state.inputSpeed * cosine;
            float component = math_fast_sin_or_cos_a(g_hero_state.targetHeading);
            ((float *)&g_hero_state.velocity)[0] += component * amount;
            component = math_fast_sin_or_cos_b(g_hero_state.targetHeading);
            ((float *)&g_hero_state.velocity)[1] += component * amount;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
    } else if (state == 17) {
        g_hero_state.heading = ((float *)&g_hero_state.jumpDirection)[3];
        qcopy(&g_hero_state.direction, &g_hero_state.jumpDirection);
        if (g_hero_state.frame > 7) hero_steer_heading(-1, 0.060480002f, 0.28800002f, 0.23736483f);
        if (g_hero_state.frame > 6) {
            if (g_hero_state.request == 0) {
                ((float *)&g_hero_state.velocity)[0] = math_fast_sin_or_cos_a(g_hero_state.heading);
                ((float *)&g_hero_state.velocity)[0] *= 0.09800001f;
                ((float *)&g_hero_state.velocity)[1] = math_fast_sin_or_cos_b(g_hero_state.heading);
                ((float *)&g_hero_state.velocity)[1] *= 0.09800001f;
            } else {
                cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, 0.0f);
                vec_scale_to_length(&local, &g_hero_state.direction, 0.09800001f);
                FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &local);
            }
        }
        g_hero_state.targetSpeed = g_hero_state.planarDistance;
    } else if (state == 129 && g_hero_input_lock == 0) {
        hero_steer_heading(0, 0.057600003f, 0.28800002f, g_hero_state.acceleration);
        g_hero_state.targetSpeed = 0.0f;
    } else {
        oldHeading = g_hero_state.heading;
        qcopy(&local, &g_hero_state.direction);
        if (g_hero_state.overrideDirection != 0) {
            g_hero_state.heading = g_drive_settings.heading;
            qcopy(&g_hero_state.direction, &g_drive_settings.direction);
        }
        hero_steer_heading(0, 0.057600003f, 0.28800002f, g_hero_state.acceleration);
        if (g_hero_state.overrideDirection != 0) {
            g_hero_state.savedHeading = oldHeading;
            qcopy(&g_hero_state.savedDirection, &local);
            g_hero_state.heading = oldHeading;
            qcopy(&g_hero_state.direction, &g_hero_state.savedDirection);
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
        {
            float damping = 0.008f;
            if (g_hero_state.speed < g_hero_l01_speed_threshold * 0.004f) {
                if (g_hero_state.mode == 2) {
                    float rate = g_hero_state.pendingDamping;
                    smoothed = cam_get_view_space_vector_length((char *)&g_hero_state.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, smoothed);
                    return;
                }
                if (g_hero_state.contact != 0) damping = 0.0044f;
                else if (g_hero_state.special != 0) damping = 0.00080000004f;
                else damping = 0.0032000002f;
            }
            func_PAL_L01_002B6870(damping);
        }
    }
}


