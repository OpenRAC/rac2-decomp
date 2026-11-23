#include "names.h"
/* func_PAL_L05_00448114, the PAL copy of func_L05_00441F30: the same C, where rename func_L05_00442A58 becomes func_PAL_L05_00448CA8; rename func_L05_004432E0 becomes func_PAL_L05_004495C8; rename func_L05_00443740 becomes func_PAL_L05_00449A28; rename func_L00_002B30E8 becomes func_PAL_L00_002B3000; rename func_L05_00442560 becomes func_PAL_L05_00448790; scale D_L05_001B1ADC - 20. */
#include "common.h"

extern unsigned char g_hero_state[];
extern char *g_hero_moby_default NOT_SDA;
extern int g_ship_mode_word;
extern float g_cam_yaw_param_first __attribute__((sda));
extern float g_cam_yaw_param_second __attribute__((sda));
extern float g_cam_yaw_param_third __attribute__((sda));
extern float g_cam_pitch_param_first __attribute__((sda));
extern float g_cam_pitch_param_second __attribute__((sda));
extern float g_cam_pitch_param_third __attribute__((sda));
extern float g_cam_chase_goal_rate __attribute__((sda));
extern float g_ship_fade_level_a, g_ship_fade_level_b;
/* These views address the same fade words through $gp. */
extern float D_L05_001B1F60_sda SDATA(D_L05_001B1F60);
extern float D_L05_001B1F64_sda SDATA(D_L05_001B1F64);
extern int g_ship_enable_flag __attribute__((sda));
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern int g_ship_crash_recovery_time __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
/* Incomplete sda arrays keep absolute addresses together without claiming
 * the complete extent of the saved transforms. */
extern char g_ship_record_position[] __attribute__((sda));
extern char g_ship_saved_euler[] __attribute__((sda));
extern char g_ship_saved_position[] __attribute__((sda));
extern char g_ship_saved_matrix_row0[] __attribute__((sda));
extern char g_ship_saved_matrix_row1[] __attribute__((sda));
extern char g_ship_saved_matrix_row2[] __attribute__((sda));
extern char g_slot_record_source[];

extern void hero_set_objects_flag_bit(void);
extern void UpdateSteeringInput_pal(void *, void *, void *);
extern void ship_apply_steering_rotation(void *, void *, void *);
extern void cam_update_chase_position_pal(void *);
extern void UpdateDrivenMobyTransform_pal(void *);
extern void euler_rotation_basis(void *, void *);
extern void hero_record_play_counters_pal(void);
extern void ship_update_record_transform(void *, float);
extern int actuator_play_waves(void *);
extern void ship_respawn_at_best_saved_slot_pal(void *);
extern float hero_get_clamped_stat(void);
extern int hero_get_state_value_c(void);
extern int math_fast_float_d(void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))

/* Dispatches the flight controller and its timed transform transitions. */
void UpdateTimedTransformState_pal(char *obj)
{
    int yaw_rate, pitch_rate;
    char *input = P(obj, 0x70) + 0x50;
    float yaw_a = g_cam_yaw_param_first, yaw_b = g_cam_yaw_param_second, yaw_c = g_cam_yaw_param_third;
    float pitch_a = g_cam_pitch_param_first, pitch_b = g_cam_pitch_param_second, pitch_c = g_cam_pitch_param_third;

    F(input, 0) = yaw_a;
    F(input, 4) = yaw_b;
    F(input, 8) = yaw_c;
    F(input, 12) = pitch_a;
    F(input, 16) = pitch_b;
    F(input, 20) = pitch_c;
    g_ship_mode_word = 2;
    if (!g_hero_state[0x22B5]) {
        I(P(g_hero_state, 0x2290), 0x98) = 0;
        hero_set_objects_flag_bit();
        g_hero_state[0x22B5] = 1;
    }
    if (!g_ship_enable_flag) {
        U(g_hero_moby_default, 0x34) |= 0x41;
        U(g_hero_moby_default, 0x34) &= 0xEFFF;
        I(g_hero_moby_default, 0x98) = 0;
    }
    g_cam_chase_goal_rate = hero_get_clamped_stat();
    if (hero_get_state_value_c()) return;

    switch (g_ship_state) {
    case 0:
        UpdateSteeringInput_pal(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position_pal(obj);
        UpdateDrivenMobyTransform_pal(obj);
        break;
    case 1:
        UpdateSteeringInput_pal(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position_pal(obj);
        UpdateDrivenMobyTransform_pal(obj);
        D_L05_001B1F60_sda = g_ship_fade_level_a + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            g_ship_fade_level_a = 1.0f;
            g_ship_state = 4;
            qcopy(obj + 0x30, g_ship_record_position);
            euler_rotation_basis(obj, g_ship_saved_euler);
        }
        break;
    case 4:
        D_L05_001B1F60_sda = g_ship_fade_level_a - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            g_ship_fade_level_a = 0.0f;
            g_ship_state = 5;
        }
        break;
    case 5:
        if (math_fast_float_d(&g_ship_transition_timer)) g_ship_state = 3;
        break;
    case 3:
        D_L05_001B1F60_sda = g_ship_fade_level_a + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            g_ship_fade_level_a = 1.0f;
            g_ship_state = 2;
            qcopy(obj + 0x30, g_ship_saved_position);
            qcopy(obj, g_ship_saved_matrix_row0);
            qcopy(obj + 0x10, g_ship_saved_matrix_row1);
            qcopy(obj + 0x20, g_ship_saved_matrix_row2);
        }
        break;
    case 2:
        UpdateSteeringInput_pal(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position_pal(obj);
        UpdateDrivenMobyTransform_pal(obj);
        D_L05_001B1F60_sda = g_ship_fade_level_a - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60_sda = 0.0f;
            g_ship_state = 0;
        }
        break;
    case 6:
        qcopy(obj + 0x30, g_ship_record_position);
        euler_rotation_basis(obj, g_ship_saved_euler);
        if (math_fast_float_d(&g_ship_transition_timer)) {
            hero_record_play_counters_pal();
        } else {
            float t = 0.16000001f;
            if (g_current_map_index == 20) t = 0.32000002f;
            ship_update_record_transform(obj, t);
            if ((((int)(g_ship_crash_recovery_time - 20) * 5 + 2) / 6) < g_ship_transition_timer) {
                actuator_play_waves(g_slot_record_source);
            }
        }
        break;
    case 7:
        D_L05_001B1F64_sda = g_ship_fade_level_b + 0.05f;
        if (D_L05_001B1F64_sda >= 1.0f) {
            g_ship_fade_level_b = 1.0f;
            g_ship_state = 8;
            ship_respawn_at_best_saved_slot_pal(obj);
        }
        break;
    case 8:
        D_L05_001B1F64_sda = g_ship_fade_level_b - 0.05f;
        if (D_L05_001B1F64_sda <= 0.0f) {
            g_ship_fade_level_b = 0.0f;
            g_ship_state = 0;
        }
        break;
    }
}
