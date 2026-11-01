#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(char *out, char *a, char *b);
extern float func_00282DF0(char *v);
extern void func_002AA548(char *out, float *res, float a, float b, float c, float d);
extern void func_00282F20(char *out, char *v, float scale);
extern float func_00283CE0(int n);
extern int func_00283D38(int from, int to, float t);
extern int func_00282978(void *timer);
extern void func_002B9180(char *particle);
extern float D_001AA348 __attribute__((sda));
extern float D_001AA34C __attribute__((sda));
extern float D_001AA33C __attribute__((sda));
extern float D_001AA338 __attribute__((sda));
extern float D_001AA31C __attribute__((sda));
extern float D_001AA318 __attribute__((sda));
#define LERP(lo, hi, t) (((hi) - (lo)) * (t) + (lo))

void func_PAL_002BD1A0(char *p)
{
    char *q = p + 0x20;
    float speed, a, b, t;

    p[8] = (unsigned char)p[8] + (unsigned char)q[0x1E];
    func_00282CC0(p + 0x10, p + 0x10, q);
    speed = -func_00282DF0(q);
    func_002AA548(p + 0x30, &speed, 0.0f, 0.0f, D_001AA348 * 0.00040000002f, speed);
    func_00282F20(q, q, -speed);
    *(float *)(p + 0x18) += D_001AA34C * 0.020000001f;
    a = func_00283CE0(*(short *)(p + 0xA));
    b = func_00283CE0((unsigned char)q[0x1D]);
    t = a / b;
    if (q[0x1F] & 1)
        *(float *)(p + 0xC) = LERP(D_001AA33C, D_001AA338, t) * 210000.0f;
    else
        *(float *)(p + 0xC) = LERP(D_001AA31C, D_001AA318, t) * 210000.0f;
    *(int *)(p + 4) = func_00283D38(*(int *)(q + 0x18), *(int *)(q + 0x14), t);
    if (*(short *)(p + 0xA) < 12) {
        a = func_00283CE0(*(short *)(p + 0xA));
        b = func_00283CE0(8);
        *(int *)(p + 4) = func_00283D38(*(int *)(p + 4) & 0xFFFFFF, *(int *)(p + 4), a / b);
    }
    if (*(float *)(p + 0x10) < 2.0f || *(float *)(p + 0x10) > 1021.0f ||
        *(float *)(p + 0x14) < 2.0f || *(float *)(p + 0x14) > 1021.0f ||
        *(float *)(p + 0x18) < 2.0f || *(float *)(p + 0x18) > 1021.0f ||
        func_00282978(p + 0xA)) {
        func_002B9180(p);
        return;
    }
    if (*(float *)(q + 0x10) < 0.01f)
        --*(short *)(p + 0xA);
}
