#include "common.h"
extern float square_root(float);
extern float math_fabs(float);
extern float ApproachValue(float *, float, float);
/* Moves a value smoothly toward a target using a speed that speeds up and slows down, and returns how far it moved. */
float math_step_value_toward_target(float *value, float *velocity, float target,
                   float step, float acceleration, float maximum)
{
    float diff;
    float stopping;
    float magnitude;
    float desired;
    float selectedVelocity;

    diff = target - *value;
    if (*velocity == 0.0f && diff == 0.0f)
        return 0.0f;
    {
        float speed = *velocity;
        if (0.0f <= speed * diff) {
            stopping = ((speed * speed) / acceleration) * 0.5f;
            if (math_fabs(diff) < stopping) {
                magnitude = math_fabs(diff);
                magnitude += math_fabs(*velocity);
                if (stopping < magnitude)
                    ApproachValue(velocity, 0.0f, acceleration);
                else
                    ApproachValue(velocity, 0.0f, acceleration * 1.1f);
            } else {
                desired = square_root((acceleration + acceleration) * diff);
                if (maximum < desired)
                    desired = maximum;
                if (diff < 0.0f)
                    ApproachValue(velocity, -desired, step);
                else
                    ApproachValue(velocity, desired, step);
            }
            magnitude = math_fabs(diff);
            if (math_fabs(*velocity) < magnitude) {
                *value = *value + *velocity;
                return *velocity;
            }
            else {
                *value = target;
                return diff;
            }
        } else {
            if (0.0f <= speed)
                selectedVelocity = speed - acceleration;
            else
                selectedVelocity = speed + acceleration;
            *velocity = selectedVelocity;
        }
        *value = *value + selectedVelocity;
        return *velocity;
    }
}
