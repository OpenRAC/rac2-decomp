#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(char *out, char *a, char *b);
extern float FastVecLength(char *v);
extern float math_step_value_toward_target(char *out, float *res, float a, float b, float c, float d);
extern void vec_scale_to_length(char *out, char *v, float scale);
extern float IntToFloat(int n);
extern int FastTweenColor(int from, int to, float t);
extern int FastDecTimer(void *timer);
extern void part_kill(char *particle);
extern float g_drift_decel_param __attribute__((sda));
extern float g_drift_rise_param __attribute__((sda));
extern float g_drift_scale_start_b __attribute__((sda));
extern float g_drift_scale_end_b __attribute__((sda));
extern float g_drift_scale_start_a __attribute__((sda));
extern float g_drift_scale_end_a __attribute__((sda));
#define LERP(lo, hi, t) (((hi) - (lo)) * (t) + (lo))

void func_PAL_002BD1A0(char *p)
{
    char *q = p + 0x20;
    float speed, a, b, t;

    p[8] = (unsigned char)p[8] + (unsigned char)q[0x1E];
    FastVecAdd(p + 0x10, p + 0x10, q);
    speed = -FastVecLength(q);
    math_step_value_toward_target(p + 0x30, &speed, 0.0f, 0.0f, g_drift_decel_param * 0.00040000002f, speed);
    vec_scale_to_length(q, q, -speed);
    *(float *)(p + 0x18) += g_drift_rise_param * 0.020000001f;
    a = IntToFloat(*(short *)(p + 0xA));
    b = IntToFloat((unsigned char)q[0x1D]);
    t = a / b;
    if (q[0x1F] & 1)
        *(float *)(p + 0xC) = LERP(g_drift_scale_start_b, g_drift_scale_end_b, t) * 210000.0f;
    else
        *(float *)(p + 0xC) = LERP(g_drift_scale_start_a, g_drift_scale_end_a, t) * 210000.0f;
    *(int *)(p + 4) = FastTweenColor(*(int *)(q + 0x18), *(int *)(q + 0x14), t);
    if (*(short *)(p + 0xA) < 12) {
        a = IntToFloat(*(short *)(p + 0xA));
        b = IntToFloat(8);
        *(int *)(p + 4) = FastTweenColor(*(int *)(p + 4) & 0xFFFFFF, *(int *)(p + 4), a / b);
    }
    if (*(float *)(p + 0x10) < 2.0f || *(float *)(p + 0x10) > 1021.0f ||
        *(float *)(p + 0x14) < 2.0f || *(float *)(p + 0x14) > 1021.0f ||
        *(float *)(p + 0x18) < 2.0f || *(float *)(p + 0x18) > 1021.0f ||
        FastDecTimer(p + 0xA)) {
        part_kill(p);
        return;
    }
    if (*(float *)(q + 0x10) < 0.01f)
        --*(short *)(p + 0xA);
}
