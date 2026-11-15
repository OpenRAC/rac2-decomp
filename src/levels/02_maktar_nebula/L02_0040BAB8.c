#include "names.h"
/* Choose a randomized point around the supplied full vector and store it in the private state.
 * The shared helper transfers the complete aligned 16-byte input vector.
 */
#include "common.h"

extern float mat_fast_helper_a(float,float),math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);

/* Picks a random spot near the target, a few steps away from the object, and stores it as the place the robot should walk to. */
void robot_pick_random_walk_target(u8 *moby, float *target) {
    float angle, distance, offset_x, cos_angle;
    u8 *vars;

    angle = mat_fast_helper_a(*(float *)(moby + 0x10) - target[0], *(float *)(moby + 0x14) - target[1]);
    angle = angle + math_random_float_range(-0.7853982448577881f, 0.7853982448577881f);
    distance = math_random_float_range(-2.0f, 2.0f) + 8.0f;
    vars = *(u8 **)(moby + 0x68);
    qcopy(vars + 0x2C0, target);
    offset_x = distance * math_fast_sin_or_cos_a(angle);
    *(float *)(vars + 0x2C0) = *(float *)(vars + 0x2C0) + offset_x;
    cos_angle = math_fast_sin_or_cos_b(angle);
    *(float *)(vars + 0x2C4) = *(float *)(vars + 0x2C4) + distance * cos_angle;
}
