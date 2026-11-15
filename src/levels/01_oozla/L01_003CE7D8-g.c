#include "include_asm.h"
#include "names.h"

typedef float f32;

extern float math_fabs(float a0);

/* Damped follow step: blends the velocity at a1 toward the spring term, then
   advances the position at a0 and passes the remaining offset to func_00282C48. */
/* Moves a value toward a target with a springy pull that slows over time. */
float math_step_damped_spring(f32 *value, f32 *velocity, f32 target, f32 strength, f32 damping, f32 range)
{
    f32 work, speed, current;

    work = 1.0f;
    range = range * range;
    speed = *velocity;
    damping = 1.0f - damping;
    damping = damping - 1.0f;
    damping = damping + 1.0f;
    speed = speed * damping;
    *velocity = speed;
    current = *value;
    work = current - target;
    work = work * work;
    if (!(work > range)) {
    } else {
        work = range;
    }
    work = work * strength;
    work = work / range;
    if (target < current)
        *velocity = speed - work;
    else
        *velocity = speed + work;
    speed = *velocity;
    work = *value;
    work = work + speed;
    target = target - work;
    *value = work;
    return math_fabs(target);
}
