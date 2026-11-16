#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float g_lift_wobble_rot_rate __attribute__((sda));
extern float g_lift_wobble_x_scale __attribute__((sda));
extern float g_lift_wobble_x_rate __attribute__((sda));
extern float g_lift_wobble_y_scale __attribute__((sda));
extern float g_lift_wobble_y_rate __attribute__((sda));
extern float g_lift_wobble_height_scale __attribute__((sda));

/* Restore the base pose, then advance its three independent oscillations. */
void lift_apply_wobble(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float step;
    float next;
    float wave;

    *(TI128 *)(object + 0x10) = *(TI128 *)(state + 0x90);
    *(TI128 *)(object + 0xF0) = *(TI128 *)(state + 0xA0);
    step = 0.00029088825f;
    *(float *)(state + 0xB8) = FastAddRotations(*(float *)(state + 0xB8), g_lift_wobble_rot_rate * step);
    wave = math_fast_sin_or_cos_b(*(float *)(state + 0xB8));
    next = g_lift_wobble_x_rate * step;
    *(float *)(object + 0xF0) += g_lift_wobble_x_scale * wave;
    *(float *)(state + 0xB4) = FastAddRotations(*(float *)(state + 0xB4), next);
    wave = math_fast_sin_or_cos_b(*(float *)(state + 0xB4));
    next = g_lift_wobble_y_rate * step;
    *(float *)(object + 0xF4) += g_lift_wobble_y_scale * wave;
    *(float *)(state + 0xB0) = FastAddRotations(*(float *)(state + 0xB0), next);
    *(float *)(object + 0x18) += g_lift_wobble_height_scale * math_fast_sin_or_cos_b(*(float *)(state + 0xB0));
}
