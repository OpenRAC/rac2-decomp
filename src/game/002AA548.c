#include "common.h"
extern float func_00282C10(float);
extern float func_00282C48(float);
extern float func_002AA2E8(float *, float, float);
float func_002AA548(float *value, float *velocity, float target,
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
            if (func_00282C48(diff) < stopping) {
                magnitude = func_00282C48(diff);
                magnitude += func_00282C48(*velocity);
                if (stopping < magnitude)
                    func_002AA2E8(velocity, 0.0f, acceleration);
                else
                    func_002AA2E8(velocity, 0.0f, acceleration * 1.1f);
            } else {
                desired = func_00282C10((acceleration + acceleration) * diff);
                if (maximum < desired)
                    desired = maximum;
                if (diff < 0.0f)
                    func_002AA2E8(velocity, -desired, step);
                else
                    func_002AA2E8(velocity, desired, step);
            }
            magnitude = func_00282C48(diff);
            if (func_00282C48(*velocity) < magnitude) {
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
