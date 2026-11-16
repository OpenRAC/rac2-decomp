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
    float lowAcceleration, highAcceleration, lowSpeed, highSpeed, deceleration;
} SteeringRateSettings;
extern SteeringRateSettings g_steering_rate_settings MACRO_ADDR;
/* Retail reaches the low-rate fields through $gp and the high-rate fields absolutely. */
extern SteeringRateSettings smallRateSettings SDATA(D_L16_001B1B28);
extern float g_steering_limit_high_deg __attribute__((sda));
typedef struct {
    float minAngle;
    char reserved[8];
    float filteredX, filteredY;
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
void UpdateSnivelakSteering(char *object)
{
    SteeringWorkspace local;
    char *state = *(char **)(object + 0x68);
    float acceleration, target, deceleration, newMagnitude;

    qcopy(&local.position, (object + 0x10));
    qcopy(&local.angles, (object + 0xf0));
    if (math_fabs(g_player_state) < g_steering_filtered_turn)
        g_steering_filtered_turn = math_fabs(g_player_state);
    else if (g_steering_filtered_turn < -math_fabs(g_player_state))
        g_steering_filtered_turn = -math_fabs(g_player_state);
    if (math_fabs(g_pad_stick_y) < g_steering_angle_settings.filteredY)
        g_steering_angle_settings.filteredY = math_fabs(g_pad_stick_y);
    else if (g_steering_angle_settings.filteredY < -math_fabs(g_pad_stick_y))
        g_steering_angle_settings.filteredY = -math_fabs(g_pad_stick_y);
    ApproachValue(&g_steering_filtered_turn, g_player_state, 0.15f);
    ApproachValue(&g_steering_angle_settings.filteredY, g_pad_stick_y, 0.15f);
    deceleration = g_steering_decel_rate*0.000004848137451f;
    if (g_steering_filtered_turn != 0.0f) {
        if (math_fabs(g_steering_filtered_turn) >= 1.0f) {
            acceleration = g_steering_accel_rate_alt[0]*0.000004848137451f;
            target = g_steering_target_speed_alt[0]*((-g_steering_filtered_turn)*0.0002908882452f);
        } else {
            acceleration = g_steering_accel_rate*(math_fabs(g_steering_filtered_turn)*0.000004848137451f);
            target = g_steering_target_speed*((-g_steering_filtered_turn)*0.0002908882452f);
        }
    } else {
        acceleration = 0.0f;
        target = 0.0f;
    }
    {
        float oldMagnitude = math_fabs(*(float *)(state + 0x80));
        newMagnitude = math_fabs(target);
        if (newMagnitude < oldMagnitude)
            ApproachValue((float *)(state + 0x80), target, deceleration);
        else
            ApproachValue((float *)(state + 0x80), target, acceleration);
    }
    {
        float inputY = g_steering_angle_settings.filteredY;
        deceleration = smallRateSettings.deceleration*0.000004848137451f;
        if (inputY != 0.0f) {
            if (math_fabs(inputY) >= 1.0f) {
                float turn = -g_steering_angle_settings.filteredY;
                acceleration = g_steering_rate_settings.highAcceleration*0.000004848137451f;
                target = g_steering_rate_settings.highSpeed*(turn*0.0002908882452f);
            } else {
                acceleration = smallRateSettings.lowAcceleration*(math_fabs(g_steering_angle_settings.filteredY)*0.000004848137451f);
                target = smallRateSettings.lowSpeed*((-g_steering_angle_settings.filteredY)*0.0002908882452f);
            }
        } else {
            acceleration = 0.0f;
            target = 0.0f;
        }
    }
    {
        float oldMagnitude = math_fabs(*(float *)(state + 0x84));
        newMagnitude = math_fabs(target);
        if (newMagnitude < oldMagnitude)
            ApproachValue((float *)(state + 0x84), target, deceleration);
        else
            ApproachValue((float *)(state + 0x84), target, acceleration);
    }
    if (*(float *)(state + 0x80) != 0.0f)
        *(float *)(object + 0xf8) = FastAddRotations(*(float *)(object + 0xf8), *(float *)(state + 0x80));
    if (*(float *)(state + 0x84) != 0.0f) {
        local.limits.high = g_steering_limit_high_deg*0.017453294f;
        local.limits.low = g_steering_angle_settings.minAngle*0.017453294f;
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
