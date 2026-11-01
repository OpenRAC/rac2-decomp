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
extern char D_00188660[];
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
extern float func_00282C48(float);
extern float func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern void func_L16_00317C90(float *, float, float);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Smooth the steering inputs, update yaw/pitch rates, and limit pitch travel. */
void func_PAL_L16_0041C470(char *object)
{
    SteeringWorkspace local;
    char *state = *(char **)(object + 0x68);
    float acceleration, target, deceleration, newMagnitude;

    qcopy(&local.position, (object + 0x10));
    qcopy(&local.angles, (object + 0xf0));
    if (func_00282C48(D_0018BDD0) < D_L16_001B1B50)
        D_L16_001B1B50 = func_00282C48(D_0018BDD0);
    else if (D_L16_001B1B50 < -func_00282C48(D_0018BDD0))
        D_L16_001B1B50 = -func_00282C48(D_0018BDD0);
    if (func_00282C48(D_0018BDD4) < D_L16_001B1B44.filteredY)
        D_L16_001B1B44.filteredY = func_00282C48(D_0018BDD4);
    else if (D_L16_001B1B44.filteredY < -func_00282C48(D_0018BDD4))
        D_L16_001B1B44.filteredY = -func_00282C48(D_0018BDD4);
    func_002AA2E8(&D_L16_001B1B50, D_0018BDD0, 0.15f);
    func_002AA2E8(&D_L16_001B1B44.filteredY, D_0018BDD4, 0.15f);
    deceleration = D_L16_001B1B20*6.981318e-06f;
    if (D_L16_001B1B50 != 0.0f) {
        if (func_00282C48(D_L16_001B1B50) >= 1.0f) {
            acceleration = D_L16_001B1B14[0]*6.981318e-06f;
            target = D_L16_001B1B1C[0]*((-D_L16_001B1B50)*0.0003490659f);
        } else {
            acceleration = D_L16_001B1B10*(func_00282C48(D_L16_001B1B50)*6.981318e-06f);
            target = D_L16_001B1B18*((-D_L16_001B1B50)*0.0003490659f);
        }
    } else {
        acceleration = 0.0f;
        target = 0.0f;
    }
    {
        float oldMagnitude = func_00282C48(*(float *)(state + 0x80));
        newMagnitude = func_00282C48(target);
        if (newMagnitude < oldMagnitude)
            func_002AA2E8((float *)(state + 0x80), target, deceleration);
        else
            func_002AA2E8((float *)(state + 0x80), target, acceleration);
    }
    {
        float inputY = D_L16_001B1B44.filteredY;
        deceleration = smallRateSettings.deceleration*6.981318e-06f;
        if (inputY != 0.0f) {
            if (func_00282C48(inputY) >= 1.0f) {
                float turn = -D_L16_001B1B44.filteredY;
                acceleration = D_L16_001B1B28.highAcceleration*6.981318e-06f;
                target = D_L16_001B1B28.highSpeed*(turn*0.0003490659f);
            } else {
                acceleration = smallRateSettings.lowAcceleration*(func_00282C48(D_L16_001B1B44.filteredY)*6.981318e-06f);
                target = smallRateSettings.lowSpeed*((-D_L16_001B1B44.filteredY)*0.0003490659f);
            }
        } else {
            acceleration = 0.0f;
            target = 0.0f;
        }
    }
    {
        float oldMagnitude = func_00282C48(*(float *)(state + 0x84));
        newMagnitude = func_00282C48(target);
        if (newMagnitude < oldMagnitude)
            func_002AA2E8((float *)(state + 0x84), target, deceleration);
        else
            func_002AA2E8((float *)(state + 0x84), target, acceleration);
    }
    if (*(float *)(state + 0x80) != 0.0f)
        *(float *)(object + 0xf8) = func_00283B98(*(float *)(object + 0xf8), *(float *)(state + 0x80));
    if (*(float *)(state + 0x84) != 0.0f) {
        local.limits.high = D_L16_001B1B40*0.017453294f;
        local.limits.low = D_L16_001B1B44.minAngle*0.017453294f;
        local.work.bounds = local.limits;
        func_L16_00317C90((float *)(state + 0x84), local.work.bounds.high - *(float *)(state + 0x90), deceleration);
        func_L16_00317C90((float *)(state + 0x84), local.work.bounds.low - *(float *)(state + 0x90), deceleration);
        *(float *)(state + 0x90) = func_00283B98(*(float *)(state + 0x90), *(float *)(state + 0x84));
        if (*(float *)(state + 0x90)>local.work.bounds.high) {
            *(float *)(state + 0x90) = local.work.bounds.high;
            *(float *)(state + 0x84) = 0.0f;
        } else if (*(float *)(state + 0x90)<local.work.bounds.low) {
            *(float *)(state + 0x90) = local.work.bounds.low;
            *(float *)(state + 0x84) = 0.0f;
        }
    }
    if (func_00282C48(*(float *)(state + 0x80))>0.0f || func_00282C48(*(float *)(state + 0x84))>0.0f) {
        int handle = *(int *)(state + 0xa4);
        char *sound = D_00188660 + 0x70*handle;
        if ((*(char **)(sound + 0x88)) != object || (*(unsigned char *)(sound + 0x74)) == 0)
            *(int *)(state + 0xa4) = func_002E5CF8(4, 4, object);
    } else {
        int handle = *(int *)(state + 0xa4);
        if (handle != -1) {
            char *sound = D_00188660 + 0x70*handle;
            if ((*(char **)(sound + 0x88)) == object && (*(unsigned char *)(sound + 0x74)) != 0)
                func_002E59F8(handle);
        }
        *(int *)(state + 0xa4) = -1;
    }
    func_00282CF0(&local.work.delta, object + 0x10, &local.position);
    func_002AD6F0(state + 0x20, &local.work.delta, &local.angles, object + 0xf0);
}
