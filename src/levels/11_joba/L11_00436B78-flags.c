#include "common.h"


#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float mat_fast_helper_a(float f12, float f13);
extern float math_random_float_range(float f12, float f13);
extern float math_fast_sin_or_cos_a(float f12);
extern float math_fast_sin_or_cos_b(float f12);

/* Same body as func_L11_0044C688, with this function's own callees. */
/* Picks a random resting spot near a point, a short way from the object, and stores it as the object's home spot. */
void enemy_pick_random_home_spot(char *moby, TI128 *target)
{
    char *vars = *(char **)(moby + 0x68);
    float f12, f13;
    if (*(s16 *)(vars + 0x286) != 0) {
        float sum, scale;
        f12 = *(float *)(moby + 0x10) - *(float *)target;
        f13 = *(float *)(moby + 0x14) - *(float *)((char *)target + 4);
        sum = mat_fast_helper_a(f12, f13) + math_random_float_range(-0.78539825f, 0.78539825f);
        scale = 15.0f;
        qcopy((vars + 0x250), target);
        *(float *)(vars + 0x250) += math_fast_sin_or_cos_a(sum) * scale;
        *(float *)(vars + 0x254) += math_fast_sin_or_cos_b(sum) * scale;
        *(float *)(vars + 0x258) = math_random_float_range(0.0f, 4.0f) + 466.0f;
    } else {
        float sum, k;
        f12 = *(float *)(moby + 0x10) - *(float *)target;
        f13 = *(float *)(moby + 0x14) - *(float *)((char *)target + 4);
        sum = mat_fast_helper_a(f12, f13);
        sum += math_random_float_range(-0.78539825f, 0.78539825f);
        k = math_random_float_range(-2.0f, 2.0f);
        k += 8.0f;
        qcopy((vars + 0x250), target);
        *(float *)(vars + 0x250) = *(float *)(vars + 0x250) + k * math_fast_sin_or_cos_a(sum);
        k *= math_fast_sin_or_cos_b(sum);
        *(float *)(vars + 0x254) += k;
    }
}
