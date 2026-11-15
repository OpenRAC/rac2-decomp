#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void vec_add_random_offset(float *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern void part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Shoots a shower of small yellow sparks out of a point, moving along with the given speed. */
void part_l08_spawn_spark_shower(char *moby, char *baseVelocity) {
    float position[4];
    float velocity[4];
    float accel[4];
    int burst;
    int i;
    float angle;
    float radius;
    float rise;
    int startColor;
    int endColor;
    char *src = moby + 0x10;

    for (burst = 0; burst < 20; burst++) {
        *(TI128 *)position = *(TI128 *)src;
        vec_add_random_offset(position, 0.25f);
        position[2] += 0.25f;
        angle = math_random_angle();
        radius = math_random_float_range(1.0f, 8.0f);
        rise = math_random_float_range(2.0f, 6.0f);
        FastVecScale(velocity, baseVelocity, math_random_float_range(0.0f, 0.0f) * 0.016666668f);
        velocity[0] += math_fast_sin_or_cos_a(angle) * 0.016666668f * radius;
        velocity[1] += math_fast_sin_or_cos_b(angle) * 0.016666668f * radius;
        velocity[2] += rise * 0.016666668f;
        *(TI128 *)accel = *(TI128 *)velocity;
        accel[2] -= 0.16666667f;
        for (i = 0; i < 10; i++) {
            float k = math_random_float_range(0.5f, 1.5f);

            velocity[3] = k * 0.125f;
            accel[3] = k * 0.065f;
            vec_add_random_offset(position, 0.125f);
            vec_add_random_offset(accel, 0.0083333338f);
            startColor = FastTweenColor(0x8000EEEE, 0x8000FF90, math_random_float_range(0.0f, 1.0f));
            endColor = FastTweenColor(0xFFEE, 0xFFEE, math_random_float_range(0.0f, 1.0f));
            part_spawn_trail(position, velocity, accel, startColor, endColor, 10, 30, FloatToInt(math_random_float_range(5.0f, 25.0f)), -1);
        }
    }
}
