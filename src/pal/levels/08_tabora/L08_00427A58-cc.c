#include "names.h"
/* func_PAL_L08_00427A58, the PAL copy of func_L08_00422578: the same C at 50 Hz, where 0.016666668f
   becomes 0.020000001f, 0.16666667f becomes 0.2f, 0.0083333338f becomes 0.010000001f, 10 and 30 go
   through the 50 Hz scale and the func_002A7878(5.0f, 25.0f) value goes through its float form.

   Retail hoists 2.0f and 0.16666667f out of the inner loop last, in the second loop pass. With 0.065f
   left as a literal that pass sees 58 real insns and a threshold of about 61, less 3 per hoist, so
   0.16666667f, the third hoist, stays in the loop. w, v, m and u leave in the first pass, in retail's
   order, so 0.065f is no longer a second-pass hoist. */
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
typedef int s32;

extern void vec_add_random_offset(float *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Shoots a shower of small yellow sparks out of a point, moving along with the given speed (PAL: 50 Hz timings). */
void part_l08_spawn_spark_shower_pal(char *moby, char *base_velocity) {
    float position[4];
    float velocity[4];
    float acceleration[4];
    int n;
    int i;
    float angle;
    float r;
    float z;
    int col1;
    int col2;
    char *src = moby + 0x10;

    for (n = 0; n < 20; n++) {
        *(TI128 *)position = *(TI128 *)src;
        vec_add_random_offset(position, 0.25f);
        position[2] += 0.25f;
        angle = math_random_angle();
        r = math_random_float_range(1.0f, 8.0f);
        z = math_random_float_range(2.0f, 6.0f);
        FastVecScale(velocity, base_velocity, math_random_float_range(0.0f, 0.0f) * 0.020000001f);
        velocity[0] += math_fast_sin_or_cos_a(angle) * 0.020000001f * r;
        velocity[1] += math_fast_sin_or_cos_b(angle) * 0.020000001f * r;
        velocity[2] += z * 0.020000001f;
        *(TI128 *)acceleration = *(TI128 *)velocity;
        acceleration[2] -= 0.2f;
        for (i = 0; i < 10; i++) {
            float w = 0.125f;
            float v = 1.0f;
            float m = 5.0f;
            float u = 0.065f;
            float k = math_random_float_range(0.5f, 1.5f);

            velocity[3] = k * w;
            acceleration[3] = k * u;
            vec_add_random_offset(position, w);
            vec_add_random_offset(acceleration, 0.010000001f);
            col1 = FastTweenColor(0x8000EEEE, 0x8000FF90, math_random_float_range(0.0f, v));
            col2 = FastTweenColor(0xFFEE, 0xFFEE, math_random_float_range(0.0f, v));
            part_spawn_trail(position, velocity, acceleration, col1, col2, ((s32)(10) * 5 + 2) / 6, ((s32)(30) * 5 + 2) / 6, FloatToInt((math_random_float_range(m, 25.0f) * m + 2.0f) * 0.16666667f), -1);
        }
    }
}
