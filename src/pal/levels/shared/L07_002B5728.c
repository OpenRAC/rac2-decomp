#include "include_asm.h"

#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0x98 - 0x60]; float rotation;
    unsigned char pad9C[0xF0 - 0x9C]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pending_result;
    float distance, planar_distance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    float yaw_rate, yaw_error;
    unsigned char pad1AC[4]; float speed, target_speed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recovery_speed;
    unsigned char pad458[0x470 - 0x458]; DriveVector local_direction, target_direction;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allow_action;
    unsigned char pad49F[0x4AE - 0x49F]; short action_frame;
    unsigned char pad4B0[12]; float lateral_speed, input_heading, target_heading;
    unsigned char pad4C8[12]; int transition; float input_speed, strafe_speed;
    unsigned char pad4E0[16]; DriveVector jump_direction;
    unsigned char pad500[0x20]; float recovery_rate; short special;
    unsigned char pad526[7]; unsigned char use_current_speed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pending_damping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector saved_direction;
    unsigned char pad1450[4]; short override_direction;
    unsigned char pad1456[2]; float saved_heading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axis_mode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animation_speed;
} PlayerDriveView;
extern PlayerDriveView g_hero_state;
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float target_speed;
} DriveVelocityView;
extern DriveVelocityView g_drive_velocity_view;
extern int g_hero_l07_lock_flag MACRO_ADDR;
extern float g_hero_speed_scale MACRO_ADDR;
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings g_hero_l07_state_block;
extern void hero_build_move_impulse(float, float);
extern void hero_approach_speed(float, float);
extern void hero_steer_heading(int, float, float, float);
extern void hero_approach_velocity_pal(float);
extern void cam_offset_point_by_side_direction(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_height(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_vector_length(void *, const void *, float);
extern float cam_get_view_space_vector_length(char *);
extern float ApproachValue(float *, float, float);
extern float math_approach_with_velocity(float *, float *, int, float, float, float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_start_pose_offset(float, float, float);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastDiffRots(float, float);
extern void FastVecAdd(void *, void *, void *);

/* Update directional movement, including the state-44 yaw spring.
 * Shares the resident views and locomotion arms with func_L01_002B7360. */
void UpdateHeroVelocityForStateWithYawSpring_pal(void)
{
    union { DriveVector q; float f[3]; } local;
    float smoothed;
    float old_heading;
    int state = g_hero_state.state;

    if (state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pending_result, &g_hero_state.pending);
        g_hero_state.target_speed = g_hero_state.planar_distance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &g_hero_state;
        if (g_hero_state.frame > 45) {
            ApproachValue((float *)(&g_hero_state.recovery_rate), 0.010000001f, 0.0028000001f);
        }
        if (g_hero_state.frame <= 45) speed = g_hero_state.recovery_speed;
        else speed = 0.07000001f;
        hero->speed = speed;
        hero_approach_speed(0.0176f, 0.018000001f);
        cam_set_view_space_vector_length(&g_drive_velocity_view.velocity, &g_drive_velocity_view.velocity, 0.0f);
        cam_offset_point_by_side_direction((DriveVector *)(&g_drive_velocity_view.velocity), (DriveVector *)(&g_drive_velocity_view.velocity), g_drive_velocity_view.target_speed);
    } else if (state == 27) {
        if (g_hero_state.frame > 33) {
            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.30019668f);
            hero_approach_velocity_pal(0.008f);
        }
        if (13.0f <= g_hero_state.plane && g_hero_state.plane <= 3e+01f) {
            if (27.0f < g_hero_state.plane)
                ApproachValue((float *)(&g_hero_state.lateral_speed), 0.0f, 0.0032000002f);
            else ApproachValue((float *)(&g_hero_state.lateral_speed), 0.040000003f, 0.0032000002f);
        }
        local.f[0] = g_hero_state.lateral_speed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&g_hero_state.velocity, &g_hero_state.basis);
        matrix_mul_vec3(&g_hero_state.velocity, &local, &g_hero_state);
    } else if (state == 11) {
        g_hero_state.heading = g_hero_state.target_heading;
        qcopy(&g_hero_state.direction, &g_hero_state.target_direction);
        hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.13962635f);
        if (g_hero_state.transition != 3) g_hero_state.target_speed = g_hero_state.input_speed;
        else g_hero_state.target_speed = 0.0f;
        if (g_hero_state.use_current_speed != 0) {
            float rate = g_hero_state.animation_speed * 0.10000001f;
            if (rate < 0.040000003f) rate = 0.040000003f;
            ApproachValue((float *)(&g_hero_state.strafe_speed), rate, 0.014800001f);
            g_hero_state.target_speed = g_hero_state.planar_distance;
        } else {
            if (g_hero_state.allow_action != 0 && g_hero_state.action_frame <= 9)
                ApproachValue((float *)(&g_hero_state.strafe_speed), 0.0f, 0.0032000002f);
            else ApproachValue((float *)(&g_hero_state.strafe_speed), 0.084f, 0.0032000002f);
        }
        if (g_hero_state.axis_mode == 0) {
            ((float *)&g_hero_state.velocity)[0] = math_fast_sin_or_cos_a(g_hero_state.input_heading);
            ((float *)&g_hero_state.velocity)[0] *= g_hero_state.strafe_speed;
            ((float *)&g_hero_state.velocity)[1] = math_fast_sin_or_cos_b(g_hero_state.input_heading);
            ((float *)&g_hero_state.velocity)[1] *= g_hero_state.strafe_speed;
        } else {
            cam_set_view_space_vector_length(&local, &g_hero_state.local_direction, g_hero_state.strafe_speed);
            cam_set_view_space_height(&local.q, &local.q, 0.0f);
            cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, 0.0f);
            FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &local);
        }
        if (g_hero_state.axis_mode == 0 && g_hero_state.use_current_speed == 0) {
            float angle = FastDiffRots(g_hero_state.target_heading, g_hero_state.input_heading);
            float cosine = math_fast_sin_or_cos_b(angle);
            float amount = g_hero_state.input_speed * cosine;
            float component = math_fast_sin_or_cos_a(g_hero_state.target_heading);
            ((float *)&g_hero_state.velocity)[0] += component * amount;
            component = math_fast_sin_or_cos_b(g_hero_state.target_heading);
            ((float *)&g_hero_state.velocity)[1] += component * amount;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pending_result, &g_hero_state.pending);
    } else if (state == 17) {
        g_hero_state.heading = ((float *)&g_hero_state.jump_direction)[3];
        qcopy(&g_hero_state.direction, &g_hero_state.jump_direction);
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
        g_hero_state.target_speed = g_hero_state.planar_distance;
    } else if (state == 129 && g_hero_l07_lock_flag == 0) {
        hero_steer_heading(0, 0.057600003f, 0.28800002f, g_hero_state.acceleration);
        g_hero_state.target_speed = 0.0f;
    } else {
        if (g_hero_state.state == 44) {
            float angle = g_hero_state.rotation;
            float delta;
            g_hero_state.yaw_error = math_approach_with_velocity(&angle, &g_hero_state.yaw_rate, 0,
                g_hero_state.heading, 0.02592f, 0.28800002f, 0.14660768f);
            delta = fast_subtract_rotations(angle, g_hero_state.rotation);
            hero_start_pose_offset(0.0f, 0.0f, delta);
        } else {
            old_heading = g_hero_state.heading;
            qcopy(&local, &g_hero_state.direction);
            if (g_hero_state.override_direction != 0) {
                g_hero_state.heading = g_hero_l07_state_block.heading;
                qcopy(&g_hero_state.direction, &g_hero_l07_state_block.direction);
            }
            hero_steer_heading(0, 0.057600003f, 0.28800002f, g_hero_state.acceleration);
            if (g_hero_state.override_direction != 0) {
                g_hero_state.saved_heading = old_heading;
                qcopy(&g_hero_state.saved_direction, &local);
                g_hero_state.heading = old_heading;
                qcopy(&g_hero_state.direction, &g_hero_state.saved_direction);
            }
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pending_result, &g_hero_state.pending);
        {
            float damping = 0.008f;
            if (g_hero_state.speed < g_hero_speed_scale * 0.004f) {
                if (g_hero_state.mode == 2) {
                    float rate = g_hero_state.pending_damping;
                    smoothed = cam_get_view_space_vector_length((char *)&g_hero_state.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, smoothed);
                    return;
                }
                if (g_hero_state.contact != 0) damping = 0.0044f;
                else if (g_hero_state.special != 0) damping = 0.00080000004f;
                else damping = 0.0032000002f;
            }
            hero_approach_velocity_pal(damping);
        }
    }
}

