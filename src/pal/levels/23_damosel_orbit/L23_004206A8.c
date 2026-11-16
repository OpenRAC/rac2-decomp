#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef unsigned long long u64;
extern s32 mothership_is_value_not_in_slots(s32 arg0);
extern s32 math_get_mask_bit(u64, s32);
extern float math_fabs(float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern s32 g_effect_pool_total __attribute__((sda));
extern s32 g_effect_pool_counts[3] __attribute__((sda));
extern s32 g_effect_pools[3][60];
extern s32 g_effect_pool_total __attribute__((sda));
extern s32 g_effect_pool_counts[3] __attribute__((sda));
extern s32 g_effect_pool_limits[4];
extern s32 g_effect_pools[3][60];

/* Springs the second measure toward its target, doubles the word at +0x74, and latches the
 * measure once it is within a tenth of the target. */
void mothership_spring_second_measure_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(s32 *)(state + 0x5D8) != 0)
        return;
    math_step_value_toward_target((float *)(state + 0x588), (float *)(state + 0x58C), *(float *)(state + 0x5D4),
                  0.024f, 0.024f, 0.49000004f);
    *(float *)(state + 0x74) *= 2.0f;
    if (math_fabs(*(float *)(state + 0x588) - *(float *)(state + 0x5D4)) < 0.1f) {
        *(s32 *)(state + 0x5D8) = 1;
        *(s32 *)(state + 0x58C) = 0;
    }
}

