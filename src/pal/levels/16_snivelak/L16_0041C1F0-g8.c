#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct {
    float high, low;
} SteeringLimits;
typedef struct {
    Vector128 position, angles;
    union {
        SteeringLimits bounds;
        Vector128 delta;
    } work;
    SteeringLimits limits;
} SteeringWorkspace;
extern char g_sound_state[];
extern struct {
    char pad[0x1fb0];
    float x, y;
} D_00189E20;
#define D_0018BDD0 D_00189E20.x
#define D_0018BDD4 D_00189E20.y
extern float g_steering_filtered_turn __attribute__((sda));
extern float g_steering_accel_rate __attribute__((sda));
extern float g_steering_accel_rate_alt[] MACRO_ADDR;
extern float g_steering_target_speed __attribute__((sda));
extern float g_steering_target_speed_alt[] MACRO_ADDR;
extern float g_steering_decel_rate __attribute__((sda));
typedef struct {
    float low_acceleration, high_acceleration, low_speed, high_speed, deceleration;
} SteeringRateSettings;
extern SteeringRateSettings g_steering_rate_settings MACRO_ADDR;
extern SteeringRateSettings smallRateSettings SDATA(D_L16_001B1B28);
extern float g_steering_limit_high_deg __attribute__((sda));
typedef struct {
    float min_angle;
    char reserved[8];
    float filtered_x, filtered_y;
} SteeringAngleSettings;
extern SteeringAngleSettings g_steering_angle_settings MACRO_ADDR;
extern float math_fabs(float);
extern float ApproachValue(float *, float, float);
extern float FastAddRotations(float, float);
extern void math_clamp_speed_to_braking_limit(float *, float, float);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Smooth the steering inputs, update yaw/pitch rates, and limit pitch travel. */
void UpdateSnivelakSteering_pal(char *object)
{
    SteeringWorkspace local;
    char *state = *(char **)(object + 0x68);
    float acceleration, target, deceleration, new_magnitude;

    qcopy(&local.position, (object + 0x10));
    qcopy(&local.angles, (object + 0xf0));
    if (math_fabs(g_player_state) < g_steering_filtered_turn)
        g_steering_filtered_turn = math_fabs(g_player_state);
    else if (g_steering_filtered_turn < -math_fabs(g_player_state))
        g_steering_filtered_turn = -math_fabs(g_player_state);
    if (math_fabs(g_pad_stick_y) < g_steering_angle_settings.filtered_y)
        g_steering_angle_settings.filtered_y = math_fabs(g_pad_stick_y);
    else if (g_steering_angle_settings.filtered_y < -math_fabs(g_pad_stick_y))
        g_steering_angle_settings.filtered_y = -math_fabs(g_pad_stick_y);
    ApproachValue(&g_steering_filtered_turn, g_player_state, 0.15f);
    ApproachValue(&g_steering_angle_settings.filtered_y, g_pad_stick_y, 0.15f);
    deceleration = g_steering_decel_rate*6.981318e-06f;
    if (g_steering_filtered_turn != 0.0f) {
        if (math_fabs(g_steering_filtered_turn) >= 1.0f) {
            acceleration = g_steering_accel_rate_alt[0]*6.981318e-06f;
            target = g_steering_target_speed_alt[0]*((-g_steering_filtered_turn)*0.0003490659f);
        } else {
            acceleration = g_steering_accel_rate*(math_fabs(g_steering_filtered_turn)*6.981318e-06f);
            target = g_steering_target_speed*((-g_steering_filtered_turn)*0.0003490659f);
        }
    } else {
        acceleration = 0.0f;
        target = 0.0f;
    }
    {
        float old_magnitude = math_fabs(*(float *)(state + 0x80));
        new_magnitude = math_fabs(target);
        if (new_magnitude < old_magnitude)
            ApproachValue((float *)(state + 0x80), target, deceleration);
        else
            ApproachValue((float *)(state + 0x80), target, acceleration);
    }
    {
        float input_y = g_steering_angle_settings.filtered_y;
        deceleration = smallRateSettings.deceleration*6.981318e-06f;
        if (input_y != 0.0f) {
            if (math_fabs(input_y) >= 1.0f) {
                float turn = -g_steering_angle_settings.filtered_y;
                acceleration = g_steering_rate_settings.high_acceleration*6.981318e-06f;
                target = g_steering_rate_settings.high_speed*(turn*0.0003490659f);
            } else {
                acceleration = smallRateSettings.low_acceleration*(math_fabs(g_steering_angle_settings.filtered_y)*6.981318e-06f);
                target = smallRateSettings.low_speed*((-g_steering_angle_settings.filtered_y)*0.0003490659f);
            }
        } else {
            acceleration = 0.0f;
            target = 0.0f;
        }
    }
    {
        float old_magnitude = math_fabs(*(float *)(state + 0x84));
        new_magnitude = math_fabs(target);
        if (new_magnitude < old_magnitude)
            ApproachValue((float *)(state + 0x84), target, deceleration);
        else
            ApproachValue((float *)(state + 0x84), target, acceleration);
    }
    if (*(float *)(state + 0x80) != 0.0f)
        *(float *)(object + 0xf8) = FastAddRotations(*(float *)(object + 0xf8), *(float *)(state + 0x80));
    if (*(float *)(state + 0x84) != 0.0f) {
        local.limits.high = g_steering_limit_high_deg*0.017453294f;
        local.limits.low = g_steering_angle_settings.min_angle*0.017453294f;
        local.work.bounds = local.limits;
        math_clamp_speed_to_braking_limit((float *)(state + 0x84), local.work.bounds.high - *(float *)(state + 0x90), deceleration);
        math_clamp_speed_to_braking_limit((float *)(state + 0x84), local.work.bounds.low - *(float *)(state + 0x90), deceleration);
        *(float *)(state + 0x90) = FastAddRotations(*(float *)(state + 0x90), *(float *)(state + 0x84));
        if (*(float *)(state + 0x90)>local.work.bounds.high) {
            *(float *)(state + 0x90) = local.work.bounds.high;
            *(float *)(state + 0x84) = 0.0f;
        } else if (*(float *)(state + 0x90)<local.work.bounds.low) {
            *(float *)(state + 0x90) = local.work.bounds.low;
            *(float *)(state + 0x84) = 0.0f;
        }
    }
    if (math_fabs(*(float *)(state + 0x80))>0.0f || math_fabs(*(float *)(state + 0x84))>0.0f) {
        int handle = *(int *)(state + 0xa4);
        char *sound = g_sound_state + 0x70*handle;
        if ((*(char **)(sound + 0x88)) != object || (*(unsigned char *)(sound + 0x74)) == 0)
            *(int *)(state + 0xa4) = PlayMobySound(4, 4, object);
    } else {
        int handle = *(int *)(state + 0xa4);
        if (handle != -1) {
            char *sound = g_sound_state + 0x70*handle;
            if ((*(char **)(sound + 0x88)) == object && (*(unsigned char *)(sound + 0x74)) != 0)
                snd_stop_voice(handle);
        }
        *(int *)(state + 0xa4) = -1;
    }
    FastVecSub(&local.work.delta, object + 0x10, &local.position);
    mat_combine_and_store(state + 0x20, &local.work.delta, &local.angles, object + 0xf0);
}
