#include "common.h"

extern void FastVecSub(char *, char *, char *);
extern float FastVecLength(char *);
extern void FastVecCross(char *, char *, char *);
extern float FastVecDot(char *, char *);
extern float math_fast_angle_helper(float);
extern float math_step_spring_damper_stored(int, float, float, float, float, float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(char *, char *, float);
extern float math_fast_sin_or_cos_a(float);
extern void vec_rotate_by_quaternion(char *, char *, char *);

/* Turns a facing vector part of the way toward a target, easing the turn, and can give back the rotation used. */
void vec_turn_toward_target(char *origin, char *forward, char *target, int mode, float turn_param_a, float turn_param_b, float turn_param_c, char *side_vec, float close_range,
                       char *out_quat)
{
    char to_target[16];
    char axis[16];
    char quat[16];
    float distance;
    float dot_product;
    float length_product;
    float angle;
    float half_angle;

    FastVecSub(to_target, target, origin);
    distance = FastVecLength(to_target);
    if (distance == 0.0f)
        return;
    FastVecCross(axis, to_target, forward);
    dot_product = FastVecDot(forward, to_target);
    length_product = FastVecLength(forward);
    length_product *= FastVecLength(to_target);
    if (length_product == 0.0f)
        return;
    angle = 1.5707964f - math_fast_angle_helper(dot_product / length_product);
    if (angle > 2.8797936f) {
        FastVecCross(quat, forward, side_vec);
        FastVecCross(axis, quat, forward);
        side_vec = quat;
    } else {
        side_vec = quat;
        if (distance < close_range && angle < 1.5707965f) {
            turn_param_b = 1.0f;
            turn_param_a = 0.5f;
        }
    }
    half_angle = math_step_spring_damper_stored(mode, 0.0f, angle, turn_param_a, turn_param_b, turn_param_c) * 0.5f;
    vec_scale_to_length(side_vec, axis, math_fast_sin_or_cos_b(half_angle));
    *(float *)(quat + 12) = math_fast_sin_or_cos_a(half_angle);
    vec_rotate_by_quaternion(forward, forward, side_vec);
    if (out_quat != 0)
        qcopy(out_quat, side_vec);
}
