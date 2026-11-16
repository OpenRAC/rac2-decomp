#include "include_asm.h"
#include "names.h"


typedef int TI128 __attribute__((mode(TI)));
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern float math_approach_target_with_direction_mode(char *, char *, float, float, float, float, int);
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);

void chainblade_steer_toward_pal(char *arg0, TI128 *arg1, float arg2, float arg3) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 vec = *arg1;
    float *v = (float *)&vec;

    math_step_value_toward_target(arg0 + 0x10, state + 0x1B0, v[0], 0.036000002f, 0.036000002f, 1.8000001f);
    math_step_value_toward_target(arg0 + 0x14, state + 0x1B4, v[1], 0.036000002f, 0.036000002f, 1.8000001f);
    math_step_value_toward_target(arg0 + 0x18, state + 0x1B8, v[2], 0.036000002f, 0.036000002f, 1.8000001f);
    math_approach_target_with_direction_mode(arg0 + 0xF8, state + 0x1C4, arg2, 0.005026549f, 0.005026549f,
                0.26529008f, 0);
    math_approach_target_with_direction_mode(arg0 + 0xF4, state + 0x2F0, arg3, *(float *)(state + 0x124),
                *(float *)(state + 0x128), *(float *)(state + 0x12C), 0);
    math_update_wrapped_angle_offset(arg0, state + 0x2F4, state + 0x304, 0.5f, 0.10471977f, -1.0f);
}

