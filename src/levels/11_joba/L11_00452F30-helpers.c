#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float mat_fast_helper_a(float f12, float f13);
extern float math_random_float_range(float f12, float f13);
extern float math_fast_sin_or_cos_a(float f12);
extern float math_fast_sin_or_cos_b(float f12);

/* Picks a spot near a point for the flamethrower robot to walk to, a little off to one side of the line between them. */
void flamethrower_robot_pick_wander_point(char *object, TI128 *point)
{
    char *state = *(char **)(object + 0x68);
    float dx, dy;
    if (*(s16 *)(state + 0x2D8) != 0) {
        float angle, scale;
        dx = *(float *)(object + 0x10) - *(float *)point;
        dy = *(float *)(object + 0x14) - *(float *)((char *)point + 4);
        angle = mat_fast_helper_a(dx, dy) + math_random_float_range(-0.78539825f, 0.78539825f);
        scale = 15.0f;
        qcopy((state + 0x2A0), point);
        *(float *)(state + 0x2A0) += math_fast_sin_or_cos_a(angle) * scale;
        *(float *)(state + 0x2A4) += math_fast_sin_or_cos_b(angle) * scale;
        *(float *)(state + 0x2A8) = math_random_float_range(0.0f, 4.0f) + 466.0f;
    } else {
        float angle, k;
        dx = *(float *)(object + 0x10) - *(float *)point;
        dy = *(float *)(object + 0x14) - *(float *)((char *)point + 4);
        angle = mat_fast_helper_a(dx, dy);
        angle += math_random_float_range(-0.78539825f, 0.78539825f);
        k = math_random_float_range(-2.0f, 2.0f);
        k += 8.0f;
        qcopy((state + 0x2A0), point);
        *(float *)(state + 0x2A0) = *(float *)(state + 0x2A0) + k * math_fast_sin_or_cos_a(angle);
        k *= math_fast_sin_or_cos_b(angle);
        *(float *)(state + 0x2A4) += k;
    }
}
