#include "include_asm.h"

#include "common.h"
extern float FastAddRotations(float f12, float f13);
extern float math_fast_sin_or_cos_b(float f12);
extern int FastTweenColor(int a0, int a1, float f12);
extern float math_random_float_range(float f12, float f13);
extern void moby_set_light_color(void *a0, int a1);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float low, float high);

/* Flickers the glow light colour of a moby and fades its brightness byte up (when on) or down (when off) (PAL). */
void glow_flicker_update_pal(void *moby, float *phase, int enable) {
    unsigned char *bytes = (unsigned char *)moby;
    float wave;
    int color;

    if (bytes[0x23] == 0 && enable == 0)
        return;

    wave = FastAddRotations(*phase, 0.17453296f);
    *phase = wave;
    wave = math_fast_sin_or_cos_b(wave);
    color = FastTweenColor(0x8000C020, 0x80008000, (wave + 0.5f) * 0.5f);
    if (math_random_float_range(0.0f, 1.0f) < 0.05f)
        color = FastTweenColor(color, 0x8080FFFF, 0.3f);
    moby_set_light_color(moby, color);

    if (enable != 0) {
        if (bytes[0x23] < 0x3D)
            bytes[0x23] = bytes[0x23] + 3;
        else
            bytes[0x23] = 0x40;
    } else {
        if (bytes[0x23] >= 4)
            bytes[0x23] = bytes[0x23] - 3;
        else
            bytes[0x23] = 0;
    }
}

