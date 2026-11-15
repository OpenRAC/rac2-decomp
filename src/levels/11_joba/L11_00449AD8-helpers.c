#include "common.h"

extern float mat_fast_helper_a(float f12, float f13);
extern float math_random_float_range(float f12, float f13);
extern float math_fast_sin_or_cos_a(float f12);
extern float math_fast_sin_or_cos_b(float f12);

/* Picks a spot near a point for the robot to walk to, a little off to one side of the line between them. */
void security_robot_pick_wander_point(char *object, char *point)
{
    char *state = *(char **)(object + 0x68);

    if (*(s16 *)(state + 0x36E) != 0) {
        float dx = *(float *)(object + 0x10) - *(float *)(point + 0x0);
        float dy = *(float *)(object + 0x14) - *(float *)(point + 0x4);
        float base = mat_fast_helper_a(dx, dy) + math_random_float_range(-0.17453295f, 0.17453295f);
        float scale = 15.0f;
        float height_jitter;

        qcopy((state + 0x330), point);
        *(float *)(state + 0x330) += math_fast_sin_or_cos_a(base) * scale;
        *(float *)(state + 0x334) += math_fast_sin_or_cos_b(base) * scale;
        height_jitter = math_random_float_range(-4.0f, 4.0f);
        *(float *)(state + 0x338) = *(float *)(object + 0x18) + height_jitter;
    } else {
        float dx = *(float *)(object + 0x10) - *(float *)(point + 0x0);
        float dy = *(float *)(object + 0x14) - *(float *)(point + 0x4);
        float base = mat_fast_helper_a(dx, dy) + math_random_float_range(-0.78539825f, 0.78539825f);
        float scale = math_random_float_range(-2.0f, 2.0f) + 8.0f;

        qcopy((state + 0x330), point);
        *(float *)(state + 0x330) += scale * math_fast_sin_or_cos_a(base);
        scale = scale * math_fast_sin_or_cos_b(base);
        *(float *)(state + 0x334) += scale;
    }
}
