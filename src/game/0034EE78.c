#include "include_asm.h"
#include "names.h"
/* Cubic Hermite blend of p0, m0, m1, p1 at t (asserted to lie in [0, 1]). */
extern char D_001AE7A0[];
extern char D_001AE7B8[];
extern void func_00115E38(char *, int, char *);
float func_0034EE78(float t, float p0, float m0, float m1, float p1)
{
    float t2, t3;
    if (!(t >= 0.0f && t <= 1.0f))
        ReportAssertAndAbort(D_001AE7A0, 0x24, D_001AE7B8);
    t2 = t * t;
    t3 = t2 * t;
    p0 *= ((t3 + t3) - (t2 * 3.0f)) + 1.0f;
    m0 = m0 * ((t3 - (t2 + t2)) + t);
    m1 = m1 * (t3 - t2);
    p1 = p1 * ((t2 * 3.0f) - (t3 + t3));
    return ((p0 + m0) + m1) + p1;
}
