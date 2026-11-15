#include "include_asm.h"

#include "common.h"
extern void *moby_get_vars_word_18(char *a0);
extern float mat_fast_helper_a(float a, float b);
extern float FastAddRotations(float a, float b);
extern int FastDecTimer(short *p);
extern int math_random_int_range(int a0, int a1);
extern int moby_move_to_target_temp_limits(char *a0, char *a1, float f12, char *a2, float f13, float f14);

/* Aim the record at the shape the caller found. */
int func_PAL_L03_0032F148(char *self, float *target, char *third, float amount, float f13, float f14)
{
    char *data = (char *)moby_get_vars_word_18(self);
    float angle;

    if (data == 0)
        return 8;
    angle = mat_fast_helper_a(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = math_random_int_range(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return moby_move_to_target_temp_limits(self, target, angle, third, f13, f14);
}

