#include "include_asm.h"
#include "names.h"

extern float func_00282C48(float);
extern float func_00282C10(float);
extern void func_002AA2E8(float *, float, float);

/* Moves a value toward a target: it speeds up, brakes early enough, and stops on the target. */
void func_002AAC80(float *value, float target, float accel, float brake, float limit)
{
    float stopDistance, total, speed, desiredSpeed, product;
    if (target == 0.0f && *value == 0.0f) return;
    product = *value * target;
    if (product >= 0.0f && target != 0.0f) {
        speed = *value;
        stopDistance = (speed * speed / brake) * 0.5f;
        if (FloatAbs(target) < stopDistance) {
            total = FloatAbs(target) + FloatAbs(*value);
            if (stopDistance < total) ApproachValue(value, 0.0f, brake);
            else ApproachValue(value, 0.0f, brake * 1.1f);
        } else {
            speed = brake * 2.0f;
            desiredSpeed = square_root(speed * target);
            if (limit < desiredSpeed) desiredSpeed = limit;
            if (target < 0.0f) ApproachValue(value, -desiredSpeed, accel);
            else ApproachValue(value, desiredSpeed, accel);
        }
        total = FloatAbs(target);
        if (!(FloatAbs(*value) < total)) *value = target;
    } else {
        speed = *value;
        if (speed >= 0.0f) speed -= brake;
        else speed += brake;
        *value = speed;
        if (target < 0.0f && speed < target) { *value = target; return; }
        if (target > 0.0f && *value > target) *value = target;
    }
}

