#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
/* Measured object flags are a 16-bit field at +0x34. */
struct InitObjectFlags { char pad[0x34]; unsigned short flags; };
extern float g_l11_limit_min __attribute__((sda));
extern float g_l11_limit_max __attribute__((sda));
extern float g_l11_duration_min __attribute__((sda));
extern float g_l11_duration_max __attribute__((sda));


/* Starts a falling, tumbling drone: gives it a random spin, a launch velocity and gravity, and picks its timing from a blend value. */
void InitializeRandomizedObjectMotion(void *obj, void *velocity, float gravity, float blend)
{
    char *p = obj;
    char *state;
    float f;
    float g;
    float angle;
    float limit;
    float duration;

    *(unsigned char *)(p + 0x30) = 255;
    *(short *)(p + 0x32) = 255;
    *(unsigned char *)(p + 0x31) = 1;
    state = *(char **)(p + 0x68);
    moby_set_state(p, 3, 0);
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(unsigned char *)(p + 0xA8) = 255;
    *(unsigned char *)(state + 0x2E) = 1;
    *(TI128 *)(state + 0x2A0) = *(TI128 *)velocity;
    f = 0.0f;
    g = 3.14159274f;
    *(float *)(state + 0x2AC) = gravity;
    *(short *)(state + 0x2EC) = 0;
    *(float *)(p + 0xF0) = math_random_float_range(f, g);
    *(float *)(p + 0xF4) = math_random_float_range(f, g);
    *(float *)(p + 0xF8) = math_random_float_range(f, g);
    angle = math_random_float_range(20.0f, 40.0f);
    angle = angle * 0.017453294f;
    if (math_random_int_below(2) != 0)
        angle = -angle;
    *(float *)(state + 0x2D4) = angle;
    *(unsigned char *)(p + 0xA8) = 255;
    ((struct InitObjectFlags *)p)->flags &= 0xFEFF;
    limit = g_l11_limit_min + (g_l11_limit_max - g_l11_limit_min) * blend;
    duration = g_l11_duration_min + (g_l11_duration_max - g_l11_duration_min) * blend;
    *(float *)(state + 0x2E0) = limit;
    *(int *)(state + 0x2E4) = FloatToInt(duration);
}
