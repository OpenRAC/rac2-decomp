#include "common.h"

/* func_PAL_L04_002DCE68, the PAL copy of func_L04_002DCE78: the same C, where speeds become x6/5,
   accelerations x36/25 and frame counts x5/6 for 50 Hz. */

extern void FastVecAdd(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(float *, float *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern float ApproachValue(float *, float, float);
extern void hero_start_pose_offset(float, float, float);
extern void hero_resolve_stick_direction(int, float);
extern void hero_steer_heading(int, float, float, float);
extern void hero_approach_speed(float, float);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern void hero_build_move_impulse(float, float);
extern void ApproachHeroVelocity(float);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern float cam_get_view_space_vector_length(void *);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern unsigned char D_L04_001B9540[];
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
typedef struct {
    unsigned char pad0[0x20];
    HopVector field20;
    unsigned char pad30[0x68];
    float yaw;
    unsigned char pad9C[0x54];
    HopVector velocity;
    unsigned char pad100[0x60];
    HopVector momentum;
    unsigned char pad170[0x4];
    float flat_speed;
    unsigned char pad178[0x18];
    HopVector move_dir;
    float move_yaw;
    float yaw_rate;
    float yaw_error;
    unsigned char pad1AC[0x4];
    float target_speed;
    float ground_speed;
    int state_timer;
    unsigned char pad1BC[0x164];
    float field320;
    unsigned char pad324[0x24];
    short field348;
    short field34A;
    unsigned char pad34C[0x108];
    float field454;
    unsigned char pad458[0x18];
    HopVector field470;
    HopVector field480;
    unsigned char pad490[0x4];
    float field494;
    unsigned char pad498[0x6];
    unsigned char field49E;
    unsigned char pad49F[0xF];
    short field4AE;
    unsigned char pad4B0[0xC];
    float ledge_jump_speed;
    float high_jump_drift_yaw;
    float takeoff_yaw;
    unsigned char pad4C8[0xC];
    int field4D4;
    float air_target_speed;
    float high_jump_drift_speed;
    unsigned char pad4E0[0x10];
    HopVector field4F0;
    unsigned char pad500[0x20];
    float jump_gravity;
    short field524;
    unsigned char pad526[0x2];
    short field528;
    unsigned char pad52A[0x3];
    unsigned char field52D;
    unsigned char pad52E[0x532];
    HopVector move_impulse;
    unsigned char padA70[0x14];
    float fieldA84;
    unsigned char padA88[0x1B0];
    float anim_frame;
    unsigned char padC3C[0x804];
    HopVector field1440;
    unsigned char pad1450[0x4];
    short field1454;
    unsigned char pad1456[0x2];
    float field1458;
    unsigned char pad145C[0x36];
    unsigned char field1492;
    unsigned char pad1493[0xE01];
    int state;
    unsigned char pad2298[0x4];
    int control_mode;
    unsigned char pad22A0[0x23];
    unsigned char field22C3;
    unsigned char pad22C4[0x1F4];
    float stick_magnitude;
} HopPlayer;
typedef struct {
    unsigned char pad0[0x158];
    float yaw;
    unsigned char pad15C[0x370 - 0x15C];
    HopVector direction;
} HopSavedState;

extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
extern int g_hero_state;

/* Per-state airborne steering; shares the hop-velocity state cases with
   rac1-decomp's hero_update_hop_velocity. */
void func_PAL_L04_002DCE68(void) {
    float probe_start[4], probe_end[4], yaw, speed, rate;

    if ((*(HopPlayer *)&g_hero_state).state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy((*(HopPlayer *)&g_hero_state).momentum.f, (*(HopPlayer *)&g_hero_state).move_impulse.f);
        (*(HopPlayer *)&g_hero_state).ground_speed = (*(HopPlayer *)&g_hero_state).flat_speed;
    } else if ((*(HopPlayer *)&g_hero_state).state == 16) {
        if ((*(HopPlayer *)&g_hero_state).state_timer >= 46) {
            ApproachValue(&(*(HopPlayer *)&g_hero_state).jump_gravity, 0.010000001f, 0.0028000001f);
        }
        if ((*(HopPlayer *)&g_hero_state).state_timer < 46) {
            (*(HopPlayer *)&g_hero_state).target_speed = (*(HopPlayer *)&g_hero_state).field454;
        } else {
            (*(HopPlayer *)&g_hero_state).target_speed = 0.07000001f;
        }
        hero_approach_speed(0.0176f, 0.018000001f);
        cam_set_view_space_vector_length((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, 0.0f);
        cam_offset_point_by_side_direction((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).ground_speed);
    } else if ((*(HopPlayer *)&g_hero_state).state == 27) {
        if ((*(HopPlayer *)&g_hero_state).state_timer >= 34) {
            hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.30019668f);
            ApproachHeroVelocity(0.008f);
        }
        if ((*(HopPlayer *)&g_hero_state).anim_frame >= 13.0f && (*(HopPlayer *)&g_hero_state).anim_frame <= 30.0f) {
            if ((*(HopPlayer *)&g_hero_state).anim_frame > 27.0f) {
                ApproachValue(&(*(HopPlayer *)&g_hero_state).ledge_jump_speed, 0.0f, 0.0032000002f);
            } else {
                ApproachValue(&(*(HopPlayer *)&g_hero_state).ledge_jump_speed, 0.040000003f, 0.0032000002f);
            }
        }
        probe_start[1] = 0.0f;
        probe_start[0] = (*(HopPlayer *)&g_hero_state).ledge_jump_speed;
        probe_start[2] = FastVecDot((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).field20.f);
        matrix_mul_vec3((*(HopPlayer *)&g_hero_state).velocity.f, probe_start, &(*(HopPlayer *)&g_hero_state));
    } else if ((*(HopPlayer *)&g_hero_state).state == 11) {
        (*(HopPlayer *)&g_hero_state).move_yaw = (*(HopPlayer *)&g_hero_state).takeoff_yaw;
        qcopy((*(HopPlayer *)&g_hero_state).move_dir.f, (*(HopPlayer *)&g_hero_state).field480.f);
        hero_steer_heading(0, 0.057600003f, 0.28800002f, 0.13962635f);
        if ((*(HopPlayer *)&g_hero_state).field4D4 != 3) {
            (*(HopPlayer *)&g_hero_state).ground_speed = (*(HopPlayer *)&g_hero_state).air_target_speed;
        } else {
            (*(HopPlayer *)&g_hero_state).ground_speed = 0.0f;
        }
        if ((*(HopPlayer *)&g_hero_state).field52D) {
            float drift = (*(HopPlayer *)&g_hero_state).stick_magnitude * 0.10000001f;

            if (drift < 0.040000003f) drift = 0.040000003f;
            ApproachValue(&(*(HopPlayer *)&g_hero_state).high_jump_drift_speed, drift, 0.014800001f);
            (*(HopPlayer *)&g_hero_state).ground_speed = (*(HopPlayer *)&g_hero_state).flat_speed;
        } else if ((*(HopPlayer *)&g_hero_state).field49E && (*(HopPlayer *)&g_hero_state).field4AE < 10) {
            ApproachValue(&(*(HopPlayer *)&g_hero_state).high_jump_drift_speed, 0.0f, 0.0032000002f);
        } else {
            ApproachValue(&(*(HopPlayer *)&g_hero_state).high_jump_drift_speed, 0.084f, 0.0032000002f);
        }
        if (!(*(HopPlayer *)&g_hero_state).field22C3) {
            (*(HopPlayer *)&g_hero_state).velocity.f[0] = math_fast_sin_or_cos_a((*(HopPlayer *)&g_hero_state).high_jump_drift_yaw) * (*(HopPlayer *)&g_hero_state).high_jump_drift_speed;
            (*(HopPlayer *)&g_hero_state).velocity.f[1] = math_fast_sin_or_cos_b((*(HopPlayer *)&g_hero_state).high_jump_drift_yaw) * (*(HopPlayer *)&g_hero_state).high_jump_drift_speed;
        } else {
            cam_set_view_space_vector_length(probe_start, (*(HopPlayer *)&g_hero_state).field470.f, (*(HopPlayer *)&g_hero_state).high_jump_drift_speed);
            cam_set_view_space_height(probe_start, probe_start, 0.0f);
            cam_set_view_space_vector_length((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, 0.0f);
            FastVecAdd((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, probe_start);
        }
        if (!(*(HopPlayer *)&g_hero_state).field22C3 && !(*(HopPlayer *)&g_hero_state).field52D) {
            float drift = (*(HopPlayer *)&g_hero_state).air_target_speed * math_fast_sin_or_cos_b(FastDiffRots((*(HopPlayer *)&g_hero_state).takeoff_yaw, (*(HopPlayer *)&g_hero_state).high_jump_drift_yaw));

            (*(HopPlayer *)&g_hero_state).velocity.f[0] += math_fast_sin_or_cos_a((*(HopPlayer *)&g_hero_state).takeoff_yaw) * drift;
            (*(HopPlayer *)&g_hero_state).velocity.f[1] += math_fast_sin_or_cos_b((*(HopPlayer *)&g_hero_state).takeoff_yaw) * drift;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy((*(HopPlayer *)&g_hero_state).momentum.f, (*(HopPlayer *)&g_hero_state).move_impulse.f);
    } else if ((*(HopPlayer *)&g_hero_state).state == 17) {
        (*(HopPlayer *)&g_hero_state).move_yaw = (*(HopPlayer *)&g_hero_state).field4F0.f[3];
        qcopy((*(HopPlayer *)&g_hero_state).move_dir.f, (*(HopPlayer *)&g_hero_state).field4F0.f);
        if ((*(HopPlayer *)&g_hero_state).state_timer >= 8) {
            hero_steer_heading(-1, 0.060480002f, 0.28800002f, 0.23736483f);
        }
        if ((*(HopPlayer *)&g_hero_state).state_timer >= 7) {
            if (!(*(HopPlayer *)&g_hero_state).field348) {
                (*(HopPlayer *)&g_hero_state).velocity.f[0] = math_fast_sin_or_cos_a((*(HopPlayer *)&g_hero_state).move_yaw) * 0.09800001f;
                (*(HopPlayer *)&g_hero_state).velocity.f[1] = math_fast_sin_or_cos_b((*(HopPlayer *)&g_hero_state).move_yaw) * 0.09800001f;
            } else {
                cam_set_view_space_vector_length((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, 0.0f);
                vec_scale_to_length(probe_start, (*(HopPlayer *)&g_hero_state).move_dir.f, 0.09800001f);
                FastVecAdd((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, probe_start);
            }
        }
        (*(HopPlayer *)&g_hero_state).ground_speed = (*(HopPlayer *)&g_hero_state).flat_speed;
    } else if ((*(HopPlayer *)&g_hero_state).state == 0x81 && !D_001A8FF0) {
        hero_steer_heading(0, 0.057600003f, 0.28800002f, (*(HopPlayer *)&g_hero_state).field494);
        (*(HopPlayer *)&g_hero_state).ground_speed = 0.0f;
    } else {
        if ((*(HopPlayer *)&g_hero_state).state == 44) {
            yaw = (*(HopPlayer *)&g_hero_state).yaw;
            (*(HopPlayer *)&g_hero_state).yaw_error = math_approach_with_velocity(&yaw, (*(HopPlayer *)&g_hero_state).move_yaw, &(*(HopPlayer *)&g_hero_state).yaw_rate,
                                      0.02592f, 0.28800002f, 0.14660768f, 0);
            {
                float delta = fast_subtract_rotations(yaw, (*(HopPlayer *)&g_hero_state).yaw);

                hero_start_pose_offset(0.0f, 0.0f, delta);
            }
        } else {
            float saved = (*(HopPlayer *)&g_hero_state).move_yaw;

            qcopy(probe_start, (*(HopPlayer *)&g_hero_state).move_dir.f);
            if ((*(HopPlayer *)&g_hero_state).field1454) {
                (*(HopPlayer *)&g_hero_state).move_yaw = (*(HopSavedState *)D_L04_001B9540).yaw;
                qcopy((*(HopPlayer *)&g_hero_state).move_dir.f, (*(HopSavedState *)D_L04_001B9540).direction.f);
            }
            hero_steer_heading(0, 0.057600003f, 0.28800002f, (*(HopPlayer *)&g_hero_state).field494);
            if ((*(HopPlayer *)&g_hero_state).field1454) {
                (*(HopPlayer *)&g_hero_state).field1458 = saved;
                qcopy((*(HopPlayer *)&g_hero_state).field1440.f, probe_start);
                (*(HopPlayer *)&g_hero_state).move_yaw = saved;
                qcopy((*(HopPlayer *)&g_hero_state).move_dir.f, (*(HopPlayer *)&g_hero_state).field1440.f);
            }
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy((*(HopPlayer *)&g_hero_state).momentum.f, (*(HopPlayer *)&g_hero_state).move_impulse.f);
        rate = 0.008f;
        if ((*(HopPlayer *)&g_hero_state).target_speed < D_001A7DC0 * 0.004f) {
            if ((*(HopPlayer *)&g_hero_state).control_mode == 2) {
                float decel = (*(HopPlayer *)&g_hero_state).fieldA84;

                if ((*(HopPlayer *)&g_hero_state).field1492) decel = 6.8e-05f;
                speed = cam_get_view_space_vector_length((*(HopPlayer *)&g_hero_state).velocity.f);
                ApproachValue(&speed, 0.0f, decel);
                cam_set_view_space_vector_length((*(HopPlayer *)&g_hero_state).velocity.f, (*(HopPlayer *)&g_hero_state).velocity.f, speed);
                return;
            }
            if ((*(HopPlayer *)&g_hero_state).field34A) {
                rate = 0.0044f;
            } else if ((*(HopPlayer *)&g_hero_state).field524) {
                rate = 0.00080000004f;
            } else {
                rate = 0.0032000002f;
            }
        }
        if ((*(HopPlayer *)&g_hero_state).field528 && (*(HopPlayer *)&g_hero_state).field1492) {
            rate = 0.00020000001f;
            if ((*(HopPlayer *)&g_hero_state).stick_magnitude > 0.9f) {
                BuildOffsetVectorPair(probe_start, probe_end, 0, 0.5f, -1.5f);
                probe_start[0] += math_fast_sin_or_cos_a((*(HopPlayer *)&g_hero_state).move_yaw) * 0.7f;
                probe_start[1] += math_fast_sin_or_cos_b((*(HopPlayer *)&g_hero_state).move_yaw) * 0.7f;
                probe_end[0] += math_fast_sin_or_cos_a((*(HopPlayer *)&g_hero_state).move_yaw) * 0.7f;
                probe_end[1] += math_fast_sin_or_cos_b((*(HopPlayer *)&g_hero_state).move_yaw) * 0.7f;
                if (CollLine(probe_start, probe_end, 2, 0, 0) && GetCollHitMaterial() != 7) {
                    (*(HopPlayer *)&g_hero_state).target_speed = 0.10000001f;
                    rate = 0.004f;
                }
            }
            if ((*(HopPlayer *)&g_hero_state).state == 15) {
                hero_resolve_stick_direction(0, 0.050000004f);
                rate = 0.0012f;
            }
            if ((*(HopPlayer *)&g_hero_state).field320 > 0.2617994248867035f) {
                (*(HopPlayer *)&g_hero_state).target_speed = 0.0f;
                rate = (*(HopPlayer *)&g_hero_state).field320 * 0.004583662f;
            }
        }
        ApproachHeroVelocity(rate);
    }
}
