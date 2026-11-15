#include "include_asm.h"
#include "names.h"

extern float math_fabs(float);
extern float square_root(float);
extern float ApproachValue(float *, float, float);

/* Moves a value toward a target: it speeds up, brakes early enough, and stops on the target. */
void math_approach_target_with_braking(float *value, float target, float accel, float brake, float limit)
{
    float stopDistance, total, speed, desiredSpeed, product;
    if (target == 0.0f && *value == 0.0f) return;
    product = *value * target;
    if (product >= 0.0f && target != 0.0f) {
        speed = *value;
        stopDistance = (speed * speed / brake) * 0.5f;
        if (math_fabs(target) < stopDistance) {
            total = math_fabs(target) + math_fabs(*value);
            if (stopDistance < total) ApproachValue(value, 0.0f, brake);
            else ApproachValue(value, 0.0f, brake * 1.1f);
        } else {
            speed = brake * 2.0f;
            desiredSpeed = square_root(speed * target);
            if (limit < desiredSpeed) desiredSpeed = limit;
            if (target < 0.0f) ApproachValue(value, -desiredSpeed, accel);
            else ApproachValue(value, desiredSpeed, accel);
        }
        total = math_fabs(target);
        if (!(math_fabs(*value) < total)) *value = target;
    } else {
        speed = *value;
        if (speed >= 0.0f) speed -= brake;
        else speed += brake;
        *value = speed;
        if (target < 0.0f && speed < target) { *value = target; return; }
        if (target > 0.0f && *value > target) *value = target;
    }
}

