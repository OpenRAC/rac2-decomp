#include "include_asm.h"

extern float D_L23_001B1400 __attribute__((sda));
extern float D_L23_001B1404 __attribute__((sda));
extern float D_L23_001B1408 __attribute__((sda));
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00282C48(float);

/* Springs the first measure toward its target at the three scaled global rates, and latches
 * it once it is within a tenth of the target. */
void func_PAL_L23_00420578(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(int *)(state + 0x5DC) != 0)
        return;
    func_002AA548((float *)(state + 0x5C8), (float *)(state + 0x5CC), *(float *)(state + 0x5D0),
                  D_L23_001B1400 * 0.00040000002f, D_L23_001B1404 * 0.00040000002f,
                  D_L23_001B1408 * 0.020000001f);
    if (func_00282C48(*(float *)(state + 0x5C8) - *(float *)(state + 0x5D0)) < 0.1f) {
        *(int *)(state + 0x5DC) = 1;
        *(int *)(state + 0x5CC) = 0;
    }
}
