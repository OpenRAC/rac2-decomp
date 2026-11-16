#include "common.h"

/* func_PAL_L16_00411E88, the PAL copy of func_L16_0040CF98: the same C, where the lead doubling
   becomes 2 * 5/6 and the turn rates take a 6/5 squared correction at 50 Hz. */

extern int math_fast_float_d(void *);
extern s32 FastDecTimer(void *);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern float fast_vec_dist(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern void moby_update_eased_node(void *, void *, s32, float, float);
extern u8 g_turret_aim_vector[] __attribute__((nosda));
extern float g_turret_ease_rate_a __attribute__((sda));
extern float g_turret_ease_rate_b __attribute__((sda));

void func_PAL_L16_00411E88(u8 *arg)
{
    float temp[4];
    float target[4];
    u8 *state;
    u8 *origin;
    float value;
    float scale;
    float rate;
    state = *(u8 **)(arg + 0x68);
    math_fast_float_d(state + 0x238);
    FastDecTimer(state + 0x23C);
    if (*(u16 *)(arg + 0x96) < 0xFFFF) ++*(u16 *)(arg + 0x96);
    moby_transform_joint_to_world(arg, 0, temp);
    if (arg[0x20] != 4) {
        origin = state + 0x1F0;
        value = fast_vec_dist(temp, origin) - 1.0f;
        FastVecScale(target, g_turret_aim_vector, value * 1.6666666f);
        target[2] = 0.0f;
        FastVecAdd(target, target, origin);
        FastVecSub(temp, target, temp);
        *(float *)(state + 0x2B8) = fast_subtract_rotations(mat_fast_helper_a(temp[0], temp[1]), *(float *)(arg + 0xF8));
        moby_transform_joint_to_world(arg, 1, temp);
        FastVecSub(temp, target, temp);
        value = fast_subtract_rotations(-mat_fast_helper_a(vec_length_xy(temp), temp[2]), *(float *)(arg + 0xF4));
        if (value > 0.523598849773407f) value = 0.523598849773407f;
        else if (value < -0.523598849773407f) value = -0.523598849773407f;
        *(float *)(state + 0x334) = value;
        scale = 0.5f;
    } else {
        *(float *)(state + 0x2B8) = FastAddRotations(*(float *)(state + 0x298), 0.523598849773407f);
        scale = 0.085f;
    }
    rate = scale * 1.44f;
    moby_update_eased_node(arg, state + 0x250, 0, g_turret_ease_rate_a * rate, g_turret_ease_rate_b * rate);
    moby_update_eased_node(arg, state + 0x2D0, 1, g_turret_ease_rate_a * rate, g_turret_ease_rate_b * rate);
}
