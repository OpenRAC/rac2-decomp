#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_003DFD18, the PAL copy of func_L02_003DBB70: the same C at 50 Hz, where 0.016666668f
   becomes 0.020000001f, 0.33333334f becomes 0.4f, 20 and 60 go through the 50 Hz scale and the
   func_002A7878(10.0f, 50.0f) value goes through its float form.

   Retail hoists 5.0f out of the inner loop but not 2.0f, 0.16666667f or -1. The inner body's w, v and
   u leave in the first loop pass, in retail's order, so 5.0f goes first in the second pass, and
   col1's initial value holds that pass at 59 real insns, which keeps 2.0f in the loop. The same
   shape as func_PAL_L08_003DC0D0. */

typedef int TI128 __attribute__((mode(TI)));
typedef int s32;

extern char *g_moby_l02_pool[] __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Throws bursts of green glitter particles out from a part of the actor,
   drifting outward and upward. */
void part_spawn_green_glitter_pal(char *actor, char *base_velocity) {
    float position[4];
    float velocity[4];
    float trail_velocity[4];
    int n;
    int i;
    float angle;
    float r;
    float z;

    for (n = 0; n < 30; n++) {
        moby_transform_joint_to_world(g_moby_l02_pool[0] + (*(int *)(*(char **)(actor + 0x68) + 0x244) << 8), 4, position);
        vec_add_random_offset(position, 0.5f);
        position[2] += 0.25f;
        angle = math_random_angle();
        r = math_random_float_range(3.0f, 16.0f);
        z = math_random_float_range(3.0f, 12.0f);
        FastVecScale(velocity, base_velocity, math_random_float_range(0.0f, 0.0f) * 0.020000001f);
        velocity[0] += math_fast_sin_or_cos_a(angle) * 0.020000001f * r;
        velocity[1] += math_fast_sin_or_cos_b(angle) * 0.020000001f * r;
        velocity[2] += z * 0.020000001f;
        *(TI128 *)trail_velocity = *(TI128 *)velocity;
        trail_velocity[2] -= 0.4f;
        for (i = 0; i < 20; i++) {
            float w = 0.25f;
            float v = 1.0f;
            float u = 0.125f;
            float k = math_random_float_range(0.5f, 1.5f);
            int col1 = 0;
            int col2;

            velocity[3] = k * w;
            trail_velocity[3] = k * u;
            vec_add_random_offset(position, w);
            vec_add_random_offset(trail_velocity, 0.020000001f);
            col1 = FastTweenColor(0x80FF00EA, 0x80FF00EA, math_random_float_range(0.0f, v));
            col2 = FastTweenColor(0x00FF0020, 0x00FF00AA, math_random_float_range(0.0f, v));
            part_spawn_trail(position, velocity, trail_velocity, col1, col2, ((s32)(20) * 5 + 2) / 6, ((s32)(60) * 5 + 2) / 6, FloatToInt((math_random_float_range(10.0f, 50.0f) * 5.0f + 2.0f) * 0.16666667f), -1);
        }
    }
}
