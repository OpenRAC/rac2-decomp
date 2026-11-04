/* func_PAL_L20_00449870 (1 place), the PAL copy of func_L20_00443DF0 with 50 Hz values: the
   per-frame scale 1/6 becomes 1/5 (0x3E4CCCCE, one ulp above 0.2f, written 0.20000002f), the
   drop -1/30 becomes -1/25, the spread 90/180 becomes 75/150 and the projectile's 180 and 600
   frames become 150 and 500. -O2 -G0 -ffunction-sections -frac2-hazard-labels, as v1.01's. */
#include "common.h"

extern void func_PAL_L20_004495C0(char *, char *, char *, float *);
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
char *func_PAL_L20_00449870(char *arg0)
{
    char *state = *(char **)(arg0 + 0x68);
    float ang[4];
    float v[4];
    float w[4];
    float t;
    float f;

    t = 0.78539825f;
    func_PAL_L20_004495C0(arg0, (char *)ang, (char *)v, &t);
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
    v[0] = func_00283180(f) * 0.20000002f;
    v[1] = func_00283198(f) * 0.20000002f;
    v[2] = -0.04f;
    if (func_002A77E0(2) != 0) {
        func_00282D30(w, v, 75.0f);
    } else {
        func_00282D30(w, v, func_002A7878(0.4f, 0.6f) * 150.0f);
    }
    func_00282CC0(w, w, ang);
    func_00282CF0(w, D_00189EA0, w);
    w[2] = 0.0f;
    func_00282F20(w, w, 0.20000002f);
    return func_L03_003D09D0((int)arg0, 0, ang, v, w, 0x96, 0x1F4, *(unsigned char *)(state + 0x36));
}
