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

/* Shoots out a burst of 200 yellow sparks from the object that inherit its movement. */
void part_spawn_yellow_spark_burst(char *moby, char *baseVelocity) {
    float position[4];
    float velocity[4];
    float acceleration[4];
    int burst;
    int spark;
    float direction;
    float speed;
    float upSpeed;
    int colorStart;
    int colorEnd;
    char *mobyPos = moby + 0x10;

    for (burst = 0; burst < 20; burst++) {
        *(TI128 *)position = *(TI128 *)mobyPos;
        vec_add_random_offset(position, 0.25f);
        position[2] += 0.25f;
        direction = math_random_angle();
        speed = math_random_float_range(1.0f, 8.0f);
        upSpeed = math_random_float_range(2.0f, 6.0f);
        FastVecScale(velocity, baseVelocity, math_random_float_range(0.0f, 0.0f) * 0.016666668f);
        velocity[0] += math_fast_sin_or_cos_a(direction) * 0.016666668f * speed;
        velocity[1] += math_fast_sin_or_cos_b(direction) * 0.016666668f * speed;
        velocity[2] += upSpeed * 0.016666668f;
        *(TI128 *)acceleration = *(TI128 *)velocity;
        acceleration[2] -= 0.16666667f;
        for (spark = 0; spark < 10; spark++) {
            float sizeScale = math_random_float_range(0.5f, 1.5f);

            velocity[3] = sizeScale * 0.125f;
            acceleration[3] = sizeScale * 0.065f;
            vec_add_random_offset(position, 0.125f);
            vec_add_random_offset(acceleration, 0.0083333338f);
            colorStart = FastTweenColor(0x8000EEEE, 0x8000FF90, math_random_float_range(0.0f, 1.0f));
            colorEnd = FastTweenColor(0xFFEE, 0xFFEE, math_random_float_range(0.0f, 1.0f));
            part_spawn_trail(position, velocity, acceleration, colorStart, colorEnd, 10, 30, FloatToInt(math_random_float_range(15.0f, 75.0f)), -1);
        }
    }
}
