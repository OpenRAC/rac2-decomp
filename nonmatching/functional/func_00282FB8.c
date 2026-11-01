/* functional: high. Plain floats in place of VU0 macro code; the length uses an exact square root, the divide an exact divide, and the comparison reads the sign of limit - length as retail does. */
#include "common.h"

/* Clamps a vector to a maximum length: when src (4 floats) has a length above zero and not below
   limit, dst gets src.xyz scaled by limit/length (dst.w = src.w) and 1 is returned; otherwise dst
   is left alone and 0 is returned. dst may be src. */
int func_00282FB8(void *dst, void *src, float limit)
{
    float *s = (float *)src;
    float *d = (float *)dst;
    float x = s[0], y = s[1], z = s[2], w = s[3];
    float sq, len, q;

    sq = x * x;
    sq = sq + y * y;
    sq = sq + z * z;
    len = __builtin_sqrtf(sq < 0.0f ? -sq : sq);
    if (len == 0.0f || limit - len > 0.0f) {
        return 0;
    }
    q = limit / len;
    d[0] = x * q;
    d[1] = y * q;
    d[2] = z * q;
    d[3] = w;
    return 1;
}
