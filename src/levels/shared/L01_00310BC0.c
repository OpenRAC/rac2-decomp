#include "include_asm.h"
#include "names.h"


extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);

/* Turns an angle toward a target with a smooth, speed-limited step and returns the new angle. */
float func_L01_00310BC0(float *speed, float angle, float target,
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
    if (FloatAbs(difference) < *speed)
        *speed = FloatAbs(difference);
    else if (*speed < -FloatAbs(difference))
        *speed = -FloatAbs(difference);
    return FastAddRotations(angle, *speed);
}
