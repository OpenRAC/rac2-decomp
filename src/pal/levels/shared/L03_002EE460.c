#include "include_asm.h"
#include "common.h"

/* func_PAL_L03_002EE460, the PAL copy of func_L03_002ECF08: the same C at 50 Hz (velocity * 0.02,
 * gravity 0.002, counts scaled by 5 and rounded over 6). */

extern float math_random_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_local_offset_to_world(float, float, float, void *, void *);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);

typedef struct { float x, y, z, w; } SparkVector;
void func_PAL_L03_002EE460(unsigned char *object, float *minimumPosition, float *maximumPosition,
                      float *minimumVelocity, float *maximumVelocity, int count, unsigned char style) {
    SparkVector velocity, acceleration, position;
    int flags = 0x1003C;
    float scale;
    float gravity = 0.002f;
    int a, b, c, startColor, endColor;
    int i;

    for (i = 0; i < count; i++) {
        velocity.x = math_random_float_range(minimumVelocity[0], maximumVelocity[0]) * 0.020000001f;
        velocity.y = math_random_float_range(minimumVelocity[1], maximumVelocity[1]) * 0.020000001f;
        velocity.z = math_random_float_range(minimumVelocity[2], maximumVelocity[2]) * 0.020000001f;
        position.x = math_random_float_range(minimumPosition[0], maximumPosition[0]);
        position.y = math_random_float_range(minimumPosition[1], maximumPosition[1]);
        position.z = math_random_float_range(minimumPosition[2], maximumPosition[2]);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        vec_local_offset_to_world(position.x, position.y, position.z, object, &position);
        scale = math_random_float_range(0.5f, 1.5f);
        a = FloatToInt((scale * 50.0f + 2.0f) * 0.16666667f);
        b = FloatToInt((scale * 175.0f + 2.0f) * 0.16666667f);
        c = FloatToInt((scale * 35.0f + 2.0f) * 0.16666667f);
        velocity.w = math_random_float_range(0.1f, 0.4f);
        vec_clear_128(&acceleration);
        acceleration.z = -gravity * (float)(a + b + c);
        FastVecAdd(&acceleration, &acceleration, &velocity);
        acceleration.w = 0.01f;
        switch (style) {
        case 1:
            startColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80102040, 0x801010A0);
            endColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x102040, 0x1010A0);
            break;
        case 3:
            startColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80201608, 0x80402510);
            endColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x201608, 0x402510);
            break;
        case 2:
            startColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80104010, 0x8020A020);
            endColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x104010, 0x20A020);
            break;
        case 0:
        default:
            startColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x80004080, 0x80408080);
            endColor = FastTweenColor(math_random_float_range(0.0f, 1.0f), 0x4080, 0x408080);
            break;
        }
        part_spawn_trail(&position, &velocity, &acceleration, startColor, endColor, a, b, c, flags);
    }
}
