/* func_L20_00443DF0 (1 place). -O2 -G0 -ffunction-sections -frac2-hazard-labels:
   without -frac2-hazard-labels the branch at +0xA4 targets one label to the
   right, so it cannot stay in L20_0043ECB0.c, whose other functions build
   without the flag. */
#include "common.h"

extern void func_L20_00443B60(char *, char *, char *, float *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_L03_003D09D0(int, int, void *, void *, void *, int, int, int);
extern char D_00189EA0[];

/* Clamps the aim angle's magnitude into [pi/6, pi/4], keeping its sign, then
   launches a projectile along the rotated, flattened offset.  Retail's
   constants are 0x3F490FDC and 0x3F060A93, one ulp above the nearest floats
   to pi/4 and pi/6, so they are written 0.78539825f and 0.52359885f. */
char *func_L20_00443DF0(char *arg0)
{
    char *state = *(char **)(arg0 + 0x68);
    float ang[4];
    float v[4];
    float w[4];
    float t;
    float f;

    t = 0.78539825f;
    func_L20_00443B60(arg0, (char *)ang, (char *)v, &t);
    ang[2] = ang[2] + 1.0f;
    if (t < 0.0f) {
        if (t > -0.52359885f)
            t = -0.52359885f;
        else if (t < -0.78539825f)
            t = -0.78539825f;
    } else {
        if (t > 0.78539825f)
            t = 0.78539825f;
        else if (t < 0.52359885f)
            t = 0.52359885f;
    }
    f = func_00283B98(t, *(float *)(arg0 + 0xF8));
    v[0] = func_00283180(f) * 0.16666667f;
    v[1] = func_00283198(f) * 0.16666667f;
    v[2] = -0.033333335f;
    if (func_002A77E0(2) != 0) {
        func_00282D30(w, v, 90.0f);
    } else {
        func_00282D30(w, v, func_002A7878(0.4f, 0.6f) * 180.0f);
    }
    func_00282CC0(w, w, ang);
    func_00282CF0(w, D_00189EA0, w);
    w[2] = 0.0f;
    func_00282F20(w, w, 0.16666667f);
    return func_L03_003D09D0((int)arg0, 0, ang, v, w, 0xB4, 0x258, *(unsigned char *)(state + 0x36));
}
