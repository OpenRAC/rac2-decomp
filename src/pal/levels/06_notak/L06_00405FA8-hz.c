#include "names.h"
/* func_PAL_L06_00405FA8, the PAL copy of func_L06_00402230: the same C with the spawn delay scale
   1/60 becomes 0x3CA3D70B, one ulp above 1/50, written 0.020000001f; the callee is PAL's
   func_PAL_L06_00469110. */
#include "common.h"

extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_float_range(float low, float high);
extern void matrix_mul_vec3(float *out, float *in, char *matrix);
extern char *part_spawn_spark_moby_pal(char *moby, float *position, float *velocity,
                             int flags, float size, float life);

/* Emit three rings of particles around the moby's local frame.
 * The flat velocity[2] = 0.0f below is dead (flow deletes it), but it gives
 * the 0.0f a second use, so loop.c keeps it in a callee-saved register
 * instead of substituting it into the single call argument. This unit is
 * built with -g, as line notes bound haifa-sched's regions here. */
void part_emit_rings_pal(char *moby)
{
    float position[4];
    float velocity[4];
    int ring, spoke;
    ring = 0;
    do {
        spoke = 0;
        do {
            float shell, angle, size, life;
            if (ring != 0 || !(spoke & 1)) {
                shell = (float)ring + math_random_float_range(0.0f, 1.0f);
                angle = 1.57079637f * ((float)spoke + (1.0f / 3.0f) * shell);
                velocity[0] = math_fast_sin_or_cos_a(angle);
                velocity[1] = math_fast_sin_or_cos_b(angle) * 0.25f;
                velocity[2] = 0.0f;
                velocity[2] = ((float)ring - 0.5f) * 0.25f;
                vec_scale_to_length(velocity, velocity,
                              math_random_float_range(8.0f, 14.0f) * 0.020000001f /* 0x3CA3D70B, one ulp above 1/50 */);
                matrix_mul_vec3(velocity, velocity, moby + 0xC0);
                position[0] = *(float *)(moby + 0x10) + velocity[0];
                position[1] = *(float *)(moby + 0x14) + velocity[1] * 3.0f;
                position[2] = *(float *)(moby + 0x18) + 0.75f + shell * 0.5f;
                size = math_random_float_range(0.25f, 1.0f);
                life = math_random_float_range(0.25f, 1.25f);
                part_spawn_spark_moby_pal(moby, position, velocity, 0, size, life);
            }
            spoke++;
        } while (spoke < 4);
        ring++;
    } while (ring < 3);
}
