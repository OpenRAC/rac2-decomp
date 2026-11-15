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
void vec_turn_toward_target(char *origin, char *forward, char *target, int mode, float turnParamA, float turnParamB, float turnParamC, char *sideVec, float closeRange,
                       char *outQuat)
{
    char toTarget[16];
    char axis[16];
    char quat[16];
    float distance;
    float dotProduct;
    float lengthProduct;
    float angle;
    float halfAngle;

    FastVecSub(toTarget, target, origin);
    distance = FastVecLength(toTarget);
    if (distance == 0.0f)
        return;
    FastVecCross(axis, toTarget, forward);
    dotProduct = FastVecDot(forward, toTarget);
    lengthProduct = FastVecLength(forward);
    lengthProduct *= FastVecLength(toTarget);
    if (lengthProduct == 0.0f)
        return;
    angle = 1.5707964f - math_fast_angle_helper(dotProduct / lengthProduct);
    if (angle > 2.8797936f) {
        FastVecCross(quat, forward, sideVec);
        FastVecCross(axis, quat, forward);
        sideVec = quat;
    } else {
        sideVec = quat;
        if (distance < closeRange && angle < 1.5707965f) {
            turnParamB = 1.0f;
            turnParamA = 0.5f;
        }
    }
    halfAngle = math_step_spring_damper_stored(mode, 0.0f, angle, turnParamA, turnParamB, turnParamC) * 0.5f;
    vec_scale_to_length(sideVec, axis, math_fast_sin_or_cos_b(halfAngle));
    *(float *)(quat + 12) = math_fast_sin_or_cos_a(halfAngle);
    vec_rotate_by_quaternion(forward, forward, sideVec);
    if (outQuat != 0)
        qcopy(outQuat, sideVec);
}
