#include "include_asm.h"
#include "names.h"

extern float D_L23_001B1400 __attribute__((sda));
extern float D_L23_001B1404 __attribute__((sda));
extern float D_L23_001B1408 __attribute__((sda));
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float math_fabs(float);

/* Springs the first measure toward its target at the three scaled global rates, and latches
 * it once it is within a tenth of the target. */
void func_PAL_L23_00420578(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(int *)(state + 0x5DC) != 0)
        return;
    math_step_value_toward_target((float *)(state + 0x5C8), (float *)(state + 0x5CC), *(float *)(state + 0x5D0),
                  D_L23_001B1400 * 0.00040000002f, D_L23_001B1404 * 0.00040000002f,
                  D_L23_001B1408 * 0.020000001f);
    if (math_fabs(*(float *)(state + 0x5C8) - *(float *)(state + 0x5D0)) < 0.1f) {
        *(int *)(state + 0x5DC) = 1;
        *(int *)(state + 0x5CC) = 0;
    }
}
