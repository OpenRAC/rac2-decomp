#include "common.h"

/* func_PAL_L01_003D2900, the PAL copy of func_L01_003CE7D8: the same C, with the
   damping scaled by 1.2 for 50 Hz. */

extern float math_fabs(float a0);

/* Damped follow step: blends the velocity at a1 toward the spring term, then
   advances the position at a0 and passes the remaining offset to func_00282C48. */
float math_step_damped_spring_pal(f32 *value, f32 *velocity, f32 target, f32 strength, f32 damping, f32 range)
{
    f32 work, speed, current;

    work = 1.0f;
    range = range * range;
    current = 1.2f;
    speed = *velocity;
    damping = 1.0f - damping;
    damping = damping - 1.0f;
    damping = damping * current;
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
