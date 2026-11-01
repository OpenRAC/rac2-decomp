/* functional: high. Plain floats in place of VU0 macro code, in the same order of operations. */
#include "common.h"

/* QuatToMatrix3: quaternion (x, y, z, w) at q into three rows of four floats at m. */
void func_00283958(void *quaternion, void *matrix)
{
    float *q = quaternion;
    float *m = matrix;
    float x = q[0] + q[0], y = q[1] + q[1], z = q[2] + q[2];
    float wx = x * q[3], wy = y * q[3], wz = z * q[3];
    float xx = x * q[0], xy = y * q[0], xz = z * q[0];
    float yy = y * q[1], yz = z * q[1];
    float zz = z * q[2];

    m[0] = (1.0f - yy) - zz;
    m[1] = xy - wz;
    m[2] = xz + wy;
    m[3] = 0.0f;
    m[4] = (0.0f + wz) + xy;
    m[5] = (1.0f - xx) - zz;
    m[6] = yz - wx;
    m[7] = 0.0f;
    m[8] = (0.0f - wy) + xz;
    m[9] = (0.0f + wx) + yz;
    m[10] = (1.0f - xx) - yy;
    m[11] = 0.0f;
}
