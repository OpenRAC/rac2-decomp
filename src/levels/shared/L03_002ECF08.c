#include "common.h"


extern float math_random_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_local_offset_to_world(float, float, float, void *, void *);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);

typedef struct { float x, y, z, w; } SparkVector;
void SpawnParticleBurst(unsigned char *object, float *minimumPosition, float *maximumPosition,
                      float *minimumVelocity, float *maximumVelocity, int count, unsigned char style) {
    SparkVector velocity, acceleration, position;
    int flags = 0x1003C;
    float scale;
    float gravity = 0.0013888889f;
    int countA, countB, countC, startColor, endColor;
    int i;

    for (i = 0; i < count; i++) {
        velocity.x = math_random_float_range(minimumVelocity[0], maximumVelocity[0]) * 0.016666668f;
        velocity.y = math_random_float_range(minimumVelocity[1], maximumVelocity[1]) * 0.016666668f;
        velocity.z = math_random_float_range(minimumVelocity[2], maximumVelocity[2]) * 0.016666668f;
        position.x = math_random_float_range(minimumPosition[0], maximumPosition[0]);
        position.y = math_random_float_range(minimumPosition[1], maximumPosition[1]);
        position.z = math_random_float_range(minimumPosition[2], maximumPosition[2]);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        vec_local_offset_to_world(position.x, position.y, position.z, object, &position);
        scale = math_random_float_range(0.5f, 1.5f);
        countA = FloatToInt(scale * 10.0f);
        countB = FloatToInt(scale * 35.0f);
        countC = FloatToInt(scale * 7.0f);
        velocity.w = math_random_float_range(0.1f, 0.4f);
        vec_clear_128(&acceleration);
        acceleration.z = -gravity * (float)(countA + countB + countC);
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
        part_spawn_trail(&position, &velocity, &acceleration, startColor, endColor, countA, countB, countC, flags);
    }
}
