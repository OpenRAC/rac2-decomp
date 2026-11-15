#include "include_asm.h"
#include "names.h"


extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float math_fabs(float);

/* Turns an angle toward a target with a smooth, speed-limited step and returns the new angle. */
float math_turn_angle_toward_target(float *speed, float angle, float target,
                      float acceleration, float damping, float limit)
{
    float difference = fast_subtract_rotations(target, angle);
    float drive = difference * 6.366197f;
    if (drive > 1.0f)
        drive = 1.0f;
    else if (drive < -1.0f)
        drive = -1.0f;
    *speed = *speed + (acceleration * drive - damping * *speed);
    if (limit != 0.0f) {
        if (*speed > limit)
            *speed = limit;
        else if (*speed < -limit)
            *speed = -limit;
    }
    if (math_fabs(difference) < *speed)
        *speed = math_fabs(difference);
    else if (*speed < -math_fabs(difference))
        *speed = -math_fabs(difference);
    return FastAddRotations(angle, *speed);
}
