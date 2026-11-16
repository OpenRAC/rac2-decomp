#include "include_asm.h"
#include "names.h"

/* func_L02_0042E680 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_add_random_offset(void *, float);
extern int g_spark_fan_colors_a[2] __attribute__((sda));
extern int g_spark_fan_colors_b[2] __attribute__((sda));

/* Throws a fan of thirty sparks out in front of the object, each with its own speed, size and colour. */
void part_throw_spark_fan(u8 *moby, float lo, float hi) {
    float offset[4];
    float origin[4];
    float upSpread[4];
    float sideSpread[4];
    float velocity[4];
    float pull[4];
    float sparkPos[4];
    int i;
    float scale;
    int partA, partB, partC;
    int colorA, colorB;
    float k = 0.0025f;

    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = 4.0f;
    offset[3] = 1.0f;
    FastVecAdd(origin, offset, moby + 0x10);
    i = 29;
    do {
        vec_scale_to_length(sideSpread, moby + 0xC0, math_random_float_range(-0.8f, 0.8f));
        vec_scale_to_length(upSpread, moby + 0xE0, math_random_float_range(0.25f, 1.0f));
        FastVecAdd(velocity, moby + 0xD0, sideSpread);
        FastVecAdd(velocity, velocity, upSpread);
        vec_scale_to_length(velocity, velocity, math_random_float_range(lo, hi));
        scale = math_random_float_range(0.5f, 1.5f);
        partA = FloatToInt(scale * 10.0f);
        partB = FloatToInt(scale * 30.0f);
        partC = FloatToInt(scale * 7.0f);
        velocity[3] = math_random_float_range(0.2f, 0.6f);
        vec_clear_128(pull);
        pull[2] = -k * (float)(partA + partB + partC);
        FastVecAdd(pull, pull, velocity);
        pull[3] = 0.01f;
        colorA = FastTweenColor(g_spark_fan_colors_a[0], g_spark_fan_colors_a[1], math_random_float_range(0.0f, 1.0f));
        colorB = FastTweenColor(g_spark_fan_colors_b[0], g_spark_fan_colors_b[1], math_random_float_range(0.0f, 1.0f));
        *(TI128 *)sparkPos = *(TI128 *)origin;
        vec_add_random_offset(sparkPos, 0.25f);
        part_spawn_trail(sparkPos, velocity, pull, colorA, colorB, partA, partB, partC, 0x1003C);
    } while (--i >= 0);
}
