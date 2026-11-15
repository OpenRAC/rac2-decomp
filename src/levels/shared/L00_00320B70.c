#include "common.h"

extern void func_00282CF0(char *, char *, char *);
extern float func_00282DF0(char *);
extern void func_00282DD8(char *, char *, char *);
extern float func_00282DB0(char *, char *);
extern float func_002831B0(float);
extern float func_002703B0(int, float, float, float, float, float);
extern float func_00283198(float);
extern void func_00282F20(char *, char *, float);
extern float func_00283180(float);
extern void func_002ACDE8(char *, char *, char *);

/* Turns a facing vector part of the way toward a target, easing the turn, and can give back the rotation used. */
void func_L00_00320B70(char *origin, char *forward, char *target, int mode, float turnParamA, float turnParamB, float turnParamC, char *sideVec, float closeRange,
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
    angle = 1.5707964f - FastAngleHelper(dotProduct / lengthProduct);
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
    halfAngle = StepSpringDamperStored(mode, 0.0f, angle, turnParamA, turnParamB, turnParamC) * 0.5f;
    vec_scale_to_length(sideVec, axis, FastSinOrCosB(halfAngle));
    *(float *)(quat + 12) = FastSinOrCosA(halfAngle);
    RotateVectorByQuaternion(forward, forward, sideVec);
    if (outQuat != 0)
        qcopy(outQuat, sideVec);
}
