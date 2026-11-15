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
extern float D_L16_001B1B50 __attribute__((sda));
extern float D_L16_001B1B10 __attribute__((sda));
extern float D_L16_001B1B14[] MACRO_ADDR;
extern float D_L16_001B1B18 __attribute__((sda));
extern float D_L16_001B1B1C[] MACRO_ADDR;
extern float D_L16_001B1B20 __attribute__((sda));
typedef struct {
    float lowAcceleration, highAcceleration, lowSpeed, highSpeed, deceleration;
} SteeringRateSettings;
extern SteeringRateSettings D_L16_001B1B28 MACRO_ADDR;
extern SteeringRateSettings smallRateSettings SDATA(D_L16_001B1B28);
extern float D_L16_001B1B40 __attribute__((sda));
typedef struct {
    float minAngle;
    char reserved[8];
    float filteredX, filteredY;
} SteeringAngleSettings;
extern SteeringAngleSettings D_L16_001B1B44 MACRO_ADDR;
extern float math_fabs(float);
extern float ApproachValue(float *, float, float);
extern float FastAddRotations(float, float);
extern void math_clamp_speed_to_braking_limit(float *, float, float);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Smooth the steering inputs, update yaw/pitch rates, and limit pitch travel. */
void func_PAL_L16_0041C470(char *object)
{
    SteeringWorkspace local;
    char *state = *(char **)(object + 0x68);
    float acceleration, target, deceleration, newMagnitude;

    qcopy(&local.position, (object + 0x10));
    qcopy(&local.angles, (object + 0xf0));
    if (math_fabs(D_0018BDD0) < D_L16_001B1B50)
        D_L16_001B1B50 = math_fabs(D_0018BDD0);
    else if (D_L16_001B1B50 < -math_fabs(D_0018BDD0))
        D_L16_001B1B50 = -math_fabs(D_0018BDD0);
    if (math_fabs(D_0018BDD4) < D_L16_001B1B44.filteredY)
        D_L16_001B1B44.filteredY = math_fabs(D_0018BDD4);
    else if (D_L16_001B1B44.filteredY < -math_fabs(D_0018BDD4))
        D_L16_001B1B44.filteredY = -math_fabs(D_0018BDD4);
    ApproachValue(&D_L16_001B1B50, D_0018BDD0, 0.15f);
    ApproachValue(&D_L16_001B1B44.filteredY, D_0018BDD4, 0.15f);
    deceleration = D_L16_001B1B20*6.981318e-06f;
    if (D_L16_001B1B50 != 0.0f) {
        if (math_fabs(D_L16_001B1B50) >= 1.0f) {
            acceleration = D_L16_001B1B14[0]*6.981318e-06f;
            target = D_L16_001B1B1C[0]*((-D_L16_001B1B50)*0.0003490659f);
        } else {
            acceleration = D_L16_001B1B10*(math_fabs(D_L16_001B1B50)*6.981318e-06f);
            target = D_L16_001B1B18*((-D_L16_001B1B50)*0.0003490659f);
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
        float inputY = D_L16_001B1B44.filteredY;
        deceleration = smallRateSettings.deceleration*6.981318e-06f;
        if (inputY != 0.0f) {
            if (math_fabs(inputY) >= 1.0f) {
                float turn = -D_L16_001B1B44.filteredY;
                acceleration = D_L16_001B1B28.highAcceleration*6.981318e-06f;
                target = D_L16_001B1B28.highSpeed*(turn*0.0003490659f);
            } else {
                acceleration = smallRateSettings.lowAcceleration*(math_fabs(D_L16_001B1B44.filteredY)*6.981318e-06f);
                target = smallRateSettings.lowSpeed*((-D_L16_001B1B44.filteredY)*0.0003490659f);
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
        local.limits.high = D_L16_001B1B40*0.017453294f;
        local.limits.low = D_L16_001B1B44.minAngle*0.017453294f;
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
