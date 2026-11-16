#include "include_asm.h"
#include "names.h"


typedef int TI128 __attribute__((mode(TI)));
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern float math_approach_target_with_direction_mode(char *, char *, float, float, float, float, int);
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);

/* Steers the Chainblade smoothly towards a goal position, a heading and a tilt. */
void chainblade_steer_toward_pal(char *self, TI128 *goal, float heading, float tilt) {
    char *state = *(char **)(self + 0x68);
    TI128 vec = *goal;
    float *v = (float *)&vec;

    math_step_value_toward_target(self + 0x10, state + 0x1B0, v[0], 0.036000002f, 0.036000002f, 1.8000001f);
    math_step_value_toward_target(self + 0x14, state + 0x1B4, v[1], 0.036000002f, 0.036000002f, 1.8000001f);
    math_step_value_toward_target(self + 0x18, state + 0x1B8, v[2], 0.036000002f, 0.036000002f, 1.8000001f);
    math_approach_target_with_direction_mode(self + 0xF8, state + 0x1C4, heading, 0.005026549f, 0.005026549f,
                0.26529008f, 0);
    math_approach_target_with_direction_mode(self + 0xF4, state + 0x2F0, tilt, *(float *)(state + 0x124),
                *(float *)(state + 0x128), *(float *)(state + 0x12C), 0);
    math_update_wrapped_angle_offset(self, state + 0x2F4, state + 0x304, 0.5f, 0.10471977f, -1.0f);
}

