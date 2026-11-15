#include "common.h"

extern unsigned char g_hero_state[];
extern char *g_hero_moby_default NOT_SDA;
extern int D_L05_001B20CC;
extern float D_L05_001B1A4C __attribute__((sda));
extern float D_L05_001B1A50 __attribute__((sda));
extern float D_L05_001B1A54 __attribute__((sda));
extern float D_L05_001B1A58 __attribute__((sda));
extern float D_L05_001B1A5C __attribute__((sda));
extern float D_L05_001B1A64 __attribute__((sda));
extern float D_L05_001B1AC0 __attribute__((sda));
extern float D_L05_001B1F60, D_L05_001B1F64;
/* These views address the same fade words through $gp. */
extern float D_L05_001B1F60_sda SDATA(D_L05_001B1F60);
extern float D_L05_001B1F64_sda SDATA(D_L05_001B1F64);
extern int D_L05_001B1AF8 __attribute__((sda));
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern int D_L05_001B1ADC __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
/* Incomplete sda arrays keep absolute addresses together without claiming
 * the complete extent of the saved transforms. */
extern char D_L05_001B3620[] __attribute__((sda));
extern char D_L05_001B3610[] __attribute__((sda));
extern char D_L05_001B3600[] __attribute__((sda));
extern char D_L05_001B35D0[] __attribute__((sda));
extern char D_L05_001B35E0[] __attribute__((sda));
extern char D_L05_001B35F0[] __attribute__((sda));
extern char D_L05_002B8770[];

extern void hero_set_objects_flag_bit(void);
extern void UpdateSteeringInput(void *, void *, void *);
extern void ship_apply_steering_rotation(void *, void *, void *);
extern void cam_update_chase_position(void *);
extern void UpdateDrivenMobyTransform(void *);
extern void euler_rotation_basis(void *, void *);
extern void hero_record_play_counters(void);
extern void ship_update_record_transform(void *, float);
extern void slot_copy_records_to_free(void *);
extern void ship_respawn_at_best_saved_slot(void *);
extern float hero_get_clamped_stat(void);
extern int hero_get_state_value_c(void);
extern int math_fast_float_d(void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))

/* Dispatches the flight controller and its timed transform transitions. */
/* Runs the player's ship each frame. It steers normally and handles the screen fades and resets between ship states. */
void UpdateTimedTransformState(char *obj)
{
    int yaw_rate, pitch_rate;
    char *input = P(obj, 0x70) + 0x50;
    float yaw_param0 = D_L05_001B1A4C, yaw_param1 = D_L05_001B1A50, yaw_param2 = D_L05_001B1A54;
    float pitch_param0 = D_L05_001B1A58, pitch_param1 = D_L05_001B1A5C, pitch_param2 = D_L05_001B1A64;

    F(input, 0) = yaw_param0;
    F(input, 4) = yaw_param1;
    F(input, 8) = yaw_param2;
    F(input, 12) = pitch_param0;
    F(input, 16) = pitch_param1;
    F(input, 20) = pitch_param2;
    D_L05_001B20CC = 2;
    if (!g_hero_state[0x22B5]) {
        I(P(g_hero_state, 0x2290), 0x98) = 0;
        hero_set_objects_flag_bit();
        g_hero_state[0x22B5] = 1;
    }
    if (!D_L05_001B1AF8) {
        U(g_hero_moby_default, 0x34) |= 0x41;
        U(g_hero_moby_default, 0x34) &= 0xEFFF;
        I(g_hero_moby_default, 0x98) = 0;
    }
    D_L05_001B1AC0 = hero_get_clamped_stat();
    if (hero_get_state_value_c()) return;

    switch (g_ship_state) {
    case 0:
        UpdateSteeringInput(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position(obj);
        UpdateDrivenMobyTransform(obj);
        break;
    case 1:
        UpdateSteeringInput(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position(obj);
        UpdateDrivenMobyTransform(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            g_ship_state = 4;
            qcopy(obj + 0x30, D_L05_001B3620);
            euler_rotation_basis(obj, D_L05_001B3610);
        }
        break;
    case 4:
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60 = 0.0f;
            g_ship_state = 5;
        }
        break;
    case 5:
        if (math_fast_float_d(&g_ship_transition_timer)) g_ship_state = 3;
        break;
    case 3:
        D_L05_001B1F60_sda = D_L05_001B1F60 + 0.05f;
        if (D_L05_001B1F60_sda >= 1.0f) {
            D_L05_001B1F60 = 1.0f;
            g_ship_state = 2;
            qcopy(obj + 0x30, D_L05_001B3600);
            qcopy(obj, D_L05_001B35D0);
            qcopy(obj + 0x10, D_L05_001B35E0);
            qcopy(obj + 0x20, D_L05_001B35F0);
        }
        break;
    case 2:
        UpdateSteeringInput(obj, &yaw_rate, &pitch_rate);
        ship_apply_steering_rotation(obj, &yaw_rate, &pitch_rate);
        cam_update_chase_position(obj);
        UpdateDrivenMobyTransform(obj);
        D_L05_001B1F60_sda = D_L05_001B1F60 - 0.05f;
        if (D_L05_001B1F60_sda <= 0.0f) {
            D_L05_001B1F60_sda = 0.0f;
            g_ship_state = 0;
        }
        break;
    case 6:
        qcopy(obj + 0x30, D_L05_001B3620);
        euler_rotation_basis(obj, D_L05_001B3610);
        if (math_fast_float_d(&g_ship_transition_timer)) {
            hero_record_play_counters();
        } else {
            float reset_speed = 0.13333334f;
            if (g_current_map_index == 20) reset_speed = 0.26666668f;
            ship_update_record_transform(obj, reset_speed);
            if (D_L05_001B1ADC - 20 < g_ship_transition_timer) {
                slot_copy_records_to_free(D_L05_002B8770);
            }
        }
        break;
    case 7:
        D_L05_001B1F64_sda = D_L05_001B1F64 + 0.05f;
        if (D_L05_001B1F64_sda >= 1.0f) {
            D_L05_001B1F64 = 1.0f;
            g_ship_state = 8;
            ship_respawn_at_best_saved_slot(obj);
        }
        break;
    case 8:
        D_L05_001B1F64_sda = D_L05_001B1F64 - 0.05f;
        if (D_L05_001B1F64_sda <= 0.0f) {
            D_L05_001B1F64 = 0.0f;
            g_ship_state = 0;
        }
        break;
    }
}
