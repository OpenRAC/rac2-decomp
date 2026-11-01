/* functional: high. Plain floats in place of VU0 macro code; the sign test reads the sign bit of 2*sin as qmfc2/dsll32 does, so -0.0 counts as negative; the square root is of an absolute value. */
#include "common.h"

extern float func_00283198(float);
extern float func_00283180(float);

/* Builds a unit quaternion for a turn of `angle` about one axis, from func_00283198 and func_00283180
   of the angle: root = sqrt(|2b| + 2), a = -func_00283198, b = func_00283180. The pair
   (a/root, 0.5*root) goes to the x and w slots (swapped when 2b is negative), then the x slot's
   value moves to y for axis 1 and to z for any other non-zero axis, x being cleared. Four floats
   are stored at dst. */
void func_00283898(void *dst, int axis, float angle)
{
    float *q = (float *)dst;
    union {
        float f;
        int i;
    } u;
    float a, b, twob, absb, root, half, ratio, x, w;

    a = -func_00283198(angle);
    b = func_00283180(angle);
    twob = b + b;
    u.f = twob;
    absb = twob < 0.0f ? -twob : twob;
    root = __builtin_sqrtf(absb + 2.0f);
    half = 0.5f * root;
    ratio = a / root;
    if (u.i < 0) {
        x = 0.0f + half;
        w = 0.0f + ratio;
    } else {
        x = 0.0f + ratio;
        w = half;
    }
    q[0] = x;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[3] = w;
    if (axis == 0) {
        return;
    }
    if (axis == 1) {
        q[1] = q[1] + q[0];
    } else {
        q[2] = q[2] + q[0];
    }
    q[0] = 0.0f;
}
